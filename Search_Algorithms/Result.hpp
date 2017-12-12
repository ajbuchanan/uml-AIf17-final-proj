#ifndef RESULTS_HPP
#define RESULTS_HPP

#include <deque>
#include <vector>

#include "Node.hpp"

typedef enum searchType {AStar, BFS, DFS, UCS, Beam, Hill, LAST_SEARCH_TYPE} SearchType;

class Result
{
private:
    int mNumMoves;
    int mTotalMoves;
    int mNumExpanded;
    int mMaxFrontier;
    bool mFoundGoal;
    SearchType mAlgorithmUsed;
    std::deque<Node*> mPath;

public:
    Result(int, int, int, bool, SearchType, std::deque<Node*>);

    int getTotalMoves();
    int getNumExpanded();
    int getMaxFrontier();
    bool foundGoal();
    SearchType getAlgorithmUsed();
    std::deque<Node*> getPath();
};

#endif