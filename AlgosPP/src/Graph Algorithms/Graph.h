#ifndef ALGOSPP_SRC_GRAPH_GRAPH_H_
#define ALGOSPP_SRC_GRAPH_GRAPH_H_

#include <vector>
#include <memory>
#include "..\..\Misc\RandomNum.h"

namespace algospp{
struct Node{
    bool marked = false;
    
    //pathLength is discovery time in DFS
    long long pathLength = LLONG_MAX; 
    long long finishTime = LLONG_MAX;
    long long sccIndex = LLONG_MAX;
    std::shared_ptr<Node> prevNode = nullptr;
    std::vector<std::shared_ptr<Node>> adjList;
    std::vector<unsigned long long> adjIndices;
};

struct NodeWeighted : Node {
    long long key = LLONG_MAX;
    std::vector<long long> edgeWeights;
};

struct LinkedListNode {
    std::shared_ptr<LinkedListNode> PrevNode = nullptr;
    std::shared_ptr<LinkedListNode> NextNode = nullptr;
    std::shared_ptr<Node> NodePtr = nullptr;

    LinkedListNode(std::shared_ptr<Node> nodePtr) : NodePtr(nodePtr) {}
    LinkedListNode(const LinkedListNode& nodeToCopy) : PrevNode(nodeToCopy.PrevNode), NextNode(nodeToCopy.NextNode), NodePtr(nodeToCopy.NodePtr) {

    }
};

class nodeWtdcomparisonKey {
    bool reverse;
public:
    nodeWtdcomparisonKey(const bool& revparam = false) {
        reverse = revparam;
    }

    bool operator() (const NodeWeighted& lhs, const NodeWeighted& rhs) const {
        if (reverse)
            return lhs.key > rhs.key;
        return lhs.key < rhs.key;
    }
};

class nodeWtdcomparisonPathLength {
    bool reverse;
public:
    nodeWtdcomparisonPathLength(const bool& revparam = false) {
        reverse = revparam;
    }

    bool operator() (const Node& lhs, const Node& rhs) const {
        if (reverse)
            return lhs.pathLength > rhs.pathLength;
        return lhs.pathLength < rhs.pathLength;
    }
};

void Relax(std::shared_ptr<NodeWeighted> u, std::shared_ptr<NodeWeighted> v, unsigned long long vAdjIndex) {
    if (u == nullptr || v == nullptr)
        throw;
    long long possiblePathLengthV = u->pathLength + u->edgeWeights[vAdjIndex];
    if (v->pathLength > possiblePathLengthV) {
        v->pathLength = possiblePathLengthV;
        v->prevNode = u;
    }
}

void RelaxAdjacent(std::shared_ptr<Node> nodePtr) {
    int numEdges = nodePtr->adjList.size();
    std::shared_ptr<NodeWeighted> uWtd = std::dynamic_pointer_cast<NodeWeighted>(nodePtr);
    for (int i = 0; i < numEdges; ++i) {
        auto vWtd = std::dynamic_pointer_cast<NodeWeighted>(uWtd->adjList[i]);
        Relax(uWtd, vWtd, i);
    }
}

class Graph{
    std::vector<std::shared_ptr<Node>> vertices;

    public:
    std::shared_ptr<std::vector<std::vector<unsigned long long>>> adjMatrix = nullptr;

    Graph(){}

    Graph(const Graph& g) : vertices(g.vertices) {}
    Graph(const Graph&& g) : vertices(g.vertices) {}

    Graph(const std::vector<std::shared_ptr<Node>>& v):vertices(v) {

    }

    Graph(std::vector<std::shared_ptr<Node>>&& v) :vertices(v) {

    }

    Graph(unsigned long long numV, unsigned long long numE) {
        CreateRandomGraph(numV, numE);
    }

    std::vector<std::shared_ptr<Node>>::iterator begin(){
        return vertices.begin();
    }
    
    std::vector<std::shared_ptr<Node>>::iterator end(){
        return vertices.end();
    }

    std::vector<std::shared_ptr<Node>>::size_type size(){
        return vertices.size();
    }

    std::shared_ptr<Node> operator [](int index){
        return vertices[index];
    }

    std::vector<std::shared_ptr<Node>>::iterator erase(std::vector<std::shared_ptr<Node>>::iterator pos) {
        return vertices.erase(pos);
    }

    void push_back(std::shared_ptr<Node> node) {
        vertices.push_back(node);
    }

    void CreateRandomGraph(unsigned long long numVertices, unsigned long long numEdges){
        ClearGraph();
        int edgesPerVert = numEdges / numVertices + 1;

        for (int i = 0; i < numVertices; ++i) {
            auto ptr = std::make_shared<Node>(Node());
            vertices.push_back(std::move(ptr));
        }
        for (int v = 0; v < numVertices; ++v) {
            auto ptr = vertices[v];
            for (int i = 0; i < edgesPerVert; ++i) {
                unsigned long long index = RandNum() % numVertices;
                ptr->adjIndices.push_back(index);
                auto adjPtri = vertices[index];
                ptr->adjList.push_back(std::move(adjPtri));
            }
        }
    }

    void ClearSccIndices() {
        for (auto nodePtr : vertices) {
            nodePtr->sccIndex = -1;
        }
    }

    void ResetVertices(){
        for (std::shared_ptr<Node> i : vertices){
            i->marked = false;
            i->pathLength = LLONG_MAX;
            i->prevNode = nullptr;
            i->finishTime = LLONG_MAX;
            i->adjIndices.clear();
            i->adjList.clear();
            i->sccIndex = LLONG_MAX;
        }
    }

    void InitSingleSource(std::shared_ptr<Node> source) {
        for (std::shared_ptr<Node> i : vertices) {
            i->pathLength = -1;
            i->prevNode = nullptr;
        }
        source->pathLength = 0;
        source->prevNode = nullptr;
    }

    //adjListIndices must be set to invert
    void InvertGraph() {
        std::vector<std::vector<unsigned long long>> allAdjListIndices;

        for (std::shared_ptr<Node> adjListIndices : vertices) {
            allAdjListIndices.push_back(adjListIndices->adjIndices);
        }

        ResetVertices();

        for (unsigned long long i = 0; i < allAdjListIndices.size(); ++i) {
            for (auto nodeIndex : allAdjListIndices[i]) {
                vertices[nodeIndex]->adjIndices.push_back(i);
                vertices[nodeIndex]->adjList.push_back(vertices[i]);
            }
        }
    }

    void ClearGraph(){
        vertices.clear();
    }
};
}//algospp
#endif//ALGOSPP_SRC_GRAPH_GRAPH_H_