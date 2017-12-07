#include "Node.hpp"
#include "Edge.hpp"

using namespace std;

class Graph
{
private:
    std::map<std::pair<int,int>,Node*> mNodes;
    std::map<Node*, std::vector<Edge*> > mEdges;

public:
    Graph(std::map<std::pair<int,int>,Node*>, std::map<Node*, std::vector<Edge*> >);

    void addNode(Node*);
    void addEdge(Node*, Node*, int cost = 1);
    Node* getNode(std::pair<int,int>);
    Node* getNode(int, int);
    std::vector<Node*> getSuccessors(Node*);
    std::vector<Node*> getSuccessors(int, int);
    std::vector<Node*> getSuccessors(std::pair<int,int>);
    
}