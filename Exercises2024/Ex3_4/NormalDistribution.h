//#ifndef NORMALDISTRIBUTION_H
//#define NORMALDISTRIBUTION_H
#pragma once



#include <string>
#include "FiniteFunctions.h"

class NormalDistribution : public FiniteFunction {
private:
    double m_mean;    // Mean of the normal distribution
    double m_stddev;  // Standard deviation of the normal distribution
    double m_step_size;



public:
    // Constructor with range and output file, mean, and standard deviation
    NormalDistribution(
        double range_min, double range_max, std::string outfile, double mean = 0.0, double stddev = 1.0, double step_size = 0.1);
        //NormalDistribution(double range_min, double range_max, std::string outfile, double mean, double stddev);

        void plotFunction();
        void plotData(std::vector<double> &points, int NBins, bool isdata=true); //NB! use isdata flag to pick between data and sampled distributions

        //void NormalDistribution::plotFunction();
        //void NormalDistribution::plotData();
    

    // Override the callFunction method
    double callFunction(double x) override;
    //double evaluate(double x) const;

    // Optional: Provide methods to set/get mean and standard deviation
    void setMean(double mean);
    void setStdDev(double stddev);
    double getMean() const;
    double getStdDev() const;
    
public:
   double m_RMin;
   double m_RMax;
   double m_Integral;
   double m_NormalizationFactor = 1.0;
    std::string m_FunctionName;
  std::string m_OutData; //Output filename for data
  std::string m_OutPng; //Output filename for plot
  std::vector< std::pair<double,double> > m_data; //input data points to plot
  std::vector< std::pair<double,double> > m_samples; //Holder for randomly sampled data 
  std::vector< std::pair<double,double> > m_function_scan; //holder for data from scanFunction (slight hack needed to plot function in gnuplot)
  bool m_plotfunction = true; //Flag to determine whether to plot function
  bool m_plotdatapoints = true; //Flag to determine whether to plot input data
  bool m_plotsamplepoints = false; //Flag to determine whether to plot sampled data 
  double integrate(int Ndiv);
  std::vector< std::pair<double, double> > makeHist(std::vector<double> &points, int Nbins); //Helper function to turn data points into histogram with Nbins
  void checkPath(std::string outstring); //Helper function to ensure data and png paths are correct
  void generatePlot(Gnuplot &gp); 
    
};

//#endif // NORMALDISTRIBUTION_H
