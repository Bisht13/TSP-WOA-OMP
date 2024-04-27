#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <limits>
#include <omp.h>

std::vector<std::vector<double>> readMatrix(const std::string &filename)
{
    std::vector<std::vector<double>> matrix;
    std::ifstream file(filename);
    double value;
    while (file)
    {
        std::vector<double> row;
        std::string line;
        if (!std::getline(file, line))
            break;
        std::istringstream iss(line);
        while (iss >> value)
        {
            row.push_back(value);
        }
        matrix.push_back(row);
    }
    return matrix;
}

double calculatePathDistance(const std::vector<int> &path, const std::vector<std::vector<double>> &distanceMatrix)
{
    double totalDistance = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i)
    {
        totalDistance += distanceMatrix[path[i]][path[i + 1]];
    }
    // Ensure the path returns to the starting city
    totalDistance += distanceMatrix[path.back()][path[0]];
    return totalDistance;
}

void initializePopulation(std::vector<std::vector<int>> &population, int populationSize, int numCities)
{
    population.resize(populationSize);
    std::vector<int> baseTour(numCities);
    std::iota(baseTour.begin(), baseTour.end(), 0);

    for (auto &individual : population)
    {
        individual = baseTour;
        std::random_shuffle(individual.begin(), individual.end());
    }
}

// Simplified WOA logic for TSP
void updateSolutionUsingWOA(std::vector<int> &solution, const std::vector<int> &bestSolution, const std::vector<std::vector<double>> &distanceMatrix)
{
    // Randomly decide between encircling prey and bubble-net attacking
    double rand = ((double)std::rand() / (RAND_MAX));
    if (rand < 0.5)
    {
        // Encircling prey: Try to make the solution closer to the best solution by swapping cities
        for (size_t i = 0; i < solution.size(); ++i)
        {
            if (((double)std::rand() / (RAND_MAX)) < 0.1)
            { // With a small probability, swap a city to make it closer to the best solution
                std::iter_swap(solution.begin() + i, std::find(solution.begin(), solution.end(), bestSolution[i]));
            }
        }
    }
    else
    {
        // Bubble-net attacking: Perform a local optimization by swapping two cities
        int idx1 = std::rand() % solution.size();
        int idx2 = std::rand() % solution.size();
        std::swap(solution[idx1], solution[idx2]);
        // If the new solution is worse, swap back
        if (calculatePathDistance(solution, distanceMatrix) > calculatePathDistance(bestSolution, distanceMatrix))
        {
            std::swap(solution[idx1], solution[idx2]);
        }
    }
}

void tspWhaleOptimization(const std::vector<std::vector<double>> &distanceMatrix, std::vector<int> &bestPath, double &bestDistance, int populationSize, int maxIterations)
{
    int numCities = distanceMatrix.size();
    std::vector<std::vector<int>> population;
    initializePopulation(population, populationSize, numCities);

    bestDistance = std::numeric_limits<double>::max();

    for (int iteration = 0; iteration < maxIterations; ++iteration)
    {
#pragma omp parallel for
        for (int i = 0; i < populationSize; ++i)
        {
            double dist = calculatePathDistance(population[i], distanceMatrix);
#pragma omp critical
            {
                if (dist < bestDistance)
                {
                    bestDistance = dist;
                    bestPath = population[i];
                }
            }
        }

        // Update solutions based on WOA logic
        for (int i = 0; i < populationSize; ++i)
        {
            updateSolutionUsingWOA(population[i], bestPath, distanceMatrix);
        }
    }
}

int main()
{
    std::string filename = "data.txt";
    auto distanceMatrix = readMatrix(filename);

    std::vector<int> bestPath;
    double bestDistance;
    int populationSize = 900;  // Example population size
    int maxIterations = 10000; // Example number of iterations

    tspWhaleOptimization(distanceMatrix, bestPath, bestDistance, populationSize, maxIterations);

    std::cout << "Optimal Path: ";
    for (int city : bestPath)
    {
        std::cout << city << " ";
    }
    std::cout << bestPath.front() << std::endl; // Assuming bestPath is not empty
    std::cout << "Total Distance: " << bestDistance << std::endl;

    return 0;
}