#ifndef NODE_HPP
#define NODE_HPP

class Node
{
private:
    int mRow;
    int mCol;
    int mDepth;
    int mCost;

    Node* mParent;

public:
    Node(int row, int col, int depth, Node* parent, int cost);

    ~Node();

    int getRow();
    int getColumn();
    int getDepth();
    int getCost();
    Node* getParent();
};

#endif