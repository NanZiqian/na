#include<iostream>
#include<math.h>
using namespace std;





//------------------------------includes, defines and abstract class
#include"Function.h"
#include"UsefulFunctions.h"
#define Pi 3.1415926
#define LN 2.71828182846
class OutputOfSolve{
    public:
    virtual ~OutputOfSolve()=0;
    virtual void print_output()=0;
};
OutputOfSolve::~OutputOfSolve(){}

/// @brief the base class of all solver
class EquationSolver{
public:
    //virtual ~EquationSolver()=0;
    virtual OutputOfSolve* solve()=0;//(Function &f,double a,double b,int M,double delta,double epsilon)
};
//---------------------------------------end





//----------------------------------------implementations of solvers
//--------------------------------bisection
/// @brief the output of bisection
//  @param m_c: root
//  @param m_h: width of interval
//  @param m_w: f(root)
//  @param m_k: number of iteration
class OutputOfBisection:public OutputOfSolve{
    public:
    OutputOfBisection(double c,double h,double w, int k):m_c(c),m_h(h),m_w(w),m_k(k){};
    ~OutputOfBisection(){}
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

/// @brief bisection implementation
class Bisection:public EquationSolver{
public:
    ~Bisection(){
        //cout << "~Bisection" << endl;
        if(m_BisectionOutput != nullptr){
            delete m_BisectionOutput;
            m_BisectionOutput = nullptr;
        }
    }

    OutputOfBisection* solve(){return nullptr;}
    /// @brief bisection method to solve nonlinear equation f(x)=0
    /// @param f element of class Function with method getvalue().C[a,b]
    /// @param a 
    /// @param b root alpha is in [a,b]
    /// @param M max iteration time
    /// @param delta target interval width
    /// @param epsilon target f(c)
    /// @return c--root
    OutputOfBisection* solve(Function &f,double a,double b,int M,double delta,double epsilon){
        double h = b-a;
        double u = f.getvalue(a);
        //cout << "f(a) = " << u << endl;
        double c,w=0;
        int k=0;
        //make sure a or b is not the root
        if(abs(f.getvalue(a)) < epsilon ){
            m_BisectionOutput = new OutputOfBisection(a,h,w,k);
            return m_BisectionOutput;
        }
        if(abs(f.getvalue(b)) < epsilon ){
            m_BisectionOutput = new OutputOfBisection(b,h,w,k);
            return m_BisectionOutput;
        }
        
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
        m_BisectionOutput = new OutputOfBisection(c,h,w,k);
        return m_BisectionOutput;
    }

    OutputOfBisection* m_BisectionOutput;

};
//--------------------------end bisection





//--------------------------newton method
/// @brief the output of newton method
//  @param m_c: root
//  @param m_h: width of interval
//  @param m_w: f(root)
//  @param m_k: number of iteration
class OutputOfNewton:public OutputOfSolve{
    public:
    OutputOfNewton(double x,double u, int k):m_x(x),m_u(u),m_k(k){};
    ~OutputOfNewton(){}
    void print_output(){
        cout << "root: " << m_x << endl;
        cout << "f(root): " << m_u << endl;
        cout << "number of iteration: "<< m_k << endl;
    }
    double m_x;
    double m_u;
    int m_k;
};

/// @brief newton method implementation
class Newton:public EquationSolver{
public:
    ~Newton(){
        if(m_Newton != nullptr){
            delete m_Newton;
            m_Newton = nullptr;
        }
    }
    OutputOfNewton* solve(){return nullptr;}
    OutputOfNewton* solve(Function& f,double x0,int M,double epsilon){
        double x = x0;
        double u;
        int k=0;
        for(;k<=M;k++){
            u = f.getvalue(x);
            if(abs(u)<epsilon)
                break;
            x = x - u/f.getderivative(x);
        }
        m_Newton = new OutputOfNewton(x,u,k);
        return m_Newton;
    }

    OutputOfNewton* m_Newton;
};
//--------------------------end newton method





//--------------------------secant method
/// @brief the output of newton method
//  @param m_c: root
//  @param m_h: width of interval
//  @param m_w: f(root)
//  @param m_k: number of iteration
class OutputOfSecant:public OutputOfSolve{
    public:
    OutputOfSecant(double xn,double xn_1,double u, int k):m_xn(xn),m_xn_1(xn_1),m_u(u),m_k(k){};
    ~OutputOfSecant(){}
    void print_output(){
        cout << "root_n: " << m_xn << endl;
        cout << "root_n_1: " << m_xn_1 << endl;
        cout << "f(root): " << m_u << endl;
        cout << "number of iteration: "<< m_k << endl;
    }
    double m_xn,m_xn_1;
    double m_u;
    int m_k;
};

/// @brief secant method implementation
class Secant:public EquationSolver{
public:
    ~Secant(){
        if(m_secant != nullptr){
            delete m_secant;
            m_secant = nullptr;
        }
    }
    OutputOfSecant* solve(){return nullptr;}
    OutputOfSecant* solve(Function& f,double x0,double x1,int M,double delta,double epsilon){
        double xn = x1,xn_1=x0;
        double u=f.getvalue(xn),v=f.getvalue(xn_1);
        int k=2;
        double s;
        for(;k<=M;k++){
            s = (xn-xn_1)/(u-v);
            xn_1 = xn;
            v = u;
            xn = xn - u*s;
            if(abs(xn - xn_1)<delta)
                break;
            u = f.getvalue(xn);
            //cout << "iteration " << k <<": f(xk)= "<<u<<endl;
            if (abs(u)<epsilon)
                break;
        }
        m_secant = new OutputOfSecant(xn,xn_1,u,k);
        return m_secant;
    }

    OutputOfSecant* m_secant;
};
//--------------------------end secant method
//-------------------------------------end implementing