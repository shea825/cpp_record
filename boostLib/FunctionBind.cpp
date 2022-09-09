//
// Created by shea on 8/25/22.
//

#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>
typedef void (*funcType)(const char *msg);

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

void outputFunc1(const char *msg, int len, int* file) {
  printf("%s", msg);
}

typedef void (*funcType1)();
double callableFunc (double x, double y) {return x/y;}

int main() {
  Foo foo;
  //boost bind
  boost::function<void (int)> fp = boost::bind(&Foo::memberFunc, &foo, 0.5, _1, 10);
  fp(100);

  //std bind
  auto f3 = std::bind(&Foo::memberFunc, &foo, 0.5, std::placeholders::_1, 10);
  f3(100);

//  FILE* g_file;
//  int* i;
//  funcType f4 = std::bind(outputFunc1, std::placeholders::_1, 10, i);
//  f4("111", 2);
  return EXIT_SUCCESS;

}