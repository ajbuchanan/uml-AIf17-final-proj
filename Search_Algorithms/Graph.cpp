#include "Graph.hpp"

Graph::Graph(Node* rootNode)
{
    mRootNode = rootNode;
}

void Graph::addNode(Node* node)
{
    std::pair<int,int> coord = std::pair<int, int>(node->getRow(),node->getColumn());

    if(mNodes.count(coord) != 1)
    {
        mNodes[coord] = node;
    }
}

void Graph::addEdge(Node* from, Node* to, int cost)
{
    mEdges[from].push_front(new Edge(cost, from, to));
}

Node* Graph::getNode(std::pair<int,int> coord)
{
    return mNodes[coord];
}

Node* Graph::getNode(int row, int col)
{
    return getNode(std::pair<int, int>(row,col));
}

Node* Graph::getRoot()
{
    return mRootNode;
}

std::deque<Node*> Graph::getSuccessors(Node* parent)
{
    std::deque<Node*> successors;

    for(int i = 0; i < mNodes[parent].size(); i++)
    {
        successors.push_front(mNodes[parent][i]);
    }

    return successors;
}

std::deque<Node*> Graph::getSuccessors(int row, int col)
{
    return getSuccessors(getNode(row, col));
}

std::deque<Node*> Graph::getSuccessors(std::pair<int,int> coord)
{
    return getSuccessors(getNode(coord));
}