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
    double m_range_min;
    double m_range_max;
    
    void computeConstants();
    double A, B, C, D, N;
public:
    // Constructor
    NegativeCrystalBallDistribution(double range_min, double range_max, std::string outfile,
                                 double x_bar, double sigma, double alpha, double n, double step_size);

    // Function to evaluate the PDF at a point x
    double callFunction(double x) override;

    // Method to generate plot data
    //void NegativeCrystalBallDistribution::computeConstants();
    //void plotFunction() ;
    //void plotFunction();
    //void plotData(std::vector<double> &points, int NBins, bool isdata=true);

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

