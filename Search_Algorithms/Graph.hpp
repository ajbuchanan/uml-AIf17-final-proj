#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <deque>
#include <map>
#include <utility>

#include "Node.hpp"
#include "Edge.hpp"

class Graph
{
private:
    Node* mRootNode;
    std::map<std::pair<int,int>,Node*> mNodes;
    std::map<Node*, std::deque<Edge*> > mEdges;

public:
    Graph() { }
    Graph(Node*);

    void addNode(Node*);
    void addEdge(Node*, Node*, int cost = 1);

    Node* getNode(std::pair<int,int>);
    Node* getNode(int, int);

    Node* getRoot();
    
    std::deque<Node*> getSuccessors(Node*);
    std::deque<Node*> getSuccessors(int, int);
    std::deque<Node*> getSuccessors(std::pair<int,int>);
    
};

#endif