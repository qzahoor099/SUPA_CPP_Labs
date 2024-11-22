#include <string>
#include <vector>
#include "gnuplot-iostream.h"

#pragma once //Replacement for IFNDEF

class FiniteFunction {
public:
    FiniteFunction(); // Empty constructor
    FiniteFunction(double range_min, double range_max, std::string outfile); // Variable constructor
    virtual ~FiniteFunction() {}  // Virtual destructor

    // Pure virtual function that must be implemented by derived classes
    virtual double evaluate(double x) const = 0;

    double rangeMin(); // Low end of the range the function is defined within
    double rangeMax(); // High end of the range the function is defined within
    double integral(int Ndiv = 1000);
    std::vector<std::pair<double, double>> scanFunction(int Nscan = 1000); // Scan over function to plot it (slight hack needed to plot function in gnuplot)
    void setRangeMin(double RMin);
    void setRangeMax(double RMax);
    void setOutfile(std::string outfile);
    void plotFunction(); // Plot the function using scanFunction
    void plotSeparateDistributions();
    void plotData(std::vector<double>& points, int NBins, bool isdata = true); // Plot data points (either provided data or points sampled from function) as a histogram using NBins
    virtual void printInfo(); // Dump parameter info about the current function (Overridable)
    virtual double callFunction(double x); // Call the function with value x (Overridable)
    void normalize(int Ndiv); // Declare the normalize method

public:
    double m_RMin;
    double m_RMax;
    double m_Integral;
    double m_NormalizationFactor = 1.0;
    int m_IntDiv = 0; // Number of divisions for performing the integral
    std::string m_FunctionName;
    std::string m_OutData; // Output filename for data
    std::string m_OutPng; // Output filename for plot
    std::vector<std::pair<double, double>> m_data; // Input data points to plot
    std::vector<std::pair<double, double>> m_samples; // Holder for randomly sampled data 
    std::vector<std::pair<double, double>> m_function_scan; // Holder for data from scanFunction (slight hack needed to plot function in gnuplot)
    bool m_plotfunction = true; // Flag to determine whether to plot function
    bool m_plotdatapoints = true; // Flag to determine whether to plot input data
    bool m_plotsamplepoints = false; // Flag to determine whether to plot sampled data 
    double integrate(int Ndiv);
    std::vector<std::pair<double, double>> makeHist(std::vector<double>& points, int Nbins); // Helper function to turn data points into histogram with Nbins
    void checkPath(std::string outstring); // Helper function to ensure data and png paths are correct
    void generatePlot(Gnuplot& gp); 
  
public:
    double invxsquared(double x); // The default functional form
};

// Distribution classes

class NormalDistribution : public FiniteFunction {
public:
    NormalDistribution(double mean, double sigma);
    double evaluate(double x) const override;  // Override evaluate

private:
    double m_mean;
    double m_sigma;
};

class CauchyLorentzDistribution : public FiniteFunction {
public:
    CauchyLorentzDistribution(double x0, double gamma);
    double evaluate(double x) const override;  // Override evaluate

private:
    double m_x0;
    double m_gamma;
};

class NegativeCrystalBallDistribution : public FiniteFunction {
public:
    NegativeCrystalBallDistribution(double mean, double sigma, double alpha, double n);
    double evaluate(double x) const override;  // Override evaluate

private:
    double m_mean;
    double m_sigma;
    double m_alpha;
    double m_n;
};
