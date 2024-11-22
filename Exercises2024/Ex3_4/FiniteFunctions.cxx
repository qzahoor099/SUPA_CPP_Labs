#include <iostream>
#include <string>
#include <vector>
#include "FiniteFunctions.h"
#include <filesystem> //To check extensions in a nice way

#include "gnuplot-iostream.h" //Needed to produce plots (not part of the course) 

using std::filesystem::path;

// Empty constructor
FiniteFunction::FiniteFunction(){
  m_RMin = -10.0;
  m_RMax = 10.0;
  this->checkPath("DefaultFunction");
  m_Integral = NULL;
}

// Initialised constructor
FiniteFunction::FiniteFunction(double range_min, double range_max, std::string outfile){
  m_RMin = range_min;
  m_RMax = range_max;
  m_Integral = NULL;
  this->checkPath(outfile); //Use provided string to name output files
}

// Plots are called in the destructor
FiniteFunction::~FiniteFunction(){
  Gnuplot gp; //Set up gnuplot object
  this->generatePlot(gp); //Generate the plot and save it to a png using "outfile" for naming 
}

/*
###################
//Setters
################### 
*/ 
void FiniteFunction::setRangeMin(double RMin) {m_RMin = RMin;};
void FiniteFunction::setRangeMax(double RMax) {m_RMax = RMax;};
void FiniteFunction::setOutfile(std::string Outfile) {this->checkPath(Outfile);};

/*
###################
//Getters
################### 
*/ 
double FiniteFunction::rangeMin() {return m_RMin;};
double FiniteFunction::rangeMax() {return m_RMax;};

/*
###################
//Function eval
################### 
*/ 


// Derived class NormalDistribution
class NormalDistribution : public FiniteFunction {
private:
    double m_mean, m_sigma;
public:
    NormalDistribution(double mean, double sigma) : m_mean(mean), m_sigma(sigma) {}
    double evaluate(double x) const override {
        return (1.0 / (m_sigma * sqrt(2 * M_PI))) * exp(-0.5 * pow((x - m_mean) / m_sigma, 2));
    }
};

// Derived class CauchyLorentzDistribution
class CauchyLorentzDistribution : public FiniteFunction {
private:
    double m_x0, m_gamma;
public:
    CauchyLorentzDistribution(double x0, double gamma) : m_x0(x0), m_gamma(gamma) {}
    double evaluate(double x) const override {
        return (1.0 / M_PI) * (m_gamma / ((x - m_x0) * (x - m_x0) + m_gamma * m_gamma));
    }
};

// Derived class NegativeCrystalBallDistribution
class NegativeCrystalBallDistribution : public FiniteFunction {
private:
    double m_mean, m_sigma, m_alpha, m_n;
public:
    NegativeCrystalBallDistribution(double mean, double sigma, double alpha, double n)
        : m_mean(mean), m_sigma(sigma), m_alpha(alpha), m_n(n) {}
    double evaluate(double x) const override {
        double a = (x - m_mean) / m_sigma;
        double abs_a = std::abs(a);
        if (abs_a < m_alpha) {
            return exp(-0.5 * a * a);  // Gaussian part
        } else {
            double b = m_n / m_alpha;
            return b * pow(m_alpha / abs_a, m_n) * exp(-0.5 * m_alpha * m_alpha);
        }
    }
};

// Function to call evaluate on any FiniteFunction derived object
double callFunction(FiniteFunction* func, double x) {
    return func->evaluate(x);  // Call the correct evaluate method based on the actual object type
}



/*
###################
//Integration by hand (output needed to normalise function when plotting)
################### 
*/ 
void double evaluate(double x) const = 0; 
double FiniteFunction::integrate(int Ndiv) {
  double step = (m_RMax - m_RMin) / Ndiv;
  double m_Integral = 0.0;

    // Apply trapezoidal rule
  for (int i = 0; i < Ndiv; ++i) {
      double x1 = m_RMin + i * step;
      double x2 = m_RMin + (i + 1) * step;
      m_Integral += 0.5 * (this->callFunction(x1) + this->callFunction(x2)) * step;
  }

    return m_Integral;
}

void FiniteFunction::normalize(int Ndiv) {
    m_Integral = this->integrate(Ndiv); // Compute the integral
    if (m_Integral != 0.0) {
        m_NormalizationFactor = 1.0 / m_Integral; // Correctly use m_Integral here
    } else {
        std::cerr << "Error: Integral is zero, cannot normalize the function!" << std::endl;
    }
}

double FiniteFunction::integral(int Ndiv) { //public
  if (Ndiv <= 0){
    std::cout << "Invalid number of divisions for integral, setting Ndiv to 1000" <<std::endl;
    Ndiv = 1000;
  }
  if (m_Integral == NULL || Ndiv != m_IntDiv){
    m_IntDiv = Ndiv;
    m_Integral = this->integrate(Ndiv);
    return m_Integral;
  }
  else return m_Integral; //Don't bother re-calculating integral if Ndiv is the same as the last call
}

/*
###################
//Helper functions 
################### 
*/

// Generate paths from user defined stem
void FiniteFunction::checkPath(std::string outfile){
 path fp = outfile;
 m_FunctionName = fp.stem(); 
 m_OutData = m_FunctionName+".data";
 m_OutPng = m_FunctionName+".png";
}

//Print (overridable)
void FiniteFunction::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}

/*
###################
//Plotting
################### 
*/

void FiniteFunction::plotFunction(){
  m_function_scan = this->scanFunction(10000);
  m_plotfunction = true;
}

void FiniteFunction::plotData(std::vector<double> &points, int Nbins, bool isdata){
  if (isdata){
    m_data = this->makeHist(points,Nbins);
    m_plotdatapoints = true;
  }
  else{
    m_samples = this->makeHist(points,Nbins);
    m_plotsamplepoints = true;
  }
}

/*
  #######################################################################################################
  ## SUPACPP Note:
  ## The three helper functions below are needed to get the correct format for plotting with gnuplot
  ## In theory you shouldn't have to touch them
  ## However it might be helpful to read through them and understand what they are doing
 ####################################################################################################### 
*/

std::vector< std::pair<double,double> > FiniteFunction::scanFunction(int Nscan){
  std::vector< std::pair<double,double> > function_scan;
  double step = (m_RMax - m_RMin)/(double)Nscan;
  double x = m_RMin;
  // We use the integral to normalize the function points
  if (m_Integral == NULL) {
    std::cout << "Integral not set, doing it now" << std::endl;
    this->integral(Nscan);
    std::cout << "Integral: " << m_Integral << ", calculated using " << Nscan << " divisions" << std::endl;
  }
  for (int i = 0; i < Nscan; i++){
    function_scan.push_back( std::make_pair(x,this->callFunction(x)/m_Integral));
    x += step;
  }
  return function_scan;
}

std::vector< std::pair<double,double> > FiniteFunction::makeHist(std::vector<double> &points, int Nbins){
  std::vector< std::pair<double,double> > histdata;
  std::vector<int> bins(Nbins,0);
  int norm = 0;
  for (double point : points){
    int bindex = static_cast<int>(floor((point-m_RMin)/((m_RMax-m_RMin)/(double)Nbins)));
    if (bindex<0 || bindex>Nbins){
      continue;
    }
    bins[bindex]++;
    norm++;
  }
  double binwidth = (m_RMax-m_RMin)/(double)Nbins;
  for (int i=0; i<Nbins; i++){
    double midpoint = m_RMin + i*binwidth + binwidth/2;
    double normdata = bins[i]/((double)norm*binwidth);
    histdata.push_back(std::make_pair(midpoint,normdata));
  }
  return histdata;
}

void FiniteFunction::generatePlot(Gnuplot &gp){
  if (m_plotfunction==true && m_plotdatapoints==true && m_plotsamplepoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set xlabel 'X-axis'\n";
    gp << "set ylabel 'Y-axis'\n";
    gp << "plot '-' with lines title 'Function " << m_FunctionName << "' , '-' with points title 'Data points', '-' with points title 'Sample points'\n";

    gp.send1d(m_function_scan); 
    gp.send1d(m_data); 
    gp.send1d(m_samples); 

  }
}
