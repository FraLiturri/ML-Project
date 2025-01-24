#ifndef demiurge // Checks if unit isn't defined;
#define demiurge // Define unit;

#include "lib.hpp"
#include "activation_functions.hpp"

#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace std;
using namespace Eigen;

vector<MatrixXd> weights; // i-th component is the weights matrix of i-th and i+1-th layer;
vector<VectorXd> outputs; // i-th component is the output (with weights) of i-the layer;
vector<VectorXd> next_inputs, biases;

vector<MatrixXd> prev_updates; // necessary for training: Nesterov;
vector<MatrixXd> V_t, M_t;     // neceessary for Adam training;

vector<int> hidden_and_out_units, counters;
VectorXd units_output, bias; // auxiliar vector;

int first_units, last_units;

//! Demiurge class: the Creator;
class Demiurge
{
public:
    int in_units, out_units, hidden_layers, rows, cols;
    Demiurge(int input_units, vector<int> hidden_units, int output_units)
    {
        // Storing some important info about NN;
        in_units = input_units;
        out_units = output_units;

        hidden_and_out_units = hidden_units;
        hidden_and_out_units.push_back(output_units); // Adds output's units to vector;
        hidden_layers = hidden_units.size();

        first_units = input_units;
        last_units = output_units;

        for (int i = 0; i < hidden_layers + 2; i++) // This cycle creates weights matrices;
        {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // Defining seed for different random numbers;
            srand(seed);

            i == 0 ? cols = in_units : cols = hidden_and_out_units[i - 1];              // Paying attention to first layer (input);
            i == hidden_layers + 1 ? rows = out_units : rows = hidden_and_out_units[i]; // Paying attention to last layer (output);

            MatrixXd weight = MatrixXd::NullaryExpr(rows, cols, []()
                                                    { return Eigen::internal::random<double>(-0.1, 0.1); });
            MatrixXd ghost = MatrixXd::NullaryExpr(rows, cols, []()
                                                   { return Eigen::internal::random<double>(0, 0); });
            MatrixXd m_aux = MatrixXd::NullaryExpr(rows, cols, []()
                                                   { return Eigen::internal::random<double>(0, 0); });
            MatrixXd v_aux = MatrixXd::NullaryExpr(rows, cols, []()
                                                   { return Eigen::internal::random<double>(0, 0); });

            bias.conservativeResize(rows); 
            bias.setConstant(1); 

            if (i != hidden_layers + 1)
            {
                weights.push_back(weight);
                prev_updates.push_back(ghost);
                V_t.push_back(v_aux);
                M_t.push_back(m_aux);
                counters.push_back(0);
                biases.push_back(bias); 
            }
        }
    };
};

#endif