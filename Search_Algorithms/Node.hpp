class Node
{
private:
    int mRow;
    int mCol;
    int mDepth;
    int mCost;

public:
    Node(int, int, int, Node*, int cost = 0);

    ~Node();

    int getRow();
    int getColumn();
    int getDepth();
    int getCost();
};