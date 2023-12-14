#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "eigen-3.4.0/Eigen/Dense"

using namespace std;

/***********************************************************************
 * abstract class
 **********************************************************************/
class Spline {
public:
    Spline(){}
    ~Spline(){};
    
    //evaluate s(x)
    virtual double operator()(double x) const = 0;

    virtual double eval(double x) const = 0;

};

class Input_Condition{
    public:
    // input condition from txt, need increasing order
    Input_Condition(){}
    Input_Condition(string filename){}
    ~Input_Condition(){};
};

/***********************************************************************
 * concrete class
 **********************************************************************/

//template <int n>
//spline function of degree n,need n+1 coefficients
// class Coefficients{
//     public:
//     Coefficients(){
//         coefficients.resize(n+1);
//     }
//     //N is the number of points, N-1 is the number of intervals
//     Coefficients(int N){
//         //coefficients[i][j] means the coefficient of x^i in the jth interval
//         coefficients.resize(n+1);
//         for(int i=0;i<n+1;i++)
//             coefficients[i].resize(N-1);
//     }
//     ~Coefficients();
//     double operator[](int i) const{
//         return coefficients[i];
//     }
//     vector<vector<double> > coefficients; 
// };

class D1S32Input_Condition: public Input_Condition{
    public:
    D1S32Input_Condition(){}
    D1S32Input_Condition(string filename){
        ifstream fin(filename);
        fin>>N;

        points.resize(2);
        points[0].resize(N);
        points[1].resize(N);

        //read data from txt file
        for(int i=0;i<N;i++){
            fin>>points[0][i]>>points[1][i];
        }
        //read additional condition
        fin>>m1>>mN;
        fin.close();

        // cout << "number of points N = " << N << endl;
        // cout << "points:" << endl;
        // for(int i=0;i<N;i++){
        //     cout << "x: " << points[0][i] << " y: " << points[1][i] << endl;
        // }
    }
    ~D1S32Input_Condition(){}

    // number of points
    int N;
    // x: points[0] f(x): points[1]
    vector< vector<double> > points;
    // additional condition
    double m1,mN;
};




class D1S32Spline: public Spline{
public:
    D1S32Spline(){}
    D1S32Spline(string filename){
        input_condition = D1S32Input_Condition(filename);
        int n = 3,N = input_condition.N;

        divided_difference.resize(N+1);

        //nth order, n+1 coefficients for each polynomial,N-1 intervals
        //coefficients[i][j] means the coefficient of x^j in the ith interval,k<=n-2
        coefficients.resize(N-1);
        for(int i=0;i<N-1;i++)
            coefficients[i].resize(n+1);

        Calc_divided_difference();
        Calc_coefficients();
        //check_correctness();
    }
    ~D1S32Spline(){}

    //evaluate s(x)
    double operator()(double x) const{
        //x \in [ x[interval],x[interval+1] ]
        int interval = judge_interval(x);
        double xi = input_condition.points[0][interval];
        //cout << "for x = " << x << "select xi = " << xi << endl;
        double result = 0;
        for(int i=0;i<=3;i++){
            result += coefficients[interval][i]*pow(x-xi,i);
            //cout << i << "th coefficient of interval " << interval << " is " << coefficients[interval][i] << endl;
        }
        return result;
    }
    double eval(double x) const{
        return (*this)(x);
    }

    void fout_coefficients(string filename="D1S32_coefficients_") const{
        int N = input_condition.N;
        filename += to_string(N);
        filename += ".txt";
        ofstream fout(filename);
        for(int i=0;i<N-1;i++){
            //ith interval
            for(int j=0;j<=3;j++){
                //x^j 's coefficient
                fout  << coefficients[i][j] << " ";
            }
            fout << endl;
        }
    }

private:
    void Calc_divided_difference(){
        int N = input_condition.N;
        divided_difference[0] = input_condition.m1;
        divided_difference[N] = input_condition.mN;
        // cout << "divided_difference[0] = m1" << divided_difference[0] << endl;
        // cout << "divided_difference[N] = mN" << divided_difference[N] << endl;
        
        for(int i=1;i<N;i++){
            divided_difference[i] = (input_condition.points[1][i]-input_condition.points[1][i-1])/(input_condition.points[0][i]-input_condition.points[0][i-1]);
        }
        divided_difference[N] = (divided_difference[N]-divided_difference[N-1])/(input_condition.points[0][N-1]-input_condition.points[0][N-2]);
        for(int i=N-1;i>=2;i--){
            divided_difference[i] = (divided_difference[i]-divided_difference[i-1])/(input_condition.points[0][i]-input_condition.points[0][i-2]);
        }
        divided_difference[1] = (divided_difference[1]-divided_difference[0])/(input_condition.points[0][1]-input_condition.points[0][0]);

        //6*[1]~6*[N] is vec b
        
    }

    void Calc_coefficients(){
        int N = input_condition.N;
        Eigen::Matrix<double, Eigen::Dynamic,Eigen::Dynamic> A;
        A.setZero(N,N);

        A(0,0) = 2;
        A(0,1) = 1;
        A(N-1,N-1) = 2;
        A(N-1,N-2) = 1;
        //mu_2~mu_{N-1}, lambda_2~lambda_{N-1}
        for(int i=1;i<N-1;i++){
            A(i,i) = 2;
            // A(i,i-1) = mu_{i+1} = (x_{i+1}-x_i)/(x_{i+2}-x_i), x_i = input_condition.points[0][i-1]
            double mu = input_condition.points[0][i]-input_condition.points[0][i-1];
            mu /= input_condition.points[0][i+1]-input_condition.points[0][i-1];
            A(i,i-1) = mu;
            // A(i,i+1) = lambda_{i+1} = (x_{i+2}-x_{i+1})/(x_{i+2}-x_i), x_i = input_condition.points[0][i-1]
            double lambda = input_condition.points[0][i+1]-input_condition.points[0][i];
            lambda /= input_condition.points[0][i+1]-input_condition.points[0][i-1];
            A(i,i+1) = lambda;
        }

        Eigen::Matrix<double, Eigen::Dynamic,1> b;
        b.resize(N,1);
        for(int i=1;i<=N;i++){
            b(i-1,0) = 6*divided_difference[i];
        }
        Eigen::Matrix<double, Eigen::Dynamic,1> M;
        M.resize(N,1);
        M = A.colPivHouseholderQr().solve(b);

        // cout << "A:" << endl;
        // cout << A << endl;
        // cout << "b:" << endl;
        // cout << b << endl;
        //cout << "M:" << endl;
        //cout << M << endl;

        //coefficients[i][j] means the coefficient of x^j in the ith interval,k<=n-2
        for(int i=0;i<N-1;i++){
            double xi = input_condition.points[0][i];
            double xi1 = input_condition.points[0][i+1];
            double yi = input_condition.points[1][i];
            double yi1 = input_condition.points[1][i+1];
            coefficients[i][0] = yi;
            coefficients[i][1] = (yi1-yi)/(xi1-xi);
            coefficients[i][1] -= (M(i+1,0)+2*M(i,0))*(xi1-xi)/6;
            coefficients[i][2] = M(i,0)/2;
            coefficients[i][3] = (M(i+1,0)-M(i,0))/(6*(xi1-xi));
        }
    }

    int judge_interval(double x) const{
        int N = input_condition.N;
        for(int i=0;i<N-1;i++){
            if(x>=input_condition.points[0][i]&&x<=input_condition.points[0][i+1])
                return i;
        }
        cout << "x is not in the interval" << endl;
        return -1;
    }

    void check_correctness(){
        int N = input_condition.N;
        for(int i=0;i<N-1;i++){
            double x = input_condition.points[0][i];
            double y = input_condition.points[1][i];
            double result = (*this)(x);
            cout << "x: " << x << " y: " << y << " result: " << result << endl;
        }
    }

    D1S32Input_Condition input_condition;
    //spline function of degree n,need n+1 coefficients
    vector<vector<double> > coefficients;
    vector<double> divided_difference;
};





class D2S32Input_Condition: public Input_Condition{
    public:
    D2S32Input_Condition(){}
    ~D2S32Input_Condition(){}
};

class D2S32Spline: public Spline{
    public:
};