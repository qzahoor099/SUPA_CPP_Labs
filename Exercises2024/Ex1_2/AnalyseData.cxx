
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

int main() {
    std::ifstream inputFile("input2D_float.txt");
    if (!inputFile.is_open()) {

        std::cerr << "Error: Could not open file.\n";
        return 1;
    }
    //first task to read the data
    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << line << "\n";
    }
    return 0;
    //2nd task to make the vector in pair 

    std::vector<std::pair<float, float>> data;
    float x, y;

    while (inputFile >> x >> y) {
        data.emplace_back(x, y); // Add the pair to the vector
    }

    for (const auto& point : data) {
        std::cout << "(" << point.first << ", " << point.second << ")\n";
    }

    inputFile.close();
    return 0;

}

