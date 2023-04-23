#pragma once
#include <chrono>
#include <random>
#include "Constants.h"

namespace Random {
    extern std::mt19937_64 rd;
    int Rand();
} // namespace Random