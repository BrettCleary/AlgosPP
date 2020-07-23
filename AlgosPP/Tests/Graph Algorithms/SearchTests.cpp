#include "../../src/Graph Algorithms/BreadthFirstSearch.h"
#include "../../src/Graph Algorithms/DepthFirstSearch.h"
#include "../../src/Graph Algorithms/Graph.h"

#include "gtest/gtest.h"

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <chrono>
#include <ctime>

namespace algospp {


	TEST(SearchTests, BFSTest){
		Graph g;
		g.CreateRandomGraph(3, 3);

		bfs(g, 0);

		//need to check predecessor graph correct

	}

	TEST(SearchTests, DFSTest) {
		Graph g;
		g.CreateRandomGraph(3, 3);

		dfs(g);

		//need to check predecessor graph correct

	}

}//algospp