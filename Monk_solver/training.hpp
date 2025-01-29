#ifndef training
#define training

#include "layer.hpp"
#include "demiurge.hpp"
#include "activation_functions.hpp"

#include <any>
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

#include "eigen_path.hpp"

using namespace std;
using namespace Eigen;

VectorXd delta, net_t, net;
vector<VectorXd> storer;
MatrixXd update, auxiliar, prev_weight;

double grad_max, grad_min; // max and min of gradient for R-prop;
double delta_k = 0;        // auxiliar double;
int i, size;               // Runs over wieghts matrices;

VectorXd net_calculator(int layer_number) // Calculates net function;
{
    net = weights[layer_number - 1] * outputs[layer_number - 1];
    return net;
};

void Hidden_Layer::BackPropagation(variant<double, VectorXd> d, double eta, double alpha = 0, double lambda = 0)
{
    i = weights.size();
    delta.setZero();
    while (i > 0)
    {
        prev_weight = weights[i - 1]; // For Tikhonov regularization;
        if (i == weights.size())
        {
            func_choiser(function_strings[i - 1]);
            net_t = net_calculator(i);

            if (holds_alternative<double>(d)) // Checks if d is a double;
            {
                delta.conservativeResize(1); // resizes delta to the correct dimension to avoid problems in Eigen's Matrix*VectorXd operations;
                delta_k = (get<double>(d) - outputs[i][0]) * der_act_func(net_t[0]);
                delta[0] = delta_k; // Storing;
            }

            else if (holds_alternative<VectorXd>(d)) // Checks if d is a VectorXd;
            {
                for (int k = 0; k < get<VectorXd>(d).size(); k++)
                {
                    delta.conservativeResize(k + 1);
                    delta_k = (get<VectorXd>(d)[k] - outputs[i][k]) * der_act_func(net_t[k]);
                    delta[k] = delta_k;
                }
            }
            else
            {
                throw runtime_error("Backpropagation accepts only double or VectorXd as first input.");
            }

            if (prev_updates[0](0, 0) == 0) // The first element is 0 only at initialization;
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight; // update to the weights;
            }
            else
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight + alpha * prev_updates[i - 1];
            }

            weights[i - 1] = weights[i - 1] + update;

            prev_updates[i - 1] = update; // storing update for the next training epoch;
            storer.push_back(delta);
        }

        else
        {
            net_t = net_calculator(i);
            delta = weights[i].transpose() * delta;
            func_choiser(function_strings[i - 1]);

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

            prev_updates[i - 1] = update;
            storer.push_back(delta);
        }
        i--;
    };
}
void Hidden_Layer::RandomTraining(variant<double, VectorXd> d, double eta, double alpha = 0, double lambda = 0) // Equal to BP, training only in the last layer;
{
    i = weights.size();
    delta.setZero();

    func_choiser(function_strings[i - 1]);
    net_t = net_calculator(i);

    if (holds_alternative<double>(d))
    {
        for (int k = 0; k < 1; k++)
        {
            delta.conservativeResize(k + 1);
            delta_k = (get<double>(d) - outputs[i][k]) * der_act_func(net_t[k]);
            delta[k] = delta_k;
        }
    }
    else if (holds_alternative<VectorXd>(d))
    {
        for (int k = 0; k < get<VectorXd>(d).size(); k++)
        {
            delta.conservativeResize(k + 1);
            delta_k = (get<VectorXd>(d)[k] - outputs[i][k]) * der_act_func(net_t[k]);
            delta[k] = delta_k;
        }
    }
    else
    {
        throw runtime_error("Backpropagation accepts only double or VectorXd as first input.");
    }

    update = delta * outputs[i - 1].transpose();
    weights[i - 1] = weights[i - 1] + eta * update;
}

#endif