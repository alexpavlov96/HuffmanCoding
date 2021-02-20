/*********************************************************
 *
 * HuffmanHeader
 *
 * Structure describing header format of Huffman code
 *
 *********************************************************/

#pragma once

#include <fstream>
#include <vector>

#include "../common/common.h"

struct HuffmanHeader
{
    encodedData_t              symbolsNum = 0; // number of different symbols
    std::vector<char>          symbols;        // all different symbols
    std::vector<encodedData_t> codesSizes;     // amount of bits describing code of each symbol
    std::vector<encodedData_t> codes;          // all codes, describing symbols, in a row
    unsigned long long         codeLength = 0; // total length of code, representing data (in bits)
};

std::ifstream& operator>>(std::ifstream& file, HuffmanHeader& header);
std::ofstream& operator<<(std::ofstream& file, HuffmanHeader& header);
