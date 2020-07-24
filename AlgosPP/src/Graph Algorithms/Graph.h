#ifndef ALGOSPP_SRC_GRAPH_GRAPH_H_
#define ALGOSPP_SRC_GRAPH_GRAPH_H_

#include <vector>
#include <memory>
#include "..\..\Misc\RandomNum.h"

namespace algospp{
struct Node{
    bool marked = false;
    unsigned long long pathLength = -1;
    unsigned long long finishTime = -1;
    std::shared_ptr<Node> prevNode = nullptr;
    std::vector<std::shared_ptr<Node>> adjList;
};

class Graph{
    std::vector<std::shared_ptr<Node>> vertices;


    public:

    std::vector<std::shared_ptr<Node>>::iterator begin(){
        return vertices.begin();
    }
    
    std::vector<std::shared_ptr<Node>>::iterator end(){
        return vertices.end();
    }

    std::vector<std::shared_ptr<Node>>::size_type size() {
        return vertices.size();
    }

    std::shared_ptr<Node> operator [](int index){
        return vertices[index];
    }

    void push_back(std::shared_ptr<Node> node) {
        vertices.push_back(node);
    }

    void CreateRandomGraph(int numVertices, int numEdges){
        int edgesPerVert = numEdges / numVertices + 1;

        for (int i = 0; i < numVertices; ++i) {
            auto ptr = std::make_shared<Node>(Node());
            vertices.push_back(std::move(ptr));
        }
        for (int v = 0; v < numVertices; ++v) {
            auto ptr = vertices[v];
            for (int i = 0; i < edgesPerVert; ++i) {
                auto adjPtri = vertices[RandNum() % numVertices];
                ptr->adjList.push_back(std::move(adjPtri));
            }
        }
    }

    void ResetVertices(){
        for (std::shared_ptr<Node> i : vertices){
            i->marked = false;
            i->pathLength = -1;
            i->prevNode = nullptr;
            i->finishTime = -1;
        }
    }

    void ClearGraph(){
        vertices.clear();
    }
};
}//algospp

#endif//ALGOSPP_SRC_GRAPH_GRAPH_H_