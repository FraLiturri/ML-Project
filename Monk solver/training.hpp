#ifndef training
#define training

#include "layer.hpp"
#include "demiurge.hpp"
#include "activation_functions.hpp"

#include <iostream>
#include <vector>
#include <cmath>

#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace std;
using namespace Eigen;

VectorXd delta, net_t, net;
vector<VectorXd> storer;
MatrixXd update, auxiliar, prev_weight;

double delta_k = 0; // auxiliar double;
int i;              // Runs over wieghts matrices;

VectorXd net_calculator(int layer_number)
{
    net = weights[layer_number - 1] * outputs[layer_number - 1];
    return net;
};

void Hidden_Layer::BackPropagation(double d, double eta, double alpha, double lambda)
{
    i = weights.size();
    while (i > 0)
    {
        prev_weight = weights[i - 1]; // For Tikhonov regularization;

        if (i == weights.size())
        {
            delta.setZero();
            func_choiser(function_strings[i - 1]);
            net_t = net_calculator(i);

            for (int k = 0; k < 1; k++)
            {
                delta.conservativeResize(k + 1);
                delta_k = (d - outputs[i][k]) * der_act_func(net_t[k]);
                delta[k] = delta_k;
            }

            if (prev_updates[0](0, 0) == 0)
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight;
            }
            else
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight + alpha * prev_updates[i - 1];
            }

            weights[i - 1] = weights[i - 1] + update;
            weights[i - 1].col(0).setConstant(1);
            prev_updates[i - 1] = update;
            storer.push_back(delta);
        }

        else
        {
            delta.setZero();
            func_choiser(function_strings[i - 1]);

            auxiliar = weights[i];
            net_t = net_calculator(i);

            delta = storer[weights.size() - (i + 1)].transpose() * auxiliar;

            for (int k = 0; k < delta.size(); k++)
            {
                delta[k] = delta[k] * der_act_func(net_t[k]);
            }

            if (prev_updates[0](0, 0) == 0)
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight;
            }
            else
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight + alpha * prev_updates[i - 1];
            }

            weights[i - 1] = weights[i - 1] + update;
            weights[i - 1].col(0).setConstant(1);
            prev_updates[i - 1] = update;

            storer.push_back(delta);
        }

        if (i == 1)
        {
            outputs.clear();
            next_inputs.clear();
            function_strings.clear();
            storer.clear();
        }
        i--;
    };
}

void Hidden_Layer::RandomTraining(double d, double eta, double alpha = 0, double lambda = 0)
{
    i = weights.size();
    delta.setZero();

    func_choiser(function_strings[i - 1]);
    net_t = net_calculator(i);

    for (int k = 0; k < 1; k++)
    {
        delta.conservativeResize(k + 1);
        delta_k = (d - outputs[i][k]) * der_act_func(net_t[k]);
        delta[k] = delta_k;
    }

    update = delta * outputs[i - 1].transpose();
    weights[i - 1] = weights[i - 1] + eta * update;
    weights[i - 1].col(0).setConstant(1);

    function_strings.clear();
    outputs.clear();
    next_inputs.clear();
    units_output.setZero();
}

#endif