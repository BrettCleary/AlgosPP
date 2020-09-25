#include "../../src/Graph Algorithms/BreadthFirstSearch.h"
#include "../../src/Graph Algorithms/DepthFirstSearch.h"
#include "../../src/Graph Algorithms/Graph.h"
#include "../../src/Graph Algorithms/TopologicalSort.h"
#include "../../src/Graph Algorithms/StronglyConnectedComponents.h"
#include "../../src/Graph Algorithms/PrimsMST.h"

#include "gtest/gtest.h"

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <chrono>
#include <ctime>

namespace algospp {

/*namespace {
bool operator== (Node& lhs, Node& rhs) {
	bool adjListsMatch = true;
	if (lhs.adjList.size() != rhs.adjList.size())
		adjListsMatch = false;

}
}//unnamed namespace*/

class DirGraph : public ::testing::Test {
	Graph* g = nullptr;

protected:

	DirGraph() {

	}
	~DirGraph() override {

	}
	void SetUp() override {

	}
	void TearDown() override {

	}

public:

	void CreateRandomDirGraph(unsigned long long numVertices, unsigned long long numEdges) {
		if (g != nullptr)
			delete g;
		g = new Graph(numVertices, numEdges);
	}

	void CreateRandomUndirWtdGraph(unsigned long long numVertices, unsigned long long numEdges) {
		if (g != nullptr)
			delete g;
		g = new Graph(numVertices, numEdges, false);
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

	/*bool NoCycles() {
		Graph gReduced = sccReducedGraph(*g);
		bool noCycles = true;
		for (auto iter = g->begin(); iter != g->end(); ++iter) {
			noCycles = noCycles && BellmanFord(gReduced, *iter);
		}
		return noCycles;
	}*/
};

/*TEST_F(DirGraph, MST_NoCyclesTest) {
	CreateRandomDirGraph(pow(10, 2), pow(10, 2));
	EXPECT_TRUE(NoCycles());

}*/

TEST_F(DirGraph, MST_RepeatableTest) {
	CreateRandomUndirWtdGraph(pow(10, 2), pow(10, 2));
	EXPECT_TRUE(MSTIsRepeatable());
}
}//algospp