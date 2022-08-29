//
// Created by shea on 8/25/22.
//

#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>

class Foo {
public:
  void memberFunc(double d, int i, int j) {
    std::cout << d << std::endl;
    std::cout << i << std::endl;
    std::cout << j << std::endl;
  }
  void print_sum(int n1, int n2) {
    std::cout << n1+n2 << '\n';
  }
};

int main() {
  Foo foo;
  //boost bind
  boost::function<void (int)> fp = boost::bind(&Foo::memberFunc, &foo, 0.5, _1, 10);
  fp(100);

  //std bind
  auto f3 = std::bind(&Foo::memberFunc, &foo, 0.5, std::placeholders::_1, 10);
  f3(100);
  return EXIT_SUCCESS;
}