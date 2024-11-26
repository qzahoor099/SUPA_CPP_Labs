#pragma once
#include "FiniteFunctions.h"
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>

class NegativeCrystalBallDistribution : public FiniteFunction {
private:
    double m_x_bar;   // Mean
    double m_sigma;   // Standard deviation
    double m_alpha;   // Transition parameter
    double m_n;       // Tail parameter
    double m_step_size;

    // Precomputed constants
    double A, B, N, C, D;

    // Compute constants
    void computeConstants();

public:
    // Constructor
    NegativeCrystalBallDistribution(double range_min, double range_max, std::string outfile,
                                     double x_bar, double sigma, double alpha, double n, double step_size);

    // Function to evaluate the PDF at a point x
    double callFunction(double x) override;

    // Method to generate plot data
    void plotFunction() ;

    // Setters and Getters
    void setXBar(double x_bar);
    void setSigma(double sigma);
    void setAlpha(double alpha);
    void setN(double n);
    double getXBar() const;
    double getSigma() const;
    double getAlpha() const;
    double getN() const;
};

/*

#pragma once
// Contents of FiniteFunctions.h

#include "FiniteFunctions.h"  // Include the base class
#include <cmath>             // For exp, pow, sqrt, erf
#include <stdexcept>         // For exception handling

// Class for Negative Crystal Ball Distribution, derived from FiniteFunction
class NegativeCrystalBallDistribution : public FiniteFunction {
private:
    double x_bar;   // Mean of the distribution
    double sigma;   // Standard deviation of the distribution
    double alpha;   // Parameter for the transition (α)
    double n;       // Parameter for the tail (n)

    // Precomputed constants
    double A, B, N, C, D;

    // Helper function to compute constants based on the parameters
    void computeConstants();

public:
    // Constructor: initializes parameters and computes constants
    NegativeCrystalBallDistribution(double x_bar_, double sigma_, double alpha_, double n_);

    // Override the evaluate method to compute the PDF at a given x
    //double evaluate(double x) const override;
    double evaluate(double x) const;

};

*/