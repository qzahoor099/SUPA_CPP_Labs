#include "CustomFunctions.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

// Function to read data into the vector
void readData(const std::string& filename, std::vector<std::pair<float, float>>& data) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "' for reading.\n";
        return;
    }
    std::string line;
    bool isHeader = true; // Skip the header

    while (std::getline(inputFile, line)) {
        if (isHeader) {
            isHeader = false; // Skip the first line
            continue;
        }

        std::istringstream iss(line);
        std::string xStr, yStr;

        if (std::getline(iss, xStr, ',') && std::getline(iss, yStr)) {
            try {
                float x = std::stof(xStr);
                float y = std::stof(yStr);
                data.emplace_back(x, y); // Add parsed pair to the vector
            } catch (const std::exception&) {
                std::cerr << "Warning: Skipping invalid line: " << line << "\n";
            }
        } else {
            std::cerr << "Warning: Skipping malformed line: " << line << "\n";
        }
    }

    if (data.empty()) {
        std::cerr << "Error: No valid data read from file. Check file content and format.\n";
    } else {
        std::cout << "Successfully read " << data.size() << " data points from '" << filename << "'.\n";
    }

    inputFile.close();
}

// Template function to print data
//template <typename T>
//void printData(const T& data, int n) {
  //  if (n > static_cast<int>(data.size())) {
    //    std::cerr << "Warning: Requested lines exceed total data points. Showing all available lines.\n";
     //   n = static_cast<int>(data.size());
   // }

   // for (int i = 0; i < n; ++i) {
     //   std::cout << "(" << data[i].first << ", " << data[i].second << ")\n";
    //}
//}

// Explicit instantiation for vector of pairs of floats
//template void printData<std::vector<std::pair<float, float>>>(const std::vector<std::pair<float, float>>& data, int n);

// Function to calculate magnitudes of (x, y) points
std::vector<float> calculateMagnitudes(const std::vector<std::pair<float, float>>& data) {
    std::vector<float> magnitudes;
    for (const auto& point : data) {
        float magnitude = std::sqrt(point.first * point.first + point.second * point.second);
        magnitudes.push_back(magnitude);
    }
    std::cout << "Calculated magnitudes for " << data.size() << " points.\n";
    return magnitudes;
}

// Function to write magnitudes to a file
void writeToFile(const std::string& filename, const std::vector<float>& magnitudes) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    for (const auto& magnitude : magnitudes) {
        outFile << magnitude << "\n";
    }

    outFile.close();
    std::cout << "Magnitudes saved to " << filename << "\n";
}

// Function to perform least squares line fit and calculate χ²/NDF
void fitLine(const std::vector<std::pair<float, float>>& data, const std::string& filename) {
    int N = data.size();
    if (N < 2) {
        std::cerr << "Error: Insufficient data points for line fitting.\n";
        return;
    }

    float sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    for (const auto& point : data) {
        sumX += point.first;
        sumY += point.second;
        sumXY += point.first * point.second;
        sumX2 += point.first * point.first;
    }

    float m = (N * sumXY - sumX * sumY) / (N * sumX2 - sumX * sumX);
    float c = (sumY - m * sumX) / N;

    // Example errors; replace with actual error values if available
    std::vector<float> errors(data.size(), 1.0); 
    double chiSquared = calculateChiSquared(data, m, c, errors);
    double ndf = N - 2;  // Number of degrees of freedom
    double chiSquaredOverNDF = chiSquared / ndf;

    std::cout << "Linear Fit: y = " << m << "x + " << c << "\n";
    std::cout << "Chi-Squared/NDF: " << chiSquaredOverNDF << "\n";

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }
    outFile << "Linear Fit: y = " << m << "x + " << c << "\n";
    outFile << "Chi-Squared/NDF: " << chiSquaredOverNDF << "\n";
    outFile.close();

    std::cout << "Fit function and chi-squared saved to " << filename << "\n";
}

// Function to calculate χ² for the fit
double calculateChiSquared(const std::vector<std::pair<float, float>>& data, double m, double c, const std::vector<float>& errors) {
    double chiSquared = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        double yModel = m * data[i].first + c;
        double residual = (data[i].second - yModel) / errors[i];
        chiSquared += residual * residual;
    }
    return chiSquared;
}

// Function to calculate x^y for each data point
//void calculatePower(const std::vector<std::pair<float, float>>& data, const std::string& filename);

void calculatePower(const std::vector<std::pair<float, float>>& data, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    for (const auto& point : data) {
        int y = static_cast<int>(std::round(point.second));  // Round y to nearest integer
        double result = std::pow(point.first, y);
        outFile << point.first << "^" << y << " = " << result << "\n";
        std::cout << point.first << "^" << y << " = " << result << "\n";
    }

    outFile.close();
    std::cout << "x^y results saved to " << filename << "\n";
}
