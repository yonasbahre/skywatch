#include <ctime>
#include <random>
#include "Utils.h"

int randInt(int min, int max) {
    static std::mt19937 eng(time(nullptr));
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(eng);
}