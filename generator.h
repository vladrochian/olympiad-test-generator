#ifndef OLYMPIAD_TEST_GENERATOR_GENERATOR_H
#define OLYMPIAD_TEST_GENERATOR_GENERATOR_H

#include <fstream>
#include <string>
#include <vector>
#include "utils.h"

template<class TestParameters> class Generator {
 public:
  virtual void generate(const std::vector<TestParameters>& testParameters) final {
    int numberOfTests = static_cast<int>(testParameters.size());
    for (int i = 0; i < numberOfTests; ++i) {
      std::string inputPath = directory + "/" + getInputFileName(i + testIndexStart);
      std::string okPath = directory + "/" + getOkFileName(i + testIndexStart);
      if (generateInputFiles) {
        std::ofstream inputFile(inputPath);
        generateInput(inputFile, testParameters[i]);
        inputFile.close();
      }
      if (generateOkFiles) {
        std::ifstream input(inputPath);
        std::ofstream output(okPath);
        solve(input, output);
        input.close();
        output.close();
      }
    }
  }

 protected:
  explicit Generator(std::string problemName, std::string directory, bool generateInputFiles, bool generateOkFiles,
                     int testIndexStart = 0)
      : problemName(std::move(problemName)), directory(std::move(directory)), generateInputFiles(generateInputFiles),
        generateOkFiles(generateOkFiles), utils(), testIndexStart(testIndexStart) {
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
   *   Overriding required if generateInputFiles is set
   *   @param inputFile       A stream to the generated input
   *   @param testParameters  The configuration for the current test (limits, constraints)
   */
  virtual void generateInput(std::ofstream& inputFile, const TestParameters& testParameters) {
    throw std::logic_error("generateInput function not implemented");
  }

  /**
   *   Function for generating an ok file based on an input (basically the official solution)
   *   Overriding required if generateOkFiles is set
   *   @param input   A stream to the input file (which was previously generated)
   *   @param output  A stream to the output file
   */
  virtual void solve(std::ifstream& input, std::ofstream& output) const {
    throw std::logic_error("solve function not implemented");
  }

  Utils utils;

 private:
  std::string problemName;
  std::string directory;
  bool generateInputFiles;
  bool generateOkFiles;
  int testIndexStart;
};

#endif //OLYMPIAD_TEST_GENERATOR_GENERATOR_H
