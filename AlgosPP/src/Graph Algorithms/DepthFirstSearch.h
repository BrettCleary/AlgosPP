#ifndef ALGOSPP_SRC_GRAPH_DEPTHFIRSTSEARCH_H_
#define ALGOSPP_SRC_GRAPH_DEPTHFIRSTSEARCH_H_

#include "Graph.h"
#include <unordered_set>

namespace algospp {


void dfsVisit(std::shared_ptr<Node> u, long long& time, std::shared_ptr<LinkedListNode> frontNode = nullptr, 
	long long sccIndex = LLONG_MAX) {
	u->pathLength = ++time;
	u->marked = true;
	u->sccIndex = sccIndex;

	for (auto iter = u->adjList.begin(); iter != u->adjList.end(); ++iter) {
		if (!(*iter)->marked) {
			(*iter)->prevNode = u;
			dfsVisit((*iter), time, frontNode, sccIndex);
		}
	}
	u->finishTime = ++time;
	if (frontNode != nullptr) {
		std::shared_ptr<LinkedListNode> newFront = std::make_shared<LinkedListNode>(u);
		newFront->NextNode = frontNode;
		frontNode->PrevNode = newFront;
		frontNode = newFront;
	}
}

//assumes a cleared graph as input
//uses adjList of graph
//does not use adjMatrix
void dfs(Graph& g) {
	long long time = 0;
	std::unordered_set<std::shared_ptr<Node>> visitedNodes;
	for (auto iter = g.begin(); iter != g.end(); ++iter) {
		if (!(*iter)->marked)
			dfsVisit(*iter, time);
	}
}
}//algospp
#endif//ALGOSPP_SRC_GRAPH_DEPTHFIRSTSEARCH_H_