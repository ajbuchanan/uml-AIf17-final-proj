#ifndef SEARCHER_HPP
#define SEARCHER_HPP

#include <map>
#include <deque>
#include <vector>
#include <math.h>
#include <string>

#include "Node.hpp"
#include "Result.hpp"
#include "Graph.hpp"

//Size of an edge of a maze N x N
#define BOARDSIZE 10

//Constants defining what each node on the map is
static const char EMPT   = '.'; //Empty space
static const char START  = 's'; //Starting Position
static const char WALL   = 'x'; //Obstacle
static const char GOAL   = 'g'; //Goal State
static const char EXP    = 'e'; //expanded state
    
class Searcher
{
private:
    char mMaze[BOARDSIZE][BOARDSIZE];
    char mRoute[BOARDSIZE][BOARDSIZE];

    std::string mProblemFile;

    //Start Position
    int mStartRow;
    int mStartCol;

    //Goal Position
    int mGoalRow;
    int mGoalCol;

    int mNumMoves;
    int mNumExpanded;
    int mMaxQueue;

    std::deque<Node*> mFrontier;
    std::deque<Node*> mVisited;
    std::deque<Node*> mPath;

    std::vector<Result> mResults;

    Graph mGraph;

    //Private funcs
    void                    GeneratePath(std::map<Node*,Node*>,Node*);
    Result                  GenerateResults(bool,SearchType);
    void                    GenerateGraph(std::string file);
    bool                    BeamEval(Node*,Node*);
    int                     HillClimbingEval(Node*);
    bool                    IsGoal(Node* node);
    void                    CleanUp();

    int                     ManhattanDistance(int row, int col);

public:
    /*Constructor*/         Searcher(std::string);

    std::vector<Result>     SearchAll();

    Result                  AStarSearch();
    Result                  BreadthFirstSearch();
    Result                  DepthFirstSearch();
    Result                  UniformCostSearch();
    Result                  BeamSearch();
    Result                  HillClimbingSearch();

    Graph                   GetGraph() const;

    //utility functions
    void                    Print();
};

#endif