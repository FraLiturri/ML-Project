#ifndef demiurge // Checks if unit isn't defined;
#define demiurge // Define unit;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

#include "activation_functions.hpp"
#include "/home/calisse/Eigen/Eigen/Dense"

using namespace std;
using namespace Eigen;

vector<MatrixXd> weights; // i-th component is the weights matrix of i-th and i+1-th layer;
vector<VectorXd> outputs; // i-th component is the output (with weights) of i-the layer;
VectorXd units_output;    // auxiliary vector;
vector<VectorXd> next_inputs;

//! Demiurge class: the Creator;
class Demiurge
{
public:
    int in_units, out_units, hidden_layers;
    int rows, cols;
    vector<int> hidden_and_out_units;

    Demiurge(int inputs_units, vector<int> hidden_units, int output_units)
    {
        in_units = inputs_units;
        out_units = output_units;
        hidden_and_out_units = hidden_units;
        hidden_and_out_units.push_back(output_units); // Adds output's units to vector;
        hidden_layers = hidden_units.size();

        for (int i = 0; i < hidden_layers + 2; i++) // This cycle creates weights matrices;
        {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // Defining seed for different random numbers;
            srand(seed);

            i == 0 ? cols = in_units : cols = hidden_and_out_units[i - 1];              // Paying attention to first layer (input);
            i == hidden_layers + 1 ? rows = out_units : rows = hidden_and_out_units[i]; // Paying attention to last layer (output);

            MatrixXd weight = MatrixXd::NullaryExpr(rows, cols, []()
                                                    { return Eigen::internal::random<double>(-1, 1); });
            weight.col(0).setConstant(1); //! Bias terms (Check);
            if (i != hidden_layers + 1)
            {
                weights.push_back(weight);
            }

            // Storing weights;
        }
    };
};

#endif