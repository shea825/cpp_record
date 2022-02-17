
/** @file file.h
 *  @author shea
 *  @date 10:10 AM 1/29/22
 *  @plat CLion
 *  @brief This file exports a standardized set of tools for working with files.
 *  The library offers at least some portability across the file systems used in the three supported platforms: Mac OSX, Windows, and Linux.
 *  Directory and search paths are allowed to contain separators in any of the supported styles, which usually makes it possible to use the same code on different platforms.
 */

#pragma once 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/**
 *  @brief Creates a new directory for the specified path.
 *  @param path File path
 *  @return No return
 *  @throw If some component of path does not exist, throw an error.
 */
void createDirectory(const std::string& path);

/**
 *  @brief Creates a new directory for the specified path.
 *  @param path File path
 *  @return No return
 *  @throw If intermediate components of path do not exist, this function creates them as needed.
 */
void createDirectoryPath(const std::string& path);

/**
 *  @brief  Add an extension to a file name if none already exists.
 *  @param ext If the extension argument begins with a leading "*",
 *  any existing extension in filename is replaced by ext
 *  @return std::string new name
 *  @throw None
 */
std::string defaultExtension(const std::string& filename, const std::string& ext);

/**
 *  @brief Deletes the specified file.
 *  @param filename
 *  @return No return
 *  @throw Errors are reported by calling function "error"
 */
void deleteFile(const std::string& filename);

/**
 *  @brief Expands a filename into a canonical name for the platform.
 *  @param filename
 *  @return std::string file path name
 *  @throw
 */
std::string expandPathname(const std::string& filename);

/**
 *  @brief Judge if specified file exists.
 *  @param filename
 *  @return bool file exists
 *  @throw
 */
bool fileExists(const std::string& filename);

/**
 *  @brief Return the canonical name of a file found using a search path.
 *         Using <code>stat</code> has the best performance.
 *  @return std::string file path name
 *  @throw If no matching file is found, returns the empty string.
 */
std::string findOnPath(const std::string& path, const std::string& filename);

/**
 *  @brief Return an absolute filename for the current directory.
 *  @return std::string file name
 *  @throw
 */
std::string getCurrentDirectory();

/**
 *  @brief Return the standard directory path separator used on this platform.
 *  @return std::string standard directory path
 *  @throw
 */
inline std::string getDirectoryPathSeparator();

/**
 *  @brief Return the extension of given file.
 *  @param filename
 *  @return string the extension
 *  @throw If no dot exists in the final component, <code>getExtension</code>
 *  returns the empty string.  These semantics ensure that concatenating
 *  the root and the extension always returns the original filename.
 */
std::string getExtension(const std::string& filename);

/**
 *  @brief Return all but the last component of a path name.
 *  @param filename
 *  @return string the first char of given path name
 *  @throw If no dot appears in the final component
 *  of the filename, <code>getRoot</code> returns the entire name.
 *  <pre>
 *    getHead("a/b")  = "a"     getTail("a/b")   = "b"
 *    getHead("a")    = ""      getTail("a")     = "a"
 *    getHead("/a")   = "/"     getTail("/a")    = "a"
 *    getHead("/")    = "/"     getTail("/")     = ""
 *  </pre>
 */
std::string getHead(const std::string& filename);

/**
 *  @brief Return the root of given file.
 *  @param filename
 *  @return string The root consists of everything in <code>filename</code>
 *  up to the last dot and the subsequent extension.
 *  @throw If no dot appears in the final component of the filename,
 *  <code>getRoot</code> returns the entire name.
 */
std::string getRoot(const std::string& filename);

/**
 *  @brief Return the standard search path separator used on this platform.
 *  @return string the standard search path separator
 */
inline std::string getSearchPathSeparator();

/**
 *  @brief Return the last component of a path name.
 *  The components of the path name can be separated by any of the directory
 *  path separators (forward or reverse slashes).
 *  @param filename
 *  @return string the last char of given path name
 *  @throw
 */
std::string getTail(const std::string& filename);

/**
 *  @brief Return the "Temp" folder of os. Can be used to store temporary files.
 *  @return string the "Temp" dir name of os
 *  @throw
 */
std::string getTempDirectory();

/**
 *  @brief Judge if the specified file is a directory.
 *  @param filename
 *  @return bool file is a dir
 *  @throw
 *
 *  This function ...
 */
bool isDirectory(const std::string& filename);

/**
 *  @brief Judge if the specified file is a regular file, not a symbolic link or directory.
 *  @param filename
 *  @return bool file is not a symbolic link or directory.
 *  @throw
 */
bool isFile(const std::string& filename);

/**
 *  @brief Judge if the specified file is a symbolic link.
 *  @param filename
 *  @return bool file is a symbolic link
 *  @throw
 */
bool isSymbolicLink(const std::string& filename);

/**
 *  @brief Adds an alphabetized list of the files in the specified directory to the string vector <code>list</code>.
 *  @param path dir path name
 *  @throw
 */
void listDirectory(const std::string& path, std::vector<std::string>& list);
std::vector<std::string> listDirectory(const std::string& path);

/**
 *  @brief Determines whether the filename matches the specified pattern.
 *  @param pattern string supports the following wildcard options:
 *  <table>
 *  <tr><th>Symbol        <th>Description
 *  <tr><td>?             <td>Matches any single character
 *  <tr><td>*             <td>Matches any sequence of characters
 *  <tr><td>[...]         <td>Matches any of the specified characters
 *  <tr><td>[^...]        <td>Matches any character <i>except</i> the specified ones
 *  </table>
 *  @return bool if the file matches the given pattern
 *  @throw
 */
bool matchFilenamePattern(const std::string& filename, const std::string& pattern);

/**
 *  @brief Opens the filestream stream using the specified filename.
 *  @param stream
 *  @return bool if open the given file successfully
 *  @throw sets the failure flag in the stream if failed
 */
bool openFile(std::ifstream& stream, const std::string& filename);
bool openFile(std::ofstream& stream, const std::string& filename);

/**
 *  @brief Opens a dialog that allows the user to choose the file.
 *  @param title displayed in the dialog title
 *  @param path used to set the working directory
 *  if path is not found, default uses the current dir
 *  @return string file name
 *  @throw
 */
inline std::string openFileDialog(std::ifstream& stream);
inline std::string openFileDialog(std::ifstream& stream,
                           const std::string& title);
std::string openFileDialog(std::ifstream& stream,
                           const std::string& title,
                           const std::string& path);
inline std::string openFileDialog(std::ofstream& stream);
inline std::string openFileDialog(std::ofstream& stream,
                           const std::string& title);
std::string openFileDialog(std::ofstream& stream,
                           const std::string& title,
                           const std::string& path);
std::string openFileDialog(const std::string& title = "Open File ...",
                           const std::string& path = "");

/**
 *  @brief Opens a file using a search path.
 *  @param
 *  @return string path name
 *  returns the first path name on the search path for which <code>stream.open</code> succeeds.
 *  @throw
 */
std::string openOnPath(std::ifstream& stream,
                       const std::string& path,
                       const std::string& filename);
std::string openOnPath(std::ofstream& stream,
                       const std::string& path,
                       const std::string& filename);

/**
 *  @brief Asks the user for the name of a file.
 *  @param stream used to open the file
 *  @param prompt (optional) provides an input prompt for the user
 *  @param reprompt (optional) provides an output message displayed each time if the user types a file that is not found
 *  @return the name of the file
 *  @throw
 *  If no value is passed, defaults to, "Unable to open that file.  Try again.".
 *  If no stream reference is passed, it is up to you to create an ifstream
 *  object and open it upon return from this function.
 */
std::string promptUserForFile(std::ifstream& stream,
                              const std::string& prompt = "",
                              const std::string& reprompt = "");
std::string promptUserForFile(std::ofstream& stream,
                              const std::string& prompt = "",
                              const std::string& reprompt = "");
std::string promptUserForFile(const std::string& prompt = "",
                              const std::string& reprompt = "");

/**
 *  @brief Reads the entire contents of the specified input stream into the string vector <code>lines</code>.
 *  @param is input stream used to read the given file
 *  @return None
 *  @throw
 */
void readEntireFile(std::istream& is, std::vector<std::string>& lines);

/**
 *  @brief An overload of readEntireFile that just returns the whole file
 *         as a very long single string, rather than a vector of lines.
 *  @return the former returns the entire file's text
 *          the latter returns true if the read was successful and false
 *          if the file was not found or unable to be opened for reading.
 *  @throw throws an error() if the file is not found or cannot be read.
 */
std::string readEntireFile(const std::string& filename);
bool readEntireFile(const std::string& filename, std::string& out);

/**
 *  @brief Renames a given file.
 *  @throw Errors are reported by calling <code>error()</code> in the implementation.
 */
void renameFile(const std::string& oldname, const std::string& newname);

/**
 *  @brief Moves the given input stream back to its beginning, so that it can be read again from start to finish.
 *  @param input the given input stream
 *  @throw
 */
void rewindStream(std::istream& input);

/**
 *  @brief Changes the given path to the current dir.
 *  @param path the given path
 *  @throw throws an error() if the given path is not found or cannot be read.
 */
void setCurrentDirectory(const std::string& path);