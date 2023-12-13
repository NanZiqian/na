#include <vector>

using namespace std;

class Spline {
public:
    Spline();
    virtual  ~Spline() = 0;
    
    double operator()(double x) const;
    Input_Condition& input_condition();
};

class Input_Condition{
    public:
    Input_Condition();
    virtual ~Input_Condition() = 0;
    void setPoints(const vector<double>& x, const vector<double>& y);
};

template <int n,int N>
//spline function of degree n
//N is the number of points
class Coefficients{
    public:
    Coefficients(){
        coefficients.resize(n+1);
        for(int i=0;i<n+1;i++)
            coefficients[i].resize(N-1);
    }
    vector<vector<double>> coefficients; 
};