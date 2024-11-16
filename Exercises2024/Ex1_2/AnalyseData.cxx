
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inputFile("input2D_float.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file.\n";
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << line << "\n";
    }

    inputFile.close();
    return 0;
}
