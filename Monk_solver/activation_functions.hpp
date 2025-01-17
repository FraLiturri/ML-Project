#ifndef activation_functions
#define activation_functions

#include <cmath>
#include <string>

using namespace std;

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
    x < 0 ? relu_res = 0 : relu_res = x;
    return relu_res;
}
double relu_der(double x)
{
    double relu_res;
    x < 0 ? relu_res = 0 : relu_res = 1;
    return relu_res;
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
    else
    {
        cout << "\nChoice unavailable.\n"
             << endl;
    }
}

#endif