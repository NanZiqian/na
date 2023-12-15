#include"Spline.h"

using namespace std;

int main(){
    D1B32Spline B32("C_B32.txt");

    vector<double> x;
    int n = 100;
    //x = linspace(-5,5,n)
    for(int i=0;i<n;i++)
        x[i] = -5+i*10*(n-1);
    B32.fout_eval(x);
}