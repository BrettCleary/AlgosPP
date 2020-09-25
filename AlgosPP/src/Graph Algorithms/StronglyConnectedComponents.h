#ifndef ALGOSPP_SRC_GRAPH_STRONGLYCONNECTEDCOMPONENTS_H_
#define ALGOSPP_SRC_GRAPH_STRONGLYCONNECTEDCOMPONENTS_H_
#include "Graph.h"

namespace algospp {
//returns a representative node for each strongly connected component
std::vector<std::shared_ptr<LinkedListNode>> stronglyConnectedComponents(Graph& g) {
	//linked list starts with highest finish time node (finishTimeList)
	//and monotonically decreases through the end of the linked list
	std::shared_ptr<LinkedListNode> finishTimeList = topologicalSort(g);
	g.InvertGraph();

	std::vector<std::shared_ptr<LinkedListNode>> sccVertices;

	auto node_i = finishTimeList;
	while (node_i != nullptr && !node_i->NodePtr->marked) {
		//max finish time that has not been visited is used as the representative vertice from its strongly connected component
		sccVertices.push_back(node_i);
		long long time = 0;
		dfsVisit(node_i->NodePtr, time);
		node_i = node_i->NextNode;
	}
	//restore original graph
	g.InvertGraph();
	//Linked List Nodes from separate strongly connected components in original graph
	return sccVertices;
}
namespace {
	Graph createReducedGraph(Graph& g, unsigned long long numSccComponents) {
		//this will be used to instantiate the new graph
		std::vector<std::shared_ptr<Node>> reducedVertices;

		for (int setIndex = 0; setIndex < numSccComponents; ++setIndex) {
			//create new node for reduced graph
			reducedVertices.push_back(std::make_shared<Node>());
		}

		//adding edges to the new reduced graph
		for (auto vertIter = g.begin(); vertIter < g.end(); ++vertIter) {
			for (std::shared_ptr<Node> connectedVert : (*vertIter)->adjList) {
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
	long long i = 0;
	std::shared_ptr<LinkedListNode> finishTimeList = topologicalSort(g);
	g.InvertGraph();
	auto node_i = finishTimeList;
	while (node_i != nullptr && !node_i->NodePtr->marked) {
		//max finish time that has not been visited is used as the representative vertice from its strongly connected component
		long long time = 0;
		dfsVisit(node_i->NodePtr, time, nullptr, i);
		++i;
		node_i = node_i->NextNode;
	}
	//restore original graph
	g.InvertGraph();
	return createReducedGraph(g, i);
}
}//algospp
#endif//ALGOSPP_SRC_GRAPH_STRONGLYCONNECTEDCOMPONENTS_H_