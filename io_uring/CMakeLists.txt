add_executable(io_uring_test test/test_UringFile.cpp src/UringFile.cpp src/UringFile.h)
target_link_libraries(io_uring_test -luring)

add_executable(file_util_test test/test_FileUtil.cpp
        src/UringFile.cpp src/UringFile.h
        src/FileUtil.cpp src/FileUtil.h)
target_link_libraries(file_util_test -luring)

add_executable(socket_test test/test_Socket.cpp
        src/Socket.cpp src/Socket.h
        src/NetUtil.cpp src/NetUtil.h)
target_link_libraries(socket_test -luring)

add_executable(copyfile test/copyFile.cpp)
target_link_libraries(copyfile -luring)