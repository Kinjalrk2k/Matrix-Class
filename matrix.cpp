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
        {
            if(m.matrix_m[i][j] == -0)  //  -0 adjustment
                out<<setw(m.max_space)<<setfill(' ')<<0<<" ";
            else
                out<<setw(m.max_space)<<setfill(' ')<<m.matrix_m[i][j]<<" ";
        }
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
Matrix operator+(const Matrix& m1, const Matrix& m2)
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
Matrix operator-(const Matrix& m1, const Matrix& m2)
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
Matrix operator*(const Matrix& m1, const Matrix& m2)
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
Matrix operator*(const Matrix& m, const double coeff)
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
Matrix operator/(const Matrix& m, const double coeff)
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
Matrix cofactor(const Matrix& m, int r, int c)
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
double determinant(const Matrix& m)
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
Matrix cofactor(const Matrix& m)
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
Matrix transpose(const Matrix& m)
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
Matrix adjoint(const Matrix& m)
{
    Matrix adj(m.rows, m.cols);

    adj = cofactor(m);
    adj = transpose(adj);
    
    return adj;
}

/*  compute the inverse of the matrix   */
Matrix inverse(const Matrix& m)
{
    Matrix inv(m.rows, m.cols);

    Matrix adj = adjoint(m);
    double det = determinant(m);
    inv = adj / det;

    return inv;
}

/* overloading ~ operator to compute the inverse    */
Matrix operator~(const Matrix& m)   //  inverse
{
    Matrix inv(m.rows, m.cols);

    Matrix adj = adjoint(m);
    double det = determinant(m);
    inv = adj / det;

    return inv;
}

/* overloading [] operator to return tha matirx element in the passed position    */
double Matrix::operator[](pair<int, int> rc)
{
    return this->matrix_m[rc.first][rc.second];
}

/*  break the whole matrix into seperate rows for row operations    */
void disintegrate_row(Matrix& m, Row& r, int r_no)
{
    r.row_m = new double[m.cols];
    r.cols = m.cols;

    for(int i=0; i<m.cols; i++)
        r.row_m[i] = m.matrix_m[r_no][i];
}

/*  join back the broken rows into the matrix   */
void integrate_row(Matrix& m, Row& r, int r_no)
{
    for(int i=0; i<m.cols; i++)
        m.matrix_m[r_no][i] = r.row_m[i];
}

/*  row operation: multiply a row with a scaler */
Row operator*(const Row& r, double coeff)
{
    Row res;
    res.row_m = new double[r.cols];
    res.cols = r.cols;

    for(int i=0; i<r.cols; i++)
        res.row_m[i] = coeff * r.row_m[i];

    return res;
}

/*  row operation: divide a row with a scaler */
Row operator/(const Row& r, const double coeff)
{
    Row res;
    res.row_m = new double[r.cols];
    res.cols = r.cols;

    for(int i=0; i<r.cols; i++)
        res.row_m[i] = r.row_m[i] / coeff;

    return res;
}

/*  row operation: add a row with another row */
Row operator+(const Row& r1, const Row& r2)
{
    Row res;
    res.row_m = new double[r1.cols];
    res.cols = r1.cols;

    for(int i=0; i<r1.cols; i++)
        res.row_m[i] = r1.row_m[i] + r2.row_m[i];

    return res;
}

/*  row operation: subtract a row from another row */
Row operator-(const Row& r1, const Row& r2)
{
    Row res;
    res.row_m = new double[r1.cols];
    res.cols = r1.cols;

    for(int i=0; i<r1.cols; i++)
        res.row_m[i] = r1.row_m[i] - r2.row_m[i];

    return res;
}

/*  swap two rows   */
void swap(Row& r1, Row& r2)
{
    Row temp;
    temp = r1;
    r1 = r2;
    r2 = temp;
}

/*  print a row */
void Row::print()
{
    for(int i=0; i<cols; i++)
        cout<<row_m[i]<<" ";
    cout<<endl;
}

/*  break the whole matrix into seperate columns for coloumn operations    */
void disintegrate_col(Matrix& m, Col& c, int c_no)
{
    c.col_m = new double[m.rows];
    c.rows = m.rows;

    for(int i=0; i<m.rows; i++)
        c.col_m[i] = m.matrix_m[i][c_no];
}

/*  join back the broken columns into the matrix   */
void integrate_col(Matrix& m, Col& c, int c_no)
{
    for(int i=0; i<m.rows; i++)
        m.matrix_m[i][c_no] = c.col_m[i];
}

/*  coloumn operation: multiply a column with a scaler */
Col operator*(const Col& c, double coeff)
{
    Col res;
    res.col_m = new double[c.rows];
    res.rows = c.rows;

    for(int i=0; i<c.rows; i++)
        res.col_m[i] = coeff * c.col_m[i];

    return res;
}

/*  coloumn operation: divide a column with a scaler */
Col operator/(const Col& r, const double coeff)
{
    Col res;
    res.col_m = new double[r.rows];
    res.rows = r.rows;

    for(int i=0; i<r.rows; i++)
        res.col_m[i] = r.col_m[i] / coeff;

    return res;
}

/*  coloumn operation: add a column with another coloumn */
Col operator+(const Col& r1, const Col& r2)
{
    Col res;
    res.col_m = new double[r1.rows];
    res.rows = r1.rows;

    for(int i=0; i<r1.rows; i++)
        res.col_m[i] = r1.col_m[i] + r2.col_m[i];

    return res;
}

/*  coloumn operation: subtract a column from another coloumn */
Col operator-(const Col& r1, const Col& r2)
{
    Col res;
    res.col_m = new double[r1.rows];
    res.rows = r1.rows;

    for(int i=0; i<r1.rows; i++)
        res.col_m[i] = r1.col_m[i] - r2.col_m[i];

    return res;
}

/*  swap two columns    */
void swap(Col& c1, Col& c2)
{
    Col temp;
    temp = c1;
    c1 = c2;
    c2 = temp;
}

/*  print a coloumn */
void Col::print()
{
    for(int i=0; i<rows; i++)
        cout<<col_m[i]<<" ";
    cout<<endl;
}

/*  Returns the row-reduced-echelon-matrix form of the passed matrix    */
Matrix rref(Matrix m, bool disp_steps)
{
    Matrix rre(m.rows, m.cols);
    Row* r;
    r = new Row[rre.rows];

    for(int i=0; i<m.rows; i++)
        disintegrate_row(m, r[i], i);

    for(int i=0, j=0; i<rre.rows, j<rre.cols; i++)
    {
        if(r[i].row_m[j] == 0)
        {
            bool found = false;
            for(int k=i+1; k<rre.rows; k++)
            {
                if(r[k].row_m[j] != 0)
                {
                    swap(r[i], r[k]);
                    found = true;

                    if(disp_steps)
                        printf("R%d <-> R%d", i+1, k+1);
                    break;
                }
            }
            if(!found)
                j++;
        }

        else
        {
            r[i] = r[i] / r[i].row_m[j];
            for(int k=i+1; k<rre.rows; k++)
            {
                double divi = r[i].row_m[j];
                double multi = r[k].row_m[j];
                double net_multi = multi/divi;
                r[k] = r[k] - (r[i]*net_multi);

                if(disp_steps)
                    printf("R%d\' -> R%d %c %g*R%d\n", k+1, k+1, ((net_multi>=0)? '-': '+') , abs(net_multi), i+1);
            }
            j++;
        }

        if(disp_steps)
        {
            for(int i=0; i<rre.rows; i++)
                integrate_row(rre, r[i], i);
            cout<<rre<<endl<<endl;

            for(int i=0; i<rre.rows; i++)
                disintegrate_row(rre, r[i], i);
        }
    }
    
    for(int i=0; i<rre.rows; i++)
        integrate_row(rre, r[i], i);

    return rre;
}

 /*  computes the rank of the passed matrix throughits rref form */
int Rank(const Matrix& m)
{
    Matrix rre = rref(m, false);
    int non_zero_row = 0;
    for(int i=0; i<rre.rows; i++)
    {
        for(int j=0; j<rre.cols; j++)
        {
            if(rre.matrix_m[i][j]!=0)
            {
                non_zero_row++;
                break;
            }
        }
    }
    return non_zero_row;
}
