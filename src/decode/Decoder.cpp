/*********************************************************
 *
 * Decoder
 *
 * Class, decoding file, compressed by Huffman algorithm
 *
 *********************************************************/

#include "Decoder.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <unordered_map>
#include <vector>

#include "../common/HuffmanHeader.h"
#include "../common/common.h"
#include "../common/helpers.h"
#include "DecoderHelper.h"

using namespace std;

/*********************************************************
 *  Filling code of each symbol
 *
 *  - transforming read vector of 8-bit numbers to code of next symbol
 *  - reading as much bits as needed according to sizes of codes
 */
codesMap_t Decoder::codesBySymbols() const
{
    auto&       codesSizes = _header.codesSizes;
    std::string currentCode;
    size_t      currentIndex       = 0; // tracking of current symbol
    size_t      currentDigitOfCode = 0; // tracking if it's time to move to next symbol

    codesMap_t codes;
    for (const auto& code : _header.codes)
    {
        for (size_t currentOffset = 0; currentOffset < bitsInByte; currentOffset++)
        {
            if ((code >> currentOffset) & 1)
                currentCode.push_back('1');
            else
                currentCode.push_back('0');
            if (++currentDigitOfCode >= codesSizes[currentIndex])
            {
                codes[_header.symbols[currentIndex]] = std::move(currentCode);
                currentDigitOfCode                   = 0;
                if (++currentIndex >= codesSizes.size())
                    break;
            }
        }
    }

    if (!currentCode.empty())
        codes[_header.symbols[currentIndex]] = std::move(currentCode);

    return codes;
}

/*********************************************************
 *  Translating input chunks to decoded chunks
 *
 *  - read data from encoded input
 *  - get codes from 8-bit numbers
 *  - iterate through the tree left (0) or right (1)
 *  - when the leaf is found, add symbol corresponding to the leaf to write buffer
 *  - continue iterating from the root again
 */
void Decoder::translate()
{
    vector<char> readBuffer(bufferSize);
    vector<char> writeBuffer(bufferSize);
    size_t       writeBufferIndex = 0;

    while (!_input.eof())
    {
        // read data from encoded input
        readBytes(_input, readBuffer);
        std::streamsize readSymbols = _input.gcount();

        for (int i = 0; i < readSymbols; i++)
        {
            encodedData_t codedSequence = readBuffer[i];

            auto   digitsLeft   = _header.codeLength - _currentCodeLenght;
            size_t digitsToRead = (digitsLeft < bitsInByte) ? digitsLeft : bitsInByte;
            _currentCodeLenght += digitsToRead;

            // get codes from 8-bit numbers
            string code = _helper.getCodeFromNumber(codedSequence, digitsToRead);

            for (char c : code)
            {
                // iterate through the tree left (0) or right (1)
                _helper.iterate(c == '0');
                // when the leaf is found, add symbol corresponding to the leaf to write buffer
                if (_helper.currentIsLeaf())
                {
                    writeBuffer[writeBufferIndex++] = _helper.currentCharacter();
                    if (writeBufferIndex == bufferSize)
                    {
                        writeBytes(_decoded, writeBuffer);
                        writeBufferIndex = 0;
                    }
                    // continue iterating from the root again
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

/*********************************************************
 *  main decoding method
 *
 *  - opens files
 *  - reads header
 *  - fills codes of symbols
 */
bool Decoder::decode(const std::string& encodedFileName, const std::string& decodedFileName)
{
    _input.open(encodedFileName, ios::binary);
    _decoded.open(decodedFileName, ios::binary);

    if (!_input.is_open() || !_decoded.is_open())
    {
        cerr << "ERROR: file not opened\n";
        return false;
    }

    // file is empty
    if (_input.peek() == std::ifstream::traits_type::eof())
    {
        return true;
    }

    try
    {
        _input >> _header;
        _helper.buildTree(codesBySymbols());
        translate();
    }
    catch (std::exception& e)
    {
        cerr << "ERROR: wrong file format\n";
        return false;
    }
    return true;
}
