#include"EquationSolver.h"

using namespace std;

/// @brief x0=0,x1=Pi/2
class function1:public Function{
public:
    double getvalue(double x){
        return sin(x/2)-1;
    }
    double getderivative(double x){
        cout << "error function1: derivative not written!" << endl;
        return 1;
    }
};

/// @brief x0=1.x1=1.4
class function2:public Function{
public:
    double getvalue(double x){
        if (abs(rem((x-Pi/2),Pi)) < EPS){
            cout << "function2: beyond the Domain of tanx!" << endl;
            return 1;
        }
        return pow(LN,x)-tan(x);
    }
    double getderivative(double x){
        cout << "error function2: derivative not written!" << endl;
        return 1;
    }
};

/// @brief x0=0,x1=-0.5
class function3:public Function{
public:
    double getvalue(double x){
        return x*x*x-12*x*x+3*x+1;
    }
    double getderivative(double x){
        cout << "error function3: derivative not written!" << endl;
        return 1;
    }
};

int main(){
    function1 f1;
    function2 f2;
    function3 f3;
    Secant secant_solver;
    OutputOfSecant* output_f1 = secant_solver.solve(f1,0,Pi/2,1e+4,1e-12,1e-12);
    OutputOfSecant* output_f2 = secant_solver.solve(f2,1,1.4,1e+3,1e-12,1e-12);
    OutputOfSecant* output_f3 = secant_solver.solve(f3,0,-0.5,1e+4,1e-12,1e-12);

    cout << "f1:" << endl;
    output_f1->print_output();
    cout << "f2:" << endl;
    output_f2->print_output();
    cout << "f3:" << endl;
    output_f3->print_output();
    delete output_f1;
    delete output_f2;

    return 0;
}
