#ifndef OLYMPIAD_TEST_GENERATOR_UTILS_H
#define OLYMPIAD_TEST_GENERATOR_UTILS_H

#include <random>
#include <string>
#include <vector>

struct CharType {
  static const uint_fast8_t LOWER = 1u;
  static const uint_fast8_t UPPER = 2u;
  static const uint_fast8_t DIGIT = 4u;
};

class Utils {
 public:
  Utils();
  bool getRandomBool();
  int getRandomInt(int minValue, int maxValue);
  int64_t getRandomInt64(int64_t minValue, int64_t maxValue);
  char getRandomChar(uint_fast8_t charTypeMask = CharType::LOWER);
  std::string getRandomString(int length, uint_fast8_t charTypeMask = CharType::LOWER);
  std::vector<int> getShuffledSequence(int size, int startFrom = 1);
  std::vector<std::pair<int, int>> getTree(int nodeCount, int startIndexFrom = 1);
  std::vector<std::pair<int, int>> getGraph(int nodeCount, int edgeCount, int startIndexFrom = 1);
  std::vector<std::pair<int, int>> getConnectedGraph(int nodeCount, int edgeCount, int startIndexFrom = 1);

 private:
  std::vector<std::pair<int, int>>
  addEdgesToGraph(const std::vector<std::pair<int, int>>& edges, int nodeCount, int totalEdgeCount,
                  int startIndexFrom);
  std::default_random_engine generator;
};

#endif //OLYMPIAD_TEST_GENERATOR_UTILS_H
