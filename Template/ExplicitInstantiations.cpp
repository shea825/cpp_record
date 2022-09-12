//
// Created by shea on 9/12/22.
//
#include <iostream>
#include <string>
using namespace std;
typedef struct{
  string name;
  float score;
} STU;

template<typename T>
const T & Max(const T &a, const T &b){
  return a > b ? a : b;
}

template<>
const STU & Max<STU>(const STU &a, const STU &b){
  return a.score > b.score ? a : b;
}
/**
 * @note Max<STU> 中的 STU 表明了要将 参数T 具体化为 STU类型
 * 因此类型参数列表为空 写作 template<>
 * 也可简写为
 * template<> const STU& Max(const STU& a, const STU& b);
 * 因为函数的形参已经表明这是STU类型一个具体化 编译器能够逆推出T的具体类型
 */

ostream & operator << (ostream & out, const STU &stu){
  out << stu.name << ' ' << stu.score;
  return out;
}

int main(int argc, char const *argv[]){
  int a = 10, b = 20;
  cout<<Max(a, b)<<endl;

  STU stu1 = {"Sam", 90}, stu2 = {"Amy", 100};
  cout<<Max(stu1, stu2);
  return 0;
}