#include"Newton interpolation.h"
#include<fstream>
#include<map>
using namespace std;

class young_leaves:public Function{
    public:
    double evaluate(double x){
        map<int,double> eval;
        eval[0] = 6.67;
        eval[6] = 17.3;
        eval[10] = 42.7;
        eval[13] = 37.3;
        eval[17] = 30.1;
        eval[20] = 29.3;
        eval[28] = 28.7;
        if(eval.find(x)!=eval.end())
            return eval[x];
        else{
            cout << "Error in young_leaves: x is not in the domain of the function." << endl;
            return 0;
        }

    }
};

class old_leaves:public Function{
    public:
    double evaluate(double x){
        map<int,double> eval;
        eval[0] = 6.67;
        eval[6] = 16.1;
        eval[10] = 18.9;
        eval[13] = 15.0;
        eval[17] = 10.6;
        eval[20] = 9.44;
        eval[28] = 8.897;
        if(eval.find(x)!=eval.end())
            return eval[x];
        else{
            cout << "Error in old_leaves: x is not in the domain of the function." << endl;
            return 0;
        }

    }
};

int main(){
    vector<double> vector_x,parameters;
    young_leaves *f1 = new young_leaves() ;
    old_leaves *f2 = new old_leaves() ;
    vector<Function*> f = {f1,f2};
    // seven points interpolation
    NewtonInterpolation NI(nullptr,vector_x);
    
    ofstream fout("E.txt",ios::out);
    vector_x = {0,6,10,13,17,20,28};
    for(int i=0;i<2;i++){
        NI.change_FunctionAndPoints(f[i],vector_x,1);
        NI.check_correctness();
        parameters = NI.get_parameters();
        for(int i=0;i<parameters.size();i++)
            fout << parameters[i] << " ";
        fout << endl;
    }
    fout.close();
    
    return 0;

}