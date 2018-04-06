#pragma once

#include <vector>

class WordInfo {
public:
    std::vector<int> chunks;
    size_t frequency;
    size_t docFrequency;
    size_t lastLocation;
};