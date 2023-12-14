#include"Spline.h"

using namespace std;

int main(){
    for(int ii = 0;ii<=4;ii++){
        int temp=1;
        for(int i=0;i<ii;i++)
            temp*=2;
        int N = 1+5*temp;
        string filename = "A_"+to_string(N)+".txt";
        D1S32Spline spline(filename);
        spline.fout_coefficients();
    }
    return 0;
}