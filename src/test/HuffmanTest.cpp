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
    , _stopOnFirstFail(stopOnFirstFail)
{
    cout << "---- " << _testName << " ----" << endl;
    for (const auto& inputFileName : inputFileNames)
    {
        if (!runTest(inputFileName, ++_currentTest))
        {
            _failedTests++;
            if (_stopOnFirstFail)
                break;
        }
    }
}

HuffmanTest::~HuffmanTest()
{
    if (_failedTests == 0)
        cout << "---- " << _testName << " PASSED ----\n"
             << endl;
    else
    {
        cerr << "---- " << _testName << " FAILED";
        if (!_stopOnFirstFail)
        {
            cerr << ": " << to_string(_failedTests) << "/" << to_string(_currentTest) << " wrong ----";
        }
        cerr << "\n"
             << endl;
    }
}

bool HuffmanTest::runTest(const std::string& inputFileName, size_t testNum) const
{
    std::string encodedFileName = inputFileName + "_enc";
    std::string decodedFileName = inputFileName + "_dec";

    cout << "----- TEST CASE " << std::to_string(testNum) << " -----" << endl;
    {
        MEASURE("Encoder");
        Encoder encoder;
        if (!encoder.encode(inputFileName, encodedFileName))
        {
            cerr << "Encoder failed" << endl;
            return false;
        }
    }

    {
        MEASURE("Decoder");
        Decoder decoder;
        if (!decoder.decode(encodedFileName, decodedFileName))
        {
            cerr << "Decoder failed" << endl;
            return false;
        }
    }

    return testEqualFiles(inputFileName, decodedFileName);
}

bool HuffmanTest::testEqualFiles(const std::string& inputFileName, const std::string& decodedFileName) const
{
    ifstream file1(inputFileName, ios::binary | std::ifstream::ate);
    ifstream file2(decodedFileName, ios::binary | std::ifstream::ate);

    if (!file1.is_open() || !file2.is_open())
    {
        cerr << "----- FAIL: file not opened -----\n"
             << endl;
        return false;
    }

    if (file1.tellg() != file2.tellg())
    {
        cerr << "----- FAIL: different sizes -----\n"
             << endl;
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
                cerr << "----- FAIL: not equal -----\n"
                     << endl;
                return false;
            }
        }
    }

    cout << "----- SUCCESS -----\n"
         << endl;
    return true;
}
