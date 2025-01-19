#ifndef validation
#define validation

#include "lib.hpp"
#include "demiurge.hpp"
#include "eigen_path.hpp"
using namespace std;
using namespace Eigen;

class Validation
{
public:
    void HoldOut(vector<VectorXd> &Inputs, VectorXd &resultsVector, vector<VectorXd> &val_data, VectorXd &val_res, vector<VectorXd> &test_data, VectorXd &test_res, int val_size, int test_size)
    {
        vector<VectorXd> data_aux(Inputs.begin(), Inputs.begin() + val_size);
        // VectorXd res_aux(resultsVector.data(), resultsVector.data() + val_size);
        VectorXd res_aux = resultsVector.segment(0, val_size);

        vector<VectorXd> val_data_aux(Inputs.begin() + val_size, Inputs.begin() + test_size);
        // VectorXd val_res_aux(resultsVector.data() + val_size, resultsVector.data() + test_size);
        VectorXd val_res_aux = resultsVector.segment(val_size, test_size - val_size);

        vector<VectorXd> test_data_aux(Inputs.begin() + test_size, Inputs.end());
        // VectorXd test_res_aux(resultsVector.data() + test_size, resultsVector.data() + resultsVector.size());
        VectorXd test_res_aux = resultsVector.segment(test_size, resultsVector.size() - test_size);

        Inputs = data_aux;
        resultsVector = res_aux;

        val_data = val_data_aux;
        val_res = val_res_aux;

        test_data = test_data_aux;
        test_res = test_res_aux;

        

    }
};

#endif