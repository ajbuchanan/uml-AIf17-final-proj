#include "Node.hpp"

Node::Node(int row, int col, int depth, Node* parent, int cost)
{
    this->mRow      = row;
    this->mCol      = col;
    this->mDepth    = depth;
    this->mCost     = cost;
    this->mParent   = parent;
}

Node::~Node()
{
    delete mParent;
}

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

Node* Node::getParent()
{
    return mParent;
}