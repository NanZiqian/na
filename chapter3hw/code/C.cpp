#include"Spline.h"

using namespace std;

int main(){
    //B32
    D1B32Spline B32("C_B32.txt");

    vector<double> x;
    int n = 101;
    x.resize(n);
    //x = linspace(1,11,n)
    for(int i=0;i<n;i++){
        x[i] = 1+i*10.0/(n-1);
        //cout << "x[i] = " << x[i] << endl;
    }
    B32.fout_eval(x);

    //B21
    B21Spline B21("C_B21.txt");
    B21.fout_eval(x);

    return 0;
}