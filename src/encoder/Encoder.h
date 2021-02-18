#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "EncoderHelper.h"
#include "FrequencyNode.h"
#include "../common/HuffmanHeader.h"

class Encoder
{
public:
    void encode(const std::string& inputFileName, const std::string& encodedFileName);

private:
    std::ifstream _file;
    std::ofstream _output;

    HuffmanHeader _header;
    EncoderHelper _helper;

    std::unordered_map<char, std::string>        _codes;
    std::vector<std::vector<char>>               _input;
    std::unordered_map<char, unsigned long long> _frequencies;
    size_t                                       _nodesSize = 0;

    std::vector<unsigned char> _encodedData;

    void readFromFile();
    void fillHeader();
    void fillCodesToWrite();
};
