/*********************************************************
 *
 * Encoder
 *
 * Class, encoding file using Huffman algorithm
 *
 *********************************************************/

#include "Encoder.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "../common/common.h"
#include "../common/helpers.h"

using namespace std;

/*********************************************************
 *  - reading data from file
 *  - filling frequencies of each symbol
 */
void Encoder::readFromFile()
{
    while (!_file.eof())
    {
        vector<char> buffer(bufferSize);
        readBytes(_file, buffer);
        std::streamsize readSymbols = _file.gcount();
        buffer.resize(readSymbols);
        for (int i = 0; i < readSymbols; i++)
        {
            _frequencies[buffer[i]]++;
        }
        _input.push_back(move(buffer));
    }
}

/*********************************************************
 *  filling the encoded array of data
 *  - 8-bit number represents set of bits
 *  - returns lenth of code in bits
 */
unsigned long long Encoder::fillEncodedData(std::vector<encodedData_t>& encodedData) const
{
    int                currentLength = 0;
    encodedData_t      currentNum    = 0;
    unsigned long long codeLength    = 0;

    for (const auto& buffer : _input)
    {
        for (const char& character : buffer)
        {
            auto& currentCode = _codes.at(character);

            encodedData_t currentCodeSize = currentCode.size();
            codeLength += currentCodeSize;
            for (const char& symbol : currentCode)
            {
                if (symbol == '1')
                    currentNum += (1 << currentLength);

                if (++currentLength == bitsInByte)
                {
                    currentLength = 0;
                    encodedData.push_back(currentNum);
                    currentNum = 0;
                }
            }
        }
    }

    if (currentLength != 0)
    {
        encodedData.push_back(currentNum);
    }
    return codeLength;
}

/*********************************************************
 *  filling the header of Huffman code
 */
void Encoder::fillHeader(size_t numOfSymbols, HuffmanHeader& header) const
{
    size_t        beginCodesNumber = 0;
    encodedData_t currentNumber    = 0;

    header.symbolsNum = ((numOfSymbols == bitsInChar) ? 0 : numOfSymbols);

    header.symbols.reserve(numOfSymbols);
    header.codesSizes.reserve(numOfSymbols);
    header.codes.reserve(numOfSymbols);
    for (const auto& freq : _frequencies)
    {
        header.symbols.push_back(freq.first);

        const auto&         currentCode     = _codes.at(freq.first);
        const encodedData_t currentCodeSize = currentCode.size();
        header.codesSizes.push_back(currentCodeSize);

        for (const char& symbol : currentCode)
        {
            if (symbol == '1')
            {
                currentNumber += (1 << beginCodesNumber);
            }
            if (++beginCodesNumber == bitsInByte)
            {
                header.codes.push_back(currentNumber);
                beginCodesNumber = currentNumber = 0;
            }
        }
    }
    if (beginCodesNumber != 0)
    {
        header.codes.push_back(currentNumber);
    }
}

/*********************************************************
 *  main encoding method
 *
 *  - opens files
 *  - reads symbols and fills frequencies
 *  - fills codes of symbols
 *  - writes codes to output
 */
bool Encoder::encode(const std::string& inputFileName, const std::string& encodedFileName)
{
    _file.open(inputFileName, ios::binary);
    _output.open(encodedFileName, ios::binary);

    if (!_file.is_open() || !_output.is_open())
    {
        cerr << "ERROR: file not opened\n";
        return false;
    }

    readFromFile();

    auto differentSymbolsNum = _frequencies.size();

    if (differentSymbolsNum == 0)
        return true;

    if (differentSymbolsNum > bitsInChar)
    {
        cerr << "ERROR: unexpected\n";
        return false;
    }

    _codes = _helper.fillCodes(_frequencies);

    fillHeader(differentSymbolsNum, _header);
    std::vector<encodedData_t> encodedData;
    _header.codeLength = fillEncodedData(encodedData);
    _output << _header;
    writeBytes(_output, encodedData);
    return true;
}
