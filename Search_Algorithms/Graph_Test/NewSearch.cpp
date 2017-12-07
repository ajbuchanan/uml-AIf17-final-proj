#include "Searcher.hpp"

using namespace std;

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
    Node* prevNode = new Node(mStartRow, mStartCol, 0, NULL, ManhattanDistance(mStartRow, mStartCol));

    std::deque<std::pair<Node*,Node*> > graphQueue;

    graphQueue.push_back(std::pair(NULL, prevNode));

    mGraph = Graph();
    mGraph.addNode(prevNode);

    while(graphQueue.size() > 0)
    {
        std::pair<Node*,Node*> current = graphQueue.front();
        graphQueue.pop_front();
        int row = current.second->getRow();
        int col = current.second->getColumn();
        gMaze[row][col] = EXP;

        if(row+1 < BOARDSIZE && (gMaze[row+1][col] == OPEN || gMaze[row+1][col] == GOAL))
        {
            Node* upNode = new Node(row+1, col,numLooked, current.second, ManhattanDistance(row+1, col))
            mGraph.addNode(upNode);
            mGraph.addEdge(current.second, upNode);

            graphQueue.push_back(std::pair(current.second, upNode));
        }
        if(row-1 >= 0 && (gMaze[row-1][col] == OPEN || gMaze[row-1][col] == GOAL))
        {
            Node* downNode = new Node(row-1, col,numLooked, current.second, ManhattanDistance(row-1, col))
            mGraph.addNode(downNode);
            mGraph.addEdge(current.second, downNode);

            graphQueue.push_back(std::pair(current.second, downNode));
        }
        if(col+1 < BOARDSIZE && (gMaze[row][col+1] == OPEN || gMaze[row][col+1] == GOAL))
        {
            Node* rightNode = new Node(row, col+1,numLooked, current.second, ManhattanDistance(row, col+1))
            mGraph.addNode(rightNode);
            mGraph.addEdge(current.second, rightNode);

            graphQueue.push_back(std::pair(current.second, rightNode));
        }
        if(col-1 >= 0 && (gMaze[row][col-1] == OPEN || gMaze[row][col-1] == GOAL))
        {
            Node* leftNode = new Node(row, col-1,numLooked, current.second, ManhattanDistance(row, col-1))
            mGraph.addNode(leftNode);
            mGraph.addEdge(current.second, leftNode);

            graphQueue.push_back(std::pair(current.second, leftNode));
        }
    }
}

Results Searcher::DepthFirstSearch()
{
    Node* currentNode = mGraph.getNode(mStartRow, mStartCol);
    Node* prevNode = NULL;
    map<Node*, Node*> DFSPath;

    mFrontier.push_front(currentNode);

    while(!IsGoal(currentNode))
    {
        DFSPath[currentNode] = prevNode;

        vector<Node*> successors = mGraph.getSuccessors(currentNode);

        mVisited.push_back(currentNode);

        for(int i = successors.size()-1; i >= 0; i--)
        {
            mFrontier.push_front(successors[i]);
        }

        prevNode = currentNode;

        currentNode = mFrontier.front();
        mFrontier.pop_front();
    }

    GeneratePath(DFSPath, currentNode);
    //Generate Results
}

Results Searcher::BreadthFirstSearch()
{
    Node* currentNode = mGraph.getNode(mStartRow, mStartCol);
    Node* prevNode = NULL;
    map<Node*, Node*> BFSPath;

    mFrontier.push_back(currentNode);

    while(!IsGoal(currentNode))
    {
        BFSPath[currentNode] = prevNode;

        vector<Node*> successors = mGraph.getSuccessors(currentNode);

        mVisited.push_back(currentNode);

        for(int i = 0; i < successors.size(); i++)
        {
            mFrontier.push_back(successors[i]);
        }

        prevNode = currentNode;

        currentNode = mFrontier.front();
        mFrontier.pop_front();
    }

    GeneratePath(BFSPath, currentNode);
    //Generate Results

}

Results Searcher::AStarSearch()
{
    Node* currentNode = mGraph.getNode(mStartRow, mStartCol);
    mFrontier.push_back(currentNode);
    map<Node*, Node*> ASPath;
    map<Node*, int> gScore;
    gScore[currentNode] = 0;
    map<Node*, int> fScore;
    fScore[currentNode] = currentNode->getCost();

    while(mFrontier.size() > 0)
    {
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
        for(int i = 0; i < successors.size(); i++)
        {
            if(std::find(mVisited.begin(), mVisited.end(), successors[i]) != mVisited.end())
            {
                continue;
            }
            if(std::find(mFrontier.begin(), mFrontier.end(), successors[i]) == mFrontier.end())
            {
                mFrontier.push_back(successors[i]);
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
}

void Searcher::UniformCostSearch()
{
    Node* currentNode = mGraph.getNode(mStartRow, mStartCol);
    mFrontier.push_back(currentNode);
    map<Node*, Node*> UCSPath;
    map<Node*, int> gScore;
    gScore[currentNode] = 0;
    map<Node*, int> fScore;
    fScore[currentNode] = 1;

    while(mFrontier.size() > 0)
    {
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
        for(int i = 0; i < successors.size(); i++)
        {
            if(std::find(mVisited.begin(), mVisited.end(), successors[i]) != mVisited.end())
            {
                continue;
            }
            if(std::find(mFrontier.begin(), mFrontier.end(), successors[i]) == mFrontier.end())
            {
                mFrontier.push_back(successors[i]);
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