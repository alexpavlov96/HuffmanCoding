#include "HuffmanHeader.h"

#include <numeric>

#include "common.h"
#include "helpers.h"

std::ifstream& operator>>(std::ifstream& file, HuffmanHeader& header)
{
    auto& symbols    = header.symbols;
    auto& codesSizes = header.codesSizes;
    auto& codes      = header.codes;

    readBytes(file, header.nodesSize);
    size_t numberOfDifferentSymbols = ((header.nodesSize == 0) ? bitsInChar : header.nodesSize);

    symbols.resize(numberOfDifferentSymbols);
    codesSizes.resize(numberOfDifferentSymbols);

    readBytes(file, symbols);
    readBytes(file, codesSizes);

    size_t totalBeginCodesSize = std::accumulate(codesSizes.begin(), codesSizes.end(), 0);

    if (totalBeginCodesSize == 0)
    {
        return file;
    }
    codes.resize((totalBeginCodesSize - 1) / bitsInByte + 1);
    readBytes(file, codes);

    readBytes(file, header.codeLength);
    return file;
}

std::ofstream& operator<<(std::ofstream& file, HuffmanHeader& header)
{
    writeBytes(file, header.nodesSize);
    writeBytes(file, header.symbols);

    writeBytes(file, header.codesSizes);
    writeBytes(file, header.codes);

    writeBytes(file, header.codeLength);
    return file;
}
