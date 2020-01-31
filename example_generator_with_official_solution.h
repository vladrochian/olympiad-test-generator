#ifndef OLYMPIAD_TEST_GENERATOR_EXAMPLE_GENERATOR_WITH_OFFICIAL_SOLUTION_H
#define OLYMPIAD_TEST_GENERATOR_EXAMPLE_GENERATOR_WITH_OFFICIAL_SOLUTION_H

#include "generator.h"

struct DfsConfig {
  int nodeCount;
  int edgeCount;

  DfsConfig(int nodeCount, int edgeCount) : nodeCount(nodeCount), edgeCount(edgeCount) {}
};

class DfsGenerator : public Generator<DfsConfig> {
 public:
  DfsGenerator() : Generator("dfs", "dfs-tests", true, true) {}

 private:
  void generateInput(std::ofstream& inputFile, const DfsConfig& testParameters) override {
    int N = testParameters.nodeCount;
    int M = testParameters.edgeCount;
    inputFile << N << " " << M << "\n";
    auto edges = utils.getGraph(N, M);
    for (const auto& edge : edges) {
      inputFile << edge.first << " " << edge.second << "\n";
    }
  }

  /*
   *  You can put the solution inside a class in order to isolate variables and make use of per instance streams;
   *  Make sure to increase the stack memory if working with large arrays or recursion
   */
  class Solution {
    // Make all constants static
    static const int N_MAX = 100000;

    // Zero initialize all primitives (and arrays)
    int N = 0, M = 0;
    bool use[N_MAX + 1] = {};
    std::vector<int> G[N_MAX + 1];
    int numberOfComponents = 0;
    // Make sure to increase stack memory if large arrays are used

    // Declare streams as references so we can use the ones from the Generator
    std::ifstream& fin;
    std::ofstream& fout;

    void read() {
      fin >> N >> M;
      for (int i = 0; i < M; ++i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
      }
    }

    void dfs(int node) {
      use[node] = true;
      for (int son : G[node]) {
        if (!use[son]) {
          dfs(son);
        }
      }
    }

    void solve() {
      for (int i = 1; i <= N; ++i) {
        if (!use[i]) {
          ++numberOfComponents;
          dfs(i);
        }
      }
    }

    void print() {
      fout << numberOfComponents << "\n";
    }

   public:
    Solution(std::ifstream& fin, std::ofstream& fout) : fin(fin), fout(fout) {}

    // Make the main function public
    int main() {
      read();
      solve();
      print();
      return 0;
    }
  };

  // We call the main function from the solution
  void solve(std::ifstream& input, std::ofstream& output) const override {
    Solution(input, output).main();
  }
};

#endif //OLYMPIAD_TEST_GENERATOR_EXAMPLE_GENERATOR_WITH_OFFICIAL_SOLUTION_H
