/*********************************************************
 *
 * Encoder
 *
 * Class, encoding file using Huffman algorithm
 *
 *********************************************************/

#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common/HuffmanHeader.h"
#include "../common/common.h"
#include "EncoderHelper.h"
#include "FrequencyNode.h"

class Encoder
{
public:
    bool encode(const std::string& inputFileName, const std::string& encodedFileName);

private:
    std::ifstream _file;
    std::ofstream _output;

    HuffmanHeader _header;
    EncoderHelper _helper;

    codesMap_t                     _codes;
    std::vector<std::vector<char>> _input;
    frequencyMap_t                 _frequencies; // frequencies by symbols

    void               readFromFile();
    void               fillHeader(size_t numOfSymbols, HuffmanHeader& header) const;
    unsigned long long fillEncodedData(std::vector<encodedData_t>& encodedData) const;
};
