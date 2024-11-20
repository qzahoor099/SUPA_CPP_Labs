#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <numeric>

// Function to calculate the mean
double calculateMean(const std::vector<double>& data) {
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

// Function to calculate the standard deviation
double calculateStdDev(const std::vector<double>& data, double mean) {
    double sum = 0.0;
    for (double value : data) {
        sum += std::pow(value - mean, 2);
    }
    return std::sqrt(sum / data.size());
}

// Function to perform normal distribution
std::vector<double> normalDistribution(const std::vector<double>& data, double mean, double stdDev) {
    std::vector<double> normalizedData;
    for (double value : data) {
        double z = (value - mean) / stdDev;
        normalizedData.push_back(z);
    }
    return normalizedData;
}

int main() {
    std::ifstream inputFile("MysteryData01202.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::vector<double> data;
    double value;
    while (inputFile >> value) {
        data.push_back(value);
    }
    inputFile.close();

    if (data.empty()) {
        std::cerr << "No data found in the file!" << std::endl;
        return 1;
    }

    double mean = calculateMean(data);
    double stdDev = calculateStdDev(data, mean);
    std::vector<double> normalizedData = normalDistribution(data, mean, stdDev);

    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Standard Deviation: " << stdDev << std::endl;
    std::cout << "Normalized Data: ";
    for (double z : normalizedData) {
        std::cout << z << " ";
    }
    std::cout << std::endl;

    return 0;
}

