#include"Function.h"
#include<vector>

using namespace std;

class NewtonInterpolation{
    public:
    NewtonInterpolation(Function &F,vector<double> &interpolating_points):interpolating_points(interpolating_points){
        if (interpolating_points.size() == 0)
            return;
        Calc_divided_difference(F);
    }

    void change_FunctionAndPoints(Function &F,vector<double> &vector_x){
        interpolating_points = vector_x;
        Calc_divided_difference(F);
    }

    double estimate(double x){
        int n = interpolating_points.size()-1;
        double result = m_parameters[n];
        for(int i=n-1;i>=0;i--){
            result *= (x-interpolating_points[i]);
            result += m_parameters[i];
        }
        return result;
    }

    void print_parameters(){
        for(int i=0;i<m_parameters.size();i++)
            cout<<"f[x0,...,x"<<i<<"]: "<<m_parameters[i]<<endl;
    }

    vector<double> get_parameters(){
        return m_parameters;
    }

    private:
    void Calc_divided_difference(Function &F){
        m_parameters.clear();
        int n = interpolating_points.size()-1;
        for(int i=0;i<=n;i++)
            m_parameters.push_back(F.evaluate(interpolating_points[i]));
        
        for(int i=1;i<=n;i++){
            for(int j=n;j>=i;j--){
                m_parameters[j] = (m_parameters[j]-m_parameters[j-1])/(interpolating_points[j]-interpolating_points[j-i]);
                //cout << "round " << i << " para["<< j <<"]"<<": " << m_parameters[j] << endl;
            }
        }
    }

    vector<double> interpolating_points;
    vector<double> m_parameters;
};