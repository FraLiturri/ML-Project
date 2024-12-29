#include "lib.hpp"
#include "layer.hpp"
#include "activation_functions.hpp"
#include "info.hpp"
#include "training.hpp"
#include "data_reader.hpp"
#include "loss.hpp"

#include <typeinfo>

#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace Eigen;
using namespace std;

vector<VectorXd> TrainingData, TestData, ValidationData, TrainingResults, TestResults, ValidationResults;

int training_accuracy = 0, test_accuracy = 0, validation_accuracy = 0;
double FinalResult; // auxiliary double;

int main(int argc, char *argv[]) // Add int argc, char *argv[] in parenthesis;
{
    //! Counter starts;
    auto start = chrono::high_resolution_clock::now();

    //! Demiurge blows;
    Demiurge NeuralNetwork(12, {10}, 3);  // Input units - hidden_units vector - output units;
    Demiurge *pointerNN = &NeuralNetwork; // Pointer to NeuralNetwork for print_info, avoidable if not desired;

    //! Preparing data for training (and validation) and test phase;
    CV_HoldOut("Data/Test.txt", TrainingData, TrainingResults);
    Vec2Vec("Data/prova.txt", TestData, TestResults);
    // DataGetter("Monk_data/monks-1binary.test", TestResults, TestData);

    //! Printing NN general info: can be avoided if not desired;
    print_info(pointerNN);

    //! Neural network construction;
    Input_Layer input_layer;
    Hidden_Layer first_hidden;
    Hidden_Layer output_layer;

    Loss TrainingLoss;
    Loss TestLoss;

    //! Output computing and training algorithm;
    for (int n = 0; n < atoi(argv[1]); n++)
    {
        for (int k = 0; k < /* TrainingData.size() */1; k++)
        {
            input_layer.forward_pass(TrainingData[k]);
            first_hidden.forward_pass("sigmoid", 1);
            output_layer.forward_pass("linear", 2, true);

            output_layer.BackPropagation(TrainingResults[k], 0.3, 0.001, 0.00001);
            TrainingLoss.calculator("MSE", "NN_results/training_loss.txt", outputs[weights.size()], TrainingResults[k], TrainingResults.size());
        };
    }

    //! Test;
      for (int k = 0; k < TestData.size(); k++)
     {
         input_layer.forward_pass(TestData[k]);
         first_hidden.forward_pass("sigmoid", 1);
         output_layer.forward_pass("linear", 2, true);

         TestLoss.calculator("MSE", "NN_results/test_loss.txt", outputs[weights.size()], TestResults[k], TestResults.size());
     } 

    cout << "Test loss is: " << TestLoss.last_loss << endl;

    //! Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "\nElapsed time: " << elapsed_time.count() << " seconds. \n"
         << endl;

    return 0;
}