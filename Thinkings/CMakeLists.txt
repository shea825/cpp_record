add_executable(OOP OOP/Thread.h OOP/Thread.cpp)
target_link_libraries(OOP -lpthread)

add_executable(Object-based Object-based/Thread.h Object-based/Thread.cpp)
target_link_libraries(Object-based -lpthread)