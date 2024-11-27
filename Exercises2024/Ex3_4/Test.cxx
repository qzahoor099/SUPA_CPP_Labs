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
    while (file >> value && count < 500) {
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
    double step_size = 0.1; 
    string output_file = "MysteryPlot";

    // Corrected constructor call (using range_min and range_max)
    FiniteFunction func(range_min, range_max, output_file);

    // Plot the function f(x) = 1 / (1 + x^2)
    func.plotFunction();

    // Read and plot mystery data for "MysteryPlot"
    string filename = "Outputs/data/MysteryData01202.txt";  // Use the correct relative file path
    vector<double> mysteryData = readDataFromFile(filename);
    if (!mysteryData.empty()) {
        func.plotData(mysteryData, 100, true);  // Use 100 bins for histogram-like plotting, setting 'true' for data
    }

    // Plot the Normal Distribution
    double mean = 0.0;
    double stddev = 1.0;
    string output_file1 = "NormalDistribution"; //the png plot
    NormalDistribution normalDist(range_min, range_max, output_file1, mean, stddev);
    normalDist.plotFunction();

    // Read and plot Normal Distribution data
    string filename1 = "Outputs/data/NormalDistribution.txt";  // Use the correct relative file path
    vector<double> mysteryData1 = readDataFromFile(filename1);
    if (!mysteryData1.empty()) {
        func.plotData(mysteryData1, 100, true);  // Use 100 bins for histogram-like plotting, setting 'false' for data
    }

    // Cauchy-Lorentz Distribution
    double x0 = 0.0;   // Location parameter
    double gamma = 1.0; // Scale parameter
    string output_file4 = "CauchyLorentzDistribution";
    CauchyLorentzDistribution cld(range_min, range_max, output_file4, x0, gamma, step_size);
    cld.plotFunction();

    // Read and plot Cauchy-Lorentz Distribution data
    string filename4 = "Outputs/data/CauchyLorentzDistribution.txt";  // Use the correct relative file path
    vector<double> mysteryData4 = readDataFromFile(filename4);
    if (!mysteryData4.empty()) {
        func.plotData(mysteryData4, 100, true);  // Use 100 bins for histogram-like plotting, setting 'false' for data
    }

    // Negative Crystal Ball Distribution
    double x_bar = 0.0;   // Mean
    double sigma = 1.0;   // Standard deviation
    double alpha = 1.5;   // Transition parameter
    double n = 2.0;       // Tail parameter
    string output_file2 = "NegativeCrystalBallDistribution";
    NegativeCrystalBallDistribution ncbdDist(range_min, range_max, output_file2, x_bar, sigma, alpha, n, step_size);
    ncbdDist.plotFunction();

    // Read and plot Negative Crystal Ball Distribution data
    string filename2 = "Outputs/data/NegativeCrystalBallDistribution.txt";  // Use the correct relative file path
    vector<double> mysteryData2 = readDataFromFile(filename2);
    if (!mysteryData2.empty()) {
        func.plotData(mysteryData2, 100, true);  // Use 100 bins for histogram-like plotting, setting 'false' for data
        //func.plotSample(mysteryData2, 100, true);  // Use 100 bins for histogram-like plotting, setting 'false' for data

    }

    return 0;  // Return 0 to indicate successful execution
}
/*

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
    double step_size = 0.1; 
    //Now we have the format for simple function

    //This will only plot the simple function
    string output_file = "MysteryPlot";

    // Corrected constructor call (using range_min and range_max)
    FiniteFunction func(range_min, range_max, output_file);

    // Plot the function f(x) = 1 / (1 + x^2)
    func.plotFunction();
    
    string filename = "Outputs/data/MysteryData01202.txt";  // Use the correct relative file path
    vector<double> mysteryData = readDataFromFile(filename);
    func.plotData(mysteryData, 100, true);  // Use 50 bins for histogram-like plotting, setting 'true' for data

    //This wil plot the Normal Distribution
    double mean = 0.0;
    double stddev = 1.0;
    string output_file1 = "NormalDistribution"; //the png plot

    NormalDistribution normalDist(range_min, range_max, output_file1, mean, stddev);

    // Now plot the data using gnuplot
    normalDist.plotFunction();
    string filename1 = "Outputs/data/NormalDistribution.txt";  // Use the correct relative file path
    vector<double> mysteryData1 = readDataFromFile(filename1);
    func.plotData(mysteryData1, 100, false);  // Use 50 bins for histogram-like plotting, setting 'true' for data

    //this is for CauchyLorentzDistribution
    double x0 = 0.0;   // Location parameter
    double gamma = 1.0; // Scale parameter
    //double step_size1 = 0.1;
    std::string output_file4 = "CauchyLorentzDistribution";


    // Create a Cauchy-Lorentz distribution instance
    CauchyLorentzDistribution cld(range_min, range_max, output_file4, x0, gamma, step_size);

    // Generate plot data
    std::string outfile = "Outputs/data/CauchyLorentzDistribution.txt";

    //string filename4 = "Outputs/data/CauchyLorentzDistribution.txt"; 
     // Use the correct relative file path
    vector<double> mysteryData4 = readDataFromFile(filename4);
    func.plotData(mysteryData4, 100, false);  // Use 50 bins for histogram-like plotting, setting 'true' for data

    
    

    // now define for NegitiveCrystalBallDistribution

    std::string outfile = "Outputs/data/NegativeCrystalBallDistribution.txt";
    //double A, B, N, C, D;

    double x_bar = 0.0;   // Mean
    double sigma = 1.0;   // Standard deviation
    double alpha = 1.5;   // Transition parameter
    double n = 2.0;       // Tail parameter
    //double step_size2 = 1;
    string output_file2 = "NegitiveCrystalBallDistribution";


//create the Negative Crystal Ball Distribution object
    NegativeCrystalBallDistribution ncbdDist(range_min, range_max, output_file2, x_bar, sigma, alpha, n, step_size);

    // Generate and plot the function data
    ncbdDist.plotFunction();
    string filename2 = "Outputs/data/NegitiveCrystalBallDistribution.txt";  // Use the correct relative file path
    vector<double> mysteryData2 = readDataFromFile(filename2);
    func.plotData(mysteryData2, 100, false);  // Use 50 bins for histogram-like plotting, setting 'true' for data

/*
     //If the data was successfully read, plot it
    if (!mysteryData.empty()) {
         //Plot the mystery data points
        func.plotData(mysteryData, 100, true);  // Use 50 bins for histogram-like plotting, setting 'true' for data
    }
*/

  //  return 0;  // Return 0 to indicate successful execution
//}   // Use the correct relative file path
