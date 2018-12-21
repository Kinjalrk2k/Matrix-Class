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
        friend Matrix operator+(Matrix& m1, Matrix& m2);
        friend Matrix operator-(Matrix& m1, Matrix& m2);
        friend Matrix operator*(Matrix& m1, Matrix& m2);
        friend Matrix operator*(Matrix& m, double coeff);
        friend Matrix operator/(Matrix& m, double coeff);

        friend Matrix cofactor(Matrix& m, int r, int c);
        friend double determinant(Matrix& m);
        friend Matrix cofactor(Matrix& m);        
        friend Matrix transpose(Matrix& m);
        friend Matrix adjoint(Matrix& m);
        friend Matrix inverse(Matrix& m);
};