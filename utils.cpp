#include <algorithm>
#include <chrono>
#include <random>
#include <set>
#include "utils.h"

Utils::Utils() : generator(std::chrono::system_clock::now().time_since_epoch().count()) {
}

bool Utils::getRandomBool() {
  return getRandomInt(0, 1) == 0;
}

int Utils::getRandomInt(int minValue, int maxValue) {
  std::uniform_int_distribution<int> distribution(minValue, maxValue);
  return distribution(generator);
}

int64_t Utils::getRandomInt64(int64_t minValue, int64_t maxValue) {
  std::uniform_int_distribution<int64_t> distribution(minValue, maxValue);
  return distribution(generator);
}

char Utils::getRandomChar(char minValue, char maxValue) {
  std::uniform_int_distribution<char> distribution(minValue, maxValue);
  return distribution(generator);
}

char Utils::getRandomChar(uint_fast8_t charTypeMask) {
  int c;
  do {
    int val = getRandomInt(0, 61);
    if (val < 26) {
      c = 'a' + val;
    } else if (val < 52) {
      c = 'A' + val - 26;
    } else {
      c = '0' + val - 52;
    }
  } while (!((std::islower(c) && (charTypeMask & CharType::LOWER)) ||
             (std::isupper(c) && (charTypeMask & CharType::UPPER)) ||
             (std::isdigit(c) && (charTypeMask & CharType::DIGIT))));
  return static_cast<char>(c);
}

std::string Utils::getRandomString(int length, char minValue, char maxValue) {
  std::string s;
  for (int i = 0; i < length; ++i) {
    s += getRandomChar(minValue, maxValue);
  }
  return s;
}

std::string Utils::getRandomString(int length, uint_fast8_t charTypeMask) {
  std::string s;
  for (int i = 0; i < length; ++i) {
    s += getRandomChar(charTypeMask);
  }
  return s;
}

std::vector<int> Utils::getShuffledSequence(int size, int startFrom) {
  std::vector<int> seq(size);
  for (int i = 0; i < size; ++i) {
    seq[i] = i + startFrom;
  }
  std::shuffle(seq.begin(), seq.end(), generator);
  return seq;
}

std::vector<std::pair<int, int>> Utils::getTree(int nodeCount, int startIndexFrom) {
  std::vector<int> indices = getShuffledSequence(nodeCount, startIndexFrom);
  std::vector<std::pair<int, int>> edges;
  for (int i = 1; i < nodeCount; ++i) {
    int parent = getRandomInt(0, i - 1);
    edges.emplace_back(indices[parent], indices[i]);
  }
  std::shuffle(edges.begin(), edges.end(), generator);
  return edges;
}

std::vector<std::pair<int, int>> Utils::getGraph(int nodeCount, int edgeCount, int startIndexFrom) {
  return addEdgesToGraph(std::vector<std::pair<int, int>>(), nodeCount, edgeCount, startIndexFrom);
}

std::vector<std::pair<int, int>> Utils::getConnectedGraph(int nodeCount, int edgeCount, int startIndexFrom) {
  auto edges = getTree(nodeCount, startIndexFrom);
  return addEdgesToGraph(edges, nodeCount, edgeCount, startIndexFrom);
}

std::vector<std::pair<int, int>>
Utils::addEdgesToGraph(const std::vector<std::pair<int, int>>& edges, int nodeCount, int totalEdgeCount,
                       int startIndexFrom) {
  std::set<std::pair<int, int>> edgeSet;
  for (auto edge : edges) {
    if (edge.first > edge.second) {
      std::swap(edge.first, edge.second);
    }
    edgeSet.insert(edge);
  }
  while (static_cast<int>(edgeSet.size()) < totalEdgeCount) {
    int x = getRandomInt(0, nodeCount - 1) + startIndexFrom;
    int y = getRandomInt(0, nodeCount - 1) + startIndexFrom;
    if (x > y) {
      std::swap(x, y);
    }
    edgeSet.emplace(x, y);
  }
  std::vector<std::pair<int, int>> edgeList(edgeSet.begin(), edgeSet.end());
  std::shuffle(edgeList.begin(), edgeList.end(), generator);
  for (auto& edge : edgeList) {
    if (getRandomBool()) {
      std::swap(edge.first, edge.second);
    }
  }
  return edgeList;
}
