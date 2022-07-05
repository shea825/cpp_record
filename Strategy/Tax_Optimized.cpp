//
// Created by shea on 6/25/22.
//

#include <map>

using Context = std::map<std::string, double>;

class Tax {
public:
    virtual double Calculate(const Context &context) = 0;   //“=0”表示该成员函数为 纯虚函数

    virtual ~Tax() = default;;
};

class CNTax : public Tax {
public:
    double Calculate(const Context &context) override {

        return 0;
    }
};

class USTax : public Tax {
public:
    double Calculate(const Context &context) override {

        return 0;
    }
};

class DETax : public Tax {
public:
    double Calculate(const Context &context) override {

        return 0;
    }
};

class SalesOrder {
private:
    Tax* tax;
public:
    SalesOrder(TaxFactory* taxFactory) {
        this->tax = taxFactory->NewTax();
    }

    ~SalesOrder() {
        delete this->tax;
    }

    double CalculateTax() {
        Context context{};
        double val = tax->Calculate(context);
    }
};



/**
 * 添加需求
 */

class FRTax : public Tax {
public:
    double Calculate(const Context &context) override {

        return 0;
    }
};

/**
 * 对于 SalesOrder 不用改变
 */