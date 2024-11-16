#include <vector>
#include <iostream>
#include <fstream>
#include <utility>

void readData(const std::string& filename, std::vector<std::pair<float, float>>& data) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file.\n";
        return;
    }

    float x, y;
    while (inputFile >> x >> y) {
        data.emplace_back(x, y);
    }
    inputFile.close();
}

void printData(const std::vector<std::pair<float, float>>& data, int n) {
    if (n > data.size()) {
        std::cerr << "Warning: Requested lines exceed total data points. Showing first 5 lines.\n";
        n = std::min(static_cast<int>(data.size()), 5);
    }
    for (int i = 0; i < n; ++i) {
        std::cout << "(" << data[i].first << ", " << data[i].second << ")\n";
    }
}

int main() {
    std::vector<std::pair<float, float>> data;
    readData("input2D_float.txt", data);
    int n = 5; // Example: Print first 5 lines
    printData(data, n);

    return 0;
}
