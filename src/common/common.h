/*********************************************************
 *
 * Common types and variables
 *
 *********************************************************/

#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>

constexpr size_t bufferSize = 1024 * 1024;
constexpr size_t bitsInByte = 8;
constexpr size_t bitsInChar = 256;

using codesMap_t     = std::unordered_map<char, std::string>;
using codePair_t     = std::pair<char, std::string>;
using encodedData_t  = unsigned char;
using frequencyMap_t = std::unordered_map<char, unsigned long long>;
