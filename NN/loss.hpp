#ifndef loss
#define loss

#include "lib.hpp"
#include <iomanip>
#include <variant>
#include <cmath>
#include "eigen_path.hpp"

using namespace std;
using namespace Eigen;

double aux;
int counter = 0;
VectorXd aux_vec;

double MSE(variant<double, VectorXd> x, variant<double, VectorXd> y)
{
    if (holds_alternative<VectorXd>(x))
    {
        aux_vec = get<VectorXd>(x) - get<VectorXd>(y);
        aux = pow(aux_vec.norm(), 2);
    }
    else if (holds_alternative<double>(x))
    {
        aux = pow(get<double>(x) - get<double>(y), 2);
    }
    else
    {
        cerr << "Type not accepted: please try with VectorXd or double" << endl;
    }
    return aux;
}
double BCE(variant<double, VectorXd> x, variant<double, VectorXd> y)
{
    if (holds_alternative<VectorXd>(x))
    {
        aux_vec = get<VectorXd>(x) - get<VectorXd>(y);
        aux = pow(aux_vec.norm(), 2);
    }
    else if (holds_alternative<double>(x))
    {
        aux = pow(get<double>(x) - get<double>(y), 2);
    }
    else
    {
        cerr << "Type not accepted: please try with VectorXd or double" << endl;
    }
    return aux;
}
double MEE(variant<double, VectorXd> x, variant<double, VectorXd> y)
{
    if (holds_alternative<VectorXd>(x))
    {
        aux_vec = get<VectorXd>(x) - get<VectorXd>(y);
        aux = aux_vec.norm();
    }
    else if (holds_alternative<double>(x))
    {
        aux = pow(get<double>(x) - get<double>(y), 2);
        aux = pow(aux, 0.5);
    }
    else
    {
        cerr << "Type not accepted: please try with VectorXd or double" << endl;
    }
    return aux;
}

double (*choice)(variant<double, VectorXd> x, variant<double, VectorXd> y);

class Loss
{
public:
    double loss_value;
    void calculator(string loss_function, string filepath, variant<double, VectorXd> NN_outputs, variant<double, VectorXd> targets, int data_size)
    {
        counter == 0 ? loss_value = 0 : 1;
        if (loss_function == "MSE")
        {
            choice = MSE;
            loss_value += choice(NN_outputs, targets) / (double)data_size;
        }
        else if (loss_function == "BCE")
        {
            choice = BCE;
            loss_value += choice(NN_outputs, targets) / (double)data_size;
        }
        else if (loss_function == "MEE")
        {
            choice = MEE;
            loss_value += choice(NN_outputs, targets) / (double)data_size;
        }
        else
        {
            cout << "\nUnvailable choice as loss function. " << endl;
        }
        counter++;
        if (counter == data_size)
        {
            ofstream outFile(filepath, std::ios::app);
            if (outFile.is_open())
            {
                outFile << fixed << setprecision(15);
                isnan(loss_value) ? loss_value = 100 : 0;
                outFile << loss_value << endl;
                outFile.close();
            }
            else
            {
                cerr << "Impossible to open file." << filepath << endl;
            }
            counter = 0;
        }
    };
};

#endif