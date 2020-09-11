#ifndef ALGOSPP_SRC_GRAPH_DAGSHORTESTPATHS_H_
#define ALGOSPP_SRC_GRAPH_DAGSHORTESTPATHS_H_

#include "Graph.h"
#include "TopologicalSort.h"

namespace algospp {

void DagShortestPaths(Graph& g, std::shared_ptr<NodeWeighted> source) {
	std::shared_ptr<LinkedListNode> frontNode = topologicalSort(g);
	g.InitSingleSource(source);

	while (frontNode != nullptr) {
		RelaxAdjacent(frontNode->NodePtr);
		frontNode = frontNode->NextNode;
	}
}
}//algospp
#endif//ALGOSPP_SRC_GRAPH_DAGSHORTESTPATHS_H_