#ifndef ALGOSPP_SRC_GRAPH_PRIMSMST_H_
#define ALGOSPP_SRC_GRAPH_PRIMSMST_H_
#include "Graph.h"

#include <set>
#include <memory>
#include <unordered_set>

namespace algospp {

/*Graph MST_Prim(Graph g) {

}*/

//assumes fully connected graph with NodeWeighted vertices
/*
std::priority_queue<std::shared_ptr<NodeWeighted>, std::vector<std::shared_ptr<NodeWeighted>>, nodeWtdcomparison> CreateMinPriorityQueue(const Graph& g) {

}*/

unsigned long long MST_Weight_Prim(Graph g, std::shared_ptr<NodeWeighted> startNode) {
	//init single source 
	for (auto nodePtr = g.begin(); nodePtr != g.end(); ++nodePtr) {
		(*nodePtr)->prevNode = nullptr;
		std::shared_ptr<NodeWeighted> nodeWtdPtr = (std::shared_ptr<NodeWeighted>)(*nodePtr);
		nodeWtdPtr->key = LLONG_MAX;
	}
	startNode->key = 0;

	//create min ordered set on key from graph vertices
	std::set<std::shared_ptr<NodeWeighted>, nodeWtdcomparisonKey> minNodeSet(nodeWtdcomparisonKey(true));
	std::unordered_set<std::shared_ptr<NodeWeighted>> unconnectedNodes;
	for (auto nodePtr = g.begin(); nodePtr != g.end(); ++nodePtr) {
		std::shared_ptr<NodeWeighted> nodeWtdPtr = std::dynamic_pointer_cast<std::shared_ptr<NodeWeighted>>(*nodePtr);
		if (nodeWtdPtr == nullptr)
			throw;
		unconnectedNodes.insert(nodeWtdPtr);
		minNodeSet.insert(std::move(nodeWtdPtr));
	}

	//successively add light edges
	unsigned long long weightSum = 0;
	while (!minNodeSet.empty()) {
		//add min node to tree
		std::shared_ptr<NodeWeighted> minNode = minNodeSet[0];
		weightSum += minNode->key;
		minNodeSet.erase(minNodeSet.begin());
		unconnectedNodes.erase(minNode);

		//relax adjacent nodes
		for (int i = 0; i < minNode->adjList.size(); ++i) {
			std::shared_ptr<NodeWeighted> adjWtdNode = std::dynamic_pointer_cast<std::shared_ptr<NodeWeighted>>(minNode->adjList[i]);
			if (unconnectedNodes.find(adjWtdNode) != unconnectedNodes.end() && minNode->edgeWeights[i] < adjWtdNode->key) {
				minNodeSet.erase(adjWtdNode);
				adjWtdNode->key = minNode->edgeWeights[i];
				adjWtdNode->prevNode = minNode;
				minNodeSet.insert(adjWtdNode);
			}
		}
	}
	return weightSum;
}
} //algospp
#endif//ALGOSPP_SRC_GRAPH_PRIMSMST_H_