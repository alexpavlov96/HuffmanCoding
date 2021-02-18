#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <sstream>
#include <unordered_map>
#include <vector>

#include <queue>

#include "../decoder/Decoder.h"
#include "../encoder/Encoder.h"
#include "HuffmanTest.h"
#include "TimeMeasurer.h"
#include "../common/common.h"

using namespace std;

#include <chrono>
#include <thread>

int main()
{
    {
        std::vector<std::string> inputFileNames = {
            "input1.txt",
            "input2.txt",
            "input3.txt",
            "input4.txt",
            "input5.txt",
            "input6.txt"
        };

        HuffmanTest test("TEST 1", inputFileNames, true);
    }

    {
        std::vector<std::string> inputFileNames = { "D://work/testing/big.exe" };
        HuffmanTest              test("TEST 2", inputFileNames, true);
    }

    return 0;
}
