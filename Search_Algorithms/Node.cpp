#include "Node.hpp"

Node::Node(int row, int col, int depth, int cost)
{
    this->mRow      = row;
    this->mCol      = col;
    this->mDepth    = depth;
    this->mCost     = cost;
}

Node::~Node(){}

int Node::getRow()
{
    return mRow;
}

int Node::getColumn()
{
    return mCol;
}

int Node::getDepth()
{
    return mDepth;
}

int Node::getCost()
{
    return mCost;
}