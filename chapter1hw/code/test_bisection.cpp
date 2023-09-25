#include"EquationSolver.h"

using namespace std;

/// @brief x \in [0,pi/2]
class function1:public Function{
public:
    double getvalue(double x){
        if (x == 0){
            cout << "function1 divided by 0!" << endl;
            return 1;
        }
        return 1/x-tan(x);
    }
    double getderivative(double x){
        return 0;
    }
};

/// @brief x \in [0,1]
class function2:public Function{
public:
    double getvalue(double x){
        if (x == 0){
            cout << "function2 divided by 0!" << endl;
            return 1;
        }
        return 1/x-pow(2,x);
    }
    double getderivative(double x){
        return 0;
    }
};

/// @brief x \in [1,3]
class function3:public Function{
public:
    double getvalue(double x){
        return pow(2,-x)+pow(LN,x)+2*cos(x)-6;
    }
    double getderivative(double x){
        return 0;
    }
};

/// @brief x \in [0,4]
class function4:public Function{
public:
    double getvalue(double x){
        return (x*x*x+4*x*x+3*x+5)/(2*x*x*x-9*x*x+18*x-2);
    }
    double getderivative(double x){
        return 0;
    }
};

int main(){
    function1 f1;
    function2 f2;
    function3 f3;
    function4 f4;
    Bisection bisection_solver;
    OutputOfBisection* output_f1=bisection_solver.solve(f1,0.001,Pi/2-0.001,1e+4,1e-12,1e-12);
    OutputOfBisection* output_f2=bisection_solver.solve(f2,0.001,1,1e+4,1e-12,1e-12);
    OutputOfBisection* output_f3=bisection_solver.solve(f3,1,3,1e+4,1e-12,1e-12);
    OutputOfBisection* output_f4=bisection_solver.solve(f4,0.12,4,1e+4,1e-12,1e-12);
    cout << "f1:" << endl;
    output_f1->print_output();
    cout << "f2:" << endl;
    output_f2->print_output();
    cout << "f3:" << endl;
    output_f3->print_output();
    cout << "f4:" << endl;
    output_f4->print_output();
    delete output_f1;
    delete output_f2;
    delete output_f3;

    return 0;
}