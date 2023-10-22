#include"Hermite interpolation.h"
using namespace std;

class function1 : public Function{
public:
    double evaluate(int n,double x){
        if(n == 0)
            return x*x*x*x*x*x*x;
        else if(n == 1)
            return 7*x*x*x*x*x*x;
        else if(n == 2)
            return 42*x*x*x*x*x;
        else if(n == 3)
            return 210*x*x*x*x;
        else if(n == 4)
            return 840*x*x*x;
        else if(n == 5)
            return 2520*x*x;
        else if(n == 6)
            return 5040*x;
        else if(n == 7)
            return 5040;
        else{
            return 0;
        }
    }
};

int main(){
    vector<double> parameters;
    vector<pair<int,double>> vector_x;
    vector_x = {{0,0},{2,1},{1,2}};
    function1 *f = new function1() ;
    HermiteInterpolation HI(f,vector_x);
    HI.print_parameters();
    return 0;
}