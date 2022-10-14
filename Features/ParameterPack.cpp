//
// Created by shea on 10/8/22.
//

#include <iostream>

template<class... Types>
struct Tuple {
};

Tuple<> t0;           // Types 不包含实参
Tuple<int> t1;        // Types 包含一个实参：int
Tuple<int, float> t2; // Types 包含两个实参：int 与 float


void tprintf(const char *format) // 基础函数
{
    std::cout << format;
}

template<typename T, typename... Targs>
void tprintf(const char *format, T value, Targs... Fargs) // 递归变参函数
{
    for (; *format != '\0'; format++) {
        if (*format == '%') {
            std::cout << value;
            tprintf(format + 1, Fargs...); // 递归调用
            return;
        }
        std::cout << *format;
    }
}


int main() {
    tprintf("% world% %\n", "Hello", '!', 123);
}