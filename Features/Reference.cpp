//
// Created by shea on 7/31/22.
//

int main() {
    /**
     * 一个变量，既有变量的属性，即是作为左值的时候是地址的属性， 又有常量的属性，即是作为右边的时候，是值的属性
     * 左值，就是在内存有确定存储地址、有变量名，表达式结束依然存在的值
     * 右值，就是在内存没有确定存储地址、没有变量名，表达式结束就会销毁的值
     * 左值引用，就是绑定到左值的引用，通过&来获得左值引用
     * 右值引用，就是绑定到右值的引用，通过&&来获得右值引用
     */

    int a=10;              //非常量左值（有确定存储地址，也有变量名）
    const int a1=10;       //常量左值（有确定存储地址，也有变量名）
    const int a2=20;       //常量左值（有确定存储地址，也有变量名）

    /**
     * 左值
     */

//非常量左值引用
    int &b1=a;            //正确，a是一个非常量左值，可以被非常量左值引用绑定
//    int &b2=a1;           //错误,a1是一个常量右值，不可以被非常量左值引用绑定
//    int &b3=10;           //错误，10是一个常量右值，不可以被非常量左值引用绑定
//    int &b4=a1+a2;        //错误,（a1+a2）是一个常量右值，不可以被非常量左值引用绑定

//常量左值引用    常用于类中构建拷贝构造函数
    const int &c1=a;      //正确，a是一个非常量左值，可以被常量右值引用绑定
    const int &c2=a1;     //正确,a1是一个常量左值，可以被常量右值引用绑定
    const int &c3=a+a1;   //正确，（a+a1）是一个非常量右值，可以被常量右值引用绑定
    const int &c4=a1+a2;  //正确,（a1+a2）是一个常量右值，可以被常量右值引用绑定

    /**
     * 右值
     */

//非常量右值引用   移动语义、转发
//    int &&b1=a;            //错误，a是一个非常量左值，不可以被非常量右值引用绑定
//    int &&b2=a1;           //错误,a1是一个常量左值，不可以被非常量右值引用绑定
    int &&b3=a+a1;         //正确，a是一个非常量右值，可以被非常量右值引用绑定
    int &&b4=a1+a2;        //正确,（a1+a2）是一个常量右值，可以被非常量右值引用绑定
    int &&b5=10;           //正确,（a1+a2）是一个常量右值，可以被非常量右值引用绑定

//常量右值引用    无实际用途
//    const int &&c1=a;      //错误，a是一个非常量左值，不可以被常量右值引用绑定
//    const int &&c2=a1;     //错误,a1是一个常量左值，不可以被常量右值引用绑定
//    const int &&c3=a+a1;   //错误，（a+a1）是一个非常量右值，不可以被常量右值引用绑定
//    const int &&c4=a1+a2;  //错误,（a1+a2）是一个常量右值，不可以被常量右值引用绑定


}