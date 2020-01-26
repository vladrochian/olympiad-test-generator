#ifndef OLYMPIAD_TEST_GENERATOR_GENERATOR_H
#define OLYMPIAD_TEST_GENERATOR_GENERATOR_H

#include <fstream>
#include <string>
#include <vector>

template<class TestParameters> class Generator {
 public:
  virtual void generate(const std::vector<TestParameters>& testParameters) const final {
    int numberOfTests = static_cast<int>(testParameters.size());
    for (int i = 0; i < numberOfTests; ++i) {
      std::string inputPath = directory + "/" + getInputFileName(i);
      std::string okPath = directory + "/" + getOkFileName(i);
      std::ofstream inputFile(inputPath);
      generateInput(inputFile, testParameters[i]);
      inputFile.close();
      if (generateOkFiles) {
        std::ifstream input(inputPath);
        std::ofstream output(okPath);
        solve(input, output);
      }
    }
  }

 protected:
  explicit Generator(std::string problemName, std::string directory, bool generateOkFiles)
      : problemName(std::move(problemName)), directory(std::move(directory)), generateOkFiles(generateOkFiles) {
  }

  /**
   * The pattern for input file names
   * @param index  The number of the test
   * @return       Generated file name
   */
  virtual std::string getInputFileName(int index) const {
    return std::to_string(index) + "-" + problemName + ".in";
  }

  /**
   * The pattern for ok file names
   * @param index  The number of the test
   * @return       Generated file name
   */
  virtual std::string getOkFileName(int index) const {
    return std::to_string(index) + "-" + problemName + ".ok";
  }

  /**
   *   Function for generating an input file, with respect to some constraints
   *   Overriding required
   *   @param inputFile       A stream to the generated input
   *   @param testParameters  The configuration for the current test (limits, constraints)
   */
  virtual void generateInput(std::ofstream& inputFile, const TestParameters& testParameters) const = 0;

  /**
   *   Function for generating an ok file based on an input (basically the official solution)
   *   Overriding required if generateOkFiles is set on true
   *   @param input   A stream to the input file (which was previously generated)
   *   @param output  A stream to the output file
   */
  virtual void solve(std::ifstream& input, std::ofstream& output) const {
    throw std::logic_error("Not implemented");
  }

 private:
  std::string problemName;
  std::string directory;
  bool generateOkFiles;
};

#endif //OLYMPIAD_TEST_GENERATOR_GENERATOR_H
