#ifndef OLYMPIAD_TEST_GENERATOR_EXAMPLE_GENERATOR_H
#define OLYMPIAD_TEST_GENERATOR_EXAMPLE_GENERATOR_H

#include "generator.h"

struct ExampleTestParameters {
  int maxValue;

  explicit ExampleTestParameters(int maxValue) : maxValue(maxValue) {}
};

class ExampleGenerator : public Generator<ExampleTestParameters> {
 public:
  explicit ExampleGenerator(int testIndexStart)
      : Generator<ExampleTestParameters>("sum", "sum-tests", true, true, testIndexStart) {}

 private:
  void generateInput(std::ofstream& inputFile, const ExampleTestParameters& testParameters) override {
    inputFile << utils.getRandomInt(1, testParameters.maxValue) << " "
              << utils.getRandomInt(1, testParameters.maxValue) << "\n";
  }

  void solve(std::ifstream& input, std::ofstream& output) const override {
    int a, b;
    input >> a >> b;
    output << a + b << "\n";
  }
};

#endif //OLYMPIAD_TEST_GENERATOR_EXAMPLE_GENERATOR_H
