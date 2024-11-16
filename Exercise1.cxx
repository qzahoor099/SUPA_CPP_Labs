#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

// Function prototypes
void printData(const std::vector<std::pair<double, double>>& data, int n);
std::vector<double> calculateMagnitudes(const std::vector<std::pair<double, double>>& data);
std::pair<double, double> leastSquaresFit(const std::vector<std::pair<double, double>>& data);
double chiSquaredTest(const std::vector<std::pair<double, double>>& data, double p, double q);
std::vector<double> calculatePowers(const std::vector<std::pair<double, double>>& data);
void writeToFile(const std::string& filename, const std::vector<std::pair<double, double>>& data);

int main() {
    // Read data from file
    std::ifstream inputFile("data.txt");
    std::vector<std::pair<double, double>> data;
    double x, y;
    while (inputFile >> x >> y) {
        data.emplace_back(x, y);
        return 0;
    }

    // Perform tasks
    printData(data, 10);
    auto magnitudes = calculateMagnitudes(data);
    auto [p, q] = leastSquaresFit(data);
    double chi2 = chiSquaredTest(data, p, q);
    auto powers = calculatePowers(data);

    // Write results to files
    writeToFile("output.txt", data);

    return 0;
}

// Function definitions
void printData(const std::vector<std::pair<double, double>>& data, int n) {
    for (int i = 0; i < n && i < data.size(); ++i) {
        std::cout << data[i].first << " " << data[i].second << std::endl;
    }
}

std::vector<double> calculateMagnitudes(const std::vector<std::pair<double, double>>& data) {
    std::vector<double> magnitudes(data.size());
    std::transform(data.begin(), data.end(), magnitudes.begin(),  
        {
        return std::sqrt(point.first * point.first + point.second * point.second);
        
    });

    return magnitudes;
}
// Function to fit a straight line using the least squares method
std::pair<double, double
   return;
