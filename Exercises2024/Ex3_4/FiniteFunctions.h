#include "FiniteFunctions.h"
#include <cmath>
#include <iostream>

// Base class constructor
FiniteFunction::FiniteFunction() 
    : m_RMin(0), m_RMax(0), m_Integral(0) {}

FiniteFunction::FiniteFunction(double range_min, double range_max, std::string outfile)
    : m_RMin(range_min), m_RMax(range_max), m_OutData(outfile), m_Integral(0) {}

FiniteFunction::~FiniteFunction() {} // Virtual destructor

// Getter and setter methods
double FiniteFunction::rangeMin() { return m_RMin; }
double FiniteFunction::rangeMax() { return m_RMax; }
void FiniteFunction::setRangeMin(double RMin) { m_RMin = RMin; }
void FiniteFunction::setRangeMax(double RMax) { m_RMax = RMax; }
void FiniteFunction::setOutfile(std::string outfile) { m_OutData = outfile; }

// Normal distribution constructor and method
NormalDistribution::NormalDistribution(double mean, double sigma)
    : FiniteFunction(-10.0, 10.0, "normal_distribution_output.txt"), m_mean(mean), m_sigma(sigma) {}

double NormalDistribution::evaluate(double x) const {
    return (1.0 / (m_sigma * sqrt(2 * M_PI))) * exp(-0.5 * pow((x - m_mean) / m_sigma, 2));
}

// Cauchy-Lorentz distribution constructor and method
CauchyLorentzDistribution::CauchyLorentzDistribution(double x0, double gamma)
    : FiniteFunction(-10.0, 10.0, "cauchy_lorentz_output.txt"), m_x0(x0), m_gamma(gamma) {}

double CauchyLorentzDistribution::evaluate(double x) const {
    return (1.0 / M_PI) * (m_gamma / ((x - m_x0) * (x - m_x0) + m_gamma * m_gamma));
}

// Negative Crystal Ball distribution constructor and method
NegativeCrystalBallDistribution::NegativeCrystalBallDistribution(double mean, double sigma, double alpha, double n)
    : FiniteFunction(-10.0, 10.0, "negative_crystal_ball_output.txt"),
      m_mean(mean), m_sigma(sigma), m_alpha(alpha), m_n(n) {}

double NegativeCrystalBallDistribution::evaluate(double x) const {
    double z = (x - m_mean) / m_sigma;
    if (z > -m_alpha) {
        return exp(-0.5 * z * z);  // Gaussian part
    } else {
        double A = pow(m_n / m_alpha, m_n) * exp(-0.5 * m_alpha * m_alpha);
        double B = m_n / m_alpha - m_alpha;
        return A * pow(B - z, -m_n);  // Tail part
    }
}
