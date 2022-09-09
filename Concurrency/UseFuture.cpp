//
// Created by shea on 9/8/22.
//
#include <future>
#include <iostream>
#include <string>
using namespace std;
string s = "not written";

void write(promise<int> &&writePromise) {
  cout << "\nwrite()" << endl;
  this_thread::sleep_for(chrono::seconds(1));
  s = "written";
  writePromise.set_value(233);
}

void read(future<int> &&readFut) {
  cout << "read(), waiting..." << flush;
  readFut.wait();
  auto i = readFut.get();
  cout << "\ns: '" << s << "'" << endl;
  cout << "\npromise: '" << i << "'" << endl;
}

int main() {
#if 1
  promise<int> writePromise; //声明一个promise对象
  future<int> writeFuture = writePromise.get_future();
  //声明一个future对象，并通过promise的get_future()函数与writePromise绑定

  thread tWrite(write, move(writePromise));
  thread tRead(read, move(writeFuture));

  tWrite.join();
  tRead.join();
#else
  /**
   * @warning terminate called after throwing an instance of 'std::future_error'
   * what():  std::future_error: No associated state
   */
  promise<int> writePromise;

  thread tWrite(write, move(writePromise));
  thread tRead(read, move(writePromise.get_future()));

  tWrite.join();
  tRead.join();
#endif
}