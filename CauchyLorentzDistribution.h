#ifndef CAUCHYLORENTZDISTRIBUTION_H
#define CAUCHYLORENTZDISTRIBUTION_H

#include "FiniteFunction.h"  // Include the base class
#include <cmath>             // For M_PI and pow
#include <stdexcept>         // For exception handling

// Class for Cauchy-Lorentz Distribution, derived from FiniteFunction
class CauchyLorentzDistribution : public FiniteFunction {
private:
    double x0;      // Location parameter (x0)
    double gamma;   // Scale parameter (gamma)

public:
    // Constructor: initializes parameters, throws exception if gamma <= 0
    CauchyLorentzDistribution(double x0_, double gamma_);

    // Override the evaluate method to compute the PDF at a given x
    double evaluate(double x) const override;
};

#endif // CAUCHYLORENTZDISTRIBUTION_H
