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
    void HoldOut(vector<VectorXd> &Inputs, vector<VectorXd> &resultsVector, vector<VectorXd> &val_data, vector<VectorXd> &val_res, vector<VectorXd> &test_data, vector<VectorXd> &test_res, int val_size, int test_size)
    {
        vector<VectorXd> data_aux(Inputs.begin(), Inputs.begin() + val_size);
        vector<VectorXd> res_aux(resultsVector.begin(), resultsVector.begin() + val_size);

        vector<VectorXd> val_data_aux(Inputs.begin() + val_size, Inputs.begin() + test_size);
        vector<VectorXd> val_res_aux(resultsVector.begin() + val_size, resultsVector.begin() + test_size);

        vector<VectorXd> test_data_aux(Inputs.begin() + test_size, Inputs.end());
        vector<VectorXd> test_res_aux(resultsVector.begin() + test_size, resultsVector.end());

        Inputs = data_aux;
        resultsVector = res_aux;

        val_data = val_data_aux;
        val_res = val_res_aux;

        test_data = test_data_aux;
        test_res = test_res_aux;
    }
};

#endif