set(matrixLibFile
        matrix.cpp
        matrix.h)

add_library(matrixLib ${matrixLibFile})

add_executable(matrixTest test.cpp ${matrixLibFile})
