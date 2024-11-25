
#pragma once
//including the libraries required 
#include <vector>
#include<utility> 
#include<string>
#include<iostream>


// Function to read data into a vector using the input file
void readData(const std::string& filename, std::vector<std::pair<float, float>>&data);


// implementing the temaplet inside the header file, using the printData fun, asking the user to 
//enter the number of lines  you want to print n>datasize it would only take the first 5 point 
//working for instruction 6 
template <typename T>
void printData(const T& data, int n) {
    if (n > data.size()) { 
        std::cerr << "Warning: Requested lines exceed total data points. Showing the first 5 points.\n";
        n = std::min((int)data.size(), 5);
        std::cout<<"the number of data lines selected"<<n<<std::endl;
    }
    for (int i = 0; i < n; ++i) {
        std::cout << "(" << data[i].first << ", " << data[i].second << ")\n";
    }
}

// function to calculate the magnitude of  a vector 
std::vector<float> calculateMagnitudes(const std::vector<std::pair<float, float>>&data);
//void printMagnitude(const std::vector<float>& magnitudes);
void printMagnitude(const std::vector<float>& magnitude);

// writing magnitude to the file
void writeToFile(const std::string& filename, const std::vector<float>& mangnitude);

// fir into the straight line 
void fitLine(const std::vector<std::pair<float, float>>&data, const std::string& filename);
// function to calculate x^y
void calculatePower(const std::vector<std::pair<float,float>>&data,const std::string& filename);
// calculating the chi function
double calculateChiSquared(const std::vector<std::pair<float, float>>& data, double m, double c, const std::vector<float>& errors);

