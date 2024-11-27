#pragma once
#include "FiniteFunctions.h"
#include <string>

class CauchyLorentzDistribution : public FiniteFunction {
private:
    double m_x0;       // Location parameter
    double m_gamma;    // Scale parameter
    
    double m_step_size = 0.1;
    double m_range_min = -20.0;

    double m_range_max = +20.0;

public:
    // Constructor
    CauchyLorentzDistribution(double range_min, double range_max, std::string outfile, double x0, double gamma, double step_size);
    //~CauchyLorentzDistribution();
   // void plotFunction() ;

    // Override callFunction for the Cauchy-Lorentz formula
    double callFunction(double x) override;

    // Setters and Getters
    void setLocation(double x0);
    void setScale(double gamma);
    double getLocation() const;
    double getScale() const;
};


