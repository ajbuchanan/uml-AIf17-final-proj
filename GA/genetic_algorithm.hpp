/*  Copyright 2017 George Le

*/
#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include <vector>

class GeneticAlgorithm_bool
{
    public:
    GeneticAlgorithm_bool();
    
    void generate_random_population();
    
    double fitness_function();
    
    void crossover();

    void mutation();

    unsigned int generate_new_population();

    private:
    std::vector<std::vector<bool>> m_population;
};

#endif // GENETIC_ALGORITHM_HPP