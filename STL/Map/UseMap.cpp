//
// Created by shea on 9/6/22.
//

#include <iostream>
#include <map>

int main() {
  std::map<int, int> delays;
  {
    int delay = 5;
    ++delays[delay];
  }
  for (auto &delay :delays) {
    std::cout << delay.first << delay.second << std::endl;
  }
  std::cout << 1e3+9 << std::endl;
  return EXIT_SUCCESS;
}