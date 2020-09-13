#ifndef ALGOSPP_SRC_GRAPH_FLOYDWARSHALL_H_
#define ALGOSPP_SRC_GRAPH_FLOYDWARSHALL_H_

#include <vector>
#include <memory>

#include "Graph.h"

namespace algospp {


std::shared_ptr<std::vector<std::vector<unsigned long long>>> FloydWarshall(Graph& g) {
	if (g.adjMatrix == nullptr || g.adjMatrix.size() != g.adjMatrix[0].size())
		return nullptr;

	std::shared_ptr<std::vector<std::vector<unsigned long long>>> dCurrent = 
		std::make_shared<std::vector<std::vector<unsigned long long>>>(g.adjMatrix.size(), std::vector<unsigned long long>(g.adjMatrix[0].size()));
	std::shared_ptr<std::vector<std::vector<unsigned long long>>> dLast = 
		std::make_shared<std::vector<std::vector<unsigned long long>>>(g.adjMatrix.size(), std::vector<unsigned long long>(g.adjMatrix[0].size()));

	for (int i = 0; i < g.adjMatrix.size(); ++i) {
		for (int j = 0; j < g.adjMatrix[0].size(); ++j) {
			dCurrent[i][j] = g.adjMatrix[i][j];
		}
	}

	int numNodes = g.adjMatrix.size();
	for (int k = 0; k < numNodes; ++k) {
		std::swap(dLast, dCurrent);
		for (int i = 0; i < g.adjMatrix.size(); ++i) {
			for (int j = 0; j < g.adjMatrix[0].size(); ++j) {
				dCurrent[i][j] = std::min(dLast[i][j], dLast[i][k] + dLast[k][j]);
			}
		}
	}
	return dCurrent;
}
}//algospp
#endif //ALGOSPP_SRC_GRAPH_FLOYDWARSHALL_H_