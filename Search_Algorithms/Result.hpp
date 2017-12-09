#ifndef RESULTS_HPP
#define RESULTS_HPP

#include <deque>

#include "Node.hpp"

typedef enum searchType {AStar, BFS, DFS, UCS, Beam, Hill} SearchType;

class Result
{
private:
    int mTotalMoves;
    int mNumExpanded;
    int mMaxFrontier;
    bool mFoundGoal;
    SearchType mAlgorithmUsed;
    std::deque<Node*> mPath;

public:
    Result(int, int, int, bool, SearchType, vector<Node>);

    int getTotalMoves();
    int getNumExpanded();
    int getMaxFrontier();
    bool foundGoal();
    SearchType getAlgorithmUsed();
    std::deque<Node*> getPath();
};

#endif