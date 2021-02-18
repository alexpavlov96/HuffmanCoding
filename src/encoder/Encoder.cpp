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

// Чтение символов из файла в _input
// Заполнение частот _frequencies
void Encoder::readFromFile()
{
    while (!_file.eof())
    {
        vector<char> buffer(bufferSize);
        readBytes(_file, buffer);
        std::streamsize s = _file.gcount();
        buffer.resize(s);
        for (int i = 0; i < s; i++)
        {
            _frequencies[buffer[i]]++;
        }
        _input.push_back(move(buffer));
    }
}

void Encoder::fillCodesToWrite()
{
    int           currentLength = 0;
    unsigned char currentNum    = 0;

    for (const auto& buffer : _input)
    {
        for (const char& character : buffer)
        {
            auto& currentCode = _codes[character];

            unsigned char currentCodeSize = currentCode.size();
            _header.codeLength += currentCodeSize;
            for (const char& symbol : currentCode)
            {
                if (symbol == '1')
                    currentNum += (1 << currentLength);

                if (++currentLength == bitsInByte)
                {
                    currentLength = 0;
                    _encodedData.push_back(currentNum);
                    //cout << "num pushed: " << (unsigned int)currentNum << endl;
                    currentNum = 0;
                }
            }
        }
    }

    if (currentLength != 0)
    {
        _encodedData.push_back(currentNum);
    }
}

void Encoder::fillHeader()
{
    size_t        beginCodesNumber = 0;
    unsigned char currentNumber    = 0;

    _header.nodesSize = ((_nodesSize == bitsInChar) ? 0 : _nodesSize);

    _header.symbols.reserve(_nodesSize);
    _header.codesSizes.reserve(_nodesSize);
    _header.codes.reserve(_nodesSize);
    for (const auto& freq : _frequencies)
    {
        _header.symbols.push_back(freq.first);

        const auto&         currentCode     = _codes[freq.first];
        const unsigned char currentCodeSize = currentCode.size();
        _header.codesSizes.push_back(currentCodeSize);

        for (const char& symbol : currentCode)
        {
            if (symbol == '1')
            {
                currentNumber += (1 << beginCodesNumber);
            }
            if (++beginCodesNumber == bitsInByte)
            {
                _header.codes.push_back(currentNumber);
                beginCodesNumber = currentNumber = 0;
            }
        }
    }
    if (beginCodesNumber != 0)
    {
        _header.codes.push_back(currentNumber);
    }
}

void Encoder::encode(const std::string& inputFileName, const std::string& encodedFileName)
{
    _file.open(inputFileName, ios::binary);

    if (!_file.is_open())
    {
        cout << "encode: error (file not opened)\n";
        return;
    }

    _output.open(encodedFileName, ios::binary);

    if (!_output.is_open())
    {
        cout << "encode: error (file not opened)\n";
        return;
    }

    readFromFile();

    _nodesSize = _frequencies.size();

    if (_nodesSize == 0)
        return;

    if (_nodesSize > bitsInChar)
    {
        cout << "ERROR: too much symbols\n";
        return;
    }

    _codes = _helper.fillCodes(_frequencies);

    fillHeader();
    fillCodesToWrite();
    _output << _header;
    writeBytes(_output, _encodedData);
}
