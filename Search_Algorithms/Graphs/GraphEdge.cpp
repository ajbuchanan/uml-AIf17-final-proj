class GraphEdge
{
    private:
    int const invalidNodeIndex = -1;

    protected:

    //index of node edge goes from and to
    int mFrom;
    int mTo;

    //The cost of traversing the edge
    double mCost;

    public:
    GraphEdge(int from, int to, double cost):mFrom(from),mTo(to),mCost(cost){}

    GraphEdge(int from, int to):mFrom(from),mTo(to),mCost(1.0){}

    GraphEdge():mFrom(invalidNodeIndex),mTo(invalidNodeIndex),mCost(1.0){}
}