#pragma once

#include <fstream>
#include <vector>

struct HuffmanHeader
{
    unsigned char              nodesSize;
    std::vector<char>          symbols;    // под символы
    std::vector<unsigned char> codesSizes; // под размеры кодов
    std::vector<unsigned char> codes;      // под коды букв подряд
    unsigned long long         codeLength = 0;
};

std::ifstream& operator>>(std::ifstream& file, HuffmanHeader& header);
std::ofstream& operator<<(std::ofstream& file, HuffmanHeader& header);
