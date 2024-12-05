#ifndef layer // Checks if unit isn't defined;
#define layer // Define unit;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

#include "activation_functions.hpp"
#include "demiurge.hpp"

#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace std;
using namespace Eigen;

vector<std::string> function_strings;

//! Input layer class;
class Input_Layer
{
public:
    Input_Layer(VectorXd input)
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
    Hidden_Layer(string choosen_function, int depth, bool isOutputLayer = false)
    {
        func_choiser(choosen_function);
        function_strings.insert(function_strings.begin()+depth +1, choosen_function);

        isLast = isOutputLayer;
        VectorXd inputs = next_inputs[depth - 1]; //! Has to be checked;

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

    void RandomTraining(VectorXd d);  // Random training;
    void BackPropagation(VectorXd d); // BackProp. algorithm;

private:
    bool isLast; // Defined to access isOutputlayer's value;
};

#endif