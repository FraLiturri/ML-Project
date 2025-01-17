#ifndef info
#define info

#include <iostream>
#include "layer.hpp"

Demiurge *pointer;

// Setting info to print in main.cpp;
void print_info(Demiurge *myNN)
{
    pointer = myNN;

    cout << "\nIn. units: " << pointer->in_units << endl;
    cout << "Hidden. layers: " << pointer->hidden_layers << endl;
    cout << "Hidden units: ";

    for (int k = 0; k < pointer->hidden_layers; k++)
    {
        cout << pointer->hidden_and_out_units[k] << " ";
    }

    cout << "\nOut. units: " << pointer->out_units << endl;
    cout << "\n";
}

#endif