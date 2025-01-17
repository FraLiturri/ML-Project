#ifndef layer // Checks if unit isn't defined;
#define layer // Define unit;

#include "lib.hpp"
#include "activation_functions.hpp"
#include "demiurge.hpp"

#include "eigen_path.hpp"

#include <variant>

using namespace std;
using namespace Eigen;

vector<std::string> function_strings;
VectorXd inputs;

//! Input layer class;
class Input_Layer
{
public:
    void forward_pass(VectorXd input)
    {
        units_output = weights[0] * input;
        outputs.insert(outputs.begin(), input);
        next_inputs.insert(next_inputs.begin(), units_output);
    };
};

//! Creating Layer classes;
class Hidden_Layer
{
public:
    void forward_pass(string choosen_function, int depth, bool isOutputLayer = false)
    {
        func_choiser(choosen_function);
        function_strings.push_back(choosen_function);

        isLast = isOutputLayer;
        inputs = next_inputs[depth - 1]; //! Has to be checked;

        for (int k = 0; k < inputs.size(); k++)
        {
            inputs[k] = act_func(inputs[k]); // Making act_function act on input for each unit;
        }

        outputs.insert(outputs.begin() + depth, inputs);

        if (!isLast)
        {
            units_output = weights[depth] * inputs;                        // Calculating outputs vector;
            next_inputs.insert(next_inputs.begin() + depth, units_output); // Storing outputs;
        }
    }

    void RandomTraining(variant<double, VectorXd> d, double eta, double alpha, double lambda);  // Random training: in this case takes a double (d) since monk is a class. problem;
    void BackPropagation(variant<double, VectorXd> d, double eta, double alpha, double lambda); // BackProp. algorithm: in this case takes a double (d) since monk is a class. problem;
    void RMSprop(variant<double, VectorXd> d, double eta, double alpha, double lambda);         // Rprop. algorithm;

private:
    bool isLast; // Defined to access isOutputlayer's value;
};

#endif