#pragma once
#include <chrono>
#include <random>
#include "Constants.h"

namespace Random {
    extern std::mt19937_64 rd;
    int Rand(int l = Constants::MinVal, int r = Constants::MaxVal);
} // namespace Random