//
// Created by shea on 9/7/22.
//
#include <functional>
#include <memory>
#include <vector>

typedef void (*FUNC)(const std::vector<int>& data);
int main() {
  std::vector<int> data{ 1, 2, 3, 4 };

  auto func = std::bind(
      [](const std::vector<int>& data)
      { /* uses of data */ },
      std::move(data));
  func();
//  FUNC f1 = func; //todo 还没搞懂
  std::function<void ()> f = func;

  std::unique_ptr<int> x(new int(42));
  auto func2 = std::bind(
      [](const std::unique_ptr<int>& y)
      {printf("%d\n", *y);},
      std::move(x));
  func2();
//  std::function<void ()> f2 = func2;
}