#ifndef RESULTS_HPP
#define RESULTS_HPP

#include <deque>

#include "Node.hpp"

typedef enum searchType {AStar, BFS, DFS, UCS} SearchType;

class Results
{
private:
    int mTotalMoves;
    int mNumExpanded;
    SearchType mAlgorithUsed;
    std::deque<Node*> mPath;

public:
    Results(int moves, int expanded, std::deque<Node*> path);
    
    int getTotalMoves();
    int getNumExpanded();
    SearchType getAlgorithmUsed();
    std::deque<Node*> getPath();
};

#endif