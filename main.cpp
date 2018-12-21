/*  sample main function demonstrating the working  */
#include "matrix.h"

int main(int argc, char const *argv[])
{
    freopen("in.txt", "r", stdin);

    Matrix m1(3, 3);

    cout<<"Enter matrix1: "<<endl;
    cin>>m1;
    cout<<endl<<"You entered: "<<endl<<m1;

    Matrix res = inverse(m1);
    cout<<endl<<"Resultant Matrix: "<<endl<<res<<endl;
    
    return 0;
}
