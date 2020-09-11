#ifndef ALGOSPP_SRC_GRAPH_TOPOLOGICALSORT_H_
#define ALGOSPP_SRC_GRAPH_TOPOLOGICALSORT_H_
#include "Graph.h"


namespace algospp {
	
//assumes a cleared graph as input
std::shared_ptr<LinkedListNode> topologicalSort(const Graph& g) {
	std::unordered_set<std::shared_ptr<Node>> visitedNodes;
	unsigned long long time = 0;
	std::shared_ptr<LinkedListNode> startLLNode = nullptr;
	for (auto iter = g.begin(); iter != g.end(); ++iter) {
		if (!(*iter)->marked) {
			auto newFront = std::make_shared<LinkedListNode>(*iter);
			if (startLLNode != nullptr) {
				newFront->NextNode = startLLNode;
				startLLNode->PrevNode = newFront;
			}
			startLLNode = newFront;
			dfsVisit(*iter, time, -1, startLLNode);
		}
	}
	return startLLNode;
}

//returns a representative node for each strongly connected component
std::vector<std::shared_ptr<LinkedListNode>> stronglyConnectedComponents(Graph& g) {
	std::vector<std::shared_ptr<LinkedListNode>> finishTimeList = topologicalSort(g);
	g.InvertGraph();

	std::vector<std::shared_ptr<LinkedListNode>> sccVertices;

	for (std::shared_ptr<LinkedListNode> node_i : finishTimeList) {
		if (node_i->NodePtr->marked)
			continue;

		//max finish time that has not been visited is used as the representative vertice from its strongly connected component
		sccVertices.push_back(node_i);
		unsigned long long time = 0;
		dfsVisit(node_i->NodePtr, time);
	}
	//restore original graph
	g.InvertGraph();
	return sccVertices;
}
namespace {
Graph createReducedGraph(const Graph& g, unsigned long long numSccComponents) {
	//this will be used to instantiate the new graph
	std::vector<std::shared_ptr<Node>> reducedVertices;

	for (int setIndex = 0; setIndex < numSccComponents; ++setIndex) {
		//create new node for reduced graph
		reducedVertices.push_back(std::make_shared<Node>());
	}

	//adding edges to the new reduced graph
	for (auto vertIter = g.begin(); vertIter < g.end(); ++vertIter) {
		for (std::shared_ptr<Node> connectedVert : (*vertiter)->adjList) {
			unsigned long long vertSccIndex = (*vertIter)->sccIndex;
			unsigned long long connectedSccIndex = connectedVert->sccIndex;
			if (vertSccIndex == connectedSccIndex) {
				//vertices are in the same component
				continue;
			}
			else {
				//there is a directed edge between components
				reducedVertices[vertSccIndex]->adjIndices.push_back(connectedSccIndex);
				reducedVertices[vertSccIndex]->adjList.push_back(reducedVertices[connectedSccIndex]);
			}
		}
	}
	return Graph(std::move(reducedVertices));
}
} //unnamed namespace

Graph sccReducedGraph(Graph& g) {
	unsigned long long i = 0;
	std::vector<std::shared_ptr<LinkedListNode>> finishTimeList = topologicalSort(g);
	g.InvertGraph();
	for (std::shared_ptr<LinkedListNode> node_i : finishTimeList) {
		if (node_i->NodePtr->marked)
			continue;

		//max finish time that has not been visited is used as the representative vertice from its strongly connected component
		unsigned long long time = 0;
		dfsVisit(node_i->NodePtr, time, nullptr, i);
		++i;
	}
	//restore original graph
	g.InvertGraph();
	return createReducedGraph(g, i);
}



}//algospp
#endif//ALGOSPP_SRC_GRAPH_TOPOLOGICALSORT_H_