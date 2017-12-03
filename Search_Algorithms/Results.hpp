#include <deque>
#include <math.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Node.hpp"

using namespace std;

typedef enum searchType {AStar, BFS, DFS, UCS} SearchType;

class Results
{
private:
    int mTotalMoves;
    int mNumExpanded;
    SearchType mAlgorithUsed;
    deque<Node*> mPath;

public:
    Results(int, int, std::vector<Node>);

    int getTotalMoves();
    int getNumExpanded();
    SearchType getAlgorithmUsed();
    deque<Node*> getPath();
};