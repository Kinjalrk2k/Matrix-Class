/*  sample main function demonstrating the working  */
#include "matrix.h"

int main(int argc, char const *argv[])
{
    freopen("in.txt", "r", stdin);

    Matrix m1(3, 3);

    cout<<"Enter matrix1: "<<endl;
    cin>>m1;
    cout<<endl<<"You entered: "<<endl<<m1<<endl;

    /*
    Row r[3];
    for(int i=0; i<3; i++)
        disintegrate_row(m1, r[i], i);

    r[1] = r[1] + r[0]*(-5);         
    r[2] = r[2] + r[0]*(-2);         
    r[1] = r[1]/(-11);               
    r[2] = r[2]/(-2);                
    r[1] = r[1] + r[2]*((-8.0)/11.0);
    r[0] = r[0] + r[2]*(-2);         
    r[0] = r[0] + r[1]*(-3);

    for(int i=0; i<3; i++)
        integrate_row(m1, r[i], i);    
    */

    Matrix res = rref(m1, false);

    cout<<endl<<"Resultant Matrix: "<<endl<<res<<endl;

    //cout<<endl<<m1[pair<int, int>(0,0)]<<endl;
    cout<<endl<<Rank(m1)<<endl;
    
    return 0;
}