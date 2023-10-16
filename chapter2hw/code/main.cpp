#include"Newton interpolation.h"

using namespace std;

class function:public Function{
    public:
    double evaluate(double x){
        return 1/(1+x*x);
    }
};

int main(){
    vector<double> vector_x;
}