#include<iostream>
#define EPS 1e-16
using namespace std;

int sgn(double x){
    if(abs(x) < EPS)
        return 0;
    return (x>0) ? 1 : -1;
}