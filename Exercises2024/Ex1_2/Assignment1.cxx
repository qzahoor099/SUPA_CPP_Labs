#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
#include <limits> // For numeric limits

// Function to read data from a file and store in a vector of pairs
void readData(const std::string& filename, std::vector<std::pair<float, float>>& data) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file.\n";
        return;
    }

    float x, y;
    while (inputFile >> x >> y) {
        data.emplace_back(x, y);
    }
    inputFile.close();
}

// Function to print `n` lines of data
void printData(const std::vector<std::pair<float, float>>& data, int n) {
    if (n > data.size()) {
        std::cerr << "Warning: Requested lines exceed total data points. Showing first 5 lines.\n";
        n = std::min(static_cast<int>(data.size()), 5);
    }
    for (int i = 0; i < n; ++i) {
        std::cout << "(" << data[i].first << ", " << data[i].second << ")\n";
    }
}

// Function to calculate magnitudes of (x, y) coordinates and return as a vector
std::vector<float> calculateMagnitudes(const std::vector<std::pair<float, float>>& data) {
    std::vector<float> magnitudes;
    for (const auto& point : data) {
        float magnitude = std::sqrt(point.first * point.first + point.second * point.second);
        magnitudes.push_back(magnitude);
    }
    return magnitudes;
}

// Function to print magnitudes
void printMagnitudes(const std::vector<float>& magnitudes) {
    for (const auto& magnitude : magnitudes) {
        std::cout << "Magnitude: " << magnitude << "\n";
    }
}

// Function to perform least squares fitting
std::pair<float, float> leastSquaresFit(const std::vector<std::pair<float, float>>& data) {
    float sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    int N = data.size();

    for (const auto& point : data) {
        sumX += point.first;
        sumY += point.second;
        sumXY += point.first * point.second;
        sumX2 += point.first * point.first;
    }

    float p = (N * sumXY - sumX * sumY) / (N * sumX2 - sumX * sumX);
    float q = (sumY * sumX2 - sumX * sumXY) / (N * sumX2 - sumX * sumX);

    std::cout << "Linear Fit: y = " << p << "x + " << q << "\n";
    return {p, q};
}

// Function to calculate χ²/NDF for the fit
float chiSquared(const std::vector<std::pair<float, float>>& data, const std::pair<float, float>& fit, const std::vector<float>& errors) {
    float chi2 = 0;
    float p = fit.first;
    float q = fit.second;

    for (size_t i = 0; i < data.size(); ++i) {
        float observed = data[i].second;
        float expected = p * data[i].first + q;
        chi2 += std::pow((observed - expected) / errors[i], 2);
    }

    int NDF = data.size() - 2; // N - number of parameters
    std::cout << "χ²/NDF = " << chi2 / NDF << "\n";
    return chi2 / NDF;
}

// Function to calculate x^y for each data point (without using `pow` or loops)
std::vector<float> calculateXY(const std::vector<std::pair<float, float>>& data) {
    std::vector<float> results;
    for (const auto& point : data) {
        float x = point.first;
        int y = static_cast<int>(std::round(point.second));
        float result = 1;

        while (y > 0) {
            result *= x;
            --y;
        }

        results.push_back(result);
    }
    return results;
}

// Function to write results to a file
template <typename T>
void writeToFile(const std::string& filename, const std::vector<T>& results) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    for (const auto& result : results) {
        outFile << result << "\n";
    }

    outFile.close();
    std::cout << "Results saved to " << filename << "\n";
}

// Main function
int main() {
    std::vector<std::pair<float, float>> data;

    // Step 1: Read data from file
    readData("input2D_float.txt", data);

    std::vector<float> errors(data.size(), 1.0); // Dummy error values for χ² calculation

    while (true) {
        // Display menu
        std::cout << "\nChoose an action:\n";
        std::cout << "1. Print data\n2. Calculate magnitudes\n3. Perform least squares fit\n";
        std::cout << "4. Calculate χ²/NDF\n5. Calculate x^y\n6. Exit\n";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int n;
                std::cout << "Enter number of lines to print: ";
                std::cin >> n;
                printData(data, n);
                break;
            }
            case 2: {
                auto magnitudes = calculateMagnitudes(data);
                printMagnitudes(magnitudes);
                writeToFile("magnitudes.txt", magnitudes);
                break;
            }
            case 3: {
                auto fit = leastSquaresFit(data);
                break;
            }
            case 4: {
                auto fit = leastSquaresFit(data);
                chiSquared(data, fit, errors);
                break;
            }
            case 5: {
                auto results = calculateXY(data);
                writeToFile("xy_results.txt", results);
                break;
            }
            case 6:
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
}
