//Name: Quratulain Zahoor
//Date: 19-Nov-2024

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

int main() {
        // Define the range for the function and output file
    double range_min = -20.0;
    double range_max = 20.0;
    string output_file = "MysteryPlot";

    // Create a FiniteFunction object
    FiniteFunction func(range_min, range_max, output_file);

    // Plot the function f(x) = 1 / (1 + x^2)
    func.plotFunction();

    // Read the mystery data points from the file
    string filename = "Outputs/data/MysteryData01202.txt";  // Use the correct relative file path
    vector<double> mysteryData = readDataFromFile(filename);

    // If the data was successfully read, plot it
    if (!mysteryData.empty()) {
        // Plot the mystery data points
        func.plotData(mysteryData, 150);  // Use 50 bins for histogram-like plotting
    
    }

    return 0;
}
