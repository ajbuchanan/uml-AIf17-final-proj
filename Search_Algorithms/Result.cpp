#include "Result.hpp"

Result::Result(int moves, int expanded, int frontier, bool success, SearchType type, std::deque<Node*> path)
{
    mNumMoves = moves;
    mNumExpanded = expanded;
    mMaxFrontier = frontier;
    mFoundGoal = success;
    mAlgorithmUsed = type;
    mPath = path;
}

int Result::getTotalMoves()
{
    return mTotalMoves;
}

int Result::getNumExpanded()
{
    return mNumExpanded;
}

int Result::getMaxFrontier()
{
    return mMaxFrontier;
}

bool Result::foundGoal()
{
    return mFoundGoal;
}

SearchType Result::getAlgorithmUsed()
{
    return mAlgorithmUsed;
}

std::deque<Node*> Result::getPath()
{
    return mPath;
}