#ifndef NORMALDISTRIBUTION_H
#define NORMALDISTRIBUTION_H

#include "FiniteFunction.h"   // Include the base class
#include <string>             // For std::string

// Class for Normal Distribution, derived from FiniteFunction
class NormalDistribution : public FiniteFunction {
public:
    // Constructor
    NormalDistribution(double range_min, double range_max, std::string outfile, double mean, double stddev);

    // Override the callFunction method to implement the Normal Distribution formula
    virtual double callFunction(double x) override;

    // Setters and getters for mean and standard deviation
    void setMean(double mean);
    void setStdDev(double stddev);

    double getMean() const;
    double getStdDev() const;

private:
    double m_mean;    // Mean (mu) of the distribution
    double m_stddev;  // Standard deviation (sigma) of the distribution
};

#endif // NORMALDISTRIBUTION_H
