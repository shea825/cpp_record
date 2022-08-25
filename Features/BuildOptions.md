```cmake
set(CMAKE_CXX_FLAGS 
        -g              #生成调试信息
        -Wall           #给出大部分警告
        -Wextra         #给出一些额外的警告
        -Werror         #警告转为错误，停止编译
        -march=native   #制定cpu体系结构为本地平台
        )
```