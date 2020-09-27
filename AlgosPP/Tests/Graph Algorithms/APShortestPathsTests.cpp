#include "../../src/Graph Algorithms/BreadthFirstSearch.h"
#include "../../src/Graph Algorithms/DepthFirstSearch.h"
#include "../../src/Graph Algorithms/Graph.h"
#include "../../src/Graph Algorithms/TopologicalSort.h"
#include "../../src/Graph Algorithms/StronglyConnectedComponents.h"
#include "../../src/Graph Algorithms/PrimsMST.h"
#include "../../src/Graph Algorithms/BellmanFord.h"
#include "../../src/Graph Algorithms/Dijkstras.h"
#include "../../src/Graph Algorithms/FloydWarshall.h"
#include "../../src/Graph Algorithms/JohnsonAllPairs.h"

#include "gtest/gtest.h"

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <chrono>
#include <ctime>

namespace algospp {

class AllPairsShortestPathsTesting : public ::testing::Test {
	Graph* g = nullptr;
protected:

	AllPairsShortestPathsTesting() {

	}
	~AllPairsShortestPathsTesting() override {

	}
	void SetUp() override {

	}
	void TearDown() override {

	}

public:

	void CreateRandomDirGraph(unsigned long long numVertices, unsigned long long numEdges, bool isDir = true, bool useRandomWeights = true) {
		if (g != nullptr)
			delete g;
		g = new Graph(numVertices, numEdges, isDir, useRandomWeights);
	}


	bool FWJohnsonEquivalent() {
		auto fwShortestMatrix = FloydWarshall(*g);
		auto japShortestMatrix = JohnsonAllPairs(*g);
		for (int i = 0; i < fwShortestMatrix->size(); ++i) {
			for (int j = 0; j < (*fwShortestMatrix)[0].size(); ++j) {
				if ((*fwShortestMatrix)[i][j] != (*japShortestMatrix)[i][j])
					return false;
			}
		}
		return true;
	}
	
	bool FloydBellmanFordEquivalent() {
		auto fwShortestMatrix = FloydWarshall(*g);
		for (int i = 0; i < fwShortestMatrix->size(); ++i) {
			bool noCycles = BellmanFord(*g, (*g)[i]);
			if (!noCycles)
				return false;
			for (int j = 0; j < (*fwShortestMatrix)[0].size(); ++j) {
				if ((*fwShortestMatrix)[i][j] != (*g)[j]->pathLength)
					return false;
			}
		}
		return true;
	}

	bool JohnsonAllPairsBellmanFordEquivalent() {
		auto fwShortestMatrix = FloydWarshall(*g);
		for (int i = 0; i < fwShortestMatrix->size(); ++i) {
			bool noCycles = BellmanFord(*g, (*g)[i]);
			if (!noCycles)
				return false;
			for (int j = 0; j < (*fwShortestMatrix)[0].size(); ++j) {
				if ((*fwShortestMatrix)[i][j] != (*g)[j]->pathLength)
					return false;
			}
		}
		return true;
	}
};

TEST_F(AllPairsShortestPathsTesting, JohnsonFloydWarshall_EquivalentTest) {
	int n = pow(10, 2);
	CreateRandomDirGraph(n, n, true);
	EXPECT_TRUE(FWJohnsonEquivalent());
}

TEST_F(AllPairsShortestPathsTesting, FloydWarshallBellmanFord_EquivalentTest) {
	int n = pow(10,2);
	CreateRandomDirGraph(n, n, true);
	EXPECT_TRUE(FloydBellmanFordEquivalent());
}

TEST_F(AllPairsShortestPathsTesting, JohnsonAllPairsBellmanFord_EquivalentTest) {
	int n = pow(10,2);
	CreateRandomDirGraph(n, n, true);
	EXPECT_TRUE(JohnsonAllPairsBellmanFordEquivalent());
}
}//algospp