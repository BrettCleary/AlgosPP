#ifndef ALGOSPP_SRC_GRAPH_DEPTHFIRSTSEARCH_H_
#define ALGOSPP_SRC_GRAPH_DEPTHFIRSTSEARCH_H_

#include "Graph.h"

namespace algospp {

struct LinkedListNode {
	std::shared_ptr<LinkedListNode> PrevNode = nullptr;
	std::shared_ptr<LinkedListNode> NextNode = nullptr;
	std::shared_ptr<Node> NodePtr = nullptr;

	LinkedListNode(std::shared_ptr<Node> nodePtr) : NodePtr(nodePtr) {}
	LinkedListNode(const LinkedListNode& nodeToCopy) : PrevNode(nodeToCopy.PrevNode), NextNode(nodeToCopy.NextNode), NodePtr(nodeToCopy.NodePtr) {

	}
};

void dfsVisit(Graph g, std::shared_ptr<Node> u, unsigned long long& time, std::shared_ptr<LinkedListNode> frontNode = nullptr) {
	u->pathLength = ++time;
	u->marked = true;

	for (auto iter = u->adjList.begin(); iter != u->adjList.end(); ++iter) {
		if (!(*iter)->marked) {
			(*iter)->prevNode = u;
			dfsVisit(g, (*iter), time, frontNode);
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
void dfs(Graph g) {
	unsigned long long time = 0;
	for (auto iter = g.begin(); iter != g.end(); ++iter) {
		if (!(*iter)->marked)
			dfsVisit(g, *iter, time);
	}
}


}//algospp
#endif//ALGOSPP_SRC_GRAPH_DEPTHFIRSTSEARCH_H_