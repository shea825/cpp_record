
#include <string>

/** @file Messager.cpp
 *  @author shea
 *  @date 10:19 PM 8/17/22
 *  @plat CLion
 *  @brief this is a 
 */
using Image = std::string;

class MessagerImp {
public:
    virtual void PlaySound() = 0;

    virtual void DrawShape() = 0;

    virtual void WriteText() = 0;

    virtual void Connect() = 0;

    virtual ~MessagerImp() = default;
};

class Messager {
protected:
    MessagerImp *messagerImp;//未来可能是 PCMessagerBase* 或者 MobileMessagerBase×
public:
    explicit Messager(MessagerImp* mImp) {
        messagerImp = mImp;
    }
    virtual void Login(std::string username, std::string password) = 0;

    virtual void SendMessage(std::string message) = 0;

    virtual void SendPicture(Image image) = 0;

    virtual ~Messager() = default;
};

class PCMessagerImp : public MessagerImp {
public:
    void PlaySound() override {
        //*******
    }

    void DrawShape() override {
        //********
    }

    void WriteText() override {
        //********
    }

    void Connect() override {
        //********
    }
};

class MobileMessagerImp : public MessagerImp {
public:
    void PlaySound() override {
        //*******
    }

    void DrawShape() override {
        //********
    }

    void WriteText() override {
        //********
    }

    void Connect() override {
        //********
    }
};

class MessagerLite : public Messager {

public:
    void Login(std::string username, std::string password) override {
        messagerImp->Connect();
        //.......
    }

    void SendMessage(std::string message) override {
        messagerImp->WriteText();
        //.......
    }

    void SendPicture(Image image) override {
        messagerImp->DrawShape();
        //.......
    }
};