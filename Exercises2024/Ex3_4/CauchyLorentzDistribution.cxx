#include <cmath>  // For M_PI

class CauchyLorentzDistribution : public FiniteFunction {
private:
    double x0;  // Location parameter
    double gamma; // Scale parameter

public:
    // Constructor
    CauchyLorentzDistribution(double x0_, double gamma_) : x0(x0_), gamma(gamma_) {
        if (gamma <= 0) throw std::invalid_argument("gamma must be > 0");
    }

    // Evaluate the PDF at a given x
    double evaluate(double x) const override {
        double numerator = gamma;
        double denominator = M_PI * (gamma * gamma + std::pow(x - x0, 2));
        return numerator / denominator;
    }
};
