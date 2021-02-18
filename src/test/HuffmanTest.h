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
    size_t      _failedTests = 0;
    size_t      _currentTest = 0;

    bool runTest(const std::string& inputFileName);

    bool test(const std::string& inputFileName, const std::string& decodedFileName);
};