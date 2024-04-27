#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> // For std::next_permutation
#include <limits>
#include <numeric>

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

double calculatePathDistance(const std::vector<int> &path, const std::vector<std::vector<double>> &matrix)
{
    double totalDistance = 0;
    for (size_t i = 0; i < path.size() - 1; ++i)
    {
        totalDistance += matrix[path[i]][path[i + 1]];
    }
    // Add distance back to the starting city
    totalDistance += matrix[path.back()][path[0]];
    return totalDistance;
}

void tspBruteForce(const std::vector<std::vector<double>> &matrix, std::vector<int> &bestPath, double &minDistance)
{
    int n = matrix.size();
    std::vector<int> path(n);
    // Initialize path with 0, 1, 2, ..., n-1
    std::iota(path.begin(), path.end(), 0);

    minDistance = std::numeric_limits<double>::max();
    do
    {
        double currentDistance = calculatePathDistance(path, matrix);
        if (currentDistance < minDistance)
        {
            minDistance = currentDistance;
            bestPath = path;
        }
    } while (std::next_permutation(path.begin(), path.end()));

    // Add starting city at the end to complete the loop for the best path
    bestPath.push_back(bestPath[0]);
}

int main()
{
    std::string filename = "data.txt";
    auto matrix = readMatrix(filename);
    std::vector<int> bestPath;
    double minDistance;

    tspBruteForce(matrix, bestPath, minDistance);

    std::cout << "Optimal Path: ";
    for (int city : bestPath)
    {
        std::cout << city << " ";
    }
    std::cout << "\nTotal Distance: " << minDistance << std::endl;

    return 0;
}