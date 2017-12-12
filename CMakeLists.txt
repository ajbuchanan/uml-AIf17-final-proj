project(AI_PROJECT)

cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb3 -O0")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++11 /MP /Wall")
endif()

set(GA
    GA/expected_data.hpp
    GA/GeneticAlgorithmBool.cpp
    GA/GeneticAlgorithmBool.hpp
    Build/driver.cpp
)

set(SEARCH_ALGORITHMS
    Search_Algorithms/Edge.cpp
    Search_Algorithms/Edge.hpp
    Search_Algorithms/Graph.cpp
    Search_Algorithms/Graph.hpp
    Search_Algorithms/Node.cpp
    Search_Algorithms/Node.hpp
    Search_Algorithms/ProblemScore.cpp
    Search_Algorithms/ProblemScore.hpp
    Search_Algorithms/Result.cpp
    Search_Algorithms/Result.hpp
    Search_Algorithms/Searcher.cpp
    Search_Algorithms/Searcher.hpp
)

add_executable(${PROJECT_NAME}
    ${SEARCH_ALGORITHMS}
    ${GA}
)

set(TEST_PROBLEM_DATA
    TestProblems/prob1.map
    TestProblems/prob2.map
    TestProblems/prob3.map
    TestProblems/prob4.map
    TestProblems/prob5.map
    TestProblems/prob6.map
    TestProblems/prob7.map
    TestProblems/prob8.map
    TestProblems/prob9.map
    TestProblems/prob10.map
    TestProblems/prob11.map
    TestProblems/prob12.map
    TestProblems/prob13.map
    TestProblems/prob14.map
    TestProblems/prob15.map
    TestProblems/prob16.map
    TestProblems/prob17.map
    TestProblems/prob18.map
    TestProblems/prob19.map
    TestProblems/prob20.map
    TestProblems/prob21.map
    TestProblems/prob22.map
    TestProblems/prob23.map
    TestProblems/prob24.map
    TestProblems/prob25.map
    TestProblems/prob26.map
    TestProblems/prob27.map
    TestProblems/prob28.map
    TestProblems/prob29.map
    TestProblems/prob20.map
)

foreach(DATA ${PROJECT_DATA})
    configure_file(${DATA} ${CMAKE_CURRENT_BINARY_DIR}/${DATA_FILENAME} COPYONLY)
endforeach()