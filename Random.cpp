#include "Random.h"

namespace Random {
    std::mt19937_64 rd(std::chrono::steady_clock::now().time_since_epoch().count());
    int Rand() {
        return std::uniform_int_distribution<int>(Constants::MinVal, Constants::MaxVal)(rd);
    }
} // namespace