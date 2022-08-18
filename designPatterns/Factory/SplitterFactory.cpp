
/** @file SplitterFactory.cpp
 *  @author shea
 *  @date 10:21 PM 8/18/22
 *  @plat CLion
 *  @brief this is a 
 */

//抽象类
class ISplitter {
public:
    virtual void split() = 0;

    virtual ~ISplitter() = default;
};

//具体类
class BinarySplitter : public ISplitter {
    void split() override {

    }
};

class TxtSplitter : public ISplitter {
    void split() override {

    }
};

class PictureSplitter : public ISplitter {
    void split() override {

    }
};

class VideoSplitter : public ISplitter {
    void split() override {

    }
};

//工厂基类
class SplitterFactory {
public:
    virtual ISplitter *CreateSplitter() = 0;//工厂方法 虚函数重写让实例化延时

    virtual ~SplitterFactory() = default;
};

//具体工厂
class BinarySplitterFactory : public SplitterFactory {
public:
    ISplitter *CreateSplitter() override {
        return new BinarySplitter();//实例化
    }
};

class TxtSplitterFactory : public SplitterFactory {
public:
    ISplitter *CreateSplitter() override {
        return new TxtSplitter();
    }
};

class PictureSplitterFactory : public SplitterFactory {
public:
    ISplitter *CreateSplitter() override {
        return new PictureSplitter();
    }
};

class VideoSplitterFactory : public SplitterFactory {
public:
    ISplitter *CreateSplitter() override {
        return new VideoSplitter();
    }
};

class Form{};
class MainForm : public Form {
    SplitterFactory* factory;
public:
    explicit MainForm(SplitterFactory* factory) {
        this->factory = factory;
        //可以是任意具体类
    }
    void buttonClick() {
        ISplitter* splitter = factory->CreateSplitter();//多态new
        splitter->split();
    }
};