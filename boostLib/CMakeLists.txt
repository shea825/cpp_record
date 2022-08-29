project(boostLib)

find_package(Boost 1.54 COMPONENTS filesystem)
if (Boost_FOUND)
    message(STATUS "Boost Lib filesystem Found")
    add_executable(boostLib boostLib.cpp)
    target_link_libraries(boostLib
            PUBLIC
            Boost::filesystem)
endif ()

add_executable(FunctionBind FunctionBind.cpp)