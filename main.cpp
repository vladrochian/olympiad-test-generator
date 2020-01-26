#include "example_generator.h"

int main() {
  ExampleGenerator generator(5);
  generator.generate({
    ExampleTestParameters(100),
    ExampleTestParameters(100),
    ExampleTestParameters(5000),
    ExampleTestParameters(1000000),
  });
  return 0;
}
