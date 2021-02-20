/*********************************************************
 *
 * HuffmanTest
 *
 * Simple test framework implementation for Huffman algorithm
 *
 *********************************************************/

#pragma once

#include <string>
#include <vector>

class HuffmanTest
{
public:
    HuffmanTest(const std::string& testName, std::vector<std::string>& inputFileNames, bool stopOnFirstFail = false);
    ~HuffmanTest();

private:
    std::string _testName;
    size_t      _failedTests     = 0;
    size_t      _currentTest     = 0;
    bool        _stopOnFirstFail = false;

    bool runTest(const std::string& inputFileName, size_t testNum) const;

    bool testEqualFiles(const std::string& inputFileName, const std::string& decodedFileName) const;
};
