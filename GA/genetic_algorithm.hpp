/*  Copyright 2017 George Le

*/
#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include <vector>

class GeneticAlgorithm
{
    public:
    GeneticAlgorithm();
    
    private:
    std::vector<bool> m_population;
};

#endif // GENETIC_ALGORITHM_HPP