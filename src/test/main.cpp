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
	std::string folderName = "../../testing";
    {
        std::vector<std::string> inputFileNames = {
            folderName + "/input1.txt",
            folderName + "/input2.txt",
            folderName + "/input3.txt",
            folderName + "/input4.txt",
            folderName + "/input5.txt",
            folderName + "/input6.txt"
        };

        HuffmanTest test("TEST 1", inputFileNames, true);
    }

    {
        std::vector<std::string> inputFileNames = { folderName + "/big.1" };
        HuffmanTest              test("TEST 2", inputFileNames, true);
    }

    return 0;
}
