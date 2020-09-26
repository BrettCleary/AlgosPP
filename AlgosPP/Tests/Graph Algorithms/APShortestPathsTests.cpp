#include "../../src/Graph Algorithms/BreadthFirstSearch.h"
#include "../../src/Graph Algorithms/DepthFirstSearch.h"
#include "../../src/Graph Algorithms/Graph.h"
#include "../../src/Graph Algorithms/TopologicalSort.h"
#include "../../src/Graph Algorithms/StronglyConnectedComponents.h"
#include "../../src/Graph Algorithms/PrimsMST.h"
#include "../../src/Graph Algorithms/BellmanFord.h"
#include "../../src/Graph Algorithms/Dijkstras.h"

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

	void CreateRandomDirGraph(unsigned long long numVertices, unsigned long long numEdges, bool useRandomWeights = false) {
		if (g != nullptr)
			delete g;
		g = new Graph(numVertices, numEdges, true, useRandomWeights);
	}

	void CreateRandomUndirWtdGraph(unsigned long long numVertices, unsigned long long numEdges) {
		if (g != nullptr)
			delete g;
		g = new Graph(numVertices, numEdges, false);
	}

	bool BfDijEquivalentFirstNode() {
		return BfDijEquivalent(*(g->begin()));
	}

	bool BfDijEquivalentAllNodes() {
		for (auto iter = g->begin(); iter != g->end(); ++iter) {
			if (!BfDijEquivalent(*iter))
				return false;
		}
		return true;
	}

	bool BfDijEquivalent(std::shared_ptr<Node> source) {
		BellmanFord(*g, source);
		std::vector<long long> bfPathLengths;
		for (auto iter = g->begin(); iter != g->end(); ++iter) {
			bfPathLengths.push_back((*iter)->pathLength);
		}

		Dijkstras(*g, source);
		std::vector<long long> dijPathLengths;
		for (int i = 0; i < g->size(); ++i) {
			auto gPathLength_i = (*g)[i]->pathLength;
			dijPathLengths.push_back(gPathLength_i);
		}
		for (int i = 0; i < bfPathLengths.size(); ++i) {
			if (bfPathLengths[i] != dijPathLengths[i])
				return false;
		}
		return true;
	}

	//assumes connected undir wtd graph
	bool MSTIsRepeatable() {
		if (g == nullptr)
			return false;
		std::shared_ptr<NodeWeighted> g_0 = std::static_pointer_cast<NodeWeighted>((*g)[0]);
		unsigned long long spanTreeWeight = MST_Weight_Prim(*g, g_0);
		for (auto iter = g->begin(); iter != g->end(); ++iter) {
			std::shared_ptr<NodeWeighted> g_i = std::static_pointer_cast<NodeWeighted>(*iter);
			auto treeWeight_i = MST_Weight_Prim(*g, g_i);
			if (spanTreeWeight != treeWeight_i)
				return false;
		}
		return true;
	}

	bool NoCycles() {
		if (g == nullptr)
			return false;
		std::shared_ptr<NodeWeighted> g_0 = std::static_pointer_cast<NodeWeighted>((*g)[0]);
		unsigned long long spanTreeWeight = MST_Weight_Prim(*g, g_0);
		Graph gPred = g->CreatePredecessorGraph(*g->begin());
		for (auto iter = g->begin(); iter != g->end(); ++iter) {
			if (!BellmanFord(gPred, *iter))
				return false;
		}
		return true;
	}
};

TEST_F(AllPairsShortestPathsTesting, FloydWarshall_CorrectTest) {
	int n = pow(10, 2);
	CreateRandomDirGraph(n, n, true);
	EXPECT_TRUE(());
}

TEST_F(AllPairsShortestPathsTesting, JohnsonAllPairs_CorrectTest) {
	int n = pow(10, 2);
	CreateRandomDirGraph(n, n, true);
	EXPECT_TRUE(());
}
}//algospp