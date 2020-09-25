#ifndef ALGOSPP_SRC_GRAPH_PRIMSMST_H_
#define ALGOSPP_SRC_GRAPH_PRIMSMST_H_
#include "Graph.h"

#include <set>
#include <memory>
#include <unordered_set>
#include <map>
#include <algorithm>

namespace algospp {

/*Graph MST_Prim(Graph g) {

}*/

//assumes fully connected graph with NodeWeighted vertices
/*
std::priority_queue<std::shared_ptr<NodeWeighted>, std::vector<std::shared_ptr<NodeWeighted>>, nodeWtdcomparison> CreateMinPriorityQueue(const Graph& g) {

}*/

namespace {
void removeNodeFromPair(std::map<long long, std::vector<std::shared_ptr<NodeWeighted>>>& minNodeSet, std::pair<const long long, std::vector<std::shared_ptr<NodeWeighted>>>& pairNode, std::shared_ptr<NodeWeighted>& node) {
	auto nodePtr = std::find(pairNode.second.begin(), pairNode.second.end(), node);
	if (nodePtr == pairNode.second.end())
		throw;

	pairNode.second.erase(nodePtr);
	if (pairNode.second.empty()) {
		auto pairPtr = minNodeSet.erase(pairNode.first);
	}
}
} //unnamed

unsigned long long MST_Weight_Prim(Graph& g, std::shared_ptr<NodeWeighted> startNode) {
	//init single source 
	for (auto nodePtr = g.begin(); nodePtr != g.end(); ++nodePtr) {
		(*nodePtr)->prevNode = nullptr;
		std::shared_ptr<NodeWeighted> nodeWtdPtr = std::static_pointer_cast<NodeWeighted>(*nodePtr);
		nodeWtdPtr->key = LLONG_MAX;
	}
	startNode->key = 0;

	//create min ordered map on key from graph vertices
	std::map<long long, std::vector<std::shared_ptr<NodeWeighted>>> minNodeSet;
	std::unordered_set<std::shared_ptr<NodeWeighted>> unconnectedNodes;
	for (auto nodePtr = g.begin(); nodePtr != g.end(); ++nodePtr) {
		std::shared_ptr<NodeWeighted> nodeWtdPtr = std::static_pointer_cast<NodeWeighted>(*nodePtr);
		if (nodeWtdPtr == nullptr)
			throw;
		unconnectedNodes.insert(nodeWtdPtr);
		minNodeSet[nodeWtdPtr->key].push_back(nodeWtdPtr);
	}

	//successively add light edges
	unsigned long long weightSum = 0;
	while (!minNodeSet.empty()) {
		//add min node to tree
		std::pair<const long long, std::vector<std::shared_ptr<NodeWeighted>>>& minNode = *(minNodeSet.begin());
		weightSum += minNode.first;
		if (minNode.second.empty())
			minNodeSet.erase(minNodeSet.begin());
		unconnectedNodes.erase(minNode.second[0]);
		auto minNodePtr = minNode.second[0];
		removeNodeFromPair(minNodeSet, minNode, minNodePtr);

		//relax adjacent nodes
		for (int i = 0; i < minNodePtr->adjList.size(); ++i) {
			std::shared_ptr<NodeWeighted> adjWtdNode = std::static_pointer_cast<NodeWeighted>(minNodePtr->adjList[i]);
			if (unconnectedNodes.find(adjWtdNode) != unconnectedNodes.end() && minNodePtr->edgeWeights[i] < adjWtdNode->key) {
				//remove adjWtdNode from its pair
				auto adjWtdNodePairPtr = minNodeSet.find(adjWtdNode->key);
				if (adjWtdNodePairPtr == minNodeSet.end())
					continue;

				removeNodeFromPair(minNodeSet, *adjWtdNodePairPtr, adjWtdNode);
				unconnectedNodes.erase(adjWtdNode);

				//add to pair with new key
				adjWtdNode->key = minNodePtr->edgeWeights[i];
				adjWtdNode->prevNode = minNodePtr;
				minNodeSet[adjWtdNode->key].push_back(adjWtdNode);
				unconnectedNodes.insert(adjWtdNode);
			}
		}
	}
	return weightSum;
}

} //algospp
#endif//ALGOSPP_SRC_GRAPH_PRIMSMST_H_