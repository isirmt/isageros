#pragma once
#include "PositionVector.hpp"
#include "Color255.hpp"
#include <string>

class ApplicationPreference
{
public:
    static const std::string applicationName;
    static const PosVec windowSize;
    static const Color255 defaultWorldColor;
};
