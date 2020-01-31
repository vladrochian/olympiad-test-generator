#include "example_generator.h"
#include "example_generator_with_official_solution.h"

int main() {
  // Assuming some of the tests were already generated, we can start from test 5
  ExampleGenerator generator(5);
  /*
   *  We create tests 5 and 6 with an upper limit of 100 for the values, test 7 with an upper limit of 5000
   *  and test 8 with an upper limit of 1000000
   */
  generator.generate({
      ExampleTestParameters(100),
      ExampleTestParameters(100),
      ExampleTestParameters(5000),
      ExampleTestParameters(1000000)
  });

  // Useful when giving partial scores for nodeCount <= 1000
  DfsGenerator().generate({
      DfsConfig(1000, 2),
      DfsConfig(1000, 500),
      DfsConfig(1000, 500),
      DfsConfig(1000, 500),
      DfsConfig(100000, 200000),
      DfsConfig(100000, 200000)
  });
  return 0;
}
