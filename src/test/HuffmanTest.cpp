/*********************************************************
 *
 * HuffmanTest
 *
 * Simple test framework implementation for Huffman algorithm
 *
 *********************************************************/

#include "HuffmanTest.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "../common/common.h"
#include "../decode/Decoder.h"
#include "../encode/Encoder.h"
#include "TimeMeasurer.h"

using namespace std;

HuffmanTest::HuffmanTest(const std::string& testName, std::vector<std::string>& inputFileNames, bool stopOnFirstFail)
    : _testName(testName)
{
    cout << "---- " << _testName << " ----\n" << endl;
    for (const auto& inputFileName : inputFileNames)
    {
        if (!runTest(inputFileName) && stopOnFirstFail)
            break;
    }
}

HuffmanTest::~HuffmanTest()
{
    if (_failedTests == 0)
        cout << "---- " << _testName << " PASSED ----\n" << endl;
    else
        cout << "---- " << _testName << " FAILED: " << to_string(_failedTests) << " wrong ----\n" << endl;
}

bool HuffmanTest::runTest(const std::string& inputFileName)
{
    std::string encodedFileName = inputFileName + "_enc";
    std::string decodedFileName = inputFileName + "_dec";

    cout << "----- TEST CASE " << std::to_string(++_currentTest) << " -----" << endl;
    {
        MEASURE("Encoder");
        Encoder encoder;
        encoder.encode(inputFileName, encodedFileName);
    }

    {
        MEASURE("Decoder");
        Decoder decoder;
        decoder.decode(encodedFileName, decodedFileName);
    }
    if (!test(inputFileName, decodedFileName))
    {
        _failedTests++;
        return false;
    }
    return true;
}

bool HuffmanTest::test(const std::string& inputFileName, const std::string& decodedFileName)
{
    ifstream file1(inputFileName, ios::binary | std::ifstream::ate);
    ifstream file2(decodedFileName, ios::binary | std::ifstream::ate);

    if (!file1.is_open() || !file2.is_open())
    {
        cout << "----- FAIL: file not opened -----\n" << endl;
        return false;
    }

    if (file1.tellg() != file2.tellg())
    {
        cout << "----- FAIL: different sizes -----\n" << endl;
        return false;
    }

    file1.seekg(ios::beg);
    file2.seekg(ios::beg);

    vector<char> buffer1(bufferSize);
    vector<char> buffer2(bufferSize);

    while (!file1.eof())
    {
        file1.read(buffer1.data(), buffer1.size());
        file2.read(buffer2.data(), buffer2.size());

        auto s = file1.gcount();
        for (int i = 0; i < s; i++)
        {
            if (buffer1[i] != buffer2[i])
            {
                cout << "----- FAIL: not equal -----\n" << endl;
                return false;
            }
        }
    }

    cout << "----- SUCCESS -----\n" << endl;
    return true;
}
