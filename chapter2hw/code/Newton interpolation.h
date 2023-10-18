#include"Function.h"
#include<vector>

using namespace std;

class NewtonInterpolation{
    public:
    NewtonInterpolation(Function *F,vector<double> &interpolating_points):m_interpolating_points(interpolating_points),m_F(F){
        if (m_interpolating_points.size() == 0)
            return;
        Calc_divided_difference();
    }
    ~NewtonInterpolation(){
        delete m_F;
    }

    void change_FunctionAndPoints(Function *F,vector<double> &vector_x,int funtion_changed=1){
        if(funtion_changed){
            delete m_F;
            m_F = F;
        }
        m_interpolating_points = vector_x;
        Calc_divided_difference();
    }

    double estimate(double x){
        int n = m_interpolating_points.size()-1;
        double result = m_parameters[n];
        for(int i=n-1;i>=0;i--){
            result *= (x-m_interpolating_points[i]);
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

    void check_correctness(){
        int correct = 1;
        double result;
        for(int i=0;i<m_interpolating_points.size();i++){
            result = estimate(m_interpolating_points[i]);
            if (abs(result-m_F->evaluate(m_interpolating_points[i]))>1e-10){
                cout << "Error: f(x"<<i<<") = "<<result<<" != "<<m_parameters[m_interpolating_points.size()-1]<<endl;
                correct = 0;
            }
        }
        if (correct)
            cout << "Correct!" << endl;
    }

    private:
    void Calc_divided_difference(){
        m_parameters.clear();
        int n = m_interpolating_points.size()-1;
        for(int i=0;i<=n;i++)
            m_parameters.push_back(m_F->evaluate(m_interpolating_points[i]));
        
        for(int i=1;i<=n;i++){
            for(int j=n;j>=i;j--){
                m_parameters[j] = (m_parameters[j]-m_parameters[j-1])/(m_interpolating_points[j]-m_interpolating_points[j-i]);
                //cout << "round " << i << " para["<< j <<"]"<<": " << m_parameters[j] << endl;
            }
        }
    }

    vector<double> m_interpolating_points;
    vector<double> m_parameters;
    Function *m_F;
};