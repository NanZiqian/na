#include<iostream>
#include<vector>
#include<cmath>
#define M_PI 3.14159265358979323846
using namespace std;

class Function{
    public:
    virtual double evaluate(double x)=0;
};

/// @brief Tn = 2^(n-1)x^n+..., cos((2k-1)/(2n)pi) are the n zeros
/// @param n 
/// @return 
vector<double> Chebyshev_Zeros(int n){
    vector<double> result;
    for(int i=1;i<=n;i++)
        result.push_back(cos(M_PI/n*(i-0.5)));
    return result;
}