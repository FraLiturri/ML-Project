#ifndef training
#define training

#include "layer.hpp"
#include "demiurge.hpp"
#include "activation_functions.hpp"
#include "eigen_path.hpp"

#include <variant>
#include <any>
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <cmath>

using namespace std;
using namespace Eigen;

VectorXd delta, net_t, net, vec_aux;
vector<VectorXd> storer;
MatrixXd update, auxiliar, gradient, gradient_square, sqrt_v, M_hat, V_hat;

double delta_k; // auxiliar double;
int i, size;

double beta_1 = 0.9, beta_2 = 0.999, epsilon = 1e-8; // for Adam optimizer;

VectorXd net_calculator(int layer_number)
{
    net = weights[layer_number - 1] * outputs[layer_number - 1];
    return net;
};

void Hidden_Layer::BackPropagation(variant<double, VectorXd> d, double eta, double alpha = 0, double lambda = 0)
{
    i = weights.size();
    while (i > 0)
    {
        if (i == weights.size())
        {
            func_choiser(function_strings[i - 1]);
            net_t = net_calculator(i);

            if (holds_alternative<double>(d))
            {
                delta.conservativeResize(1);
                for (int k = 0; k < 1; k++)
                {
                    delta_k = (get<double>(d) - outputs[i][k]) * der_act_func(net_t[k]);
                    delta[k] = delta_k;
                }
            }
            else if (holds_alternative<VectorXd>(d))
            {
                delta.conservativeResize(get<VectorXd>(d).size());
                for (int k = 0; k < get<VectorXd>(d).size(); k++)
                {
                    delta_k = (get<VectorXd>(d)[k] - outputs[i][k]) * der_act_func(net_t[k]);
                    delta[k] = delta_k;
                }
            }
            else
            {
                throw runtime_error("Backpropagation accepts only double or VectorXd as first input.");
            }

            if (prev_updates[0](0, 0) == 0) // The first element is 0 only at initialization; after is always 1 (bias term);
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * weights[i - 1];
            }
            else
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * weights[i - 1] + alpha * prev_updates[i - 1];
            }

            update = eta * delta * outputs[i - 1].transpose();
            weights[i - 1] = weights[i - 1] + update;

            prev_updates[i - 1] = update;
            // storer.push_back(delta);
        }

        else
        {
            net_t = net_calculator(i);
            func_choiser(function_strings[i - 1]);
            delta = weights[i].transpose() * delta;

            for (int k = 0; k < delta.size(); k++)
            {
                delta[k] = delta[k] * der_act_func(net_t[k]);
            }

            if (prev_updates[0](0, 0) == 0)
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * weights[i - 1];
            }
            else
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * weights[i - 1] + alpha * prev_updates[i - 1];
            }

            weights[i - 1] = weights[i - 1] + update;
            prev_updates[i - 1] = update;
            // storer.push_back(delta);
        }
        i--;
    };

    function_strings.clear();
    next_inputs.clear();
    units_output.setZero();
}
void Hidden_Layer::RandomTraining(variant<double, VectorXd> d, double eta, double alpha = 0, double lambda = 0)
{
    i = weights.size();
    if (i == weights.size())
    {
        func_choiser(function_strings[i - 1]);
        net_t = net_calculator(i);

        if (holds_alternative<double>(d))
        {
            delta.conservativeResize(1);
            for (int k = 0; k < 1; k++)
            {
                delta_k = (get<double>(d) - outputs[i][k]) * der_act_func(net_t[k]);
                delta[k] = delta_k;
            }
        }
        else if (holds_alternative<VectorXd>(d))
        {
            delta.conservativeResize(get<VectorXd>(d).size());
            for (int k = 0; k < get<VectorXd>(d).size(); k++)
            {
                delta_k = (get<VectorXd>(d)[k] - outputs[i][k]) * der_act_func(net_t[k]);
                delta[k] = delta_k;
            }
        }
        else
        {
            throw runtime_error("Backpropagation accepts only double or VectorXd as first input.");
        }

        if (prev_updates[0](0, 0) == 0) // The first element is 0 only at initialization; after is always 1 (bias term);
        {
            update = eta * delta * outputs[i - 1].transpose() - lambda * weights[i - 1];
        }
        else
        {
            update = eta * delta * outputs[i - 1].transpose() - lambda * weights[i - 1] + alpha * prev_updates[i - 1];
        }

        weights[i - 1] = weights[i - 1] + update;

        prev_updates[i - 1] = update;
        storer.push_back(delta);
    }

    function_strings.clear();
    next_inputs.clear();
    units_output.setZero();
}
void Hidden_Layer::Adam(variant<double, VectorXd> d, double eta, double alpha = 0, double lambda = 0)
{
    i = weights.size();

    while (i > 0)
    {
        counters[0]++;
        if (i == weights.size())
        {
            func_choiser(function_strings[i - 1]);
            net_t = net_calculator(i);
            eta = eta * sqrt(1 - pow(beta_2, counters[0])) / (double)(1 - pow(beta_1, counters[0]));

            if (holds_alternative<double>(d))
            {
                delta.conservativeResize(1);
                for (int k = 0; k < 1; k++)
                {
                    delta_k = (get<double>(d) - outputs[i][k]) * der_act_func(net_t[k]);
                    delta[k] = delta_k;
                }
            }
            else if (holds_alternative<VectorXd>(d))
            {
                delta.conservativeResize(get<VectorXd>(d).size());
                for (int k = 0; k < get<VectorXd>(d).size(); k++)
                {
                    delta_k = (get<VectorXd>(d)[k] - outputs[i][k]) * der_act_func(net_t[k]);
                    delta[k] = delta_k;
                }
            }
            else
            {
                throw runtime_error("Backpropagation accepts only double or VectorXd as first input.");
            }

            gradient = delta * outputs[i - 1].transpose();
            gradient_square = (gradient.array().square()).matrix();

            M_t[i - 1] = M_t[i - 1] * beta_1 + (1 - beta_1) * gradient;
            V_t[i - 1] = V_t[i - 1] * beta_2 + (1 - beta_2) * gradient_square;

            M_hat = M_t[i - 1] / (1 - pow(beta_1, counters[0]));
            V_hat = V_t[i - 1] / (1 - pow(beta_2, counters[0]));

            sqrt_v = (V_hat.array().sqrt()).matrix();
            sqrt_v = sqrt_v.array() + epsilon;

            update = (M_hat.array() / sqrt_v.array()).matrix();

            weights[i - 1] = weights[i - 1] + eta * update - lambda * weights[i - 1];
        }

        else
        {
            net_t = net_calculator(i);
            func_choiser(function_strings[i - 1]);

            delta = weights[i].transpose() * delta;
            eta = eta * sqrt(1 - pow(beta_2, counters[0])) / (double)(1 - pow(beta_1, counters[0]));

            for (int k = 0; k < delta.size(); k++)
            {
                delta[k] = delta[k] * der_act_func(net_t[k]);
            }

            gradient = delta * outputs[i - 1].transpose();
            gradient_square = (gradient.array().square()).matrix();

            M_t[i - 1] = M_t[i - 1] * beta_1 + (1 - beta_1) * gradient;
            V_t[i - 1] = V_t[i - 1] * beta_2 + (1 - beta_2) * gradient_square;

            M_hat = M_t[i - 1] / (1 - pow(beta_1, counters[0]));
            V_hat = V_t[i - 1] / (1 - pow(beta_2, counters[0]));

            sqrt_v = (V_hat.array().sqrt()).matrix();
            sqrt_v = sqrt_v.array() + epsilon;

            update = (M_hat.array() / sqrt_v.array()).matrix();
            weights[i - 1] = weights[i - 1] + eta * update - lambda * weights[i - 1];
        }
        i--;
    };
}

#endif