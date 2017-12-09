#include "Graph.hpp"

Graph::Graph(Node* rootNode)
{
    mRootNode = rootNode;
}

void Graph::addNode(Node* node)
{
    std::pair<int,int> coord = pair(node->getRow(),node->getColumn());

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
    return getNode(std::pair(row,col));
}

Node* Graph::getRoot()
{
    return mRootNode;
}

std::vector<Node*> Graph::getSuccessors(Node* parent)
{
    std::vector<Node*> successors;

    for(int i = 0; i < mEdges[parent].size(); i++)
    {
        successors.push_front(mEdges[parent][i]);
    }

    return successors;
}

std::vector<Node*> Graph::getSuccessors(int row, int col)
{
    return getSuccessors(getNode(row, col));
}

std::vector<Node*> Graph::getSuccessors(std::pair<int,int> coord)
{
    return getSuccessors(getNode(coord));
}