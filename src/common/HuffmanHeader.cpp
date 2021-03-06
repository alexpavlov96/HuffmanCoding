/*********************************************************
 *
 * HuffmanHeader
 *
 * Structure describing header format of Huffman code
 *
 *********************************************************/

#include "HuffmanHeader.h"

#include <numeric>

#include "common.h"
#include "helpers.h"

std::ifstream& operator>>(std::ifstream& file, HuffmanHeader& header)
{
    auto& symbols    = header.symbols;
    auto& codesSizes = header.codesSizes;
    auto& codes      = header.codes;

    readBytes(file, header.symbolsNum);
    size_t numberOfDifferentSymbols = ((header.symbolsNum == 0) ? bitsInChar : header.symbolsNum);

    symbols.resize(numberOfDifferentSymbols);
    codesSizes.resize(numberOfDifferentSymbols);

    readBytes(file, symbols);
    readBytes(file, codesSizes);

    size_t totalBeginCodesSize = std::accumulate(codesSizes.begin(), codesSizes.end(), 0);

    if (totalBeginCodesSize == 0 || totalBeginCodesSize > codesSizes.size() * bitsInChar)
    {
        throw std::logic_error("wrong number of codes size");
    }

    codes.resize((totalBeginCodesSize - 1) / bitsInByte + 1);
    readBytes(file, codes);

    readBytes(file, header.codeLength);
    if (header.codeLength == 0)
    {
        throw std::logic_error("wrong size of code");
    }
    return file;
}

std::ofstream& operator<<(std::ofstream& file, HuffmanHeader& header)
{
    writeBytes(file, header.symbolsNum);
    writeBytes(file, header.symbols);

    writeBytes(file, header.codesSizes);
    writeBytes(file, header.codes);

    writeBytes(file, header.codeLength);
    return file;
}
