#include "Edge.hpp"

Edge::Edge(int cost, Node* from, Node* to)
{
    this->mCost = cost;
    this->mFrom = from;
    this->mTo = to;
}

int Edge::getCost()
{
    return this->mCost;
}

Node* Edge::getFrom()
{
    return this->mFrom;
}

Node* Edge::getTo()
{
    return this->mTo;
}