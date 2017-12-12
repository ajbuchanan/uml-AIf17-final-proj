#include <random>

#include "GeneticAlgorithmBool.hpp"

bool return_random_bool()
{
    int random_number = -1;
	
	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<> dist(0, 1);
	random_number = dist(gen); 

    if(random_number)
    {
        return true;
    }
    return false;
}

void GeneticAlgorithmBool::generate_random_population()
{
    for(int i = 0; i < m_size_of_population; ++i)
    {
        for(int j = 0; i < m_number_of_traits; ++i)
        {
            /*------------------------------------------------------
                Creates a member of the population with n number
                of traits; each trait is generated randomly.
             Ex: 
              For a member with four traits, it could be a vector
              containing:
                  { true, false, true, false }
              This individual would have the first and third trait
              and not the second and fourth trait. The use of a map
              allows for each individual of a generation to be mapped
              to an integer value for easy lookup. 
            -------------------------------------------------------*/
            m_generation[i].push_back(return_random_bool());
        }
    }
}
    
void GeneticAlgorithmBool::fitness_function()
{
    int highest_score = 0, index_of_highest_scores = 0;

    for(unsigned int i = 0; i < m_size_of_population; ++i)
    {
        
    }
}

void GeneticAlgorithmBool::crossover()
{
    // TODO
}

void GeneticAlgorithmBool::mutation()
{
    // TODO
}