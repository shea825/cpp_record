#include <iostream>
#include <assert.h>
#include <iomanip>
#include <vector>
#include "matrix.h"
#include <fstream>

Matrix::Matrix(int r,int c) {
    initData(r,c);
    initMatrix(static_cast<int *>(0));
}

Matrix::Matrix(int r, int c, int *array) {
    initData(r,c);
    initMatrix(array);
}

Matrix::Matrix(const Matrix &rhs) {
    initData(rhs.rows,rhs.cols);
    initMatrix(rhs.im);
}

void Matrix::initMatrix(int *array) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (array) {
                im[i][j] = *array++;
            }
            else {
                im[i][j] = 0;
            }
        }
    }
}

void Matrix::initMatrix(int **matrix) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            im[i][j] = matrix[i][j];
        }
    }
}

void Matrix::initData(int r, int c) {
    rows = r;
    cols = c;
    im = new int *[rows];
    for (int i = 0; i < rows; ++i) {
        im[i] = new int[cols];
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; ++i) {
        delete [] im[i];
    }
    delete [] im;
}

Matrix &Matrix::operator=(const Matrix &rhs) {
    if (this != &rhs) {
        if (rows != rhs.rows || cols != rhs.cols) {
            this->~Matrix();
            initData(rhs.rows,rhs.cols);
        }
        initMatrix(rhs.im);
    }
    return *this;
}

int &Matrix::operator()(int r, int c) {
    assert(r >= 0 && r < rows && c >= 0 && c < cols);
    return im[r][c];
}

bool Matrix::operator==(const Matrix &rhs) const {
    if (this != &rhs) {
        if (rows != rhs.rows || cols != rhs.cols)
            return false;
    }
    for (int i = 0; i < rhs.rows; ++i) {
        for (int j = 0; j < rhs.cols; ++j) {
            if (im[i][j] != rhs.im[i][j])
                return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &rhs) const {
    if (*this == rhs)
        return false;
    else
        return true;
}

int Matrix::getColumnSize() const {
    return cols;
}

int Matrix::getRowSize() const {
    return rows;
}

std::ostream &operator<<(std::ostream &out,const Matrix &rhs) {
    for (int i = 0; i < rhs.rows; ++i) {
        for (int j = 0; j < rhs.cols-1; ++j) {
            out << std::setiosflags(std::ios::right) << std::setw(5) << rhs.im[i][j] << ' ';
        }
        out << rhs.im[i][rhs.cols] << std::endl;
    }
    return out;
}

std::istream &operator>>(std::istream &in, Matrix &rhs) {
    int elem;
    for (int i = 0; i < rhs.rows; ++i) {
        for (int j = 0; j < rhs.cols; ++j) {
            in >> elem;
            rhs.im[i][j] = elem;
        }
    }
    return in;
}

int main() {

    return EXIT_SUCCESS;
}
