#include"EquationSolver.h"

using namespace std;

double beta1 = 11.5/180*Pi,l=89,h=49,D=55;
double A = l*sin(beta1);
double B = l*cos(beta1);
double C = (h+0.5*D)*sin(beta1)-0.5*D*tan(beta1);
double E = (h+0.5*D)*cos(beta1)-0.5*D;

class function:public Function{
public:
    double getvalue(double x){
        
        return A*sin(x)*cos(x)+B*sin(x)*sin(x)-C*cos(x)-E*sin(x);
    }
    double getderivative(double x){
        return A*cos(2*x)+B*sin(2*x)+C*sin(x)-E*cos(x);
    }
};

void a_b_c1(){
    function f;
    Newton newton_solver;
    //(a)
    OutputOfNewton* output_a = newton_solver.solve(f,33.0/180*Pi,1e+4,1e-12);
    output_a->print_output();
    delete output_a;

    //(b)
    D=30;
    C = (h+0.5*D)*sin(beta1)-0.5*D*tan(beta1);
    E = (h+0.5*D)*cos(beta1)-0.5*D;
    OutputOfNewton* output_b = newton_solver.solve(f,33.0/180*Pi,1e+4,1e-12);
    output_b->print_output();

    //(c)
    Secant secant_solver;
    OutputOfSecant* output_c = secant_solver.solve(f,33.0/180*Pi,50.0/180*Pi,1e+3,1e-12,1e-12);
    output_c->print_output();
}

void c2(){
    function f;
    Secant secant_solver;
    OutputOfSecant* output_c = secant_solver.solve(f,2,2.5,1e+3,1e-12,1e-12);
    output_c->print_output();

    // delete output_c;
    // secant_solver.m_secant = nullptr;
}

int main(){
    //a_b_c1();
    c2();
    return 0;
}