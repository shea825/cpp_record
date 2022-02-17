
/** @file file.cpp
 *  @author shea
 *  @date 10:10 AM 1/29/22
 *  @plat CLion
 *  @brief This is a file lib implementation according to Standford C++ Lib.
 *         This file exports a standardized set of tools for working with files.
 */

#include "file.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <dirent.h>
#include <sstream>

/** Private functions */
static void splitPath(const std::string& path, std::vector<std::string> list) {
    char sep = (path.find(';') == std::string::npos) ? ':' : ';';
    std::string pathCopy = path + sep;
    size_t start = 0;
    while (true) {
        size_t finish = pathCopy.find(sep, start);
        if (finish == std::string::npos) break;
        if (finish > start + 1) {
            list.emplace_back(pathCopy.substr(start, finish - start - 1));
        }
        start = finish + 1;
    }
}

static bool recursiveMatch(const std::string& str, int sx, const std::string& pattern, int px) {
    int slen = str.length();
    int plen = pattern.length();
    if (px == plen) return (sx == slen);
    char pch = pattern[px];
    if (pch == '*') {
        for (int i = sx; i <= slen; i++) {
            if (recursiveMatch(str, i, pattern, px + 1)) return true;
        }
        return false;
    }
    if (sx == slen) return false;
    char sch = str[sx];
    if (pch == '[') {
        bool match = false;
        bool invert = false;
        px++;
        if (px == plen) {
            perror("matchFilenamePattern: missing ]");
        }
        if (pattern[px] == '^') {
            px++;
            invert = true;
        }
        while (px < plen && pattern[px] != ']') {
            if (px + 2 < plen && pattern[px + 1] == '-') {
                match |= (sch >= pattern[px] && sch <= pattern[px + 2]);
                px += 3;
            } else {
                match |= (sch == pattern[px]);
                px++;
            }
        }
        if (px == plen) {
            perror("matchFilenamePattern: missing ]");
        }
        if (match == invert) return false;
    } else if (pch != '?') {
        if (pch != sch) return false;
    }
    return recursiveMatch(str, sx + 1, pattern, px + 1);
}

void appendSpace(std::string& prompt) {
    if (!prompt.empty() && !isspace(prompt[prompt.length() - 1])) {
        prompt += ' ';
    }
}

/** Implementation */
bool endsWith(const std::string& str, char suffix) {
    return str.length() > 0 && str.at(str.length()-1) == suffix;
}
void createDirectory(const std::string &path) {
    std::string pathCopy = path;
    if (endsWith(pathCopy, '/')) {
        pathCopy = pathCopy.substr(0, path.length() - 2);
    }
    if (mkdir(pathCopy.c_str(), 0777) != 0) {
        if (errno == EEXIST && isDirectory(pathCopy)) return;
        std::string msg = "createDirectory: ";
        std::string err = std::string(strerror(errno));
        perror((msg + err).c_str());
    }
}

bool isDirectory(const std::string &filename) {
    struct stat fileInfo{};
    if (stat(filename.c_str(), &fileInfo) != 0) return false;
    return S_ISDIR(fileInfo.st_mode) != 0;
}

void createDirectoryPath(const std::string &path) {
    size_t cp = 1;
    if (path.empty()) return;
    while ((cp = path.find('/', cp + 1)) != std::string::npos) {
        createDirectory(path.substr(0, cp - 1));
    }
    createDirectory(path);
}

std::string defaultExtension(const std::string &filename, const std::string &ext) {
    std::string extCopy = ext;
    bool force = (extCopy[0] == '*');
    if (force) extCopy = extCopy.substr(1);
    int dot = -1;
    int len = filename.length();
    for (int i = 0; i < len; i++) {
        char ch = filename[i];
        if (ch == '.') dot = i;
        if (ch == '/' || ch == '\\') dot = -1;
    }
    if (dot == -1) {
        force = true;
        dot = len;
    }
    if (force) {
        return filename.substr(0, dot) + extCopy;
    } else {
        return filename;
    }
}

void deleteFile(const std::string &filename) {
    remove(expandPathname(filename).c_str());
}

std::string expandPathname(const std::string &filename) {
    std::string filenameCopy = filename;
    if (filename.empty()) return "";
    int len = filename.length();
    if (filename[0] == '~') {
        int spos = 1;
        while (spos < len && filename[spos] != '\\' && filename[spos] != '/') {
            spos++;
        }
        char *homedir = nullptr;
        if (spos == 1) {
            homedir = getenv("HOME");
            if (homedir == nullptr) {
                homedir = getpwuid(getuid())->pw_dir;
            }
        } else {
            struct passwd *pw = getpwnam(filename.substr(1, spos - 1).c_str());
            if (pw == nullptr) {
                perror("expandPathname: No such user");
            } else {
                homedir = pw->pw_dir;
            }
        }
        filenameCopy = std::string(homedir) + filename.substr(spos);
        len = filenameCopy.length();
    }
    for (int i = 0; i < len; i++) {
        if (filenameCopy[i] == '\\') filenameCopy[i] = '/';
    }
    return filenameCopy;
}

bool fileExists(const std::string &filename) {
    struct stat fileInfo{};
    return stat(filename.c_str(), &fileInfo) == 0;
}

std::string findOnPath(const std::string &path, const std::string &filename) {
    std::ifstream stream;
    std::string result = openOnPath(stream, path, filename);
    if (!result.empty()) stream.close();
    return result;
}

std::string getCurrentDirectory() {
    char *cwd = getcwd(nullptr, 0);
    if (cwd == nullptr) {
        std::string msg = "getCurrentDirectory: ";
        std::string err = std::string(strerror(errno));
        perror((msg + err).c_str());
        return "";
    } else {
        std::string result = std::string(cwd);
        free(cwd);
        return result;
    }
}

inline std::string getDirectoryPathSeparator() {
    return "/";
}

std::string getExtension(const std::string &filename) {
    int dot = -1;
    int len = filename.length();
    for (int i = 0; i < len; i++) {
        char ch = filename[i];
        if (ch == '.') dot = i;
        if (ch == '/' || ch == '\\') dot = -1;
    }
    if (dot == -1) {
        return "";
    } else {
        return filename.substr(dot);
    }
}

std::string getHead(const std::string &filename) {
    size_t slash = std::string::npos;
    size_t len = filename.length();
    for (size_t i = 0; i < len; i++) {
        char ch = filename[i];
        if (ch == '/' || ch == '\\') slash = i;
    }
    if (slash == std::string::npos) {
        return "";
    } else if (slash == 0) {
        return "/";
    } else {
        return filename.substr(0, slash);
    }
}

std::string getRoot(const std::string &filename) {
    int dot = -1;
    int len = filename.length();
    for (int i = 0; i < len; i++) {
        char ch = filename[i];
        if (ch == '.') dot = i;
        if (ch == '/' || ch == '\\') dot = -1;
    }
    if (dot == -1) {
        return filename;
    } else {
        return filename.substr(0, dot);
    }
}

inline std::string getSearchPathSeparator() {
    return ":";
}

std::string getTail(const std::string &filename) {
    size_t slash = std::string::npos;
    size_t len = filename.length();
    for (size_t i = 0; i < len; i++) {
        char ch = filename[i];
        if (ch == '/' || ch == '\\') slash = i;
    }
    if (slash == std::string::npos) {
        return filename;
    } else {
        return filename.substr(slash + 1);
    }
}

std::string getTempDirectory() {
    char* dir = getenv("TMPDIR");
    if (!dir) dir = getenv("TMP");
    if (!dir) dir = getenv("TEMP");
    if (!dir) dir = getenv("TEMPDIR");
    if (!dir) return "/tmp";
    return dir;
}

bool isFile(const std::string &filename) {
    struct stat fileInfo{};
    if (stat(filename.c_str(), &fileInfo) != 0) return false;
    return S_ISREG(fileInfo.st_mode) != 0;
}

bool isSymbolicLink(const std::string &filename) {
    struct stat fileInfo{};
    if (stat(filename.c_str(), &fileInfo) != 0) return false;
    return S_ISLNK(fileInfo.st_mode) != 0;
}

void listDirectory(const std::string &path, std::vector<std::string> &list) {
    std::string pathCopy = path;
    if (pathCopy.empty()) pathCopy = ".";
    DIR *dir = opendir(path.c_str());
    if (dir == nullptr) perror(("listDirectory: Can't open " + path).c_str());
    list.clear();
    while (true) {
        struct dirent *ep = readdir(dir);
        if (ep == nullptr) break;
        std::string name = std::string(ep->d_name);
        if (name != "." && name != "..") list.emplace_back(name);
    }
    closedir(dir);
    sort(list.begin(), list.end());
}

std::vector<std::string> listDirectory(const std::string &path) {
    std::vector<std::string> retList;
    listDirectory(path, retList);
    return retList;
}

bool matchFilenamePattern(const std::string &filename, const std::string &pattern) {
    return recursiveMatch(filename, 0, pattern, 0);
}

bool openFile(std::ifstream &stream, const std::string &filename) {
    stream.clear();
    stream.open(expandPathname(filename).c_str());
    return !stream.fail();
}

bool openFile(std::ofstream &stream, const std::string &filename) {
    stream.clear();
    stream.open(expandPathname(filename).c_str());
    return !stream.fail();
}

std::string openOnPath(std::ifstream& stream, const std::string& path, const std::string& filename) {
    std::vector<std::string> paths;
    splitPath(path, paths);
    for (auto &dir: paths) {
        std::string pathname = dir.append("/") + filename;
        if (openFile(stream, pathname)) return pathname;
    }
    return "";
}
std::string openOnPath(std::ofstream &stream, const std::string &path, const std::string &filename) {
    std::vector<std::string> paths;
    splitPath(path, paths);
    for (auto &dir: paths) {
        std::string pathname = dir.append("/") + filename;
        if (openFile(stream, pathname)) return pathname;
    }
    return "";
}

std::string promptUserForFile(std::ifstream &stream, const std::string &prompt, const std::string &reprompt) {
    std::string promptCopy = prompt;
    std::string repromptCopy = reprompt;
    if (reprompt.empty()) {
        repromptCopy = "Unable to open that file.  Try again.";
    }
    appendSpace(promptCopy);
    while (true) {
        std::cout << promptCopy;
        std::string filename;
        getline(std::cin, filename);
        if (!filename.empty()) {
            openFile(stream, filename);
            if (!stream.fail()) return filename;
            stream.clear();
        }
        std::cout << repromptCopy << std::endl;
        if (promptCopy.empty()) promptCopy = "Input file: ";
    }
}

std::string promptUserForFile(std::ofstream &stream, const std::string &prompt, const std::string &reprompt) {
    std::string promptCopy = prompt;
    std::string repromptCopy = reprompt;
    if (reprompt.empty()) {
        repromptCopy = "Unable to open that file.  Try again.";
    }
    appendSpace(promptCopy);
    while (true) {
        std::cout << promptCopy;
        std::string filename;
        getline(std::cin, filename);
        if (!filename.empty()) {
            openFile(stream, filename);
            if (!stream.fail()) return filename;
            stream.clear();
        }
        std::cout << repromptCopy << std::endl;
        if (promptCopy.empty()) promptCopy = "Output file: ";
    }
}

std::string promptUserForFile(const std::string &prompt, const std::string &reprompt) {
    std::string promptCopy = prompt;
    std::string repromptCopy = reprompt;
    if (reprompt.empty()) {
        repromptCopy = "Unable to open that file.  Try again.";
    }
    appendSpace(promptCopy);
    while (true) {
        std::cout << promptCopy;
        std::string filename;
        getline(std::cin, filename);
        if (!filename.empty()) {
            std::ifstream stream;
            openFile(stream, filename);
            if (!stream.fail()) {
                stream.close();
                return filename;
            }
        }
        std::cout << repromptCopy << std::endl;
        if (promptCopy.empty()) promptCopy = "Input file: ";
    }
}

void readEntireFile(std::istream &is, std::vector<std::string> &lines) {
    lines.clear();
    while (true) {
        std::string line;
        getline(is, line);
        if (is.fail()) break;
        lines.emplace_back(line);
    }
}

std::string readEntireFile(const std::string &filename) {
    std::string out;
    if (readEntireFile(filename, out)) {
        return out;
    } else {
        perror(("input file not found or cannot be opened: " + filename).c_str());
        return "";
    }
}

bool readEntireFile(const std::string& filename, std::string& out) {
    std::ifstream input;
    input.open(filename.c_str());
    if (input.fail()) {
        return false;
    }
    std::ostringstream output;
    while (true) {
        int ch = input.get();
        if (input.fail()) break;
        output << (char) ch;
    }
    input.close();
    out = output.str();
    return true;
}

void renameFile(const std::string &oldname, const std::string &newname) {
    std::string oldExpand = expandPathname(oldname);
    std::string newExpand = expandPathname(newname);
    rename(oldExpand.c_str(), newExpand.c_str());
}

void rewindStream(std::istream &input) {
    input.clear();                  // removes any current eof/failure flags
    input.seekg(0, std::ios::beg);  // tells the stream to seek back to the beginning
}

void setCurrentDirectory(const std::string &path) {
    if (chdir(path.c_str()) == 0) {
        std::string msg = "setCurrentDirectory: ";
        std::string err = std::string(strerror(errno));
        perror((msg + err).c_str());
    }
}

int main() {

}