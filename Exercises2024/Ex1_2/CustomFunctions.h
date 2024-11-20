#ifndef CUSTOMFUNCTIONS_H
#define CUSTOMFUNCTIONS_H

#include <vector>
#include <utility> // for std::pair
#include <string>
#include <iostream>

// Function to read data into a vector
void readData(const std::string& filename, std::vector<std::pair<float, float>>& data);

// Template function to print `n` lines of data
template <typename T>
void printData(const T& data, int n) {
    if (n > data.size()) {
        std::cerr << "Warning: Requested lines exceed total data points. Showing all available lines.\n";
        n = data.size();
    }
    for (int i = 0; i < n; ++i) {
        std::cout << "(" << data[i].first << ", " << data[i].second << ")\n";
    }
}

// Function to calculate the magnitude of each (x, y) point and store it in a vector
std::vector<float> calculateMagnitudes(const std::vector<std::pair<float, float>>& data);

// Function to write magnitudes to a file
void writeToFile(const std::string& filename, const std::vector<float>& magnitudes);

// Function to fit a straight line using the least squares method
void fitLine(const std::vector<std::pair<float, float>>& data, const std::string& filename);

// Function to calculate x^y for each data point and store the results
//void calculatePower(std::vector<std::pair<float, float>>& data, const std::string& filename);
void calculatePower(const std::vector<std::pair<float, float>>& data, const std::string& filename);

// Function to calculate chi-squared per degree of freedom (χ²/NDF)
double calculateChiSquared(const std::vector<std::pair<float, float>>& data, double m, double c, const std::vector<float>& errors);

#endif
