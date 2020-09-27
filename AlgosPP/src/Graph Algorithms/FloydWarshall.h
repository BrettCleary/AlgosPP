#ifndef ALGOSPP_SRC_GRAPH_FLOYDWARSHALL_H_
#define ALGOSPP_SRC_GRAPH_FLOYDWARSHALL_H_

#include <vector>
#include <memory>

#include "Graph.h"

namespace algospp {
// (i,j) is the shortest path from vertex i to vertex j
// graph is assumed to have adjMatrix populated with edge weights from i to j for (i,j)
// adjList in Node is not used
// assuming no negative weight cycles
std::shared_ptr<std::vector<std::vector<long long>>> FloydWarshall(Graph& g) {
	if (g.adjMatrix == nullptr || g.adjMatrix->size() != (*g.adjMatrix)[0].size())
		return nullptr;

	std::shared_ptr<std::vector<std::vector<long long>>> dCurrent = 
		std::make_shared<std::vector<std::vector<long long>>>(g.adjMatrix->size(), std::vector<long long>((*g.adjMatrix)[0].size()));
	std::shared_ptr<std::vector<std::vector<long long>>> dLast = 
		std::make_shared<std::vector<std::vector<long long>>>(g.adjMatrix->size(), std::vector<long long>((*g.adjMatrix)[0].size()));

	for (int i = 0; i < g.adjMatrix->size(); ++i) {
		for (int j = 0; j < (*g.adjMatrix)[0].size(); ++j) {
			(*dCurrent)[i][j] = (*g.adjMatrix)[i][j];
		}
	}

	int numNodes = g.adjMatrix->size();
	for (int k = 0; k < numNodes; ++k) {
		std::swap(dLast, dCurrent);
		for (int i = 0; i < g.adjMatrix->size(); ++i) {
			for (int j = 0; j < (*g.adjMatrix)[0].size(); ++j) {
				long long newLength = LLONG_MAX;
				auto lastik = (*dLast)[i][k];
				auto lastkj = (*dLast)[k][j];
				//check that pathLength won't overflow positive or negative
				if ((lastik > 0 && lastkj < LLONG_MAX - lastik) ||
					(lastik < 0 && lastkj > LLONG_MIN - lastik)) {
					newLength = lastik + lastkj;
				}
				(*dCurrent)[i][j] = std::min((*dLast)[i][j], newLength);
			}
		}
	}
	return dCurrent;
}
}//algospp
#endif //ALGOSPP_SRC_GRAPH_FLOYDWARSHALL_H_