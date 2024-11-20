#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "FiniteFunctions.h"  // Include the FiniteFunction class

using namespace std;

// Function to read the mystery data from the file
vector<double> readDataFromFile(const string& filename) {
    vector<double> data;
    ifstream file(filename);
    double value;

    while (file >> value) {
        data.push_back(value);
    }

    return data;
}

int main() {
    // Define the range for the function and output file
    double range_min = -5.0;
    double range_max = 5.0;
    string output_file = "MysteryPlot";

    // Create a FiniteFunction object
    FiniteFunction func(range_min, range_max, output_file);

    // Plot the function f(x) = 1 / (1 + x^2)
    func.plotFunction();

    // Read the mystery data points from the generated file
    string filename = "Output/Data/MysteryData01202.txt";  // Replace XXXXX with the actual string
    vector<double> mysteryData = readDataFromFile(filename);

    // Plot the mystery data points
    func.plotData(mysteryData, 50);  // Use 50 bins for histogram-like plotting

    // Generate and save the plot
    Gnuplot gp;
    func.generatePlot(gp);

    return 0;
}
