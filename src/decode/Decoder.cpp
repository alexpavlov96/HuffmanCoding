#include "Decoder.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <unordered_map>
#include <vector>

#include "DecoderHelper.h"
#include "../common/common.h"
#include "../common/helpers.h"
#include "../common/HuffmanHeader.h"

using namespace std;

// Заполнение _codes
void Decoder::fillCodes()
{
    auto&       codesSizes = _header.codesSizes;
    std::string currentCode;
    size_t      currentIndex       = 0;
    size_t      currentDigitOfCode = 0;

    for (const auto& code : _header.codes)
    {
        for (size_t currentOffset = 0; currentOffset < bitsInByte; currentOffset++)
        {
            if ((code >> currentOffset) & 1)
                currentCode += "1";
            else
                currentCode += "0";
            if (++currentDigitOfCode >= codesSizes[currentIndex])
            {
                _codes[_header.symbols[currentIndex]] = std::move(currentCode);
                currentDigitOfCode                    = 0;
                if (++currentIndex >= codesSizes.size())
                    break;
            }
        }
    }

    if (!currentCode.empty())
        _codes[_header.symbols[currentIndex]] = std::move(currentCode);
}

void Decoder::writeToFile()
{
    _helper.buildTree(_codes);

    vector<char> buffer(bufferSize);
    vector<char> writeBuffer(bufferSize);
    size_t       writeBufferIndex = 0;

    while (!_file.eof())
    {
        readBytes(_file, buffer);
        std::streamsize s = _file.gcount();

        for (int i = 0; i < s; i++)
        {
            unsigned char codedSequence = buffer[i];

            auto   digitsLeft   = _header.codeLength - _currentCodeLenght;
            size_t digitsToRead = (digitsLeft < bitsInByte) ? digitsLeft : bitsInByte;
            _currentCodeLenght += digitsToRead;
            string code = _helper.getCodeFromNumber(codedSequence, digitsToRead);

            for (char c : code)
            {
                _helper.iterate(c == '0');
                if (_helper.currentIsLeaf())
                {
                    writeBuffer[writeBufferIndex++] = _helper.currentCharacter();
                    if (writeBufferIndex == bufferSize)
                    {
                        writeBytes(_decoded, writeBuffer);
                        writeBufferIndex = 0;
                    }
                    _helper.setCurrentToRoot();
                }
            }
        }
    }

    if (writeBufferIndex > 0)
    {
        writeBytes(_decoded, writeBuffer, writeBufferIndex);
    }
}

void Decoder::decode(const std::string& encodedFileName, const std::string& decodedFileName)
{
    _file.open(encodedFileName, ios::binary);
    _decoded.open(decodedFileName, ios::binary);

    if (!_file.is_open() || !_decoded.is_open())
    {
        cout << "decode: error (file not opened)\n";
        return;
    }

    if (_file.peek() == std::ifstream::traits_type::eof())
    {
        return;
    }

    _file >> _header;
    fillCodes();
    writeToFile();
}
