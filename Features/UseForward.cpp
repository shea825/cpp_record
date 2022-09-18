//
// Created by shea on 9/16/22.
//
#include <iostream>
#define USE_FORWARD 1

class CData {
public:
  CData() = delete;
  explicit CData(const char *ch) : data(ch) {
    std::cout << "CData(const char* ch)" << std::endl;
  }
  explicit CData(const std::string &str) : data(str) {
    std::cout << "CData(const std::string& str)" << std::endl;
  }
  explicit CData(std::string &&str) : data(str) {
    std::cout << "CData(std::string&& str)" << std::endl;
  }
  ~CData() { std::cout << "~CData()" << std::endl; }

private:
  std::string data;
};

#if USE_FORWARD
/**
 * @note std::forward会将输入的参数原封不动地传递到下一个函数中，
 * 这个“原封不动”指的是，如果输入的参数是左值，那么传递给下一个函数的参数的也是左值；
 * 如果输入的参数是右值，那么传递给下一个函数的参数的也是右值
 */
template <typename T> CData *Creator(T &&t) {
  return new CData(std::forward<T>(t));
}

#else
//右值引用模板
template <typename T> CData *Creator(T &&t) {
  return new CData(t);
}

#endif
void Forward() {
  const char *value = "hello";
  std::string str1 = "hello";
  std::string str2 = " world";
  CData *p = Creator(str1 + str2);

  delete p;
}

int main() {
  Forward();
}