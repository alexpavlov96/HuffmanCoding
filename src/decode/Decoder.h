#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>

#include "DecoderHelper.h"
#include "../common/HuffmanHeader.h"

class Decoder
{
public:
    void decode(const std::string& encodedFileName, const std::string& decodedFileName);

private:
    std::ifstream _file;
    std::ofstream _decoded;

    HuffmanHeader _header;
    DecoderHelper _helper;

    std::unordered_map<char, std::string> _codes;
    unsigned long long                    _currentCodeLenght = 0;

    void fillCodes();
    void writeToFile();
};
