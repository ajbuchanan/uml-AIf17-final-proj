/*  Copyright 2017 George Le

*/
#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include <map> // std::map
#include <memory> // std::shared_ptr
#include <vector> // std::vector

#include "Search_Algorithms/Results.hpp"
#include "expected_data.hpp"

class GeneticAlgorithmBool
{
    public:
    static GeneticAlgorithmBool* get_instance_ptr(unsigned int number_of_traits, unsigned int size_of_initial_population, unsigned int number_of_generations) {
        static GeneticAlgorithmBool* instance = new GeneticAlgorithmBool(number_of_traits, size_of_initial_population, size_of_initial_population);
        return instance;
    }

    static std::shared_ptr<GeneticAlgorithmBool> get_instance(unsigned int number_of_traits, unsigned int size_of_initial_population, unsigned int number_of_generations) {
        static std::shared_ptr<GeneticAlgorithmBool> instance(new GeneticAlgorithmBool(number_of_traits, size_of_initial_population, size_of_initial_population));
        return instance;
    }

    /*----------------------------------------------------------------
        User calls this function which will return the fittest member 
        of the last generation of the genetic algorithm.
    ----------------------------------------------------------------*/
    std::vector<bool> get_fittest_pop() const { return m_fittest_population; }

    private:
    // The constructor of the genetic algorithm is private because the class
    // is a singleton.
    GeneticAlgorithmBool(unsigned int number_of_traits, unsigned int size_of_initial_population, unsigned int number_of_generations)
        : m_number_of_traits(number_of_traits), m_size_of_population(size_of_initial_population), m_number_of_generations(size_of_initial_population) { }

    /*-----------------------------------------------------------------
        This function generates pseudo-random sequences for each of the
        members of the population. Because this genetic algorithm uses
        boolean values to model the traits of the individuals of the
        population.
    -----------------------------------------------------------------*/
    void generate_random_population();
    
    /*-----------------------------------------------------------------
        This function determines which member of the population is the
        fittest member of the generation which will survive and 
        reproduce for the next generation. 
    -----------------------------------------------------------------*/
    void fitness_function();
    
    /*-----------------------------------------------------------------
    
    -----------------------------------------------------------------*/
    void crossover();

    /*-----------------------------------------------------------------
    
    -----------------------------------------------------------------*/
    void mutation();

    std::map<int, std::vector<bool>> m_generation;

    std::vector<bool> m_fittest_population;

    unsigned int m_number_of_traits;
    unsigned int m_size_of_population;
    unsigned int m_number_of_generations;
};

#endif // GENETIC_ALGORITHM_HPP