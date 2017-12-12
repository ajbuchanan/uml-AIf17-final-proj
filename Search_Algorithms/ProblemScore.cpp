#include "ProblemScore.hpp"

ProblemScore::ProblemScore(std::vector<Result> results)
{
    mProblemResults = results;

    mScores[AStar] = 0;
    mScores[Beam] = 0;
    mScores[BFS] = 0;
    mScores[DFS] = 0;
    mScores[Hill] = 0;
    mScores[UCS] = 0;

    GenerateScores();
}

int ProblemScore::getASScore()
{
    return mScores[AStar];
}

int ProblemScore::getBeamScore()
{
    return mScores[Beam];
}

int ProblemScore::getBFSScore()
{
    return mScores[BFS];
}

int ProblemScore::getDFSScore()
{
    return mScores[DFS];
}

int ProblemScore::getHillScore()
{
    return mScores[Hill];
}

int ProblemScore::getUCSScore()
{
    return mScores[UCS];
}

std::vector<Result> ProblemScore::getResults()
{
    return mProblemResults;
}

std::map<SearchType,int> ProblemScore::getScores()
{
    return mScores;
}

void ProblemScore::GenerateScores()
{
    for(int i = 0; i < mProblemResults.size(); i++)
    {
        if(mProblemResults[i].foundGoal())
        {
            mScores[mProblemResults[i].getAlgorithmUsed()] += 4;
        }
    }

    int bestVal = INT_MAX;

    //Find shortest path
    for(int i = 0; i < mProblemResults.size(); i++)
    {
        int val = mProblemResults[i].getPath().size();
        if(val < bestVal)
        {
            bestVal = val;
        }
    }

    for(int i = 0; i < mProblemResults.size(); i++)
    {
        if(mProblemResults[i].getPath().size() == bestVal)
        {
            mScores[mProblemResults[i].getAlgorithmUsed()] += 2;
        }
    }
    
    //Find least number of nodes expanded
    bestVal = INT_MAX;

    for(int i = 0; i < mProblemResults.size(); i++)
    {
        int val = mProblemResults[i].getNumExpanded();
        if(val < bestVal)
        {
            bestVal = val;
        }
    }

    for(int i = 0; i < mProblemResults.size(); i++)
    {
        if(mProblemResults[i].getPath().size() == bestVal)
        {
            mScores[mProblemResults[i].getAlgorithmUsed()] += 2;
        }
    }
    
    //Find least number of nodes searched
    bestVal = INT_MAX;
    for(int i = 0; i < mProblemResults.size(); i++)
    {
        int val = mProblemResults[i].getMaxFrontier();
        if(val < bestVal)
        {
            bestVal = val;
        }
    }

    for(int i = 0; i < mProblemResults.size(); i++)
    {
        if(mProblemResults[i].getPath().size() == bestVal)
        {
            mScores[mProblemResults[i].getAlgorithmUsed()] += 2;
        }
    }
}