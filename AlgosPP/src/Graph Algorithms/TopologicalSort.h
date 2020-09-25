#ifndef ALGOSPP_SRC_GRAPH_TOPOLOGICALSORT_H_
#define ALGOSPP_SRC_GRAPH_TOPOLOGICALSORT_H_
#include "Graph.h"

namespace algospp {
//assumes a cleared graph as input
std::shared_ptr<LinkedListNode> topologicalSort(Graph& g) {
	std::unordered_set<std::shared_ptr<Node>> visitedNodes;
	long long time = 0;
	std::shared_ptr<LinkedListNode> startLLNode = nullptr;
	for (auto iter = g.begin(); iter != g.end(); ++iter) {
		if (!(*iter)->marked) {
			auto newFront = std::make_shared<LinkedListNode>(*iter);
			if (startLLNode != nullptr) {
				newFront->NextNode = startLLNode;
				startLLNode->PrevNode = newFront;
			}
			startLLNode = newFront;
			dfsVisit(*iter, time, startLLNode);
		}
	}
	return startLLNode;
}
}//algospp
#endif//ALGOSPP_SRC_GRAPH_TOPOLOGICALSORT_H_