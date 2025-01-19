#include "lib.hpp"
#include "layer.hpp"
#include "activation_functions.hpp"
#include "info.hpp"
#include "training.hpp"
#include "data_reader.hpp"
#include "loss.hpp"
#include "safe_writer.hpp"
#include "validation.hpp"
#include "eigen_path.hpp"


using namespace Eigen;
using namespace std;

vector<VectorXd> TrainingData, TestData, ValidationData, InternalTestData;
VectorXd TrainingResults, TestResults, ValidationResults, InternalTestResults;

int TN = 0, TP = 0, FN = 0, FP = 0;
int training_accuracy = 0, test_accuracy = 0, validation_accuracy = 0;
double FinalResult; // auxiliary double;

int main(int argc, char *argv[]) // Add int argc, char *argv[] in parenthesis;
{
    //! Counter starts;
    auto start = chrono::high_resolution_clock::now();

    ofstream("NN_results/training_loss.txt", std::ios::trunc).close();
    ofstream("NN_results/val_loss.txt", std::ios::trunc).close();
    ofstream("NN_results/test_loss.txt", std::ios::trunc).close();

    //! Demiurge blows;
    Demiurge NeuralNetwork(17, {10}, 1);  // Input units - hidden_units vector - output units;
    Demiurge *pointerNN = &NeuralNetwork; // Pointer to NeuralNetwork for print_info, avoidable if not desired;

    //! Preparing data for training (and validation) and test phase;
    DataGetter("Monk_data/monks-2binary.train", TrainingData, TrainingResults);
    DataGetter("Monk_data/monks-2binary.test", TestData, TestResults);
    cout << TrainingData.size() << " " << ValidationData.size() << endl;

    //! Splitting data for validation part;
    Validation Validator;
    Validator.HoldOut(TrainingData, TrainingResults, ValidationData, ValidationResults, InternalTestData, InternalTestResults, TrainingData.size() - 10, TrainingData.size());
    cout << TrainingData.size() << " " << ValidationData.size() << endl;

    //! Printing NN general info: can be avoided if not desired;
    print_info(pointerNN);

    //! Neural network construction;
    Input_Layer input_layer;
    Hidden_Layer first_hidden;
    Hidden_Layer output_layer;

    Loss TrainingLoss, TestLoss, ValidationLoss;

    //! Output computing and training algorithm;
    for (int n = 0; n < atoi(argv[4]); n++)
    {
        for (int k = 0; k < TrainingData.size(); k++)
        {
            input_layer.forward_pass(TrainingData[k]);
            first_hidden.forward_pass("sigmoid", 1);
            output_layer.forward_pass("sigmoid", 2, true);

            output_layer.BackPropagation(TrainingResults[k], stod(argv[1]), stod(argv[2]), stod(argv[3]));
            TrainingLoss.calculator("MSE", "NN_results/training_loss.txt", outputs[weights.size()][0], TrainingResults[k], TrainingResults.size());
            if (n == atoi(argv[4]) - 1) // Accuracy calculator;
            {
                outputs[weights.size()][0] >= 0.5 ? FinalResult = 1 : FinalResult = 0;
                FinalResult == TrainingResults[k] ? training_accuracy++ : 0;
            }
            outputs.clear();
        };
        //! Validation;
        for (int k = 0; k < ValidationData.size(); k++)
        {
            input_layer.forward_pass(ValidationData[k]);
            first_hidden.forward_pass("sigmoid", 1);
            output_layer.forward_pass("sigmoid", 2, true);

            ValidationLoss.calculator("MSE", "NN_results/val_loss.txt", outputs[weights.size()][0], ValidationResults[k], ValidationResults.size());
            if (n == atoi(argv[4]) - 1) // Accuracy calculator;
            {
                outputs[weights.size()][0] >= 0.5 ? FinalResult = 1 : FinalResult = 0;
                FinalResult == ValidationResults[k] ? validation_accuracy++ : 0;
            }
            outputs.clear();
        }
    }

    //! Test;
    for (int k = 0; k < TestData.size(); k++)
    {
        input_layer.forward_pass(TestData[k]);
        first_hidden.forward_pass("sigmoid", 1);
        output_layer.forward_pass("sigmoid", 2, true);

        outputs[weights.size()][0] >= 0.5 ? FinalResult = 1 : FinalResult = 0;
        FinalResult == TestResults[k] ? test_accuracy++ : 0;
        
        if (FinalResult == TestResults[k])
        {
            FinalResult == 1 ? TP++ : TN++;
        }
        else
        {
            FinalResult == 1 ? FP++ : FN++;
        }

        TestLoss.calculator("MSE", "NN_results/test_loss.txt", outputs[weights.size()][0], TestResults[k], TestResults.size());
    }
    cout << "Eta: " << stod(argv[1]) << "\nAlpha: " << stod(argv[2]) << "\nLambda: " << stod(argv[2]) << endl
         << endl;

    cout << "Validation accuracy: " << validation_accuracy / (double)ValidationData.size() * 100 << "% (" << validation_accuracy << "/" << (double)ValidationData.size() << ")" << endl;
    cout << "Test accuracy: " << test_accuracy / (double)TestData.size() * 100 << "% (" << test_accuracy << "/" << TestData.size() << ")" << endl;
    cout << "Test loss is: " << TestLoss.last_loss << endl;
    cout << "Val loss is: " << ValidationLoss.last_loss << endl;
    //! Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "\nElapsed time: " << elapsed_time.count() << " seconds."
         << endl;

    //! Writing data safely during parallel grid search;
    const std::string NameOfOutputFile = "grid_results.txt";
    std::ostringstream oss;
    oss << "Eta: " <<argv[1] << " Alpha: " << argv[2] << " Lambda: " << argv[3] << " Training Accuracy: " << training_accuracy / (double)TrainingData.size() << " Validation accuracy: " << validation_accuracy / (double)ValidationData.size() << " Val Loss: " << ValidationLoss.loss_value << " TP: " << TP << " FP: " << FP << " TN: " << TN << " FN: " << FN << " ";

    const std::string Information = oss.str();
    writeToFileSafely(NameOfOutputFile, Information);

    return 0;
}