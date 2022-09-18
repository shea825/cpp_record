//
// Created by shea on 9/16/22.
//
#include <vector>
#include <string>

template<typename T>
std::vector<unsigned char> TypeToVec(const T &data) {
  std::vector<unsigned char> ret;
  ret.resize(sizeof(data));
  memcpy(ret.data(), &data, sizeof(data));
  return ret;
}

template<typename T>
T VecToType(const std::vector<unsigned char> &data) {
  T ret;
  memcpy(&ret, data.data(), data.size());
  return ret;
}

template<>
std::vector<unsigned char> TypeToVec(const std::string &data) {
  return std::vector<unsigned char>(data.begin(), data.end());
}

template<>
std::string VecToType(const std::vector<unsigned char> &data) {
  return std::string(data.begin(), data.end());
}

int main() {
  std::string str = "123456";
  std::vector<unsigned char> vec = TypeToVec<std::string>(str);
  std::string str2 = VecToType<std::string>(vec);
}