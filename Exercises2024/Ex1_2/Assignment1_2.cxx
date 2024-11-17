#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
#include <limits> // For numeric limits
#include <iomanip> // For formatted output
#include <sstream> // For istringstream

// Function to read data from a file and store it in a vector of pairs
void readData(const std::string& filename, std::vector<std::pair<float, float>>& data) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "' for reading.\n";
        return;
    }

    std::string line;
    bool isHeader = true; // To skip the header

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

// Function to print `n` lines of data
void printData(const std::vector<std::pair<float, float>>& data, int n) {
    if (data.empty()) {
        std::cerr << "Error: No data available to print.\n";
        return;
    }

    // Limit `n` to the size of the data
    n = std::min(n, static_cast<int>(data.size()));

    for (int i = 0; i < n; ++i) {
        std::cout << "(" << data[i].first << ", " << data[i].second << ")\n";
    }

    std::cout << "Displayed " << n << " lines of data.\n";
}

// Function to calculate magnitudes of (x, y) coordinates and return as a vector
std::vector<float> calculateMagnitudes(const std::vector<std::pair<float, float>>& data) {
    std::vector<float> magnitudes;
    for (const auto& point : data) {
        float magnitude = std::sqrt(point.first * point.first + point.second * point.second);
        magnitudes.push_back(magnitude);
    }
    std::cout << "Calculated magnitudes for " << data.size() << " points.\n";
    return magnitudes;
}

// Function to write results to a file
template <typename T>
void writeToFile(const std::string& filename, const std::vector<T>& results) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "' for writing.\n";
        return;
    }

    for (const auto& result : results) {
        outFile << result << "\n";
    }

    std::cout << "Results saved to '" << filename << "'.\n";
    outFile.close();
}

// Main function
int main() {
    std::vector<std::pair<float, float>> data;

    // Step 1: Read data from file
    readData("input2D_float.txt", data);

    if (data.empty()) {
        return 1; // Exit if no data was loaded
    }

    while (true) {
        // Display menu
        std::cout << "\nChoose an action:\n";
        std::cout << "1. Print data\n2. Calculate magnitudes\n3. Exit\n";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int n;
                std::cout << "Enter number of lines to print: ";
                std::cin >> n;

                if (std::cin.fail() || n <= 0) {
                    std::cerr << "Error: Please enter a valid positive number.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
                    printData(data, n);
                }
                break;
            }
            case 2: {
                auto magnitudes = calculateMagnitudes(data);
                writeToFile("magnitudes.txt", magnitudes);
                break;
            }
            case 3:
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
}
