/*  matric.h consisting of the matrix class and assoicated functions    */
#include <iostream>
#include <math.h>
#include <string.h>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "console_position.h"

using namespace std;

static int num_digs_spaces(double num);

class Row;
class Col;
class Matrix;

class Matrix
{
    unsigned int rows, cols;
    double **matrix_m;
    int max_space;
    void get_max_space();

    public:
        bool exists;
        Matrix(unsigned int r, unsigned int c);      
 
        friend ostream& operator<<(ostream& out, Matrix& m);
        friend istream& operator>>(istream& out, Matrix& m);
        friend Matrix operator+(const Matrix& m1, const Matrix& m2);
        friend Matrix operator-(const Matrix& m1, const Matrix& m2);
        friend Matrix operator*(const Matrix& m1, const Matrix& m2);
        friend Matrix operator*(const Matrix& m, const double coeff);
        friend Matrix operator/(const Matrix& m, const double coeff);
        friend Matrix operator~(const Matrix& m);   //  inverse
        double operator[](pair<int, int> rc);

        friend Matrix cofactor(const Matrix& m, int r, int c);
        friend double determinant(const Matrix& m);
        friend Matrix cofactor(const Matrix& m);        
        friend Matrix transpose(const Matrix& m);
        friend Matrix adjoint(const Matrix& m);
        friend Matrix inverse(const Matrix& m);

        friend void disintegrate_row(Matrix& m, Row& r, int r_no);
        friend void integrate_row(Matrix& m, Row& r, int r_no);

        friend void disintegrate_col(Matrix& m, Col& c, int c_no);
        friend void integrate_col(Matrix& m, Col& c, int c_no);
};

/*  for row-operations  */
class Row
{
    unsigned int cols;
    double *row_m;

    public:
        friend void disintegrate_row(Matrix& m, Row& r, int r_no);
        friend void integrate_row(Matrix& m, Row& r, int r_no);

        friend Row operator*(const Row& m, const double coeff);
        friend Row operator/(const Row& m, const double coeff);

        friend Row operator+(const Row& r1, const Row& r2);
        friend Row operator-(const Row& r1, const Row& r2);

        friend void swap(Row& r1, Row& r2);

        void print();
};

/*  for coloumn operatins    */
class Col
{
    unsigned int rows;
    double *col_m;

    public:
        friend void disintegrate_col(Matrix& m, Col& c, int c_no);
        friend void integrate_col(Matrix& m, Col& c, int c_no);

        friend Col operator*(const Col& m, const double coeff);
        friend Col operator/(const Col& m, const double coeff);

        friend Col operator+(const Col& c1, const Col& c2);
        friend Col operator-(const Col& c1, const Col& c2);

        friend void swap(Col& c1, Col& c2);

        void print();
};