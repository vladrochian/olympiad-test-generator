#ifndef OLYMPIAD_TEST_GENERATOR_GENERATOR_H
#define OLYMPIAD_TEST_GENERATOR_GENERATOR_H

#include <fstream>
#include <string>
#include <vector>

template<class TestParameters> class Generator {
 public:
  explicit Generator(std::string problemName, std::string directory)
      : problemName(std::move(problemName)), directory(std::move(directory)) {
  }

  virtual void generate(const std::vector<TestParameters>& testParameters) const final {
    int numberOfTests = static_cast<int>(testParameters.size());
    for (int i = 0; i < numberOfTests; ++i) {
      std::string inputPath = directory + "/" + getInputFileName(i);
      std::string okPath = directory + "/" + getOkFileName(i);
      std::ofstream inputFile(inputPath);
      generateInput(inputFile, testParameters[i]);
      inputFile.close();
      std::ifstream input(inputPath);
      std::ofstream output(okPath);
      solve(input, output);
    }
  }

 protected:
  virtual std::string getInputFileName(int index) const {
    return std::to_string(index) + "-" + problemName + ".in";
  }

  virtual std::string getOkFileName(int index) const {
    return std::to_string(index) + "-" + problemName + ".ok";
  }

  virtual void generateInput(std::ofstream& inputFile, const TestParameters& testParameters) const = 0;

  virtual void solve(std::ifstream& input, std::ofstream& output) const = 0;

 private:
  std::string problemName;
  std::string directory;
};

#endif //OLYMPIAD_TEST_GENERATOR_GENERATOR_H
