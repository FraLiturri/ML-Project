#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <iomanip>

std::mutex file_mutex;

void writeToFileSafely(const std::string &filename, const std::string &message)
{
    std::lock_guard<std::mutex> lock(file_mutex);
    std::ofstream file(filename, std::ios::app);

    if (file.is_open())
    {
        file << message << "\n";
    }
    else
    {
        std::cerr << "Errore nell'apertura del file." << std::endl;
    }
}