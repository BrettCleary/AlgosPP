#ifndef ALGOSPP_SRC_GRAPH_DIJKSTRAS_H_
#define ALGOSPP_SRC_GRAPH_DIJKSTRAS_H_

#include "Graph.h"
#include <set>

namespace algospp {

//weights assumed to be nonnegative
void Dijkstras(Graph& g, std::shared_ptr<Node> source) {
	g.InitSingleSource(source);

	//create min ordered set on path length
	std::set<std::shared_ptr<Node>, nodeWtdcomparisonPathLength> minNodeSet(nodeWtdcomparisonPathLength(true));
	for (auto nodePtr = g.begin(); nodePtr != g.end(); ++nodePtr) {
		minNodeSet.insert(*nodePtr);
	}

	//successively add light edge connected vertices to shortest paths predecessor subgraph
	//and update ordered set
	while (!minNodeQueue.empty()) {
		auto u = minNodeSet[0];
		minNodeSet.erase(minNodeSet.begin());
		for (auto adjNode : u->adjList)
			minNodeSet.erase(adjNode);
		RelaxAdjacent(u);
		for (auto adjNode : u->adjList)
			minNodeSet.insert(adjNode);
	}
}
}//algospp
#endif//ALGOSPP_SRC_GRAPH_DIJKSTRAS_H_