cmake_minimum_required(VERSION 3.24)
project(ga_Knapsack)

set(CMAKE_CXX_STANDARD 14)

add_executable(ga_Knapsack
        CIndividual.cpp
        CKnapsackProblem.cpp
        knapsackDataFileFactory.cpp
        main.cpp)
