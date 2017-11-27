template<class graphType>
class DepthFirstSearch
{
    private:
    enum {visited, unvisited, noParent};

    typedef typename graphType::EdgeType Edge;
    typedef typename graphType::NodeType Node;

    const graphType& mGraph;

    std::vector<int> mVisited;
    std::vector<int> mRoute;

    //Start (source) and Goal (target) nodes
    int mSource, mTarget;

    //true when a path has been found
    bool mFound;

    bool Search();

    public:
    DepthFirstSearch(const graphType& graph, int source, int target = -1):
                                                                        mGraph(graph),
                                                                        mSource(source),
                                                                        mTarget(target),
                                                                        mFound(false),
                                                                        mVisited(mGraph.NumNodes(), unvisited),
                                                                        mRoute(mGraph.NumNodes(), noParent)
    {
        mFound = Search();
    }

    bool Found()const{return mFound;}

    //returns a vector of node indices that comprise the resulting path from the search
    std::list<int> GetPathToTarget()const;
};

template <class graphType>
bool DepthFirstSearch<graphType>::Search()
{
    std::stack<const Edge*> stack;

    Edge Dummy(mSource, mSource, 0);

    stack.push(&Dummy);

    while(!stack.empty())
    {
        const Edge* next = stack.top();

        stack.pop();

        mRoute[next->To] = next->From;

        mVisited[next->To] = visited;

        if(next->To == mTarget)
        {
            return true;
        }

        graphType::ConstEdgeIterator edgeIterator(mGraph, next->To);

        for(const Edge* pE=edgeIterator.begin(); !edgeIterator.end(); pE=edgeIterator.next())
        {
            if(mVisited[pE->To] == unvisited)
            {
                stack.push(pE);
            }
        }

        return false;
    }
}

std::list<int> DepthFirstSearch<graphType>::GetPathToTarget()const
{
    std::list<int> path;

    if(!mFound || mTarget < 0) return path;

    int nd = mTarget;

    path.push_back(nd);

    while(nd != mSource)
    {
        nd = mRoute[nd];

        path.push_back(nd);
    }

    return path;
}