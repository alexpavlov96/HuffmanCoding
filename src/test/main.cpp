#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <sstream>
#include <unordered_map>
#include <vector>

#include <queue>

#include "HuffmanTest.h"
#include "TimeMeasurer.h"

using namespace std;

#include <chrono>
#include <thread>

int main(int argc, char** argv)
{
    {
        std::vector<std::string> inputFileNames = {
            "D://work/testing/input1.txt",
            "D://work/testing/input2.txt",
            "D://work/testing/input3.txt",
            "D://work/testing/input4.txt",
            "D://work/testing/input5.txt",
            "D://work/testing/input6.txt"
        };

        HuffmanTest test("TEST 1", inputFileNames, true);
    }

    {
        std::vector<std::string> inputFileNames = { "D://work/testing/big.exe" };
        HuffmanTest              test("TEST 2", inputFileNames, true);
    }

    return 0;
}
