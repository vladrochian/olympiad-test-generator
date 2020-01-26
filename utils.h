#ifndef OLYMPIAD_TEST_GENERATOR_UTILS_H
#define OLYMPIAD_TEST_GENERATOR_UTILS_H

#include <random>

class Utils {
 public:
  Utils();
  int getRandomInt(int minValue, int maxValue);
  int64_t getRandomInt64(int64_t minValue, int64_t maxValue);

 private:
  std::default_random_engine generator;
};

#endif //OLYMPIAD_TEST_GENERATOR_UTILS_H
