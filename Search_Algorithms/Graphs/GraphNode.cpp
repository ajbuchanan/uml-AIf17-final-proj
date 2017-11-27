class GraphNode
{
    private:
    int const invalidNodeIndex = -1;
    
    protected:
    int mIndex;

    public:
    GraphNode():mIndex(invalidNodeIndex){}
    GraphNode(int index):mIndex(index){}

    virtual ~GraphNode(){}

    int Index()const;
    void SetIndex(int NewIndex);
};
