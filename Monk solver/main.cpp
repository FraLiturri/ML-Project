#include "layer.hpp"
#include "activation_functions.hpp"
#include "info.hpp"
#include "training.hpp"
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

    std::string fileinput = "Monk_data/monks-1.train";
    std::string line; // declaring the std::string that will act as a placeholder for each line of the file
    std::ifstream myfile_in(fileinput);
    std::vector<int> Placeholder(6);
    std::vector<std::vector<int>> Inputs;
    std::vector<int> Results;

    if (myfile_in.is_open())
    {
        while (getline(myfile_in, line))
        {
            std::istringstream iss{line};
            std::vector<std::string> words // we make a vector of words rather than chars
                {
                    std::istream_iterator<std::string>(iss),
                    std::istream_iterator<std::string>()};
            Results.push_back(std::stoi(words[0]));
            for (int ss = 1; ss < words.size()-1; ss++)
            {
                Placeholder.push_back(std::stoi(words[ss]));
            }
            Inputs.push_back(Placeholder);
            Placeholder.clear();
        }
    }

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
