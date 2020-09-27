#ifndef ALGOSPP_SRC_GRAPH_JOHNSONALLPAIRS_H_
#define ALGOSPP_SRC_GRAPH_JOHNSONALLPAIRS_H_

#include <vector>
#include <memory>

#include "Graph.h"
#include "BellmanFord.h"
#include "Dijkstras.h"

namespace algospp {

	//g required to use adjLists and adjIndices, adjMatrix not needed
	//assumes NodeWeighted
	std::shared_ptr<std::vector<std::vector<long long>>> JohnsonAllPairs(Graph& g) {
		std::shared_ptr<NodeWeighted> source = std::make_shared<NodeWeighted>();
		source->edgeWeights.resize(g.size(), 0);
		for (auto iter = g.begin(); iter != g.end(); ++iter) {
			source->adjList.push_back(*iter);
		}
		g.push_back(source);

		//O(VE) time complexity
		if (!BellmanFord(g, source)) {
			std::cout << "The input graph contains a negative weight cycle." << std::endl;
			return nullptr;
		}

		//remove source from graph vertices
		g.erase(g.end() - 1);

		std::vector<long long> reweightVector;
		for (auto iter : source->adjList) {
			reweightVector.push_back(iter->pathLength);
		}

		//reweight so weights are nonnegative for Dijkstras
		for (int i = 0; i < g.size(); ++i) {
			auto iter = g[i];
			std::shared_ptr<NodeWeighted> wtdIter = std::static_pointer_cast<NodeWeighted>(iter);
			for (int j = 0; j < wtdIter->adjIndices.size(); ++j) {
				wtdIter->edgeWeights[j] += reweightVector[i] - reweightVector[wtdIter->adjIndices[j]];
			}
		}

		std::shared_ptr<std::vector<std::vector<long long>>> shortestPathsMatrix =
			std::make_shared<std::vector<std::vector<long long>>>(g.size(), std::vector<long long>(g.size(), LLONG_MAX));

		//run Dijkstras on every vertice
		int i = 0;
		for (auto vert_i = g.begin(); vert_i != g.end(); ++vert_i) {
			Dijkstras(g, *vert_i);
			int j = 0;
			for (auto vert_j = g.begin(); vert_j != g.end(); ++vert_j) {
				(*shortestPathsMatrix)[i][j] = (*vert_j)->pathLength + reweightVector[j] - reweightVector[i];
				++j;
			}
			++i;
		}
		return shortestPathsMatrix;
	}


}//algospp
#endif //ALGOSPP_SRC_GRAPH_JOHNSONALLPAIRS_H_