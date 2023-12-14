#include"Spline.h"

using namespace std;

int main(){
    D1S32Spline spline("test_D1S32.txt");
    double ln5 = spline(5);
    cout << "ln5: " << ln5 << endl;
    //fout coefficents to python
    return 0;
}