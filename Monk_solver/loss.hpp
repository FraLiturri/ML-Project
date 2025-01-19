#ifndef loss
#define loss

#include "lib.hpp"

#include "eigen_path.hpp"

using namespace std;
using namespace Eigen;

double aux = 0;
int counter = 0;

double MSE(double x, double y)
{
    aux = pow((x - y), 2);
    return aux;
}
double BCE(double x, double y)
{
    return aux;
}

double (*choice)(double, double);

class Loss
{
public:
    double loss_value;
    double last_loss; 
    void calculator(string loss_function, string filepath, double NN_outputs, double targets, int data_size)
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
                outFile << loss_value << endl;
                outFile.close();
            }
            else
            {
                cerr << "Impossible to open file." << filepath << endl;
            }
            counter = 0;
            last_loss = loss_value;
        }
    };
};

#endif