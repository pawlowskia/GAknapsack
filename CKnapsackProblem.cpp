//
// Created by Adam on 18/01/2023.
//
#include <iostream>
#include <fstream>
#include <string>

class CKnapsackProblem {
public:
    unsigned int N, knapsackCap;
    std::pair<int, int> *items; // first - weight, second - cost
    CKnapsackProblem() {
        std::ifstream dataFile;
        dataFile.open("data.txt");
        if (!dataFile.good()) {
            std::cout << "Error while opening dataFile" << std::endl;
            exit(1);
        }
        dataFile >> N >> knapsackCap;
        if (N <= 0 || knapsackCap <= 0) {
            std::cout << "Error while reading dataFile" << std::endl;
            exit(1);
        }
        items = new std::pair<int, int>[N];
        for (int i = 0; i < N; i++) {
            dataFile >> items[i].first >> items[i].second;
            if (items[i].first <= 0 || items[i].second <= 0) {
                std::cout << "Error while reading dataFile" << std::endl;
                exit(1);
            }
        }
    }

    CKnapsackProblem(const std::string &fileName) {
        std::ifstream dataFile;
        dataFile.open(fileName);
        if (!dataFile.good()) {
            std::cout << "Error while opening dataFile" << std::endl;
            exit(1);
        }
        dataFile >> N >> knapsackCap;
        if (N <= 0 || knapsackCap <= 0) {
            std::cout << "Error while reading dataFile" << std::endl;
            exit(1);
        }
        items = new std::pair<int, int>[N];
        for (int i = 0; i < N; i++) {
            dataFile >> items[i].first >> items[i].second;
            if (items[i].first <= 0 || items[i].second <= 0) {
                std::cout << "Error while reading dataFile" << std::endl;
                exit(1);
            }
        }
    }

    ~CKnapsackProblem() {
        delete[] items;
    }

    int score(bool *solution) {
        int weight = 0, cost = 0;
        for (int i = 0; i < N; i++) {
            if (solution[i]) {
                weight += items[i].first;
                cost += items[i].second;
            }
        }
        if (weight > knapsackCap) return 0;
        return cost;
    }


};