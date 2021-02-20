/*********************************************************
 *
 * Decoder
 *
 * Class, decoding file, compressed by Huffman algorithm
 *
 *********************************************************/

#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>

#include "../common/HuffmanHeader.h"
#include "../common/common.h"
#include "DecoderHelper.h"

class Decoder
{
public:
    bool decode(const std::string& encodedFileName, const std::string& decodedFileName);

private:
    std::ifstream _input;   // input file descriptor
    std::ofstream _decoded; // decoded file descriptor

    HuffmanHeader _header;
    DecoderHelper _helper;

    unsigned long long _currentCodeLenght = 0;

    codesMap_t codesBySymbols() const; // filling codes of each symbol
    void       translate();
};
