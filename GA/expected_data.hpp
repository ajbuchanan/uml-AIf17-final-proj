/*  Copyright 2017 George Le

*/
#ifndef EXPECTED_DATA_HPP
#define EXPECTED_DATA_HPP

#include <iostream> // std::cout
#include <map> // std::map
#include <memory> // std::shared_ptr
#include <string> // std::string
#include <utility> // std::pair
#include <vector> // std::vector

#include "Search_Algorithm/Node.hpp"

class ExpectedData
{
    public:
    ExpectedData(std::vector<std::string> problems, std::vector<Node*> solution, std::vector<std::string> problem_labels)
    {
        if((problems.size() != solution.size()) && (solution.size() != problem_labels.size()))
        {
            std::cout << "Error: vectors provided into ExpectedData class are not of the same size\n";
            return;
        }

        for(int i = 0; i < problems.size(); ++i)
        {
            m_stored_data.emplace(problems.at(i), make_pair(solution.at(i), problem_labels.at(i)));
        }
    }
    
    // accessor function
    std::vector<Node*> get_solution(std::string problem) const { return m_stored_data.at(problem).first; }
    std::string get_problem_label(std::string problem) const { return m_stored_data.at(problem).second; }

    // TODO comparison operator between what is returned by the ANN and this expected data class
    // bool operator==(const ExpectedData& first)

    private:
    // The problems that are to be solved are stored in the files,
    // whose names are tracked as strings and are stored and mapped
    // to the true solution to the problems storing the ids for the 
    // various nodes that comprise the solution to the problems. 
    std::map<std::string, std::pair<std::vector<Node*>, std::string>> m_stored_data;
};

#endif // EXPECTED_DATA_HPP