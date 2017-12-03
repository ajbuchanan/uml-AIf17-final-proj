/*  Copyright 2017 George Le

    Creates usable data
*/

#ifndef PARSE_TRAINING_DATA_HPP
#define PARSE_TRAINING_DATA_HPP

#include <map> // std::map
#include <memory> // std::shared_ptr
#include <string> // std::string
#include <utility> // std::pair
#include <vector> // std::vector

template <class T>
class ExpectedData
{
    public:
    ExpectedData();
    ExpectedData(std::vector<T> problems, std::vector<auto> solution, std::vector<std::string> problem_labels) :
        m_problems { problems }, m_solution { solution }, m_problem_labels { problem_labels }

    // accessor function
    T get_problem(unsigned int problem_number) const { return m_problems.at(problem_number); }
    auto get_solution(unsigned int problem_number) const { return m_solutions.at(problem_number); }
    std::string get_problem_label(unsigned int problem_number) const { return m_problem_labels.at(problem_number); }

    private:
    // the problems that are to be solved that can be quantified by a class T
    std::vector<T> m_problems;
    
    // the true solution to the problems
    std::vector<unsigned int> m_solutions;
    
    // the labels for the problem's solution
    std::vector<std::string> m_problem_labels;
};

#endif // PARSE_TRAINING_DATA_HPP