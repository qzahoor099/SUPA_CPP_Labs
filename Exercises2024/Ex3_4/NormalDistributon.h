#ifndef NORMALDISTRIBUTION_H
#define NORMALDISTRIBUTION_H

#include <string>
#include "FiniteFunctions.h"

class NormalDistribution : public FiniteFunction {
private:
    double m_mean;    // Mean of the normal distribution
    double m_stddev;  // Standard deviation of the normal distribution

public:
    // Constructor with range and output file, mean, and standard deviation
    NormalDistribution(double range_min, double range_max, std::string outfile, double mean = 0.0, double stddev = 1.0);

    // Override the callFunction method
    double callFunction(double x) override;

    // Optional: Provide methods to set/get mean and standard deviation
    void setMean(double mean);
    void setStdDev(double stddev);
    double getMean() const;
    double getStdDev() const;
};

#endif // NORMALDISTRIBUTION_H
