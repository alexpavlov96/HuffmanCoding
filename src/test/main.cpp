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

int main()
{
    std::string folderName = "testing/";

    {
        std::vector<std::string> inputFileNames = {
            folderName + "input1",
            folderName + "input2",
            folderName + "input3",
            folderName + "input4",
            folderName + "input5",
            folderName + "input6"
        };

        HuffmanTest test("TEST 1", inputFileNames, true);
    }

    return 0;
}
