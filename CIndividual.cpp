//
// Created by Adam on 18/01/2023.
//
#include <cstdlib>
#include <string>
#include <vector>
#include "CKnapsackProblem.cpp"


class CIndividual {
public:
    CIndividual() {
        this->solution = nullptr;
        this->score = this->n = 0;
    }

    unsigned int score, n;
    bool *solution;

    explicit CIndividual(unsigned int n) {
        this->n = n;
        solution = new bool[n];
        for (int i = 0; i < n; i++) solution[i] = rand() % 2;
        score = 0;
    }

    CIndividual(CIndividual &mom, CIndividual &dad, unsigned int crossPoint) {
        n = mom.n;
        solution = new bool[n];
        for (unsigned int i = 0; i < crossPoint; i++) solution[i] = mom.solution[i];
        for (unsigned int i = crossPoint; i < n; i++) solution[i] = dad.solution[i];
        score = 0;
    }

    ~CIndividual() = default;

    unsigned int fitness(CKnapsackProblem &problem) {
        score = problem.score(solution);
        return score;
    }

    void mutate(unsigned int MutProb) {
        for (int i = 0; i < n; i++) if (rand() % 100 < MutProb) solution[i] = !solution[i];
    }

    std::pair<CIndividual, CIndividual> crossover(CIndividual &other) {
        unsigned int crossPoint = rand() % n;
        return {CIndividual(*this, other, crossPoint), CIndividual(other, *this, crossPoint)};
    }

    std::string toString() {
        std::string result = "osobnik: ";
        for (int i = 0; i < n; i++) result += std::to_string(solution[i]) + " ";
        return result;
    }
};


