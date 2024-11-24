#ifndef NEGATIVECRYSTALBALLDISTRIBUTION_H
#define NEGATIVECRYSTALBALLDISTRIBUTION_H

#include "FiniteFunction.h"  // Include the base class
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
    double evaluate(double x) const override;

};

#endif // NEGATIVECRYSTALBALLDISTRIBUTION_H
