#ifndef activation_functions
#define activation_functions

#include <cmath>
#include <string>
#include <iostream>

using namespace std;

double leaky_coeff = 0.1;

// Defining activation functions and their derivatives (needed for Backpropagation);
double sigmoid(double x)
{
    return 1 / (double)(1 + exp(-x)); // Is "a" needed? (e^-ax);
}
double sigmoid_der(double x)
{
    return sigmoid(x) * (1 - sigmoid(x));
}

double linear(double x)
{
    return x;
}
double linear_der(double x)
{
    return 1;
}

double threshold(double x)
{
    double threshold;
    x > 0 ? threshold = 1 : threshold = 0;
    return threshold;
}
double threshold_der(double x)
{
    return 0;
}

double relu(double x)
{
    double relu_res;
    x <= 0 ? relu_res = 0 : relu_res = x;
    return relu_res;
}
double relu_der(double x)
{
    double relu_res;
    x <= 0 ? relu_res = 0 : relu_res = 1;
    return relu_res;
}

double tangent(double x)
{
    return tanh(x);
}
double tan_der(double x)
{
    double res = 1 / (double)cosh(x);
    return res * res;
}

double leaky_relu(double x)
{
    double res;
    x <= 0 ? res = leaky_coeff *x : res = x;
    return res;
}
double leaky_der(double x)
{
    double der_res;
    x <= 0 ? der_res = leaky_coeff : der_res = 1;
    return der_res;
}

double elu(double x)
{
    double res;
    x > 0 ? res = x : res = exp(x) - 1;
    return res;
}
double der_elu(double x)
{
    double res_der;
    x > 0 ? res_der = 1 : res_der = exp(x);
    return res_der;
}

// Defining pointer to activation function(s) and derivative(s);
double (*act_func)(double);     // pointer to f;
double (*der_act_func)(double); // pointer to f';

// Choosing activation function and its derivative;
void func_choiser(std::string choice)
{
    if (choice == "sigmoid")
    {
        act_func = sigmoid;
        der_act_func = sigmoid_der;
    }
    else if (choice == "linear")
    {
        act_func = linear;
        der_act_func = linear_der;
    }
    else if (choice == "threshold")
    {
        act_func = threshold;
        der_act_func = threshold_der;
    }
    else if (choice == "relu")
    {
        act_func = relu;
        der_act_func = relu_der;
    }
    else if (choice == "tanh")
    {
        act_func = tangent;
        der_act_func = tan_der;
    }
    else if (choice == "leaky_relu")
    {
        act_func = leaky_relu;
        der_act_func = leaky_der;
    }
    else if (choice == "elu")
    {
        act_func = elu;
        der_act_func = elu;
    }
    else
    {
        cout << "\nChoice unavailable.\n"
                  << endl;
    }
}

#endif