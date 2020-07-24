
#include "Graph.h"


namespace algospp {
	struct LinkedListNode {
		std::shared_ptr<LinkedListNode> PrevNode = nullptr;
		std::shared_ptr<LinkedListNode> NextNode = nullptr;
		std::shared_ptr<Node> Node = nullptr;

		LinkedListNode(std::shared_ptr<Node> nodePtr) : Node(nodePtr) {}
	};


namespace {
	void dfsVisit(Graph g, std::shared_ptr<Node> u, unsigned long long& time, std::shared_ptr<LinkedListNode> frontNode) {
		u->pathLength = ++time;
		u->marked = true;

		for (auto iter = u->adjList.begin(); iter != u->adjList.end(); ++iter) {
			if (!(*iter)->marked) {
				(*iter)->prevNode = u;
				dfsVisit(g, (*iter), time);
			}
		}
		u->finishTime = ++time;
		std::shared_ptr<LinkedListNode> newFront = std::make_shared<LinkedListNode>(u);
		newFront->NextNode = frontNode;
		frontNode->PrevNode = newFront;
		frontNode = newFront;
	}
}//unnamed namespace



//assumes a cleared graph as input
std::vector<LinkedListNode> topologicalSort(Graph g) {
	std::vector<LinkedListNode> linkedLists;
	unsigned long long time = 0;
	for (auto iter = g.begin(); iter != g.end(); ++iter) {
		if (!(*iter)->marked) {
			std::shared_ptr<LinkedListNode> startLLNode = std::make_shared<LinkedListNode>(*iter);
			linkedLists.push_back(startLLNode);
			dfsVisit(g, *iter, time, startLLNode);
		}
	}
}


}//algospp