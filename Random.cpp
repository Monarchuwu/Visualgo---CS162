#include "Random.h"

namespace Random {
    std::mt19937_64 rd(std::chrono::steady_clock::now().time_since_epoch().count());
    int Rand(int l, int r) {
        return std::uniform_int_distribution<int>(l, r)(rd);
    }
} // namespace