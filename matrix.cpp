/*  defines the functions for matrix.h  */
#include "matrix.h"

/*  get number of digits including sign and decimal point   */
int num_digs_spaces(double num)
{
    char buffer[100];   //  buffer to store the whole number
    int ret = snprintf(buffer, sizeof (buffer), "%lf", num);

    int dig_int = log10((int)(num)) + 1;

    int steps=0;
    for(int i=strlen(buffer)-1; i>=0; i--)
    {
        if(buffer[i]=='0')
            steps++;
        else
            break;
    }

    int total_count = strlen(buffer) - steps;

    if(total_count - dig_int == 1)
        total_count--;

    if(num<0 && total_count - dig_int == 2)
        total_count--;

    return total_count;
}

/*  parameterized constructor   */
Matrix::Matrix(unsigned int r, unsigned int c)
{
    matrix_m = new double*[r];
    for(int i=0; i<r; i++)
        matrix_m[i] = new double[c];

    this->rows = r;
    this->cols = c;
    exists = true;
}

/*  find the maximum space among all the elements   */
void Matrix::get_max_space()
{
    int space = 0;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(num_digs_spaces(matrix_m[i][j]) > space)
                space = num_digs_spaces(matrix_m[i][j]);
        }
    }
    max_space = space;
}

ostream& operator<<(ostream &out, Matrix& m)
{
    if(!m.exists)
    {
        out<<"Matrix impossible to handle";
        return out;
    }

    position start = wherexy();
    position p = start;
        
    m.get_max_space();
    out<<(char)218;
    for(int i=0; i<((m.max_space*m.cols)+(m.cols-1)); i++)
        out<<" ";
    out<<(char)191;
    p.y++;  gotoxy(p);

    for(int i=0; i<m.rows; i++)
    {
        out<<(char)179;
        for(int j=0; j<m.cols; j++)
            out<<setw(m.max_space)<<setfill(' ')<<m.matrix_m[i][j]<<" ";

        out<<"\b"<<(char)179;
        p.y++;  gotoxy(p);
    }

    out<<(char)192;
    for(int i=0; i<((m.max_space*m.cols)+(m.cols-1)); i++)
        out<<" ";
    out<<(char)217;
    //p.y++;  gotoxy(p);

    return out;
}

istream& operator>>(istream &in, Matrix &m)
{
    for(int i=0; i<m.rows; i++)
    {
        for(int j=0; j<m.cols; j++)
            in>>m.matrix_m[i][j];
    }

    return in;
}

Matrix operator+(Matrix& m1, Matrix& m2)
{
    Matrix res(m1.rows, m1.cols);
    if(m1.rows == m2.rows && m1.cols == m2.cols)
    {
        for(int i=0; i<m1.rows; i++)
        {
            for(int j=0; j<m1.cols; j++)
                res.matrix_m[i][j] = m1.matrix_m[i][j] + m2.matrix_m[i][j];
        }
    }
    else
        res.exists = false;

    return res;
}

Matrix operator-(Matrix& m1, Matrix& m2)
{
    Matrix res(m1.rows, m1.cols);
    if(m1.rows == m2.rows && m1.cols == m2.cols)
    {
        for(int i=0; i<m1.rows; i++)
        {
            for(int j=0; j<m1.cols; j++)
                res.matrix_m[i][j] = m1.matrix_m[i][j] - m2.matrix_m[i][j];
        }
    }
    else
        res.exists = false;

    return res;
}

Matrix operator*(Matrix& m1, Matrix& m2)
{
    Matrix res(m1.rows, m2.cols);
    if(m1.cols == m2.rows)
    {
        for(int i = 0; i < m1.rows; ++i)
        {
            for(int j = 0; j < m2.cols; ++j)
            {
                res.matrix_m[i][j] = 0;
                for(int k = 0; k < m1.cols; ++k)
                    res.matrix_m[i][j] += m1.matrix_m[i][k] * m2.matrix_m[k][j];
            }             
        }
    }
    else
        res.exists = false;

    return res;
}

Matrix cofactor(Matrix& m, int r, int c)
{
    Matrix cf(m.rows-1, m.rows-1);
    int k=0, l=0;
    for(int i=0; i<m.rows; i++)
    {
        for(int j=0; j<m.cols; j++)
        {
            if(i!=r && j!=c)
            {
                cf.matrix_m[k][l++] = m.matrix_m[i][j];
                if(l == m.rows-1)
                {
                    l=0;
                    k++;
                }
            }
        }
    }

    return cf;
}

double determinant(Matrix& m)
{
    double det = 0.0;
    int sign = 1;

    if(m.rows == 1)
        return m.matrix_m[0][0];
    
    for(int i=0; i<m.rows; i++)
    {
        Matrix cf = cofactor(m, 0, i);
        det += sign * m.matrix_m[0][i] * determinant(cf);
        sign = -sign;
    }
    return det;
}