#include"Spline.h"

using namespace std;

int main(){
    int N[3] = {11,41,161};


    vector<double> x;
    int n = 1001;
    x.resize(n);
    //x = linspace(0,1,n)
    for(int i=0;i<n;i++){
        x[i] = double(i)/(n-1);
        //cout << "x[i] = " << x[i] << endl;
    }

    for(int ii = 0;ii<3;ii++){
        string filename = "heart_x_"+to_string(N[ii])+".txt";
        D1S32Spline spline_x(filename);
        spline_x.fout_eval(x,"heart_x_evals_");

        filename = "heart_y_"+to_string(N[ii])+".txt";
        D1S32Spline spline_y(filename);
        spline_y.fout_eval(x,"heart_y_evals_");
    }
}