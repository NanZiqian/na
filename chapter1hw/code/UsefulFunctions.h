#include<iostream>
#define EPS 1e-12
using namespace std;

int sgn(double x){
    if(abs(x) < EPS)
        return 0;
    return (x>0) ? 1 : -1;
}

double rem(double a,double b){
    int k=(int)(a/b); //a/b的整数部分 k
	double r=a-b*k;	//求出余数   a=kb+r
    return r;
}