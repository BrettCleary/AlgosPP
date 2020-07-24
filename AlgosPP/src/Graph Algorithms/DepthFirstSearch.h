#ifndef ALGOSPP_SRC_GRAPH_DEPTHFIRSTSEARCH_H_
#define ALGOSPP_SRC_GRAPH_DEPTHFIRSTSEARCH_H_

#include "Graph.h"

namespace algospp {
namespace {
	void dfsVisit(Graph g, std::shared_ptr<Node> u, unsigned long long& time) {
		u->pathLength = ++time;
		u->marked = true;

		for (auto iter = u->adjList.begin(); iter != u->adjList.end(); ++iter) {
			if (!(*iter)->marked) {
				(*iter)->prevNode = u;
				dfsVisit(g, (*iter), time);
			}
		}
		u->finishTime = ++time;
	}
}//unnamed namespace

//assumes a cleared graph as input
void dfs(Graph g) {
	unsigned long long time = 0;
	for (auto iter = g.begin(); iter != g.end(); ++iter) {
		if (!(*iter)->marked)
			dfsVisit(g, *iter, time);
	}
}


}//algospp
#endif//ALGOSPP_SRC_GRAPH_DEPTHFIRSTSEARCH_H_