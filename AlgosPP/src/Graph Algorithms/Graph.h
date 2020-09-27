#ifndef ALGOSPP_SRC_GRAPH_GRAPH_H_
#define ALGOSPP_SRC_GRAPH_GRAPH_H_

#include <vector>
#include <memory>
#include <set>
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

struct DoublyLinkedNode;
struct NodeDL : NodeWeighted {
    std::shared_ptr<DoublyLinkedNode> heapNode = nullptr;
};

struct DoublyLinkedNode {

    std::shared_ptr<NodeDL> node;
    long long key = LLONG_MAX;

    std::shared_ptr<DoublyLinkedNode> next = nullptr;
    std::shared_ptr<DoublyLinkedNode> prev = nullptr;
    std::shared_ptr<DoublyLinkedNode> parent = nullptr;
    std::shared_ptr<DoublyLinkedNode> child = nullptr;
    bool mark = false;
    unsigned long long degree = 0;

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

    bool operator() (const std::shared_ptr<NodeWeighted>& lhs, const std::shared_ptr<NodeWeighted>& rhs) const {
        if (reverse)
            return lhs->key > rhs->key;
        return lhs->key < rhs->key;
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
    long long possiblePathLengthV = LLONG_MAX;
    //check that pathLength won't overflow positive or negative
    if ((u->edgeWeights[vAdjIndex] > 0 && u->pathLength < LLONG_MAX - u->edgeWeights[vAdjIndex]) ||
        (u->edgeWeights[vAdjIndex] < 0 && u->pathLength > LLONG_MIN - u->edgeWeights[vAdjIndex]))
        possiblePathLengthV = u->pathLength + u->edgeWeights[vAdjIndex];

    if (v->pathLength > possiblePathLengthV) {
        v->pathLength = possiblePathLengthV;
        v->prevNode = u;
    }
}

void RelaxAdjacent(std::shared_ptr<Node> nodePtr) {
    int numEdges = nodePtr->adjList.size();
    std::shared_ptr<NodeWeighted> uWtd = std::static_pointer_cast<NodeWeighted>(nodePtr);
    for (int i = 0; i < numEdges; ++i) {
        auto vWtd = std::static_pointer_cast<NodeWeighted>(uWtd->adjList[i]);
        Relax(uWtd, vWtd, i);
    }
}

class Graph{
    std::vector<std::shared_ptr<Node>> vertices;

    public:
    std::shared_ptr<std::vector<std::vector<long long>>> adjMatrix = nullptr;

    Graph(){}

    Graph(const Graph& g) : vertices(g.vertices) {}
    Graph(const Graph&& g) : vertices(g.vertices) {}
    Graph(const std::vector<std::shared_ptr<Node>>& v):vertices(v) {}
    Graph(std::vector<std::shared_ptr<Node>>&& v) :vertices(v) {}

    Graph(unsigned long long numV, unsigned long long numE, bool isDir = true, bool useRandWeights = false) {
        if (isDir)
            CreateRandomGraph(numV, numE, useRandWeights);
        else
            CreateRandomUnDirWtdGraph(numV, numE);
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

    void CreateRandomGraph(unsigned long long numVertices, unsigned long long numEdges, bool randomWeights = false){
        ClearGraph();
        int edgesPerVert = numEdges / numVertices + 1;
        adjMatrix = std::make_shared<std::vector<std::vector<long long>>>(numVertices, std::vector<long long>(numVertices, LLONG_MAX));

        for (int i = 0; i < numVertices; ++i) {
            auto ptr = std::make_shared<NodeDL>();
            vertices.push_back(std::move(ptr));
        }
        for (int v = 0; v < numVertices; ++v) {
            auto ptr = std::static_pointer_cast<NodeDL>(vertices[v]);
            std::set<unsigned long long> edgesAdded;
            for (int i = 0; i < edgesPerVert; ++i) {
                unsigned long long index = RandNum() % numVertices;
                if (edgesAdded.find(index) == edgesAdded.end())
                    edgesAdded.insert(index);
                else
                    continue;
                ptr->adjIndices.push_back(index);
                auto adjPtri = vertices[index];
                ptr->adjList.push_back(std::move(adjPtri));
                if (randomWeights) {
                    auto randomWeight = abs(RandNum() % 10 + 1);
                    ptr->edgeWeights.push_back(randomWeight);
                    (*adjMatrix)[v][index] = randomWeight;
                }
                else {
                    ptr->edgeWeights.push_back(1);
                    (*adjMatrix)[v][index] = 1;
                }
            }
        }

        for (int i = 0; i < numVertices; ++i) {
            (*adjMatrix)[i][i] = 0;
        }
    }

    void CreateRandomUnDirWtdGraph(unsigned long long numVertices, unsigned long long numEdges) {
        ClearGraph();
        int edgesPerVert = numEdges / numVertices + 1;
        adjMatrix = std::make_shared<std::vector<std::vector<long long>>>(numVertices, std::vector<long long>(numVertices, LLONG_MAX));

        for (int i = 0; i < numVertices; ++i) {
            auto ptr = std::make_shared<NodeWeighted>();
            vertices.push_back(std::move(ptr));
        }
        for (int v = 0; v < numVertices; ++v) {
            auto ptr = std::static_pointer_cast<NodeWeighted>(vertices[v]);
            for (int i = 0; i < edgesPerVert; ++i) {
                unsigned long long index = RandNum() % numVertices;
                if (index <= v) {
                    continue;
                }
                ptr->adjIndices.push_back(index);
                auto adjPtri = vertices[index];
                ptr->adjList.push_back(std::move(adjPtri));
                auto edgeW = rand() % 100 + 1;
                ptr->edgeWeights.push_back(edgeW);

                auto adjPtr = std::static_pointer_cast<NodeWeighted>(vertices[index]);
                adjPtr->adjList.push_back(ptr);
                adjPtr->adjIndices.push_back(v);
                adjPtr->edgeWeights.push_back(edgeW);

                (*adjMatrix)[v][index] = edgeW;
                (*adjMatrix)[index][v] = edgeW;
            }
        }

        for (int i = 0; i < numVertices; ++i) {
            (*adjMatrix)[i][i] = 0;
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
            i->pathLength = LLONG_MAX;
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

    void ClearMarks() {
        for (auto iter = vertices.begin(); iter != vertices.end(); ++iter) {
            (*iter)->marked = false;
        }
    }

    Graph CreatePredecessorGraph(std::shared_ptr<Node> source) {
        ClearMarks();
        source->marked = true;

        Graph predGraph;
        std::vector<std::shared_ptr<Node>> adjNodesToExplore{ source };

        //these are new predGraph nodes to be populated with adjList with prevNode = node from previous graph
        std::shared_ptr<NodeWeighted> predGraphSourceNode = std::make_shared<NodeWeighted>();
        predGraph.push_back(predGraphSourceNode);
        std::vector<std::shared_ptr<NodeWeighted>> adjPredNodes{ predGraphSourceNode };
        
        while (!adjNodesToExplore.empty()) {
            auto nextNode = adjNodesToExplore[0];
            adjNodesToExplore.erase(adjNodesToExplore.begin());
            std::shared_ptr<NodeWeighted> predGraphNextNode = adjPredNodes[0];
            adjPredNodes.erase(adjPredNodes.begin());
            for (auto& adjNode_i : nextNode->adjList) {
                if (adjNode_i->prevNode == nextNode && adjNode_i->marked == false) {
                    adjNode_i->marked = true;
                    adjNodesToExplore.push_back(adjNode_i);
                    
                    //create corresponding node in predecessor graph
                    std::shared_ptr<NodeWeighted> predGraphAdjNode = std::make_shared<NodeWeighted>();
                    predGraphAdjNode->prevNode = predGraphNextNode;
                    predGraphNextNode->adjList.push_back(predGraphAdjNode);
                    predGraphNextNode->adjIndices.push_back(predGraph.size() - 1);
                    predGraphNextNode->edgeWeights.push_back(1);
                    predGraph.push_back(predGraphAdjNode);
                    adjPredNodes.push_back(predGraphAdjNode);
                }
            }
        }
        return predGraph;
    }
};
}//algospp
#endif//ALGOSPP_SRC_GRAPH_GRAPH_H_