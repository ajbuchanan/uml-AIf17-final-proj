#include "Searcher.hpp"

using namespace std;

Searcher::Searcher(std::string file)
{
    mProblemFile = file;

    mNumMoves = 0;
    mNumExpanded = 0;
    mMaxQueue = 0;

    generateGraph(file);
}

vector<Result> Searcher::SearchAll()
{
    mResults.push_back(BreadthFirstSearch());
    CleanUp();

    mResults.push_back(DepthFirstSearch());
    CleanUp();

    mResults.push_back(AStarSearch());
    CleanUp();

    mResults.push_back(UniformCostSearch());
    CleanUp();

    return mResults
}

Graph* Searcher::generateGraph(std::string file)
{
    ifstream mazeFile;
    mazeFile.open(file, ios::in);
    char gMaze[BOARDSIZE][BOARDSIZE]; 

    if(mazeFile.is_open())
    {
        for(int i = 0; i < BOARDSIZE; i++)
        {
            for(int j = 0; j < BOARDSIZE; j++)
            {
                char node = 'n';
                mazeFile >> node;
                mRoute[i][j] = node; 
                mMaze[i][j] = node;
                gMaze[i][j] = node;

                if(node == START)
                {
                    mStartRow = i;
                    mStartCol = j;
                }
                else if(node == GOAL)
                {
                    mGoalRow = i;
                    mGoalCol = j;
                }
            }
        }

        mazeFile.close();
    }
    else
    {
        cout << "Unable to open file";
    }

    int numLooked = 0;
    int totalNodes = BOARDSIZE * BOARDSIZE;
    int currentCol = mStartCol;
    int currentRow = mStartRow;
    Node* prevNode = new Node(mStartRow, mStartCol, 0, ManhattanDistance(mStartRow, mStartCol));

    deque<pair<Node*,Node*> > graphQueue;

    graphQueue.push_back(pair(NULL, prevNode));

    mGraph = Graph(prevNode);

    while(graphQueue.size() > 0)
    {
        pair<Node*,Node*> current = graphQueue.front();
        graphQueue.pop_front();
        int row = current.second->getRow();
        int col = current.second->getColumn();
        gMaze[row][col] = EXP;

        if(row+1 < BOARDSIZE && (gMaze[row+1][col] == EMPT || gMaze[row+1][col] == GOAL))
        {
            Node* upNode = new Node(row+1, col, numLooked, ManhattanDistance(row+1, col))
            mGraph.addNode(upNode);
            mGraph.addEdge(current.second, upNode);

            graphQueue.push_back(std::pair(current.second, upNode));
        }
        if(row-1 >= 0 && (gMaze[row-1][col] == EMPT || gMaze[row-1][col] == GOAL))
        {
            Node* downNode = new Node(row-1, col, numLooked, ManhattanDistance(row-1, col))
            mGraph.addNode(downNode);
            mGraph.addEdge(current.second, downNode);

            graphQueue.push_back(std::pair(current.second, downNode));
        }
        if(col+1 < BOARDSIZE && (gMaze[row][col+1] == EMPT || gMaze[row][col+1] == GOAL))
        {
            Node* rightNode = new Node(row, col+1, numLooked, ManhattanDistance(row, col+1))
            mGraph.addNode(rightNode);
            mGraph.addEdge(current.second, rightNode);

            graphQueue.push_back(std::pair(current.second, rightNode));
        }
        if(col-1 >= 0 && (gMaze[row][col-1] == EMPT || gMaze[row][col-1] == GOAL))
        {
            Node* leftNode = new Node(row, col-1, numLooked, ManhattanDistance(row, col-1))
            mGraph.addNode(leftNode);
            mGraph.addEdge(current.second, leftNode);

            graphQueue.push_back(std::pair(current.second, leftNode));
        }
    }
}

Result Searcher::DepthFirstSearch()
{
    Node* currentNode = mGraph.getRoot();
    Node* prevNode = NULL;
    map<Node*, Node*> DFSPath;

    mFrontier.push_front(currentNode);

    while(!IsGoal(currentNode))
    {
        mNumMoves++;
        
        DFSPath[currentNode] = prevNode;

        vector<Node*> successors = mGraph.getSuccessors(currentNode);
        mNumExpanded++;

        mVisited.push_back(currentNode);

        for(int i = successors.size()-1; i >= 0; i--)
        {
            mFrontier.push_front(successors[i]);
            if(mFrontier.size() > mMaxQueue)
            {
                mMaxQueue = mFrontier.size();
            }
        }

        prevNode = currentNode;

        currentNode = mFrontier.front();
        mFrontier.pop_front();
    }

    GeneratePath(DFSPath, currentNode);
    
    return GenerateResults(true, SearchType.DFS);
}

Results Searcher::BreadthFirstSearch()
{
    Node* currentNode = mGraph.getRoot();
    Node* prevNode = NULL;
    map<Node*, Node*> BFSPath;

    mFrontier.push_back(currentNode);

    while(!IsGoal(currentNode))
    {
        mNumMoves++;
        
        BFSPath[currentNode] = prevNode;

        vector<Node*> successors = mGraph.getSuccessors(currentNode);
        mNumExpanded++;

        mVisited.push_back(currentNode);

        for(int i = 0; i < successors.size(); i++)
        {
            mFrontier.push_back(successors[i]);
            if(mFrontier.size() > mMaxQueue)
            {
                mMaxQueue = mFrontier.size();
            }
        }

        prevNode = currentNode;

        currentNode = mFrontier.front();
        mFrontier.pop_front();
    }

    GeneratePath(BFSPath, currentNode);
    
    return GenerateResults(true, SearchType.BFS);
}

Results Searcher::AStarSearch()
{
    Node* currentNode = mGraph.getRoot();
    mFrontier.push_back(currentNode);
    map<Node*, Node*> ASPath;
    map<Node*, int> gScore;
    gScore[currentNode] = 0;
    map<Node*, int> fScore;
    fScore[currentNode] = currentNode->getCost();

    while(mFrontier.size() > 0)
    {
        mNumMoves++;

        int fScoreVal = INT_MAX;
        for(int i = 0; i < mFrontier.size(); i++)
        {
            if(fScore[mFrontier[i]] < fScoreVal)
            {
                currentNode = mFrontier[i];
                mFrontier.erase(mFrontier.begin()+i);
            }
        }

        if(IsGoal(currentNode))
        {
            break;
        }

        mVisited.push_back(currentNode);

        vector<Node*> successors = mGraph.getSuccessors(currentNode);
        mNumExpanded++;

        for(int i = 0; i < successors.size(); i++)
        {
            if(std::find(mVisited.begin(), mVisited.end(), successors[i]) != mVisited.end())
            {
                continue;
            }
            if(std::find(mFrontier.begin(), mFrontier.end(), successors[i]) == mFrontier.end())
            {
                mFrontier.push_back(successors[i]);
                if(mFrontier.size() > mMaxQueue)
                {
                    mMaxQueue = mFrontier.size();
                }
            }

            tempScore = gScore[currentNode] + 1;
            if(gScore.count(successors[i]) == 1 && tempScore >= gScore[successors[i]])
            {
                continue;
            }

            ASPath[successors[i]] = currentNode;
            gScore[successors[i]] = tempScore;
            fScore[successors[i]] = gScore[successors[i]] + successors[i]->getCost();
        }
    }

    GeneratePath(ASPath, currentNode);
    
    return GenerateResults(true, SearchType.AStar);
}

void Searcher::UniformCostSearch()
{
    Node* currentNode = mGraph.getRoot();
    mFrontier.push_back(currentNode);
    map<Node*, Node*> UCSPath;
    map<Node*, int> gScore;
    gScore[currentNode] = 0;
    map<Node*, int> fScore;
    fScore[currentNode] = 1;

    while(mFrontier.size() > 0)
    {
        mNumMoves++;
        
        int fScoreVal = INT_MAX;
        for(int i = 0; i < mFrontier.size(); i++)
        {
            if(fScore[mFrontier[i]] < fScoreVal)
            {
                currentNode = mFrontier[i];
                mFrontier.erase(mFrontier.begin()+i);
            }
        }

        if(IsGoal(currentNode))
        {
            break;
        }

        mVisited.push_back(currentNode);

        vector<Node*> successors = mGraph.getSuccessors(currentNode);
        mNumExpanded++;

        for(int i = 0; i < successors.size(); i++)
        {
            if(std::find(mVisited.begin(), mVisited.end(), successors[i]) != mVisited.end())
            {
                continue;
            }
            if(std::find(mFrontier.begin(), mFrontier.end(), successors[i]) == mFrontier.end())
            {
                mFrontier.push_back(successors[i]);
                if(mFrontier.size() > mMaxQueue)
                {
                    mMaxQueue = mFrontier.size();
                }
            }

            tempScore = gScore[currentNode] + 1;
            if(gScore.count(successors[i]) == 1 && tempScore >= gScore[successors[i]])
            {
                continue;
            }

            UCSPath[successors[i]] = currentNode;
            gScore[successors[i]] = tempScore;
            fScore[successors[i]] = gScore[successors[i]] + 1;
        }
    }

    GeneratePath(UCSPath, currentNode);
    
    return GenerateResults(true, SearchType.UCS);
}

Result Searcher::HillClimbingSearch()
{
    Node* currentNode = mGraph.getRoot();
    int nextEval = -INT_MAX;
    Node* nextNode = NULL;
    map<Node*,Node*> HillPath;
    success = false;

    while(!IsGoal(currentNode))
    {
        mNumMoves++;

        vector<Node*> children = mGraph.getSuccessors(currentNode);
        mNumExpanded++;

        mMaxQueue += children.size() - 1;

        for(int i = 0; i < children.size(); i++)
        {
            int childEval = HillClimbingEval(children[i])
            if(childEval > nextEval)
            {
                nextNode = children[i];
                nextEval = childEval
            }
        }

        HillPath[nextNode] = currentNode;

        if(currentNode == nextNode)
        {
            break;
        }
        else if(IsGoal(nextNode))
        {
            success = true;
        }

        currentNode = nextNode;
    }

    GeneratePath(HillPath, currentNode);

    return GenerateResults(success, SearchType.Hill);
}

int Searcher::HillClimbingEval(Node* node)
{
    int startDist = ManhattanDistance(mStartRow, mStartCol);
    return (startDist - ManhattanDistance(node->getRow(), node->getColumn()));
}

Result Searcher::BeamSearch()
{
    Node* currentNode = mGraph.getRoot();
    Node* prevNode = NULL;
    map<Node*,Node*> BeamPath;

    const int BEAM_SIZE = 4;

    mFrontier.push_back(currentNode);

    while(mFrontier.size() > 0 && !IsGoal(currentNode))
    {
        mNumMoves++;

        currentNode = mFrontier.front();
        mFrontier.pop_front();

        vector<Node*> children = mGraph.getSuccessors(currentNode);
        mNumExpanded++;

        for(int i  = 0; i < children.size(); i++)
        {
            mFrontier.push_back(children[i]);
        }

        sort(mFrontier.begin(), mFrontier.end(), BeamEval);

        if(mFrontier.size() > mMaxQueue)
        {
            mMaxQueue = mFrontier.size();
        }

        while(mFrontier.size() > BEAM_SIZE)
        {
            mFrontier.pop_back();
        }

        BeamPath[currentNode] = prevNode;

        prevNode = currentNode;
    }

    GeneratePath(BeamPath, currentNode);

    return GenerateResults(IsGoal(currentNode), SearchType.Beam);
}

bool Searcher::BeamEval(Node* a, Node* b)
{
    return (a->getCost() < b->getCost());
}

void Searcher::GeneratePath(map<Node*, Node*> path, Node* currentNode)
{
    while(currentNode != NULL)
    {
        mPath.push_front(currentNode);
        currentNode = path[currentNode];
    }
}

bool Searcher::IsGoal(Node* node)
{
    if(node->getRow() == mGoalRow && node->getColumn() == mGoalCol)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Result Searcher::GenerateResults(bool success, SearchType type)
{
    return Result(mNumMoves, mNumExpanded, mMaxQueue, success, type, mPath);
}

Graph Searcher::getGraph()
{
    return mGraph;
}

int Searcher::ManhattanDistance(int row, int col)
{
    int dist = abs(row - mGoalRow) + abs(col - mGoalCol);

    return dist;
}

void Searcher::CleanUp()
{
    mPath.clear();
    mFrontier.clear();
    mVisited.clear();
    mNumMoves = 0;
    mMaxQueue = 0;
    mNumExpanded = 0;
}