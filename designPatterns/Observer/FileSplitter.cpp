
#include <string>

/** @file FileSplitter.cpp
 *  @author shea
 *  @date 8:10 PM 6/26/22
 *  @plat CLion
 *  @brief this is a 
 */

class IProgress {
public:
    virtual void DoProgress(float value) = 0;

    virtual ~IProgress() = default;
};

class FileSplitter {
    std::string filePath_;
    int fileNumber_;

    ProgressBar *progressBar_;  //具体通知控件
    IProgress *iProgress_;      //抽象通知机制

public:
    FileSplitter(const std::string &filePath, int fileNumber, IProgress *iProgress) :
            filePath_(filePath),
            fileNumber_(fileNumber),
            iProgress_(iProgress) {

    }

    void split() {
        //读取大文件

        //分批次向小文件中写入
        for (int i = 0; i < fileNumber_; ++i) {
            if (iProgress_) {
                float progressValue = fileNumber_;
                progressValue = (i + 1) / fileNumber_;
                iProgress_->DoProgress(progressValue);  //更新进度条
            }
        }
    }
};