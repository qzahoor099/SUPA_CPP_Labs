#include <cmath>  // For exp, sqrt, M_PI

class NormalDistribution : public FiniteFunction {
private:
    double mu;   // Mean
    double sigma; // Standard deviation

public:
    // Constructor
    NormalDistribution(double mu_, double sigma_) : mu(mu_), sigma(sigma_) {}

    // Evaluate the PDF at a given x
    double evaluate(double x) const override {
        double coeff = 1.0 / (sigma * std::sqrt(2 * M_PI));
        double exponent = -0.5 * std::pow((x - mu) / sigma, 2);
        return coeff * std::exp(exponent);
    }

    // (Optional) Implement integration, bounds checking, etc., as needed.
};
