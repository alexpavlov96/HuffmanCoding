#pragma once

#include <fstream>
#include <vector>

template <typename T>
void readBytes(std::ifstream& file, std::vector<T>& buffer, size_t bytes = 0)
{
    auto bytesToRead = (bytes == 0) ? buffer.size() : bytes;
    file.read(reinterpret_cast<char*>(buffer.data()), bytesToRead);
}

template <typename T>
void readBytes(std::ifstream& file, T& var)
{
    file.read(reinterpret_cast<char*>(&var), sizeof(var));
}

template <typename T>
void writeBytes(std::ofstream& file, std::vector<T>& buffer, size_t bytes = 0)
{
    auto bytesToWrite = (bytes == 0) ? buffer.size() : bytes;
    file.write(reinterpret_cast<char*>(buffer.data()), bytesToWrite);
}

template <typename T>
void writeBytes(std::ofstream& file, T& var)
{
    file.write(reinterpret_cast<char*>(&var), sizeof(var));
}
