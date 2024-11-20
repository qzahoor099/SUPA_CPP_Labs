#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "FiniteFunctions.h"  // Include the FiniteFunction class
#include <filesystem>  // To check if the file exists

using namespace std;

// Function to read the mystery data from the file with error handling
vector<double> readDataFromFile(const string& filename) {
    vector<double> data;

    // Optionally print the number of data points read
    cout << "Read " << data.size() << " data points from file." << endl;

    return data;
}
    
    // Check if the file exists in the current directory
    if (!std::filesystem::exists(filename)) {
        cout << "Error: File '" << filename << "' does not exist in the current directory." << endl;
        return data;  // Return an empty vector as a signal of failure
    }

    // Try to open the file
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file '" << filename << "'." << endl;
        return data;  // Return an empty vector as a signal of failure
    }

    

    // Check if no valid data was read
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
    double range_min = -5.0;
    double range_max = 5.0;
    string output_file = "MysteryPlot";
     while (file >> value && count < 300) {  // Limit to 300 data points
        data.push_back(value);
        count++;
    }
    // Create a FiniteFunction object
    FiniteFunction func(range_min, range_max, output_file);

    // Plot the function f(x) = 1 / (1 + x^2)
    func.plotFunction();

    // Read the mystery data points from the generated file
    string filename = "Outputs/data/MysteryData01202.txt";  // Use the correct relative file path
    vector<double> mysteryData = readDataFromFile(filename);

    // If the data was successfully read, plot it
    if (!mysteryData.empty()) {
        // Plot the mystery data points
        func.plotData(mysteryData, 50);  // Use 50 bins for histogram-like plotting

        // Generate and save the plot
        Gnuplot gp;
        func.generatePlot(gp);
    } else {
        cout << "Error: No valid data to plot." << endl;
    }

    return 0;
}
