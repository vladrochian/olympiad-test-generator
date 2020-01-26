#ifndef OLYMPIAD_TEST_GENERATOR_GENERATOR_H
#define OLYMPIAD_TEST_GENERATOR_GENERATOR_H

#include <fstream>
#include <string>
#include <vector>

template<class InputParameters> class Generator {
 public:
  explicit Generator(std::string problemName, std::string directory)
      : problemName(std::move(problemName)), directory(std::move(directory)) {
  }

  virtual void generate(const std::vector<InputParameters>& testParameters) const final {
    int numberOfTests = static_cast<int>(testParameters.size());
    for (int i = 0; i < numberOfTests; ++i) {
      std::string inputPath = directory + "/" + getInputFileName(i);
      std::string okPath = directory + "/" + getOkFileName(i);
      generateInput(std::ofstream(inputPath), testParameters[i]);
      solve(std::ifstream(inputPath), std::ofstream(okPath));
    }
  }

 protected:
  virtual std::string getInputFileName(int index) {
    return std::to_string(index) + "-" + problemName + ".in";
  }

  virtual std::string getOkFileName(int index) {
    return std::to_string(index) + "-" + problemName + ".ok";
  }

  virtual void generateInput(std::ofstream& inputFile, const InputParameters& inputParameters) = 0;

  virtual void solve(std::ifstream& input, std::ofstream& output) = 0;

 private:
  std::string problemName;
  std::string directory;
};

#endif //OLYMPIAD_TEST_GENERATOR_GENERATOR_H
