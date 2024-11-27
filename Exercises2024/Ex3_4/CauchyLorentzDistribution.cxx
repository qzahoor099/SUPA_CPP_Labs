#include "CauchyLorentzDistribution.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>

// Constructor
CauchyLorentzDistribution::CauchyLorentzDistribution(double range_min, double range_max, std::string outfile, double x0, double gamma, double step_size)
    : FiniteFunction(range_min, range_max, outfile), m_x0(x0), m_gamma(gamma), m_step_size(step_size) {
    if (gamma <= 0) throw std::invalid_argument("Gamma must be greater than 0.");
    // Debugging: Check initial values of x0 and gamma
    std::cout << "Initializing CauchyLorentzDistribution with x0 = " << m_x0 << " and gamma = " << m_gamma << std::endl;
}

// Override callFunction to implement the Cauchy-Lorentz formula
double CauchyLorentzDistribution::callFunction(double x) {
    double numerator = m_gamma;
    double denominator = M_PI * (m_gamma * m_gamma + std::pow(x - m_x0, 2));

    // Debugging: Check calculation of the function
    double result = numerator / denominator;
    std::cout << "callFunction(x = " << x << ") = " << result << std::endl;

    return result;
}

// Generate plot data
void CauchyLorentzDistribution::plotFunction() {
    // Ensure the output directory exists
    // Open the output file
    std::ofstream file("Outputs/data/CauchyLorentzDistribution.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not create the file.\n";
        return;
    }

    // Debugging: Verify the range and step size
    std::cout << "Plotting data from x = " << m_range_min << " to x = " << m_range_max << " with step size = " << m_step_size << std::endl;

    // Loop through values of x from range_min to range_max
    for (double x = m_range_min; x <= m_range_max; x += m_step_size) {
        double y = callFunction(x);
        file << x << " " << y << "\n";
        std::cout << "x: " << x << ", y: " << y << std::endl;
    }

    file.close();
    std::cout << "Data generated and written to 'CauchyLorentzDistribution.txt'.\n";
}

// Setters and Getters
void CauchyLorentzDistribution::setLocation(double x0) { 
    m_x0 = x0;
    std::cout << "Location set to x0 = " << m_x0 << std::endl;
}

void CauchyLorentzDistribution::setScale(double gamma) { 
    m_gamma = gamma;
    std::cout << "Scale set to gamma = " << m_gamma << std::endl;
}

double CauchyLorentzDistribution::getLocation() const { 
    return m_x0; 
}

double CauchyLorentzDistribution::getScale() const { 
    return m_gamma; 
}
