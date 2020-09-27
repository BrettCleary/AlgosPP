#ifndef ALGOSPP_SRC_GRAPH_BELLMANFORD_H_
#define ALGOSPP_SRC_GRAPH_BELLMANFORD_H_

#include "Graph.h"

namespace algospp {

//assumes graph vertices are NodeWeighted vertices
bool BellmanFord(Graph& g, std::shared_ptr<Node> source) {
	g.InitSingleSource(source);

	for (int j = 0; j < g.size() - 1; ++j) {
		for (int i = 0; i < g.size(); ++i) {
			std::shared_ptr<Node>& u = g[i];
			int numEdgesNode_i = u->adjList.size();
			for (int j = 0; j < numEdgesNode_i; ++j) {
				Relax(std::static_pointer_cast<NodeWeighted>(u), std::static_pointer_cast<NodeWeighted>(u->adjList[j]), j);
			}
		}
	}

	for (int i = 0; i < g.size() - 1; ++i) {
		auto& u = g[i];
		int numEdgesNode_i = u->adjList.size();
		for (int j = 0; j < numEdgesNode_i; ++j) {
			auto uWtd = std::static_pointer_cast<NodeWeighted>(u);
			auto vWtd = std::static_pointer_cast<NodeWeighted>(u->adjList[j]);
			auto vLength = vWtd->pathLength;
			auto uLength = uWtd->pathLength;
			auto uWeight = uWtd->edgeWeights[j];
			if (((vLength > 0 && uLength < LLONG_MAX - uWeight) ||
				(vLength < 0 && uLength > LLONG_MIN - uWeight)) &&
				vLength > uLength + uWeight)
				return false;
		}
	}
	return true;
}
}//algospp
#endif//ALGOSPP_SRC_GRAPH_BELLMANFORD_H_