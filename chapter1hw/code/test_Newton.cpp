#include"EquationSolver.h"

using namespace std;

class function:public Function{
public:
    double getvalue(double x){
        if (rem((x-Pi/2),Pi) < EPS){
            cout << "function: beyond the Domain of tanx!" << endl;
            return 1;
        }
        return tan(x)-x;
    }
    double getderivative(double x){
        if(rem((x-Pi/2),Pi) < EPS){
            cout << "function derivative: beyond the Domain of 1/cosx^2!" << endl;
            return 1;
        }
        return 1.0/cos(x)/cos(x)-1;
    }
};

int main(){
    function f;
    Newton newton_solver;
    
    OutputOfNewton* output_f_1 = newton_solver.solve(f,4.5,1e+4,1e-12);
    OutputOfNewton* output_f_2 = newton_solver.solve(f,4.5,1e+4,1e-12);
    cout << "root near 4.5: " << endl;
    output_f_1->print_output();
    cout << "root near 7.7: ;" << endl;
    output_f_2->print_output();
    delete output_f_1;
    return 0;
}