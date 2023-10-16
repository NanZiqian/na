#include"Function.h"
#include<vector>

using namespace std;

class NewtonInterpolation{
    public:
    NewtonInterpolation(Function &F,vector<double> &vector_x):interpolating_points(vector_x){
        parameters = Calc_divided_difference(F,interpolating_points);
    }

    double change_FunctionAndPoints(Function &F,vector<double> &vector_x){
        interpolating_points = vector_x;
        parameters = Calc_divided_difference(F,interpolating_points);
    }

    double estimate(double x){
        // double result = parameters[0];
        // double temp = 1;
        // for(int i=1;i<parameters.size();i++){
        //     temp *= (x-interpolating_points[i-1]);
        //     result += parameters[i]*temp;
        // }
        // return result;
    }

    private:
    vector<double> Calc_divided_difference(Function &F,vector<double> &vector_x){
        // vector<double> parameters;
        // parameters.push_back(F.evaluate(vector_x[0]));
        // for(int i=1;i<vector_x.size();i++){
        //     parameters.push_back((F.evaluate(vector_x[i])-F.evaluate(vector_x[i-1]))/(vector_x[i]-vector_x[i-1]));
        // }
        // return parameters;
    }

    vector<double> interpolating_points;
    vector<double> parameters;
};