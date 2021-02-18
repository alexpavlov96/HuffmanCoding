#include "TimeMeasurer.h"

#include <iostream>

TimeMeasurer::TimeMeasurer(const std::string& name)
    : _name(name)
{
    std::cout << _name << " started" << std::endl;
    _beforeTime = std::chrono::high_resolution_clock::now();
}
TimeMeasurer::~TimeMeasurer()
{
    auto afterTime = std::chrono::high_resolution_clock::now();
    auto duration  = std::chrono::duration_cast<std::chrono::milliseconds>(afterTime - _beforeTime).count();
    std::cout << _name << " finished. Time spent: " << duration / 1000 << "." << duration % 1000 << "s" << std::endl;
}
