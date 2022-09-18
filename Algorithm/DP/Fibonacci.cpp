//
// Created by shea on 9/15/22.
//

#include <iostream>
int dp(int i) {
  int f = 0;
  int g = 1;
  while (i-- > 0) { //F(n) = F(n-1) + F(n-2)
    g += f;     //计算本次结果F(n)
    f = g - f;  //将上次的结果F(n-1)转移到 f
  }
  return g;
}

int fibonacci(int i) {
  if (i == 1) {
    return 0;
  } else if (i == 2) {
    return 1;
  } else {  //i > 2
    return dp(i - 2);
  }
}

int main() {
  int x;
  std::cin >> x;
  std::cout << fibonacci(x) << std::endl;
}