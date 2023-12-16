#include"Spline.h"

using namespace std;

int main(){
    D1B32Spline B32("C_B32.txt");

    vector<double> x;
    x.resize(100);
    int n = 100;
    //x = linspace(1,11,n)
    for(int i=0;i<n;i++){
        x[i] = 1+i*10.0/(n-1);
        //cout << "x[i] = " << x[i] << endl;
    }

    B32.fout_eval(x);
    return 0;
}