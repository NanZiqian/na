#include<iostream>
#include<math.h>
using namespace std;


#include"Function.h"
#include"UsefulFunctions.h"

/// @brief the output of every solver
//  @param m_c: root
//  @param m_h: width of interval
//  @param m_w: f(root)
//  @param m_k: number of iteration
class OutputOfSolve{
    public:
    OutputOfSolve(double c,double h,double w, int k):m_c(c),m_h(h),m_w(w),m_k(k){};
    void print_output(){
        cout << "root: " << m_c << endl;
        cout << "width of interval: " << m_h << endl;
        cout << "number of iteration: "<< m_k << endl;
        cout << "f(root): " << m_w << endl;
    }
    double m_c;
    double m_h;
    double m_w;
    int m_k;
};

/// @brief the base class of all solver
class EquationSolver{
public:
    virtual OutputOfSolve solve(Function &f,double a,double b,int M,double delta,double epsilon)=0;
};

/// @brief bisection implementation
class Bisection:public EquationSolver{
public:
    /// @brief bisection method to solve nonlinear equation f(x)=0
    /// @param f element of class Function with method getvalue().C[a,b]
    /// @param a 
    /// @param b root alpha is in [a,b]
    /// @param M max iteration time
    /// @param delta target interval width
    /// @param epsilon target f(c)
    /// @return c--root
    OutputOfSolve solve(Function &f,double a,double b,int M,double delta,double epsilon){
        double h = b-a;
        double u = f.getvalue(a);
        //cout << "f(a) = " << u << endl;
        double c,w=0;
        int k=0;
        //make sure a or b is not the root
        if(abs(f.getvalue(a)) < epsilon )
            return OutputOfSolve(a,h,w,k);
        if(abs(f.getvalue(b)) < epsilon )
            return OutputOfSolve(b,h,w,k);
        
        for(;k<=M;k++){
            h/=2;
            c = a+h;
            if(abs(h) < delta || k==M)
                break;
            w = f.getvalue(c);
            if(abs(w)<epsilon)
                break;
            else if (sgn(w) == sgn(u))
                a = c;
        }
        
        return OutputOfSolve(c,h,w,k);
    }


};