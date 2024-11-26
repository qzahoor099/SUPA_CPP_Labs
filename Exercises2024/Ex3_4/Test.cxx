
// Name: Quratulain Zahoor
// Date: 19-Nov-2024
#include "NormalDistribution.h"
#include "NegativeCrystalBallDistribution.h"
#include "CauchyLorentzDistribution.h"


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

    // Corrected constructor call (using range_min and range_max)
    FiniteFunction func(range_min, range_max, output_file);

    // Plot the function f(x) = 1 / (1 + x^2)
    func.plotFunction();
    //now this if for normal distribution 
    double mean = 0.0;
    double stddev = 1.0;
    NormalDistribution normalDist(range_min, range_max, output_file, mean, stddev);

    // Now plot the data using gnuplot
    normalDist.plotFunction();
    // now define for NegitiveCrystalBallDistribution

    std::string outfile = "Outputs/data/NegativeCrystalBallDistribution.txt";
    //double A, B, N, C, D;

    double x_bar = 0.0;   // Mean
    double sigma = 1.0;   // Standard deviation
    double alpha = 1.5;   // Transition parameter
    double n = 2.0;       // Tail parameter
    double step_size = 1;

//create the Negative Crystal Ball Distribution object
    NegativeCrystalBallDistribution ncbdDist(range_min, range_max, output_file, x_bar, sigma, alpha, n, step_size);

    // Generate and plot the function data
    ncbdDist.plotFunction();
    
    
     
    

    string filename = "Outputs/data/MysteryData01202.txt";  // Use the correct relative file path
    vector<double> mysteryData = readDataFromFile(filename);

    // If the data was successfully read, plot it
    if (!mysteryData.empty()) {
        // Plot the mystery data points
        func.plotData(mysteryData, 100, true);  // Use 50 bins for histogram-like plotting, setting 'true' for data
    }

    return 0;  // Return 0 to indicate successful execution
}


