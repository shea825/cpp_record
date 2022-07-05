//
// Created by shea on 5/23/22.
//

#include <map>
#include <iostream>

class non_copyable {
public:
    non_copyable() = default;

    non_copyable(non_copyable&&) = default;
    non_copyable& operator=(non_copyable&&) = default;

    // you shall not copy
    non_copyable(const non_copyable&) = delete;
    non_copyable& operator=(const non_copyable&) = delete;
};

class test : non_copyable {
private:
    int a{};
    long b{};
    const int c;
public:
    explicit test(const int arg_c) : c(arg_c) {};
    int get_c() const {
        return c;
    }
    void print() const {
        std::cout << "a: " << a << std::endl
        << "c: " << c << std::endl;
    }
    void set_a(int arg_a) {
        a = arg_a;
    }
    friend bool operator<(const test& test1, const test& test2) {
        return test1.get_c() < test2.get_c();
    }
};
using Tests1 = std::map<int, test>;
using Tests2 = std::map<int, non_copyable>;

int main() {

    Tests1 tests1;

    tests1.insert({12, test(12)});
    tests1.at(12).set_a(11);
    tests1.at(12).print();

//    test test1 = tests1.at(12);//error

    std::cout << tests1.at(12).get_c() << std::endl;

    Tests2 tests2;
    tests2.insert({12, non_copyable()});

    std::map<int, non_copyable> map;
    map.insert({ 1, non_copyable() });
}