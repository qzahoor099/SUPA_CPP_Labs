#include "NegativeCrystalBallDistribution.h"

// Constructor
NegativeCrystalBallDistribution::NegativeCrystalBallDistribution(double range_min, double range_max, std::string outfile,
                                                                 double x_bar, double sigma, double alpha, double n, double step_size)
    : FiniteFunction(range_min, range_max, outfile),
      m_x_bar(x_bar), m_sigma(sigma), m_alpha(alpha), m_n(n), m_step_size(step_size) {
    if (alpha <= 0 || n <= 1)
        throw std::invalid_argument("Alpha must be > 0 and n must be > 1");
    computeConstants();
}

// Compute constants
void NegativeCrystalBallDistribution::computeConstants() {
    A = std::pow(m_n / std::abs(m_alpha), m_n) * std::exp(-0.5 * m_alpha * m_alpha);
    B = m_n / std::abs(m_alpha) - std::abs(m_alpha);
    C = m_n / std::abs(m_alpha) * (1.0 / (m_n - 1.0)) * std::exp(-0.5 * m_alpha * m_alpha);
    D = std::sqrt(M_PI / 2.0) * (1 + std::erf(m_alpha / std::sqrt(2.0)));
    N = 1.0 / (m_sigma * (C + D));
}

// Evaluate the PDF
double NegativeCrystalBallDistribution::callFunction(double x) {
    double z = (x - m_x_bar) / m_sigma;
    if (z > -m_alpha) {
        return N * std::exp(-0.5 * z * z);
    } else {
        return N * A * std::pow(B - z, -m_n);
    }
}

// Generate plot data
void NegativeCrystalBallDistribution::plotFunction() {
    std::ofstream file(m_outfile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create the file.\n";
        return;
    }

    for (double x = m_range_min; x <= m_range_max; x += m_step_size) {
        double y = callFunction(x);
        file << x << " " << y << "\n";
    }

    file.close();
    std::cout << "Data generated and written to '" << m_outfile << "'.\n";
}

// Setters
void NegativeCrystalBallDistribution::setXBar(double x_bar) { m_x_bar = x_bar; computeConstants(); }
void NegativeCrystalBallDistribution::setSigma(double sigma) { m_sigma = sigma; computeConstants(); }
void NegativeCrystalBallDistribution::setAlpha(double alpha) { m_alpha = alpha; computeConstants(); }
void NegativeCrystalBallDistribution::setN(double n) { m_n = n; computeConstants(); }

// Getters
double NegativeCrystalBallDistribution::getXBar() const { return m_x_bar; }
double NegativeCrystalBallDistribution::getSigma() const { return m_sigma; }
double NegativeCrystalBallDistribution::getAlpha() const { return m_alpha; }
double NegativeCrystalBallDistribution::getN() const { return m_n; }

/*

#include <iostream>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

// Base class for a generic function
class FiniteFunction {
public:
    virtual double evaluate(double x) const = 0; // Pure virtual function
};

// Negative Crystal Ball Distribution class
class NegativeCrystalBallDistribution : public FiniteFunction {
private:
    double x_bar; // Mean
    double sigma; // Standard deviation
    double alpha; // Parameter for the transition
    double n;     // Parameter for the tail

    // Precomputed constants
    double A, B, N, C, D;

    // Precompute constants based on the parameters
    void computeConstants() {
        A = std::pow(n / std::abs(alpha), n) * std::exp(-0.5 * alpha * alpha);
        B = n / std::abs(alpha) - std::abs(alpha);
        C = n / std::abs(alpha) * (1.0 / (n - 1.0)) * std::exp(-0.5 * alpha * alpha);
        D = std::sqrt(M_PI / 2.0) * (1 + std::erf(alpha / std::sqrt(2.0)));
        N = 1.0 / (sigma * (C + D));
    }

public:
    // Constructor
    NegativeCrystalBallDistribution(double x_bar_, double sigma_, double alpha_, double n_)
        : x_bar(x_bar_), sigma(sigma_), alpha(alpha_), n(n_) {
        if (alpha <= 0 || n <= 1)
            throw std::invalid_argument("alpha > 0 and n > 1 are required");
        computeConstants();
    }

    // Evaluate the PDF at a given x
    double evaluate(double x) const override {
        double z = (x - x_bar) / sigma;
        if (z > -alpha) {
            return N * std::exp(-0.5 * z * z);
        } else {
            return N * A * std::pow(B - z, -n);
        }
    }

    // Generate and store results in a file
    void generateData(double x_min, double x_max, double step_size, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file for writing.\n";
            return;
        }

        for (double x = x_min; x <= x_max; x += step_size) {
            double y = evaluate(x);
            file << std::fixed << std::setprecision(6) << x << " " << y << "\n";
        }

        file.close();
        std::cout << "Data written to '" << filename << "' successfully.\n";
    }

    // Print distribution statistics
    void printStatistics() const {
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "Negative Crystal Ball Distribution Parameters:\n";
        std::cout << "Mean (x_bar): " << x_bar << "\n";
        std::cout << "Standard Deviation (sigma): " << sigma << "\n";
        std::cout << "Alpha (Transition Parameter): " << alpha << "\n";
        std::cout << "n (Tail Parameter): " << n << "\n";
        std::cout << "Precomputed Constants:\n";
        std::cout << "  A: " << A << "\n";
        std::cout << "  B: " << B << "\n";
        std::cout << "  N (Normalization): " << N << "\n";
    }
};

int main() {
    // Distribution parameters
    double x_bar = 0.0;   // Mean
    double sigma = 1.0;   // Standard deviation
    double alpha = 1.5;   // Transition parameter
    double n = 2.0;       // Tail parameter

    try {
        // Create the distribution object
        NegativeCrystalBallDistribution ncbd(x_bar, sigma, alpha, n);

        // Print statistics
        ncbd.printStatistics();

        // Filepath for output
        std::string filename = "Output/data/NegativeCrystalBallDistribution.txt";

        // Generate data
        double x_min = -5.0, x_max = 5.0, step_size = 0.1;
        ncbd.generateData(x_min, x_max, step_size, filename);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
*/

/*
#include <cmath>  // For exp, pow, sqrt, erf

class NegativeCrystalBallDistribution : public FiniteFunction {
private:
    double x_bar; // Mean
    double sigma; // Standard deviation
    double alpha; // Parameter for the transition
    double n;     // Parameter for the tail

    // Precomputed constants
    double A, B, N, C, D;

    void computeConstants() {
        A = std::pow(n / std::abs(alpha), n) * std::exp(-0.5 * alpha * alpha);
        B = n / std::abs(alpha) - std::abs(alpha);
        C = n / std::abs(alpha) * (1.0 / (n - 1.0)) * std::exp(-0.5 * alpha * alpha);
        D = std::sqrt(M_PI / 2.0) * (1 + std::erf(alpha / std::sqrt(2.0)));
        N = 1.0 / (sigma * (C + D));
    }

public:
    // Constructor
    NegativeCrystalBallDistribution(double x_bar_, double sigma_, double alpha_, double n_)
        : x_bar(x_bar_), sigma(sigma_), alpha(alpha_), n(n_) {
        if (alpha <= 0 || n <= 1) throw std::invalid_argument("alpha > 0 and n > 1 are required");
        computeConstants();
    }

    // Evaluate the PDF at a given x
    double evaluate(double x) const override {
        double z = (x - x_bar) / sigma;
        if (z > -alpha) {
            return N * std::exp(-0.5 * z * z);
        } else {
            return N * A * std::pow(B - z, -n);
        }
    }

};
*/