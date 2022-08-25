//
// Created by shea on 8/25/22.
//
#include <iostream>

int main() {
    volatile int var, ret;  //防止编译器指令重排 对代码进行优化
    //原子get and add
    var = 1;
    ret = __sync_fetch_and_add(&var, 2);
    std::cout << "__sync_fetch_and_add\t" << var << "\t" << ret << std::endl;

    //原子get
    var = 0;
    ret = __sync_val_compare_and_swap(&var, 0, 0);
    std::cout << "__sync_val_compare_and_swap\t" << var << "\t" << ret << std::endl;

    //原子get and set
    var = 8;
    ret = __sync_lock_test_and_set(&var, 100);
    std::cout << "__sync_lock_test_and_set\t" << var << "\t" << ret << std::endl;

}
