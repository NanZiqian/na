#include"Newton interpolation.h"

using namespace std;

class function1:public Function{
    public:
    double evaluate(double x){
        return 6-9*x+3*x*(x-1)+2*x*(x-1)*(x-2);
    }
};

int main(){
    vector<double> vector_x;
    vector_x.push_back(0);
    vector_x.push_back(1);
    vector_x.push_back(2);
    vector_x.push_back(3);
    function1 f;
    NewtonInterpolation NI(f,vector_x);
    NI.print_parameters();
    // for(int i=0;i<=n;i++)
    //     cout<<NI.estimate(vector_x[i])<<endl;
    return 0;
}