#include "NormalDistribution.h"
#include <cmath>
#include <fstream>
#include <iostream>

// Constructor
NormalDistribution::NormalDistribution(double range_min, double range_max, std::string outfile, double mean, double stddev, double step_size)
    : FiniteFunction(range_min, range_max, outfile), m_mean(mean), m_stddev(stddev), m_step_size(step_size) {}

// Override the callFunction method to implement the Normal Distribution formula
double NormalDistribution::callFunction(double x) {
    double normalizationFactor = 1.0 / (m_stddev * sqrt(2 * M_PI));
    double exponent = -0.5 * pow((x - m_mean) / m_stddev, 2);
    return normalizationFactor * exp(exponent);
}

// Method to generate plot data for the normal distribution
void NormalDistribution::plotFunction() {
    std::ofstream file("Outputs/data/NormalDistribution.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not create the file.\n";
        return;
    }

    for (double x = -20.0; x <= 20.0; x += m_step_size) {
        double y = callFunction(x);
        file << x << " " << y << "\n";
         m_function_scan = this->scanFunction(10000);
         m_plotfunction = true; //already handling the normalzati
    }

    file.close();
    std::cout << "Data generated and written to 'NormalDistribution.txt'.\n";
}

// Setters and Getters
void NormalDistribution::setMean(double mean) { m_mean = mean; }
void NormalDistribution::setStdDev(double stddev) { m_stddev = stddev; }
double NormalDistribution::getMean() const { return m_mean; }
double NormalDistribution::getStdDev() const { return m_stddev; }
