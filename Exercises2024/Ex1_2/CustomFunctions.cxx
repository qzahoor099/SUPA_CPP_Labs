\\name: Quratulain Zahoor (17/11)

#include "CustomFunctions.h"
#include <iostream>
#include <fstream>
#include <cmath>  

// Function to read data into the vector
void readData(std::vector<std::pair<float, float>>& data) {
    std::ifstream inputFile("input2D_float.txt");
    
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file.\n";
        return;  // Return early if the file can't be opened
    }

    float x, y;
    // Read each pair of (x, y) from the file and store in the vector
    while (inputFile >> x >> y) {
        data.push_back({x, y});
    }

    inputFile.close();
}

// Function to calculate the magnitude of a vector (x, y)
float calculateMagnitude(float x, float y) {
    return std::sqrt(x * x + y * y);  
}
