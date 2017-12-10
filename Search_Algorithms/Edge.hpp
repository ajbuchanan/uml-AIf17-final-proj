#ifndef EDGE_HPP
#define EDGE_HPP

#include "Node.hpp"

class Edge
{
private:
    int mCost;
    Node* mFrom;
    Node* mTo;

public:
    Edge(int, Node*, Node*);

    int getCost();
    Node* getFrom();
    Node* getTo();
};

#endif