/*  defines the functions for matrix.h  */
#include "matrix.h"

/*  get number of digits including sign and decimal point   */
int num_digs_spaces(double num)
{
    char buffer[100];   //  buffer to store the whole number
    int ret = snprintf(buffer, sizeof (buffer), "%lf", num);    //  snprintf the buffer

    int dig_int = log10((int)(num)) + 1;    //  no of digits in the integer part

    /*  gets the number of tailing zeros after the decimal point */
    int steps=0;
    for(int i=strlen(buffer)-1; i>=0; i--)
    {
        if(buffer[i]=='0')
            steps++;
        else
            break;
    }

    int total_count = strlen(buffer) - steps;   //  removing the count of tailing zeros

    /*  additional special cases, when an int is used   */
    if(total_count - dig_int == 1)
        total_count--;

    if(num<0 && total_count - dig_int == 2)
        total_count--;

    return total_count;
}

/*  parameterized constructor: dynamically allocate the matrix  
    This constructor initialises the matrix as a NULL MATRIX    */
Matrix::Matrix(unsigned int r, unsigned int c)
{
    matrix_m = new double*[r];
    for(int i=0; i<r; i++)
        matrix_m[i] = new double[c]();  //  settig all the elements to zero

    /*  setting the current rows and coloumns   */
    this->rows = r;
    this->cols = c;
    exists = true;  //  yay! the matix exsists!
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

/*  oveloading << operator to print the matrix  */
ostream& operator<<(ostream &out, Matrix& m)
{
    if(!m.exists)   //  if matrix does not exsists
    {
        out<<"Matrix impossible to handle";
        return out;
    }

    position start = wherexy(); //  get current position
    position p = start;
    position xend = start;

    m.get_max_space();

    /*  printing the matrix */

    //  printing left cover top
    out<<(char)218;
    p.y++;  gotoxy(p);

    for(int i=0; i<m.rows; i++)
    {
        out<<(char)179; //  printing left cover
        for(int j=0; j<m.cols; j++)
            out<<setw(m.max_space)<<setfill(' ')<<m.matrix_m[i][j]<<" ";
        out<<"\b";

        /*  computing the maximum right cover position    */
        position temp = wherexy();
        if(temp.x > xend.x)
            xend.x = temp.x;
        
        p.y++;  gotoxy(p);
    }

    //  printing left cover bottom
    out<<(char)192;

    /*  printing the right side cover   */
    gotoxy(xend);  out<<(char)191;  xend.y++;
    for(int i=0; i<m.rows; i++)
    {
        gotoxy(xend);   out<<(char)179; xend.y++;
    }
    gotoxy(xend);   out<<(char)217;

    return out;
}

/*  oveloading >> operator to input the matrix  */
istream& operator>>(istream &in, Matrix &m)
{
    for(int i=0; i<m.rows; i++)
    {
        for(int j=0; j<m.cols; j++)
            in>>m.matrix_m[i][j];
    }

    return in;
}

/*  oveloading + operator to add two matrices  */
Matrix operator+(Matrix& m1, Matrix& m2)
{
    Matrix res(m1.rows, m1.cols);
    if(m1.rows == m2.rows && m1.cols == m2.cols)    //  if square matrix
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

/*  oveloading - operator to subtract two matrices  */
Matrix operator-(Matrix& m1, Matrix& m2)
{
    Matrix res(m1.rows, m1.cols);
    if(m1.rows == m2.rows && m1.cols == m2.cols)    //  if square matrix
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

/*  oveloading + operator to add two matrices  */
Matrix operator*(Matrix& m1, Matrix& m2)
{
    Matrix res(m1.rows, m2.cols);

    //  if no. of columns in the first matix is equal to no. of rows of the second
    if(m1.cols == m2.rows)  
    {
        for(int i = 0; i < m1.rows; ++i)
        {
            for(int j = 0; j < m2.cols; ++j)
            {
                res.matrix_m[i][j] = 0; //  setting the resultant matrix as NULL matrix
                for(int k = 0; k < m1.cols; ++k)
                    res.matrix_m[i][j] += m1.matrix_m[i][k] * m2.matrix_m[k][j];
            }             
        }
    }
    else
        res.exists = false;

    return res;
}

/*  overloading * operator to multiply a scaler value to a matrix   */
Matrix operator*(Matrix& m, double coeff)
{
    Matrix res(m.rows, m.cols);

    for(int i=0; i<m.rows; i++)
    {
        for(int j=0; j<m.cols; j++)
            res.matrix_m[i][j] = coeff * m.matrix_m[i][j];  //  multiplying each element
    }

    return res;
}

/*  overloading / operator to divide a scaler value to a matrix   */
Matrix operator/(Matrix& m, double coeff)
{
    Matrix res(m.rows, m.cols);

    for(int i=0; i<m.rows; i++)
    {
        for(int j=0; j<m.cols; j++)
            res.matrix_m[i][j] = m.matrix_m[i][j] / coeff;  //  dividing each element
    }

    return res;
}

/*  compute cofactor matrix of a specific element located at [r,c] */
Matrix cofactor(Matrix& m, int r, int c)
{
    Matrix cf(m.rows-1, m.rows-1);

    int k=0, l=0;
    for(int i=0; i<m.rows; i++)
    {
        for(int j=0; j<m.cols; j++)
        {
            //  not setting up the elements from the element's own row and coloumn
            if(i!=r && j!=c)    
            {
                cf.matrix_m[k][l++] = m.matrix_m[i][j];
                if(l == m.rows-1)   //  reaching the end of the row
                {
                    l=0;
                    k++;
                }
            }
        }
    }

    return cf;
}

/*  compute determinate value of a matrix(reccursively)   */
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

/*  compute cofactor matrix of the total matrix */
Matrix cofactor(Matrix& m)
{
    Matrix cf(m.rows, m.cols);

    for(int i=0; i<m.rows; i++)
    {
        for(int j=0; j<m.cols; j++)
        {
            Matrix cff = cofactor(m, i, j);
            int sign = pow((-1), (i+j));
            double det = determinant(cff);
            cf.matrix_m[i][j] = sign * det;

            if(sign == (-1) && det == 0)    //  adjustment for -0 problem
                cf.matrix_m[i][j] = 0;
        }
    }

    return cf;
}

/*  compute transpose of a matrix   */
Matrix transpose(Matrix& m)
{
    Matrix trans(m.cols, m.rows);

    for(int i=0; i<m.rows; i++)
    {
        for(int j=0; j<m.cols; j++)
            trans.matrix_m[j][i] = m.matrix_m[i][j];
   }

    return trans;
}

/*  compute adjoint of a matrix */
Matrix adjoint(Matrix& m)
{
    Matrix adj(m.rows, m.cols);

    adj = cofactor(m);
    adj = transpose(adj);
    
    return adj;
}

/*  compute the inverse of the matrix   */
Matrix inverse(Matrix& m)
{
    Matrix inv(m.rows, m.cols);

    Matrix adj = adjoint(m);
    double det = determinant(m);
    inv = adj / det;

    return inv;
}