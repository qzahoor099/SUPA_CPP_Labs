//Name: Quratulain Zahoor
//Date: 19-Nov-2024

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "FiniteFunctions.h"  // Include the FiniteFunction class
#include <filesystem>  // To check if the file exists

using namespace std;

// Function to read the mystery data from the file with error handling and limit to 500 points
vector<double> readDataFromFile(const string& filename) {
    vector<double> data;
    double value;
    int count = 0;

    // Check if the file exists in the current directory
    if (!std::filesystem::exists(filename)) {
        cout << "Error reported: File '" << filename << "' does not exist in the current directory." << endl;
        return data;  // Return an empty vector as a signal of failure
    }

    // Try to open the file
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file '" << filename << "'." << endl;
        return data;  // Return an empty vector as a signal of failure
    }

    // Read data from the file, limit to 500 points
    while (file >> value && count < 100000) {
        data.push_back(value);
        count++;
    }

    // If no valid data was read, output a warning
    if (data.empty()) {
        cout << "Warning: No valid data found in the file '" << filename << "'." << endl;
    } else {
        cout << "File '" << filename << "' successfully read with " << data.size() << " data points." << endl;
    }

    file.close();  // Close the file after reading

    return data;
}
double callFunction(FiniteFunction* func, double x) {
    return func->evaluate(x);
}


    //return 0;
    int main() {
    NormalDistribution normal(0.0, 1.0);  // Mean=0, Sigma=1
    CauchyLorentzDistribution cauchy(0.0, 1.0);  // x0=0, gamma=1
    NegativeCrystalBallDistribution crystal(0.0, 1.0, 1.5, 3.0);  // mean=0, sigma=1, alpha=1.5, n=3

    // Using callFunction to evaluate at x = 0.5 for all distributions
    std::cout << "Normal Distribution result: " << callFunction(&normal, 0.5) << std::endl;
    std::cout << "Cauchy-Lorentz Distribution result: " << callFunction(&cauchy, 0.5) << std::endl;
    std::cout << "Negative Crystal Ball Distribution result: " << callFunction(&crystal, 0.5) << std::endl;
    
    
    // Define the range_min, range_max, and output_file variables
    double range_min = -10.0;
    double range_max = 10.0;
    string output_file = "output.txt";

    // Create a FiniteFunction object (or remove if unnecessary)
    //FiniteFunction func(range_min, range_max, output_file);

    // Plot the function f(x) = 1 / (1 + x^2)
    func.plotFunction();
    //func->plotSeparateDistributions();
    //func.plotSeparateDistributions();


    // Read the mystery data points from the file
    string filename = "Outputs/data/MysteryData01202.txt";  // Use the correct relative file path
    vector<double> mysteryData = readDataFromFile(filename);   

    return 0;
}
/*
int main() {
       
    FiniteFunction* normal =  NormalDistribution(0.0, 1.0);  // Standard normal
    FiniteFunction* cauchy =  CauchyLorentzDistribution(0.0, 1.0);  // Cauchy at x=0, γ=1
    FiniteFunction* crystal =  NegativeCrystalBallDistribution(-1.0, 2.0, 1.5, 3.0);  // Negative Crystal Ball

    double x = 0.5; // Example value for evaluation

    // Now you can call evaluate on the base pointer
    std::cout << "Normal f(x): " << normal->evaluate(x) << std::endl;
    std::cout << "Cauchy f(x): " << cauchy->evaluate(x) << std::endl;
    std::cout << "Crystal f(x): " << crystal->evaluate(x) << std::endl;

    //delete normal;
    //delete cauchy;
    //delete crystal;

    // Create a FiniteFunction object
    FiniteFunction func(range_min, range_max, output_file);

    // Plot the function f(x) = 1 / (1 + x^2)
    func.plotFunction();
    func. plotSeparateDistributions();

    // Read the mystery data points from the file
    string filename = "Outputs/data/MysteryData01202.txt";  // Use the correct relative file path
    vector<double> mysteryData = readDataFromFile(filename);   
    return 0;
}
*/