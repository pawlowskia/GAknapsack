#include <cstdlib>
#include <vector>
#include "knapsackDataFileFactory.cpp"
#include "CIndividual.cpp"

bool ValueCmp(CIndividual const &a, CIndividual const &b) {
    return a.score < b.score;
}

class CGeneticAlgorithm {
public:
    unsigned int PopSize, MutProb, CrossProb, iterations; // probs - in %
    std::vector<CIndividual> Population;
    CKnapsackProblem problem;

    CGeneticAlgorithm(unsigned int PopSize, unsigned int MutProb, unsigned int CrossProb, unsigned int iterations) :
            PopSize(PopSize),
            MutProb(MutProb),
            CrossProb(CrossProb),
            iterations(iterations) {
        problem = *new CKnapsackProblem("data.txt");
//        printf("%s", problem.toString().c_str());
        Population.reserve(PopSize);
        for (int i = 0; i < PopSize; i++) {
            Population.emplace_back(problem.N);
//            printf("%s\n", Population[i].toString().c_str());
        }
    }

    CGeneticAlgorithm(unsigned int PopSize, unsigned int MutProb, unsigned int CrossProb, unsigned int iterations,
                      std::string fileName) :
            PopSize(PopSize),
            MutProb(MutProb),
            CrossProb(CrossProb),
            iterations(iterations) {
        problem = *new CKnapsackProblem(fileName);
//        printf("%s", problem.toString().c_str());
        Population.reserve(PopSize);
        for (int i = 0; i < PopSize; i++) {
            Population.emplace_back(problem.N);
//            printf("%s\n", Population[i].toString().c_str());
        }
    }

    ~CGeneticAlgorithm() {
        while (!Population.empty()) Population.pop_back();
    }

    bool *run() {
        CIndividual bestFromFirstGen, bestFromLastGen, bestFromAll = *new CIndividual(problem.N);
        bestFromAll.fitness(problem);

        for (int i = 0; i < iterations; i++) {
            for (int j = 0; j < PopSize; j++) {
                Population[j].fitness(problem);
            }
            std::sort(Population.begin(), Population.end(), ValueCmp);
            std::reverse(Population.begin(), Population.end());
            printf("Best score from current gen: %d\n", Population[0].score);
            printf("Best individual from current gen: %s\n", Population[0].toString().c_str());


            if (i == 0) bestFromFirstGen = Population[0];
            if (i == iterations - 1) bestFromLastGen = Population[0];
            if (Population[0].score > bestFromAll.score) bestFromAll = Population[0];

            std::vector<CIndividual> newPopulation;
            newPopulation.reserve(PopSize);
            //krzyzowanie:
            for (int j = 0; j < PopSize / 2; j++) {
                //wybierz 1 rodzica
                CIndividual candidate1 = Population[rand() % PopSize];
                CIndividual candidate2 = Population[rand() % PopSize];
                if (candidate2.score > candidate1.score) std::swap(candidate1, candidate2);

                //wybierz 2 rodzica
                CIndividual candidate3 = Population[rand() % PopSize];
                CIndividual candidate4 = Population[rand() % PopSize];
                if (candidate4.score > candidate3.score) std::swap(candidate3, candidate4);

                //zkrzyzuj 1 i 3 oraz dodaj ich dzieci do nowej populacji, albo dodaj rodzicow
                if (rand() % 100 < CrossProb) {
                    std::pair<CIndividual, CIndividual> children = candidate1.crossover(candidate3);
                    newPopulation.emplace_back(children.first);
                    newPopulation.emplace_back(children.second);
                } else {
                    newPopulation.emplace_back(candidate1);
                    newPopulation.emplace_back(candidate3);
                }
            }
            //mutacja
            for (int j = 0; j < PopSize; j++) {
                newPopulation[j].mutate(MutProb);
            }
        }
        printf("\n");
        printf("Best score from first gen: %d\n", bestFromFirstGen.score);
        printf("Best score from last gen: %d\n", bestFromLastGen.score);
        printf("Best score from all: %d\n", bestFromAll.score);
        printf("\n");
        return Population[0].solution;
    }

};

void example1();

void example2();

int main() {
    example1();
//    example2();
}

void example1() {
    knapsackDataFileFactory factory = *new knapsackDataFileFactory(20, 1000, 50, 100, "data.txt");
    CGeneticAlgorithm algorithm = *new CGeneticAlgorithm(500, 1, 60, 500, "data.txt");
    bool *tmp = algorithm.run();
}

void example2() {
    knapsackDataFileFactory factory2 = *new knapsackDataFileFactory(100, 10000, 100, 500, "data2.txt");
    CGeneticAlgorithm algorithm2 = *new CGeneticAlgorithm(1000, 1, 30, 1000, "data2.txt");
    bool *tmp2 = algorithm2.run();
}