//
// Created by shea on 9/16/22.
//
#include <iostream>
#include <memory>
class ClassB;

class ClassA
{
public:
  ClassA() { std::cout << "ClassA Constructor..." << std::endl; }
  ~ClassA() { std::cout << "ClassA Destructor..." << std::endl; }
  std::weak_ptr<ClassB> pb;  // 在A中引用B
};

class ClassB
{
public:
  ClassB() { std::cout << "ClassB Constructor..." << std::endl; }
  ~ClassB() { std::cout << "ClassB Destructor..." << std::endl; }
  std::weak_ptr<ClassA> pa;  // 在B中引用A
};

int main() {
  std::shared_ptr<ClassA> spa = std::make_shared<ClassA>();
  std::shared_ptr<ClassB> spb = std::make_shared<ClassB>();
  spa->pb = spb;
  spb->pa = spa;
}