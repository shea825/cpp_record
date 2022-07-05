//
// Created by shea on 7/5/22.
//

//业务操作
class Stream {

public:
    virtual char Read(int number) = 0;

    virtual void Seek(int position) = 0;

    virtual void Write(char data) = 0;

    virtual ~Stream() = default;
};

//主体类
class FileStream : public Stream {
public:
    char Read(int number) override {
        //读文件流
    }

    void Seek(int position) override {
        //定位文件流
    }

    void Write(char data) override {
        //写文件流
    }

};

class NetworkStream : public Stream {
public:
    char Read(int number) override {
        //读网络流
    }

    void Seek(int position) override {
        //定位网络流
    }

    void Write(char data) override {
        //写网络流
    }

};

class MemoryStream : public Stream {
public:
    char Read(int number) override {
        //读内存流
    }

    void Seek(int position) override {
        //定位内存流
    }

    void Write(char data) override {
        //写内存流
    }

};

//扩展操作

class DecoratorStream : public Stream {
protected:
    Stream *stream;//...

    explicit DecoratorStream(Stream *stm) : stream(stm) {

    }

};

class CryptoStream : public DecoratorStream {


public:
    explicit CryptoStream(Stream *stm) : DecoratorStream(stm) {

    }


    char Read(int number) override {

        //额外的加密操作...
        stream->Read(number);//读文件流
    }

    void Seek(int position) override {
        //额外的加密操作...
        stream->Seek(position);//定位文件流
        //额外的加密操作...
    }

    void Write(char data) override {
        //额外的加密操作...
        stream->Write(data);//写文件流
        //额外的加密操作...
    }
};


class BufferedStream : public CryptoStream {

    Stream *stream;//...

public:
    explicit BufferedStream(Stream *stm) : CryptoStream(stm) {

    }
};


void Process() {

    //运行时装配
    FileStream *s1 = new FileStream();

    CryptoStream *s2 = new CryptoStream(s1);

    BufferedStream *s3 = new BufferedStream(s1);

    BufferedStream *s4 = new BufferedStream(s2);

}