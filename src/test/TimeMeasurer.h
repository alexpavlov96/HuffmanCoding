/*********************************************************
 *
 * TimeMeasurer
 *
 * Class, measuring time of execution during it's lifetime
 *
 *********************************************************/

#pragma once

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#define MEASURE(name) TimeMeasurer measurer(name)

class TimeMeasurer
{
public:
    using time_stamp_t = decltype(std::chrono::high_resolution_clock::now());
    TimeMeasurer(const std::string& name);
    ~TimeMeasurer();

private:
    time_stamp_t _startTime;
    std::string  _name;
};
