#ifndef OLYMPIAD_TEST_GENERATOR_UTILS_H
#define OLYMPIAD_TEST_GENERATOR_UTILS_H

#include <random>
#include <vector>

class Utils {
 public:
  Utils();
  bool getRandomBool();
  int getRandomInt(int minValue, int maxValue);
  int64_t getRandomInt64(int64_t minValue, int64_t maxValue);
  std::vector<int> getShuffledSequence(int size, int startFrom = 1);
  std::vector<std::pair<int, int>> getTree(int nodeCount, int startIndexFrom = 1);
  std::vector<std::pair<int, int>> getGraph(int nodeCount, int edgeCount, int startIndexFrom = 1);
  std::vector<std::pair<int, int>> getConnectedGraph(int nodeCount, int edgeCount, int startIndexFrom = 1);

 private:
  std::vector<std::pair<int, int>>
  addEdgesToGraph(const std::vector<std::pair<int, int>>& edges, int nodeCount, int totalEdgeCount,
                  int startIndexFrom = 1);
  std::default_random_engine generator;
};

#endif //OLYMPIAD_TEST_GENERATOR_UTILS_H
