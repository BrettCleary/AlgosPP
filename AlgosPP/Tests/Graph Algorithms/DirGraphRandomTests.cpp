#include "../../src/Graph Algorithms/BreadthFirstSearch.h"
#include "../../src/Graph Algorithms/DepthFirstSearch.h"
#include "../../src/Graph Algorithms/Graph.h"
#include "../../src/Graph Algorithms/TopologicalSort.h"

#include "gtest/gtest.h"

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <chrono>
#include <ctime>

namespace algospp {

class DirGraph : public ::testing::Test {
	Graph g;

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

	void CreateRandomDirGraph(unsigned long long numVertices, unsigned long long numEdges) : g(numVertices, numEdges) {}

	bool SccIsRepeatable() {
		Graph gRed = sccReducedGraph(g);
		if (gRed.size() == sccReducedGraph(gRed).size())
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

};
}


TEST_F(DirGraph, SCC_RepeatableTest) {
	for (int i = 0; i < 4; ++i) {
		CreateRandomDirGraph(pow(10,i), pow(10, i));
		EXPECT_TRUE(SccIsRepeatable());
	}
}

/*TEST_F(DirGraph, SCC_CorrectTest) {
	CreateRandomDirGraph(100, 100);

}*/