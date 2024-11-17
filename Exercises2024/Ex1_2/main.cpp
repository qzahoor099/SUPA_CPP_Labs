#include <iostream>
#include <vector>
#include "CustomFunctions.h"

int main() {
    std::vector<std::pair<float, float>> data;
    
    // Step 1: Read data from file and print it
    readData(data);
    
    if (data.empty()) {
        std::cerr << "No data found in the file.\n";
        return 1;  // Exit if no data was read
    }
    
    std::cout << "Data read from the file:\n";
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << "(" << data[i].first << ", " << data[i].second << ")\n";
    }

    // Step 2: Ask the user for the number of vectors they want to analyze
    int n;
    std::cout << "\nEnter the number of vectors you want to analyze: ";
    std::cin >> n;

    // Step 3: Validate user input
    if (n > data.size()) {
        std::cerr << "Warning: The number of vectors exceeds the available data. Only analyzing the first " << data.size() << " vectors.\n";
        n = data.size();  // Adjust n to be the size of the data if it's larger than available
    }

    // Step 4: Calculate and print the magnitude of the selected vectors
    for (int i = 0; i < n; ++i) {
        const auto& point = data[i];
        float magnitude = calculateMagnitude(point.first, point.second);
        std::cout << "Vector: (" << point.first << ", " << point.second << ") -> Magnitude: " << magnitude << "\n";
    }

    return 0;
}
