#include"Newton interpolation.h"
#include<fstream>

using namespace std;

class function1:public Function{
    public:
    double evaluate(double x){
        return 1/(1+x*x);
    }
};

int main(){
    vector<double> vector_x,parameters;
    function1 *f = new function1() ;
    NewtonInterpolation NI(f,vector_x);

    // int n = 8;
    // for(int i=0;i<=n;i++){
    //     vector_x.push_back(-5+10.0/n*i);
    //     NI.change_FunctionAndPoints(f,vector_x,0);
    // }
    //double y = NI.estimate(-5);

    ofstream fout("B.txt",ios::out);

    for(int n = 2;n<=8;n+=2){
        vector_x.clear();
        for(int i=0;i<=n;i++)
            vector_x.push_back(-5+10.0/n*i);
        NI.change_FunctionAndPoints(f,vector_x,0);
        NI.check_correctness();
        parameters = NI.get_parameters();
        fout << n << " ";
        for(int i=0;i<parameters.size();i++)
            fout << parameters[i] << " ";
        fout << endl;
    }
    fout.close();
    
    return 0;
}