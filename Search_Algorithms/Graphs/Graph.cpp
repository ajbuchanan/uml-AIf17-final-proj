template <class nodeType, class edgeType>
class Graph
{
    public:
    typedef std::vector<nodeType> NodeVector;
    typedef std::list<edgeType> EdgeList;
    typedef std::vector<EdgeList> EdgeListVector;

    typedef nodeType NodeType;
    typedef edgeType EdgeType;

    private:
    NodeVector mNodes;

    EdgeListVector mEdges;

    bool mDirGraph;

    int mNextNodeIndex;

    public:
    
    Graph(bool dirGraph):mDirGraph(dirGraph), mNextNodeIndex(0){}

    const nodeType& GetNode(int index)const;

    nodeType& GetNode(int index);

    const edgeType& GetEdge(int from, to)const;

    edgeType& getEdge(int from, int to);

    int GetNextFreeNodeIndex()const;

    int NumNodes()const;

    int NumActiveNodes()const;

    int NumEdges()const;

    bool isDirGraph()const;

    bool isEmpty()const;

    bool isPresent()const;

    bool Save(const char* FileName)const;
    bool Save(std::ofstream& stream)const;
    bool Load(const char* FileName);
    bool Load(std::ifstream& stream);
};