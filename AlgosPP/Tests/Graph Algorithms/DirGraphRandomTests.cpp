#include "../../src/Graph Algorithms/BreadthFirstSearch.h"
#include "../../src/Graph Algorithms/DepthFirstSearch.h"
#include "../../src/Graph Algorithms/Graph.h"
#include "../../src/Graph Algorithms/TopologicalSort.h"
#include "../../src/Graph Algorithms/StronglyConnectedComponents.h"
#include "../../src/Graph Algorithms/BellmanFord.h"

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

	bool SccIsRepeatable() {
		Graph gOne = sccReducedGraph(*g);
		Graph gSecond = sccReducedGraph(gOne);
		if (gOne.size() == gSecond.size())
			return true;
		else
			return false;
	}

	/*bool SccIsCorrect() {
		//check if any edges create a cycle with ssp algo
		Graph gRed = sccReducedGraph(g);
		if (gRed.size() != sccRepNodes.size())
			return false;

		return true;
	}*/

	bool SccNoCycles() {
		Graph gReduced = sccReducedGraph(*g);
		bool noCycles = true;
		for (auto iter = g->begin(); iter != g->end(); ++iter) {
			noCycles = noCycles && BellmanFord(gReduced, *iter);
		}
		return noCycles;
	}
};


TEST_F(DirGraph, SCC_RepeatableTest) {
	for (int i = 0; i < 4; ++i) {
		CreateRandomDirGraph(pow(10,i), pow(10, i));
		EXPECT_TRUE(SccIsRepeatable());
	}
}

//Dependent on BellmanFord being correct
TEST_F(DirGraph, SCC_NoCyclesTest) {
	for (int i = 0; i < 4; ++i) {
		CreateRandomDirGraph(pow(10, i), pow(10, i));
		EXPECT_TRUE(SccNoCycles());
	}
}

/*TEST_F(DirGraph, SCC_CorrectTest) {
	CreateRandomDirGraph(100, 100);

}*/
}//algospp