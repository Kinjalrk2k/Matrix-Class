/*  sample main function demonstrating the working  */
#include "matrix.h"

int main(int argc, char const *argv[])
{
    freopen("in.txt", "r", stdin);

    Matrix m1(3, 3);
    //cout<<m1;
    //getch();

    cout<<"Enter matrix1: "<<endl;
    cin>>m1;
    cout<<endl<<"You entered: "<<endl<<m1;

    /*Matrix res = cofactor(m1, 3, 2);
    cout<<endl<<"Resultant Matrix: "<<endl<<res<<endl;*/

    cout<<endl<<"Determinant: "<<determinant(m1)<<endl;
    
    return 0;
}
