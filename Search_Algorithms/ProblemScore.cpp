#include "ProblemScore.hpp"

ProblemScore::ProblemScore(std::vector<Result> results)
{
    mProblemResults = results;

    mScores[SearchType.AStar] = 0;
    mScores[SearchType.Beam] = 0;
    mScores[SearchType.BFS] = 0;
    mScores[SearchType.DFS] = 0;
    mScores[SearchType.Hill] = 0;
    mScores[SearchType.UCS] = 0;

    GenerateScores();
}

int ProblemScore::getASScore()
{
    return mScores[SearchType.AStar];
}

int ProblemScore::getBeamScore()
{
    return mScores[SearchType.Beam];
}

int ProblemScore::getBFSScore()
{
    return mScores[SearchType.BFS];
}

int ProblemScore::getDFSScore()
{
    return mScores[SearchType.DFS];
}

int ProblemScore::getHillScore()
{
    return mScores[SearchType.Hill];
}

int ProblemScore::getUCSScore()
{
    return mScores[SearchType.UCS];
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