#ifndef PROBLEM_SCORE_HPP
#define PROBLEM_SCORE_HPP

#include <map>
#include <vector>

#include "Result.hpp"

class ProblemScore
{
private:
    std::vector<Result>         mProblemResults;
    std::map<SearchType,int>    mScores;

    void                        GenerateScores();

public:
    /*Constructor*/             ProblemScore(std::vector<Result>);

    int                         getASScore();
    int                         getBFSScore();
    int                         getBeamScore();
    int                         getDFSScore();
    int                         getHillScore();
    int                         getUCSScore();
    std::vector<Result>         getResults();
    std::map<SearchType,int>    getScores();
};

#endif // PROBLEM_SCORE_HPP