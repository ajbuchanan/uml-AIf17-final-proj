#include <algorithm> // std::swap_ranges
#include <random> // std::mt19937, std::random_device, std::uniform_int_distribution

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

int return_rand_index(int smallest_index, int greatest_index)
{
    int random_number = -1;
	
	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<> dist(smallest_index, greatest_index);
	random_number = dist(gen); 

    return random_number;
}

ExpectedData GeneticAlgorithmBool::generate_expected_data()
{
    for(unsigned int i = 0; i < m_repetitions; ++i)
    {
        for(unsigned int i = 0; i < m_current_problem.size(); ++i)
        {
            Searcher searches(m_current_problem.at(i));
            ProblemScore scores(searches.SearchAll());

            generate_random_population();

            for(unsigned int i = 1; i < m_number_of_generations; ++i)
            {   
                fitness_function(scores);
                crossover();
            }
        }
    }

    return ExpectedData(m_current_problem, scores.getResults())
}

void GeneticAlgorithmBool::generate_random_population()
{
    ++m_current_generation;
    for(int index = 0; index < m_size_of_population; ++index)
    {
        for(int j = 0; j < m_number_of_traits; ++j)
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
            m_generations[m_current_generation][index].push_back(return_random_bool());
        }
    }
}
    
void GeneticAlgorithmBool::fitness_function(const ProblemScore& scores)
{
    std::vector<double> average_scores = {m_size_of_population , 0.0};

    for(unsigned int index = 0; index < m_size_of_population; ++index)
    {
        for(unsigned int i = 0; i < m_number_of_traits; ++i)
        {
            if(m_generations.at(m_current_generation).at(index).at(i))
            {
                average_scores.at(index) += (double)scores.getScores().at(i);
            }
            average_scores.at(index) / (double)m_number_of_traits;
        }
    }

    std::sort(average_scores.begin(), average_scores.end());

    double median = average_scores.at(average_scores.size() / 2);

    for(unsigned int index = 0; index < m_size_of_population; ++index)
    {
        if(average_scores.at(index) >= median)
        {
            m_fittest_population.push_back(m_generations.at(m_current_generation).at(index));
        }
    }
}

void GeneticAlgorithmBool::crossover()
{
    int index_parent1 = -1, index_parent2 = -1;

    // push all the fittest population into the next generation
    for(unsigned int i = 0; i < m_fittest_population.size(); ++i)
    {
        m_generations[m_current_generation + 1].push_back(m_fittest_population.at(i));
    }

    // select two at random of the fittest population to reproduce
    // a new individual of the next generation and there is a coin
    // flip to see if the individual has a mutation. Add the new 
    // individual to the next generation.
    while(m_generations.at(m_current_generation + 1).size() < m_size_of_population)
    {
        // generates where the start and the end points of the uniform crossover
        int index_start_flip = return_rand_index(0, m_fittest_population.size() - 2);
        int index_end_flip = return_rand_index(index_start_flip + 1, m_fittest_population.size() - 1);

        // randomly selects two parents
        index_parent1 = return_rand_index(0, m_fittest_population.size());
        index_parent2 = return_rand_index(0, m_fittest_population.size());

        // creates two children from the two parents
        std::vector<bool> child1 = m_fittest_population.at(index_parent1);
        std::vector<bool> child2 = m_fittest_population.at(index_parent2);

        // applies the crossover to the children at the randomly generated start and end points
        std::swap_ranges(child1.begin + index_start_flip, child2.begin + index_end_flip, child2.begin + index_start_flip);

        // coin flip to see if the child recieves a mutation
        if(return_random_bool())
        {
            mutation(child1);
        }
        if(return_random_bool())
        {
            mutation(child2);
        }
        // adds the child to the new generation
        m_generations.at(m_current_generation + 1).push_back(child1);
        // checks if the child can join the new generation or if its addition will
        // overpopulate the next generation
        if(m_generations.at(m_current_generation + 1).size() < m_size_of_population)
        {
            // if there is still space in the next generation, the child is added
            m_generations.at(m_current_generation + 1).push_back(child2);
        }
    }
    // move onto the next generation
    ++m_current_generation;
}

void GeneticAlgorithmBool::mutation(std::vector<bool> child)
{   
    int random_index = return_rand_index(0, child.size());

    child.at(random_index) = !child.at(random_index);
}