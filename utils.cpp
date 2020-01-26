#include <chrono>
#include "utils.h"

Utils::Utils() : generator(std::chrono::system_clock::now().time_since_epoch().count()) {
}

int Utils::getRandomInt(int minValue, int maxValue) {
  std::uniform_int_distribution<int> distribution(minValue, maxValue);
  return distribution(generator);
}

int64_t Utils::getRandomInt64(int64_t minValue, int64_t maxValue) {
  std::uniform_int_distribution<int64_t> distribution(minValue, maxValue);
  return distribution(generator);
}
