#include <deque>
#include <climits>
#include <math.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Node.hpp"
#include "Result.hpp"
#include "Graph.hpp"

using namespace std;

//Size of an edge of a maze N x N
static const int BOARDSIZE = 10;

//Constants defining what each node on the map is
static const char EMPT   = '.'; //Empty space
static const char START  = 's'; //Starting Position
static const char WALL   = 'x'; //Obstacle
static const char GOAL   = 'g'; //Goal State

class Searcher
{
private:
    char mMaze[BOARDSIZE][BOARDSIZE];
    char mRoute[BOARDSIZE][BOARDSIZE];

    string mProblemFile;

    //Start Position
    int mStartRow;
    int mStartCol;

    //Goal Position
    int mGoalRow;
    int mGoalCol;

    int mNumMoves;
    int mNumExpanded;
    int mMaxQueue;

    deque<Node*> mFrontier;
    deque<Node*> mVisited;
    deque<Node*> mPath;

    vector<Result> mResults;

    Graph mGraph;

    //Private funcs
    void                    GeneratePath(map<Node*,Node*>,Node*);
    Results                 GenerateResults(bool,SearchType);
    bool                    BeamEval(Node*,Node*);
    int                     HillClimbingEval(Node*);
    void                    CleanUp();

public:
    /*Constructor*/         Searcher(string);

    vector<Result>          SearchAll();

    Result                  AStarSearch();
    Result                  BreadthFirstSearch();
    Result                  DepthFirstSearch();
    Result                  UniformCostSearch();

    Graph                   GetGraph()const;

    //utility functions
    void                    Print();
};