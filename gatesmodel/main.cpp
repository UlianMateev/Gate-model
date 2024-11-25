#include<vector> 
#include"parameters.h"
#include"passes.h"

int main()
{

    /*float weights1[2][2];
    float weights2[2];
    float bias[3];
    init_parametres(weights1, weights2, bias);

    std::vector<float> loss;

    new_start(weights1,weights2,bias,loss);
    best_start(loss); */

    float a[4];//array for acuracy in %
    float w1[2][2] = { {(float)-3.58206 ,(float)-2.71119},{(float)0 ,(float)0} };
    float w2[2] = { (float)0 ,(float)10.1392 };
    float b[3] = { (float)-3.78147 ,(float)0 ,(float)0 };
    test_model(w1, w2, b, a);
    accuracy(a);
    std::cin.get();
}