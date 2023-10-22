#include"Hermite interpolation.h"
#include<map>
using namespace std;

template<typename T>
std::vector<double> linspace(T start_in, T end_in, int num_in){

    std::vector<double> linspaced;

    double start = static_cast<double>(start_in);
    double end = static_cast<double>(end_in);
    double num = static_cast<double>(num_in);

    if (num == 0) { return linspaced; }
    if (num == 1) 
    {
        linspaced.push_back(start);
        return linspaced;
    }

    double delta = (end - start) / (num - 1);

    for(int i=0; i < num-1; ++i)
    {
        linspaced.push_back(start + delta * i);
    }
    linspaced.push_back(end);
    return linspaced;
}

class car_travel:public Function{
    public:
    double evaluate(int n,double x){
        //eval[(n,x)] = f^(n)(x));
        map<pair<int,double>,double> eval;
        eval[make_pair(0,0)] = 0;
        eval[make_pair(1,0)] = 75;
        eval[make_pair(0,3)] = 225;
        eval[make_pair(1,3)] = 77;
        eval[make_pair(0,5)] = 383;
        eval[make_pair(1,5)] = 80;
        eval[make_pair(0,8)] = 623;
        eval[make_pair(1,8)] = 74;
        eval[make_pair(0,13)] = 993;
        eval[make_pair(1,13)] = 72;
        if(eval.find(make_pair(n,x))!=eval.end())
            return eval[make_pair(n,x)];
        else{
            cout << "Error in car_travel: (n,x) is not in the domain of the function." << endl;
            return 0;
        }
    }
};

int main(){
    vector<double> parameters;
    vector<pair<int,double>> vector_x;
    vector_x = {{1,0},{1,3},{1,5},{1,8},{1,13}};
    car_travel *f = new car_travel() ;
    HermiteInterpolation HI(f,vector_x);
    HI.check_correctness();
    
    //D(a)
    double v_10 = HI.estimate(1,10);
    cout << "The velocity of the car at t=10 is " << v_10 << " m/s." << endl;

    //D(b)
    std::vector<double> vec = linspace(0.0, 13.0, 1000);
    int count = 0;
    double start,v;
    int exceed = 0;
    for(int i=0;i<vec.size();i++){
        v = HI.estimate(1,vec[i]);
        // if(v > 81){
        //     cout << "The car's speed exceeds 81 at t = " << vec[i] << endl;
        // }
        if(v > 81){
            if(exceed == 0){
                start = vec[i];
                exceed = 1;
                count++;
            }
        }else if(exceed && v < 81 ){
            cout << "The car's speed exceeds 81 m/s between t = " << start << " and t = " << vec[i] << endl;
            exceed = 0;
        }else if(exceed && i == vec.size()-1 ){
            cout << "The car's speed exceeds 81 m/s between t = " << start << " and t = " << vec[i] << endl;
            exceed = 0;
        }
    }
    if(count == 0)
        cout << "The car's speed never exceeds 81 m/s." << endl;

    return 0;
}