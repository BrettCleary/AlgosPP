#include "../../src/Graph Algorithms/BreadthFirstSearch.h"
#include "../../src/Graph Algorithms/DepthFirstSearch.h"
#include "../../src/Graph Algorithms/Graph.h"
#include "../../src/Graph Algorithms/TopologicalSort.h"
#include "../../src/Graph Algorithms/StronglyConnectedComponents.h"

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

class BstTests : public ::testing::Test {
	Graph g;
	std::shared_ptr<BstNode> startNode = nullptr;

protected:

	BstTests() {

	}
	~BstTests() override {

	}
	void SetUp() override {

	}
	void TearDown() override {

	}


public:

	Graph* getGraphPtr() {
		return &g;
	}

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

	bool ParenthesisTheoremHolds() {
		return ParenthesisTheoremHoldsRec(startNode->left, startNode->pathLength, startNode->finishTime) && 
			ParenthesisTheoremHoldsRec(startNode->right, startNode->pathLength, startNode->finishTime);
	}

	bool ParenthesisTheoremHoldsRec(std::shared_ptr<BstNode> s, unsigned long long parentStartTime, unsigned long long parentFinishTime) {
		if (s == nullptr)
			return true;

		if (s->pathLength <= parentStartTime || s->finishTime >= parentFinishTime)
			return false;

		return ParenthesisTheoremHoldsRec(s->left, s->pathLength, s->finishTime) &&
			ParenthesisTheoremHoldsRec(s->right, s->pathLength, s->finishTime);
	}

	bool AllBstNodesReached() {
		return (AllBstNodesReachedRec(startNode));
	}

	bool AllBstNodesReachedRec(std::shared_ptr<BstNode> s) {
		bool leftNodesReached = true, rightNodesreached = true;
		if (s->left == nullptr && s->right == nullptr)
			return s->marked;

		if (s->left != nullptr)
			leftNodesReached = AllBstNodesReachedRec(s->left);
		if (s->right != nullptr)
			rightNodesreached = AllBstNodesReachedRec(s->right);

		return leftNodesReached && rightNodesreached;
	}

	void Clear() {
		g.ClearGraph();
	}

};


TEST_F(BstTests, BFSTest){
	CreateBstGraph(1000);
	BreadthFirstSearch();
	EXPECT_TRUE(IsMinPathLength());
}

TEST_F(BstTests, DFSParenthesisTest) {
	CreateBstGraph(1000);
	DepthFirstSearch();
	EXPECT_TRUE(ParenthesisTheoremHolds());
}

TEST_F(BstTests, DFSWhitePathTheoremTest) {
	CreateBstGraph(1000);
	DepthFirstSearch();
	EXPECT_TRUE(AllBstNodesReached());
}

TEST_F(BstTests, SCC_BST_Test) {
	CreateBstGraph(1000);
	std::vector<std::shared_ptr<LinkedListNode>> components = stronglyConnectedComponents(*getGraphPtr());
	EXPECT_TRUE(components.size() == 1);
}
}//algospp