#ifndef SEARCHER_HPP
#define SEARCHER_HPP

#include <deque>

#include "Node.hpp"
#include "Results.hpp"

//Size of an edge of a maze N x N
static const int BOARDSIZE = 10;

//Which algorithm we are using
static bool BFS = true;     //Breadth First Search
static bool DFS = false;    //Depth First Search
static bool AS  = false;    //A*
static bool UCS = false;    //Uniform Cost Search

//Constants defining what each node on the map is
static const char EMPT   = '.'; //Empty space
static const char START  = 's'; //Starting Position
static const char WALL   = 'x'; //Obstacle
static const char OPEN   = 'o'; //Node that has been added to queue but not expanded
static const char EXP    = 'e'; //Node that has been expanded (visited)
static const char GOAL   = 'g'; //Goal State

class Searcher
{
private:
    char mMaze[BOARDSIZE][BOARDSIZE];
    char mRoute[BOARDSIZE][BOARDSIZE];

    //Start Position
    int mStartRow;
    int mStartCol;

    //Goal Position
    int mGoalRow;
    int mGoalCol;

    int mNumMoves;
    int mMaxQueue;

    //If set to true will print to console the results of the searches
    bool mDebugMode;

    std::deque<Node*> mFrontier;
    std::deque<Node*> mVisited;
    std::deque<Node*> mPath;

    //Private funcs
    void        Search();
    void        GenericSearch(int, int);
    void        HeuristicSearch(int, int, int, Node*);
    void        GeneratePath();
    Results*    GenerateResults();

    int ManhattanDistance(int row, int col);

public:
    Searcher(std::string file = "TestProblems/template.map", bool debug = false);

    void        AStarSearch();
    void        BreadthFirstSearch();
    void        DepthFirstSearch();
    void        UniformCostSearch();

    //utility functions
    void        Print();
    void        CleanUp();
    void        SetDebugMode(bool); //turns on or off debug mode
};

#endif