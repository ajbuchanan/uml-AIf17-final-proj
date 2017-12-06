#include "Results.hpp"

Results::Results(int moves, int expanded, std::deque<Node*> path)
{
    this->mTotalMoves = moves;
    this->mNumExpanded = expanded;
    this->mPath = path;
}

int Results::getTotalMoves()
{
    return mTotalMoves;
}

int Results::getNumExpanded()
{
    return mNumExpanded;
}

SearchType Results::getAlgorithmUsed()
{
    return mAlgorithUsed;
}

std::deque<Node*> Results::getPath()
{
    return mPath;
}