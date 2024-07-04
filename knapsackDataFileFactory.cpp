//
// Created by Adam on 18/01/2023.
//
#include <iostream>
#include <cstdlib>
#include <fstream>

class knapsackDataFileFactory {
public:
    knapsackDataFileFactory(int n, int knapsackCap, int maxWeight, int maxCost, std::string fileName) {
        std::ofstream dataFile;
        dataFile.open(fileName);
        if (!dataFile.good()) {
            std::cout << "Error while opening dataFile" << std::endl;
            exit(1);
        }
        dataFile << n << ' ' << knapsackCap << '\n';
        for (int i = 0; i < n; i++) dataFile << rand() % maxWeight + 1 << ' ' << rand() % maxCost + 1 << '\n';
    }
};
