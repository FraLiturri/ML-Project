#ifndef data_reader
#define data_reader

#include "lib.hpp"
#include "demiurge.hpp"
#include "eigen_path.hpp"

#include <variant>

using namespace std;
using namespace Eigen;

void DataGetter(const string fileinput, vector<VectorXd> &Inputs, VectorXd &resultsVector) //, double splitting_index = 124)
{
    string line; // declaring the std::string that will act as a placeholder for each line of the file;
    ifstream myfile_in(fileinput);
    vector<double> Placeholder, Results;
    VectorXd PlaceholderConverter;

    if (myfile_in.is_open())
    {
        while (getline(myfile_in, line))
        {
            istringstream iss{line};
            vector<string> words // we make a vector of words rather than chars;
                {
                    istream_iterator<string>(iss),
                    istream_iterator<string>()};

            Results.push_back(stoi(words[0]));

            for (int ss = 1; ss < words.size(); ss++)
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