#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <vector>
#include <utility>

#include "Node.hpp"
#include "Edge.hpp"

class Graph
{
private:
    Node* mRootNode;
    std::map<std::pair<int,int>,Node*> mNodes;
    std::map<Node*, std::vector<Edge*> > mEdges;

public:
    Graph(Node*);

    void addNode(Node*);
    void addEdge(Node*, Node*, int cost = 1);

    Node* getNode(std::pair<int,int>);
    Node* getNode(int, int);

    Node* getRoot();
    
    std::vector<Node*> getSuccessors(Node*);
    std::vector<Node*> getSuccessors(int, int);
    std::vector<Node*> getSuccessors(std::pair<int,int>);
    
}

#endif