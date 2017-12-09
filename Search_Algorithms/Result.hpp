#include <deque>
#include <math.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Node.hpp"

using namespace std;

typedef enum searchType {AStar, BFS, DFS, UCS, Beam, Hill} SearchType;

class Result
{
private:
    int mTotalMoves;
    int mNumExpanded;
    int mMaxFrontier;
    bool mFoundGoal;
    SearchType mAlgorithmUsed;
    deque<Node*> mPath;

public:
    Result(int, int, int, bool, SearchType, vector<Node>);

    int getTotalMoves();
    int getNumExpanded();
    int getMaxFrontier();
    bool foundGoal();
    SearchType getAlgorithmUsed();
    deque<Node*> getPath();
};