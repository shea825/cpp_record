set(UringFileSrc
        UringFile.h
        UringFile.cpp)

set(FileUtilSrc
        FileUtil.h
        FileUtil.cpp)

add_library(fileUtil ${FileUtilSrc} ${UringFileSrc})
target_link_libraries(fileUtil -luring)

set(SocketSrc
        Socket.h
        Socket.cpp
        NetUtil.cpp)
