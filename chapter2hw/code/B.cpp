#include"Newton interpolation.h"

using namespace std;

class function1:public Function{
    public:
    double evaluate(double x){
        return 1/(1+x*x);
    }
};

int main(){
    vector<double> vector_x;
    function1 f;
    NewtonInterpolation NI(f,vector_x);
    for(int n = 2;n<=8;n+=2){
        vector_x.clear();
        for(int i=0;i<n;i++)
            vector_x.push_back(-5+10.0/n*i);
        NI.change_FunctionAndPoints(f,vector_x);
        //fout NI.get_parameters()
    }
    
    return 0;
}