#include"EquationSolver.h"

using namespace std;

double L =10,r=1,V=12.4;

class function:public Function{
public:
    double getvalue(double x){
        return L*(0.5*Pi*r*r-r*r*asin(x/r)-x*sqrt(r*r-x*x))-V;
    }
    double getderivative(double x){
        return -L*r/sqrt(1-x*x/r/r)-L*sqrt(r*r-x*x)-L*x*x/pow(r*r-x*x,3/2);
    }
};

int main(){
    function f;
    Bisection bisection_solver;
    OutputOfBisection* output_bisection_f=bisection_solver.solve(f,0,1,1e+4,1e-12,1e-12);
    Newton newton_solver;
    OutputOfNewton* output_newton_f = newton_solver.solve(f,0.1,1e+4,1e-12);
    Secant secant_solver;
    OutputOfSecant* output_secant_f = secant_solver.solve(f,0.1,0.2,1e+4,1e-12,1e-12);

    cout << "bisection:" << endl;
    output_bisection_f->print_output();
    cout << "newton method:" << endl;
    output_newton_f->print_output();
    cout << "secant method:" << endl;
    output_secant_f->print_output();

    cout << "f(c-0.005) = " << f.getvalue(0.166166-0.005) << endl;
    cout << "f(c+0.005) = " << f.getvalue(0.166166+0.005) << endl;

    return 0;

}