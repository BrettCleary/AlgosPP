#ifndef ALGOSPP_SRC_GRAPH_BREADTHFIRSTSEARCH_H_
#define ALGOSPP_SRC_GRAPH_BREADTHFIRSTSEARCH_H_

#include "Graph.h"
#include <memory>
#include <queue>

namespace algospp {

namespace {
	class NodeComparison
	{
		bool reverse;
	public:
		NodeComparison(const bool& revparam = false)
		{
			reverse = revparam;
		}
		bool operator() (std::shared_ptr<Node>& lhs, std::shared_ptr<Node>& rhs) const
		{
			if (reverse) return (lhs->pathLength > rhs->pathLength);
			else return (lhs->pathLength < rhs->pathLength);
		}
	};
}

//assumes a cleared graph as input
void bfs(Graph& g, unsigned long long sIndex, unsigned long long sccIndex = -1) {
	g[sIndex]->marked = true;
	g[sIndex]->pathLength = 0;
	g[sIndex]->sccIndex = sccIndex;

	std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeComparison> frontierQueue(NodeComparison(true));
	auto sPtr = g[sIndex];
	frontierQueue.push(sPtr);
	while (!frontierQueue.empty()) {
		std::shared_ptr<Node> node_i = frontierQueue.top();
		frontierQueue.pop();
		for (auto node_j : node_i->adjList) {
			if (!node_j->marked) {
				node_j->marked = true;
				node_j->pathLength = node_i->pathLength + 1;
				node_j->prevNode = node_i;
				node_j->sccIndex = sccIndex;
				frontierQueue.push(node_j);
			}
		}
	}
}

void bfs(Graph& g, std::shared_ptr<Node> sPtr, unsigned long long sccIndex = -1) {
	sPtr->marked = true;
	sPtr->pathLength = 0;
	sPtr->sccIndex = sccIndex;

	std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeComparison> frontierQueue(NodeComparison(true));
	frontierQueue.push(sPtr);
	while (!frontierQueue.empty()) {
		std::shared_ptr<Node> node_i = frontierQueue.top();
		frontierQueue.pop();
		for (auto node_j : node_i->adjList) {
			if (!node_j->marked) {
				node_j->marked = true;
				node_j->pathLength = node_i->pathLength + 1;
				node_j->prevNode = node_i;
				node_j->sccIndex = sccIndex;
				frontierQueue.push(node_j);
			}
		}
	}
}



}//algospp

#endif//ALGOSPP_SRC_GRAPH_BREADTHFIRSTSEARCH_H_