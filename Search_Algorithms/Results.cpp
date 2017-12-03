#include "Results.hpp"

Results::Results(int moves, int expanded, std::vector<Node*> path)
{
    this->mNumMoves = moves;
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

deque<Node*> Results::getPath()
{
    return mPath;
}