#ifndef layer // Checks if unit isn't defined;
#define layer // Define unit;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "activation_functions.hpp"
#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense" //works
using namespace std;
using namespace Eigen;

// Defining networks variables;
const int in_units = 2;      // Number of units in input layer; //?For some reasons in. units has to be greater than 1...fix it (it's not that important)
const int out_units = 1;     // Number of units in the output layer;
const int hidden_layers = 2; // Number of hidden layers + output;

Vector<int, hidden_layers> hidden_units(1,1); // Each component represents the numbers of unit in each HIDDEN layer;
                                                        // In case of bigger networks, change to VectorXd (specifing the size);
// Creating weights matrices and output vec;
vector<MatrixXd> weights;
vector<VectorXd> outputs;
VectorXd single_output;
void weights_creator()
{
    int rows;
    int columns;
    for (int i = 0; i <= hidden_layers; i++)
    {
        i == 0 ? columns = in_units : columns = hidden_units[i - 1];    // Paying attention to first layer (input);
        i == hidden_layers ? rows = out_units : rows = hidden_units[i]; // Paying attention to last layer (output);

        MatrixXd weight = MatrixXd::NullaryExpr(rows, columns, []()
                                                { return Eigen::internal::random<double>(-1.0, 1.0); });
        weights.push_back(weight); // Storing weights;
        cout << i << " Weights matrix: " << weight << endl;
    }
}

//! Creating Layer classes;
class hidden_Layer
{
public: //! Problem to be solved: for some reasons size of inputs vector has to be specified...;
    hidden_Layer(string choosen_function, int depth, bool isOutputLayer = false)
    {
        func_choiser(choosen_function);
        isLast = isOutputLayer;
        VectorXd inputs = outputs[depth - 1]; //! Has to be checked;
        for (int k = 0; k < inputs.size(); k++)
        {
            inputs[k] = act_func(inputs[k]);
        }
        single_output = weights[depth] * inputs; // Calculating outputs vector;
        outputs.insert(outputs.begin() + depth, single_output);
        cout << depth << " hidden layer's output: "
             << single_output.transpose() << endl;
    }

    void BackPropagation() // A pointer function that returns a Layer-type;
    {
        if (isLast)
        {
            cout << "\n";
            for (int i = hidden_layers + 1; i >= 0; i--)
            {
                // Insert BP here, making i flowing from end to start in weights vector;
            }
        }
    }

private:
    bool isLast; // Defined to access isOutputlayer's value;
};

//! Input layer class;
class input_Layer // works
{
public:
    input_Layer(Vector<double, in_units> input)
    {
        single_output = weights[0] * input; // Encapsulate in a function?
        outputs.insert(outputs.begin(), single_output);

        cout << "Input layer's output: "
             << single_output.transpose()
             << endl;
    };
};

#endif