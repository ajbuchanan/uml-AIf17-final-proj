/*  Copyright 2017 George Le

*/
#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include <map> // std::map
#include <memory> // std::shared_ptr
#include <vector> // std::vector

#include "Search_Algorithms/Result.hpp"
#include "Search_Algorithms/ProblemScore.hpp"
#include "Search_Algorithms/Searcher.hpp"
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

    void add_problem(const std::string& filename) { m_current_problem.push_back(filename); }

    void set_repetitions(unsigned int repetitions) { m_repetitions = repetitions; }

    /*----------------------------------------------------------------
        User calls this function which will return the ExpectedData 
        that the genetic algorithm 
    ----------------------------------------------------------------*/
    ExpectedData generate_expected_data();

    private:
    // The constructor of the genetic algorithm is private because the class
    // is a singleton.
    GeneticAlgorithmBool(unsigned int number_of_traits, unsigned int size_of_initial_population, unsigned int number_of_generation)
        : m_number_of_traits(number_of_traits), m_size_of_population(size_of_initial_population), m_number_of_generations(size_of_initial_population), m_current_generation(0)
            m_repetitions(100) { }

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
    void fitness_function(const ProblemScore& scores);
    
    /*-----------------------------------------------------------------
        Performs two point crossover on the parent organism strings.
    -----------------------------------------------------------------*/
    void crossover();

    /*--------------------------------------------------------------------
        Performs a bit string mutation on the child of the new generation.
    --------------------------------------------------------------------*/
    void mutation(std::vector<bool> child);

    std::map<int, std::vector<std::vector<bool>>> m_generations;

    std::vector<std::vector<bool>> m_fittest_population;

    std::vector<std::string> m_current_problem;

    unsigned int m_number_of_traits;
    unsigned int m_size_of_population;
    unsigned int m_number_of_generations;
    unsigned int m_current_generation;
    unsigned int m_repetitions;
};

#endif // GENETIC_ALGORITHM_HPP