//
// Created by shea on 9/29/21.
//

#ifndef TEST_MATRIX_H
#define TEST_MATRIX_H
class Matrix {
public:
    explicit Matrix( int = defaultRowSize, int = defaultColumnSize );//default constructor
    Matrix(int,int,int *);//constructor
    Matrix(const Matrix &);
    ~Matrix();//destructor

    Matrix &operator=(const Matrix &);
    bool operator==(const Matrix &) const;
    bool operator!=(const Matrix &) const;

    int &operator()(int,int);
    int getRowSize() const;
    int getColumnSize() const;

    friend std::ostream &operator<<(std::ostream &,const Matrix &);
    friend std::istream &operator>>(std::istream &,Matrix &);

private:
    int **im;
    int rows;
    int cols;
    static const int defaultRowSize = 5;
    static const int defaultColumnSize = 5;
    void initMatrix(int *);
    void initMatrix(int **);
    void initData(int r,int c);
};
#endif //TEST_MATRIX_H
