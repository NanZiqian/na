#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

class Function{
    public:
    /// @brief nth derivative of f(x), if n=0, return f(x)
    /// @param n 
    /// @param x 
    /// @return 
    virtual double evaluate(int n,double x)=0;
};

class HermiteInterpolation{
    public:
    /// @brief initialize the Hermite interpolation
    /// @param F f(x), f'(x), f''(x),...
    /// @param interpolating_points [order,x0],[order,x1],...
    HermiteInterpolation(Function *F,vector<pair<int,double>> &interpolating_points):m_interpolating_points(interpolating_points),m_F(F){
        if (m_interpolating_points.size() == 0)
            return;
        Calc_divided_difference();
    }
    ~HermiteInterpolation(){
        if(m_F!=nullptr)
            delete m_F;
    }

    void change_FunctionAndPoints(Function *F,vector<pair<int,double>> &vector_x,int funtion_changed=1){
        if(funtion_changed){
            if(m_F!=nullptr)
                delete m_F;
            m_F = F;
        }
        m_interpolating_points = vector_x;
        Calc_divided_difference();
    }

    double estimate(int order,double x){
        if(order == 0){
            int n = m_parameters.size()-1;
            double result = m_parameters[n];
            //cout << result << endl;
            for(int i=n-1;i>=0;i--){
                int j = find(i);
                result *= (x-m_interpolating_points[j].second);
                result += m_parameters[i];
                //cout << result << endl;
            }
            return result;
        }else if(order == 1){
            double result = estimate(0,x+0.01)-estimate(0,x);
            return result/0.01;
        }
    }

    void print_parameters(){
        for(int i=0;i<m_parameters.size();i++)
            cout<<"f[x0,...,x"<<i<<"]: "<<m_parameters[i]<<endl;
    }

    vector<double> get_parameters(){
        return m_parameters;
    }

    /// @brief only check f(x0),f(x1),..., not f'(x0),f'(x1),...
    void check_correctness(){
        int correct = 1;
        double result,exact;
        for(int i=0;i<m_interpolating_points.size();i++){
            result = estimate(0,m_interpolating_points[i].second);
            exact = m_F->evaluate(0,m_interpolating_points[i].second);
            if (abs(result-exact)>1e-10){
                cout << "Error: f(x"<<i<<") = "<<result<<" != "<<exact<<endl;
                correct = 0;
            }
        }
        if (correct)
            cout << "Correct!" << endl;
    }

    private:
    /// @brief 
    /// @param m_interpolating_points, vector of [order,x0],[order,x1],...
    /// @param m_F has the data of f(x), f'(x), f''(x),...
    /// @return m_parameters
    void Calc_divided_difference(){
        //prefix[i] = sum_{j=0}^{i-1} n_j + i
        prefix = {0};
        for(int i=1;i<m_interpolating_points.size();i++){
            //m_interpolating_points[i-1].first is n_i-1
            prefix.push_back(prefix[i-1]+m_interpolating_points[i-1].first+1);
        }

        m_parameters.clear();
        //n+1 is the size of parameters
        //m_interpolating_points.size()-1 is the size of prefix or m_interpolating_points 
        int n = prefix[m_interpolating_points.size()-1]+m_interpolating_points[m_interpolating_points.size()-1].first;
        m_parameters.resize(n+1);
        for(int i=0;i<=n;i++){
            for(int ii=n;ii>=i;ii--){
                int j = find(ii);
                if(i <= m_interpolating_points[j].first && (ii >= prefix[j] && ii <= prefix[j] + m_interpolating_points[j].first)){
                    m_parameters[ii] = m_F->evaluate(i,m_interpolating_points[j].second)/factorial(i);
                }
                else{
                    m_parameters[ii] = (m_parameters[ii]-m_parameters[ii-1])/(m_interpolating_points[j].second-m_interpolating_points[j].first);
                }
            }
        }
    }

    /// @brief find j such that x is in [prefix[j],prefix[j+1])
    int find(int x){
        for(int i=0;i<prefix.size();i++){
            if (x<prefix[i])
                return i-1;
        }
        return prefix.size()-1;
    }

    int factorial(int n){
        if(n==0)
            return 1;
        int factorial = 1;
        for(int i = 1; i <=n; ++i)
        {
            factorial *= i;
        }
        return factorial;
    }
    

    vector<pair<int,double>> m_interpolating_points;
    vector<int> prefix;
    vector<double> m_parameters;
    Function *m_F;
};