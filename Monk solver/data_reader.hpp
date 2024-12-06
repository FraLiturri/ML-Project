#ifndef data_reader
#define data_reader

#include "lib.hpp"
#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace std;
using namespace Eigen;

void FillData(const string fileinput, VectorXd &resultsVector, vector<VectorXd> &Inputs)
{
    string line; // declaring the std::string that will act as a placeholder for each line of the file
    ifstream myfile_in(fileinput);
    vector<double> Placeholder(6);
    VectorXd PlaceholderConverter;
    vector<double> Results;

    if (myfile_in.is_open())
    {
        while (getline(myfile_in, line))
        {
            istringstream iss{line};
            vector<string> words // we make a vector of words rather than chars
                {
                    istream_iterator<string>(iss),
                    istream_iterator<string>()};

            Results.push_back(stoi(words[0]));
            for (int ss = 1; ss < words.size() - 1; ss++)
            {
                Placeholder.push_back(stoi(words[ss]));
            }
            PlaceholderConverter = Map<VectorXd>(Placeholder.data(), Placeholder.size());
            Inputs.push_back(PlaceholderConverter);
            Placeholder.clear();
        }
    }

    resultsVector.resize(Results.size());
    for (size_t i = 0; i < Results.size(); ++i)
    {
        resultsVector[i] = Results[i];
    }
}

#endif