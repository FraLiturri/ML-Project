#include "layer.hpp"
#include "activation_functions.hpp"
#include "info.hpp"
#include "training.hpp"
#include "data_reader.hpp"
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iterator>
#include<algorithm>
#include "/home/calisse/Eigen/Eigen/Dense"

using namespace Eigen;
using namespace std;

int main()
{
    // Counter starts;
    auto start = chrono::high_resolution_clock::now();

    std::vector<VectorXd> Inputs;
    VectorXd Results;
    std::string fileinput = "Monk_data/monks-1.train";

    FillData(fileinput,Results, Inputs);
    //! Data vector (inputs to Input_Layer);
    Vector<double, 3> data = {3.56, 4.89, 3}; // Creating data vector;
    Vector<double, 2> results = {-3.34, 2.23};

    //! Demiurge blows;
    Demiurge NeuralNetwork(3, {5, 2, 3}, 2); // input units - hidden_units vector - output units;
    Demiurge *pointerNN = &NeuralNetwork;    // pointer to NeuralNetwork;

    //! Printing NN general info:
    print_info(pointerNN);

    for (int i = 0; i < 100; i++)
    {
        
        //! Neural network construction;
        Input_Layer input_layer(data);
        Hidden_Layer first_hidden("sigmoid", 1);
        Hidden_Layer second_hidden("sigmoid", 2);
        Hidden_Layer third_hidden("threshold", 3);
        Hidden_Layer output_layer("linear", 4, true);

        //! Training algorithm;
        // output_layer.RandomTraining(results);
        output_layer.BackPropagation(results);
        // cout << "Final output: " << outputs[weights.size()].transpose() << endl;
    }

    // Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    std::cout << "Elapsed time: " << elapsed_time.count() << " seconds.\n"
              << endl;

    return 0;
}
