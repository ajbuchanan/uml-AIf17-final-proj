#include <deque>
#include <math.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Node.hpp"
#include "Searcher.hpp"

using namespace std;

Searcher::Searcher(std::string file, bool debug) : mNumMoves(0), mMaxQueue(0)
{
    mDebugMode = debug;
    ifstream mazeFile;
    mazeFile.open(file, ios::in);

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
}

int Searcher::ManhattanDistance(int row, int col)
{
    int dist = abs(row - mGoalRow) + abs(col - mGoalCol);

    return dist;
}

void Searcher::Search()
{
    Node* startNode = new Node(mStartRow, mStartCol, 0, 0);
    if(BFS)
    {
        mFrontier.push_back(startNode);
    }
    else if(DFS)
    {
        mFrontier.push_front(startNode);
    }
    else if(AS || UCS)
    {
        int cost = -1;

        if(AS)
        {
            cost = this->ManhattanDistance(mStartRow, mStartCol);
        }
        else if(UCS)
        {
            cost = 1;
        }

        mFrontier.push_back(new Node(mStartRow, mStartCol, 0, startNode ,cost));
    }

    mMaxQueue = 1;

    mMaze[mStartRow][mStartCol] = OPEN;

    int row = 0;
    int col = 0;

    bool win = false;

    while(mFrontier.size() != 0)
    {
        row = mFrontier.front()->getRow();
        col = mFrontier.front()->getColumn();

        mRoute[row][col] = EXP;
        mNumMoves++;

        if(mMaze[row][col] == GOAL)
        {
            mVisited.push_back(mFrontier.front());
            mFrontier.pop_front();
            win = true;
            break;
        }
        else
        {
            mVisited.push_back(mFrontier.front());
            mFrontier.pop_front();
            
            GenericSearch(row,col);
        }
    }

    if(!win)
    {
        cout << "Failed to find Solution" << endl;
    }

    if(mDebugMode)
    {
        Print();
    }
    else
    {
        GeneratePath();
    }
}

void Searcher::GenericSearch(int row, int col)
{
    int depth = (mVisited.back()->getDepth()) + 1;
    Node* parent = mVisited.back();

    //Node left of current position
    if((col - 1 > -1) && mRoute[row][col-1] != WALL && mRoute[row][col-1] != EXP && mRoute[row][col-1] != OPEN)
    {
        mRoute[row][col-1] = OPEN;

        if(BFS)
        {
            mFrontier.push_back(new Node(row, col-1, depth, parent));
        }
        else if(DFS)
        {
            mFrontier.push_front(new Node(row, col-1, depth, parent));
        }
        else if(AS || UCS)
        {
            HeuristicSearch(row, col-1, depth, parent);
        }
    }

    //Node above current position
    if((row - 1 > -1) && mRoute[row-1][col] != WALL && mRoute[row-1][col] != EXP && mRoute[row-1][col] != OPEN)
    {
        mRoute[row-1][col] = OPEN;

        if(BFS)
        {
            mFrontier.push_back(new Node(row-1, col, depth, parent));
        }
        else if(DFS)
        {
            mFrontier.push_front(new Node(row-1, col, depth, parent));
        }
        else if(AS || UCS)
        {
            HeuristicSearch(row-1, col, depth, parent);
        }
    }

    //Node right of the current position
    if((col + 1 > BOARDSIZE) && mRoute[row][col+1] != WALL && mRoute[row][col+1] != EXP && mRoute[row][col+1] != OPEN)
    {
        mRoute[row][col+1] = OPEN;

        if(BFS)
        {
            mFrontier.push_back(new Node(row, col+1, depth, parent));
        }
        else if(DFS)
        {
            mFrontier.push_front(new Node(row, col+1, depth, parent));
        }
        else if(AS || UCS)
        {
            HeuristicSearch(row, col+1, depth, parent);
        }
    }

    //Node below current position
    if((row + 1 > BOARDSIZE) && mRoute[row+1][col] != WALL && mRoute[row+1][col] != EXP && mRoute[row+1][col] != OPEN)
    {
        mRoute[row+1][col] = OPEN;

        if(BFS)
        {
            mFrontier.push_back(new Node(row+1, col, depth, parent));
        }
        else if(DFS)
        {
            mFrontier.push_front(new Node(row+1, col, depth, parent));
        }
        else if(AS || UCS)
        {
            HeuristicSearch(row+1, col, depth, parent);
        }
    }

    mMaxQueue = (mFrontier.size() > mMaxQueue) ? mFrontier.size() : mMaxQueue;
}

void Searcher::HeuristicSearch(int row, int col, int depth, Node* parent)
{
    int heuristic = -1;
    if(AS)
    {
        heuristic = ManhattanDistance(row, col) + depth;
    }
    else if(UCS)
    {
        heuristic = 1;
    }
    else
    {
        cout << "Wrong Method, something broke\n";
        return;
    }

    bool insertSuccess = false;

    if(mFrontier.size() == 0)
    {
        mFrontier.push_back(new Node(row, col, depth, parent, heuristic));
    }
    else
    {
        deque<Node*>::iterator iter;
        int i = 0;

        for(iter = mFrontier.begin(); iter != mFrontier.end(); iter++)
        {
            if(heuristic < mFrontier[i]->getCost())
            {
                mFrontier.insert(iter, new Node(row, col, depth, parent, heuristic));
                insertSuccess = true;
                break;
            }
            i++;
        }

        if(!insertSuccess)
        {
            mFrontier.push_back(new Node(row, col, depth, parent, heuristic));
        }
    }
}

void Searcher::GeneratePath()
{
    Node* graphIterator;

    for(graphIterator = mVisited.back(); graphIterator->getParent() != 0; graphIterator = graphIterator->getParent())
    {
        mPath.push_front(graphIterator);
    }

    mPath.push_front(graphIterator);
}

void Searcher::Print()
{
    GeneratePath();

    cout << "\nSolution" << endl;

    for(int i = 0; i < BOARDSIZE; i++)
    {
        for(int j = 0; j < BOARDSIZE; j++)
        {
            if(mMaze[i][j] == WALL)
            {
                cout << "X";
            }
            else if(mMaze[i][j] == START)
            {
                cout << "S";
            }
            else if(mMaze[i][j] == GOAL)
            {
                cout << "G";
            }
            else
            {
                bool onPath = false;
                for(int x = 0; x < mPath.size(); x++)
                {
                    if(mPath[x]->getRow() == i && mPath[x]->getColumn() == j)
                    {
                        onPath = true;
                    }
                }

                if(onPath)
                {
                    cout << ".";
                }
                else
                {
                    cout << " ";
                }
            }
        }
        cout << "\n";
    }

    cout << "\nNode Order: " << endl;
	for ( int k = 0; k < mPath.size(); k++ )
    {
         cout << "(" << ( mPath[k]->getColumn() ) << "," <<  BOARDSIZE - ( mPath[k]->getRow() ) - 1 << ")";

         if( k < path.size() - 1 )
         {
             cout << " -> ";
         }
    }

    cout << "\n\n";

    cout << "Total Length: " << mPath.size() << "\n";
    cout << "Total Number of Moves: " << mNumMoves-1 << "\n";
    cout << "Max Size of Frontier: " << mMaxQueue << "\n";
    cout << "Final Frontier Size: " << mFrontier.size() << "\n";
    cout << "Number of Expanded Nodes: " << mVisited.size() << "\n";
    cout << "Total Nodes Looked at: " << mFrontier.size() + mVisited.size() << "\n";
}

void Searcher::CleanUp()
{
    for(int i = 0; i < BOARDSIZE; i++)
    {
        for(int j = 0; j < BOARDSIZE; j++)
        {
            mRoute[i][j] = mMaze[i][j];
        }
    }

    mFrontier.clear();
    mVisited.clear();
    mNumMoves = 0;
    mMaxQueue = 0;
}

Results* Searcher::GenerateResults()
{
    return new Results(mNumMoves, mVisited.size(), mPath);
}

void Searcher::AStarSearch()
{
    AS = true;
    BFS = false;
    DFS = false;
    UCS = false;

    Search();
    Results res = GenerateResults();
}

void Searcher::BreadthFirstSearch()
{
    AS = false;
    BFS = true;
    DFS = false;
    UCS = false;

    Search();
    Results res = GenerateResults();
}

void Searcher::DepthFirstSearch()
{
    AS = false;
    BFS = false;
    DFS = true;
    UCS = false;
    
    Search();
    Results res = GenerateResults();
}

void Searcher::UniformCostSearch()
{
    AS = false;
    BFS = false;
    DFS = false;
    UCS = true;
    
    Search();
    Results res = GenerateResults();
}

void Searcher::SetDebugMode(bool debug)
{
    mDebugMode = debug;
}

//------------------Main Method, for test Purposes-----------------------------

int main()
{
    Searcher* s = new Searcher();

    s->AStarSearch();
    s->BreadthFirstSearch();
    s->DepthFirstSearch();
    s->UniformCostSearch();
}