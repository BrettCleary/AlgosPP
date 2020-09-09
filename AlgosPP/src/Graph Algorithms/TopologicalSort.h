
#include "Graph.h"


namespace algospp {
	
//assumes a cleared graph as input
std::vector<std::shared_ptr<LinkedListNode>> topologicalSort(Graph g) {
	std::vector<std::shared_ptr<LinkedListNode>> linkedLists;
	unsigned long long time = 0;
	for (auto iter = g.begin(); iter != g.end(); ++iter) {
		if (!(*iter)->marked) {
			std::shared_ptr<LinkedListNode> startLLNode = std::make_shared<LinkedListNode>(*iter);
			linkedLists.push_back(startLLNode);
			dfsVisit(g, *iter, time, startLLNode);
		}
	}
	return linkedLists;
}

std::vector<std::shared_ptr<LinkedListNode>> stronglyConnectedComponents(Graph g) {
	std::vector<std::shared_ptr<LinkedListNode>> finishTimeList = topologicalSort(g);
	Graph invG = g.CreateInvertedGraph();

	std::vector<std::shared_ptr<LinkedListNode>> sccVertices;

	for (std::shared_ptr<LinkedListNode> node_i : finishTimeList) {
		if (node_i->NodePtr->marked)
			continue;

		sccVertices.push_back(node_i);
		unsigned long long time = 0;
		dfsVisit(invG, node_i->NodePtr, time);
	}
	return sccVertices;
}
}//algospp