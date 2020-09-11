#ifndef ALGOSPP_SRC_GRAPH_BELLMANFORD_H_
#define ALGOSPP_SRC_GRAPH_BELLMANFORD_H_

#include "Graph.h"

namespace algospp {

bool BellmanFord(Graph& g, std::shared_ptr<Node> source) {
	for (int i = 0; i < g.size() - 1; ++i) {
		auto& u = g[i];
		int numEdgesNode_i = u->adjList.size();
		for (int j = 0; j < numEdgesNode_i.size(); ++j) {
			Relax(std::dynamic_pointer_cast<std::shared_ptr<NodeWeighted>>(u), std::dynamic_pointer_cast<std::shared_ptr<NodeWeighted>>(u->adjList[j]), j);
		}
	}

	for (int i = 0; i < g.size() - 1; ++i) {
		auto& u = g[i];
		int numEdgesNode_i = u->adjList.size();
		for (int j = 0; j < numEdgesNode_i.size(); ++j) {
			auto uWtd = std::dynamic_pointer_cast<std::shared_ptr<NodeWeighted>>(u);
			auto vWtd = std::dynamic_pointer_cast<std::shared_ptr<NodeWeighted>>(u->adjList[j]);
			if (vWtd > uWtd->pathLength + uWtd->edgeWeights[vAdjIndex])
				return false;
		}
	}
	return true;
}
}//algospp
#endif//ALGOSPP_SRC_GRAPH_BELLMANFORD_H_