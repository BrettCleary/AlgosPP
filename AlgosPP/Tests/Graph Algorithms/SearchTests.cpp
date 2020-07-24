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

	struct BstNode : Node {
		unsigned long long correctDist = -1;
		std::shared_ptr<BstNode> left = nullptr;
		std::shared_ptr<BstNode> right = nullptr;
	};

	class SearchTests : public ::testing::Test {
		Graph g;
		std::shared_ptr<BstNode> startNode = nullptr;

	protected:

		SearchTests() {

		}
		~SearchTests() override {

		}
		void SetUp() override {

		}
		void TearDown() override {

		}


	public:

		void CreateBstGraph(int n) {
			startNode = std::make_shared<BstNode>();
			startNode->correctDist = 0;
			startNode->pathLength = 0;
			g.push_back(startNode);
			RecursiveCreateBstGraph(n, startNode, 0);
		}

		void RecursiveCreateBstGraph(int& n, std::shared_ptr<BstNode> s, int dist) {
			++dist;
			n -= 2;
			auto leftNode = std::make_shared<BstNode>();
			s->left = leftNode;
			s->adjList.push_back(leftNode);
			leftNode->correctDist = dist;
			auto rightNode = std::make_shared<BstNode>();
			s->right = rightNode;
			s->adjList.push_back(rightNode);
			rightNode->correctDist = dist;

			g.push_back(leftNode);
			g.push_back(rightNode);

			if (n > 0) {
				RecursiveCreateBstGraph(n, leftNode, dist);
				RecursiveCreateBstGraph(n, rightNode, dist);
			}
		}

		void BreadthFirstSearch() {
			bfs(g, 0);
		}

		void DepthFirstSearch() {
			dfs(g);
		}

		bool IsMinPathLength() {
			if (startNode->correctDist != 0 || startNode->pathLength != 0) {
				return false;
			}
			return TreeIsCorrectPathLength(startNode->left) && TreeIsCorrectPathLength(startNode->right);
		}

		bool TreeIsCorrectPathLength(std::shared_ptr<BstNode> node) {
			if (node == nullptr)
				return true;
			if (node->correctDist != node->pathLength)
				return false;

			return TreeIsCorrectPathLength(node->left) && TreeIsCorrectPathLength(node->right);
		}

		void Clear() {
			g.ClearGraph();
		}

	};


	TEST_F(SearchTests, BFSTest){
		CreateBstGraph(1000);
		BreadthFirstSearch();
		EXPECT_TRUE(IsMinPathLength());
	}

	/*TEST_F(SearchTests, DFSTest) {

	}*/

}//algospp