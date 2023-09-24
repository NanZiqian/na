#include<iostream>

using namespace std;

class Function{
public:
    virtual double getvalue(double x)=0;
    virtual double getderivative(double x)=0;
};