#include "NegativeCrystalBallDistribution.h"
#include <cmath>
#include <fstream>
#include <iostream>


// Constructor
NegativeCrystalBallDistribution::NegativeCrystalBallDistribution(double range_min, double range_max, std::string outfile,
                                                                 double x_bar, double sigma, double alpha, double n, double step_size)
     //: FiniteFunction(range_min, range_max, outfile), m_mean(mean), m_stddev(stddev), m_step_size(step_size) {}

    : FiniteFunction(range_min, range_max, outfile),
      m_x_bar(x_bar), m_sigma(sigma), m_alpha(alpha), m_n(n), m_step_size(step_size){ 
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
   // return A, B, C, D, N;
    // Debugging Output
    std::cout << "Constants:\n";
    std::cout << "A: " << A << ", B: " << B << ", C: " << C << ", D: " << D << ", N: " << N << "\n";
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
/*
double range_min= -20.0;
double range_max = 20.0;
double step_size= 0.1;
// Generate plot data

void NegativeCrystalBallDistribution::plotFunction() {
    std::ofstream file("Outputs/data/NegitiveCrystalBallDistribution.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not create the file.\n";
        return;
    }
    //for (double x = m_range_min; x <= m_range_max; x += m_step_size) {


    for (double x = -20.0; x <= 20.0; x += 0.1) {
        double y = callFunction(x);
        file << x << " " << y << "\n";
       std::cout << "x: " << x << ", y: " << y << "\n";
         m_function_scan = this->scanFunction(10000);
         m_plotfunction = true; //already handling the normalzatiom
    }

    file.close();
        std::cout << "Data generated and written to 'NegitiveCrystalBallDistribution.txt'.\n";


}
*/
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

