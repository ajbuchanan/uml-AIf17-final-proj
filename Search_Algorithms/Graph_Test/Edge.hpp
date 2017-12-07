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
}