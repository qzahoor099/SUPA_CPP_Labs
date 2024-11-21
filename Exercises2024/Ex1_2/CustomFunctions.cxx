/* Quratulain Zahoor: 19 Nov
*/

//this is my .cxx file to define the processing for other file, defining function and other stuff
//includes the packages
#include "CustomFunctions.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

// function to read the data into the vector 
void readData(const std::string& filename, std::vector<std::pair<float, float>>& data) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "' for reading.\n";
        return;
    }
    std::string line;
    bool isHeader = true; // skip the header to avoid any problem later

    while (std::getline(inputFile, line)) {
        if (isHeader) {
            isHeader = false; 
            continue;
        }

        std::istringstream iss(line);
        std::string xStr, yStr;

        if (std::getline(iss, xStr, ',') && std::getline(iss, yStr)) {
            try {
                float x = std::stof(xStr);
                float y = std::stof(yStr);
                data.emplace_back(x, y); // adding prased pair to the vector 
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

    inputFile.close(); //data file has been closed 
}


// defining the function to calculate the magnitude m = sqrt(a^2=b^2)
std::vector<float> calculateMagnitudes(const std::vector<std::pair<float, float>>& data) {
    std::vector<float> magnitudes;
    for (const auto& point : data) {
        float magnitude = std::sqrt(point.first * point.first + point.second * point.second);
        magnitudes.push_back(magnitude);
    }
    std::cout << "Calculated magnitudes for " << data.size() << " points.\n";
    return magnitudes;
}
//print the magnitude
void printMagnitude(const std::vector<float>& magnitudes) {
    for (const auto& magnitude : magnitudes) {
        std::cout << magnitude << std::endl;
    }
}
// writing the magnitude to the file
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

    // using the error file defined inside the AnalyseData.cxx , calculating the chi 
    std::vector<float> errors(data.size(), 1.0);  

    double chiSquared = calculateChiSquared(data, m, c, errors);
    double ndf = N - 2;  // Number of degrees of freedom
    double chiSquaredOverNDF = chiSquared / ndf;

    std::cout << "Linear Fit: y = " << m << "x + " << c << "\n";
    std::cout << "Chi-Squared/NDF: " << chiSquaredOverNDF << "\n";

    // writing the results to the file
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "' for writing.\n";
        return;
    }

    outFile << "Linear Fit: y = " << m << "x + " << c << "\n"; //writing values in the files
    outFile << "Chi-Squared/NDF: " << chiSquaredOverNDF << "\n"; //same logic 
    outFile.close();

    std::cout << "Fit function and chi-squared saved to " << filename << "\n";
}

// calculating the chi squared
double calculateChiSquared(const std::vector<std::pair<float, float>>& data, double m, double c, const std::vector<float>& errors) {
    double chiSquared = 0.0;
    for (size_t i = 0; i < data.size(); ++i) {
        double yModel = m * data[i].first + c;  // Calculate model value for current x
        double residual = (data[i].second - yModel) / errors[i];  // Normalize residual by error
        chiSquared += residual * residual;  // Sum squared residuals
    }
    return chiSquared;
}

// calculating x^y
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
// you can see my outfile in my folder, for easiness i have defines my Makefile
//do the make
//now you have the filename.txt (for the differnt option you want to calculate)
