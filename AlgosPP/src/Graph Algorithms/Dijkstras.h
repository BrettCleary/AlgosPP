#ifndef ALGOSPP_SRC_GRAPH_DIJKSTRAS_H_
#define ALGOSPP_SRC_GRAPH_DIJKSTRAS_H_

#include "Graph.h"
#include "../Data Structures/FibonacciHeap.h"
#include <set>

namespace algospp {


void RelaxAdjacent(FibHeap& minQueue, std::shared_ptr<DoublyLinkedNode> nodePtr) {
	int numEdges = nodePtr->node->adjList.size();
	std::shared_ptr<NodeWeighted> uWtd = std::static_pointer_cast<NodeWeighted>(nodePtr->node);
	for (int i = 0; i < numEdges; ++i) {
		auto vWtd = std::static_pointer_cast<NodeDL>(uWtd->adjList[i]);
		if (vWtd->marked)
			continue;
		Relax(uWtd, vWtd, i);
		if (vWtd->pathLength != LLONG_MAX)
			minQueue.decreaseKey(vWtd->heapNode, vWtd->pathLength);
	}
}

//weights assumed to be nonnegative
//g assumed to have NodeDL nodes
void Dijkstras(Graph& g, std::shared_ptr<Node> source) {
	g.InitSingleSource(source);

	//create min ordered fib heap on path length
	FibHeap minQueue;
	for (auto nodePtr = g.begin(); nodePtr != g.end(); ++nodePtr) {
		std::shared_ptr<DoublyLinkedNode> dlNode_i = std::make_shared<DoublyLinkedNode>();
		dlNode_i->node = std::static_pointer_cast<NodeDL>(*nodePtr);
		dlNode_i->node->heapNode = dlNode_i;
		dlNode_i->node->marked = false;
		dlNode_i->key = (*nodePtr)->pathLength;
		minQueue.insert(dlNode_i);
	}

	//successively add light edge connected vertices to shortest paths predecessor subgraph
	//and update ordered set
	while (!minQueue.empty()) {
		auto u = minQueue.extractMin();
		//if node has already been extracted, mark so that relaxAdjacent does not try to relax edge into extracted node
		u->node->marked = true;
		RelaxAdjacent(minQueue, u);
	}
}


}//algospp
#endif//ALGOSPP_SRC_GRAPH_DIJKSTRAS_H_