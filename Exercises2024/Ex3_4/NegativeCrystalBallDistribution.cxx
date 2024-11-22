#include <cmath>  // For exp, pow, sqrt, erf

class NegativeCrystalBallDistribution : public FiniteFunction {
private:
    double x_bar; // Mean
    double sigma; // Standard deviation
    double alpha; // Parameter for the transition
    double n;     // Parameter for the tail

    // Precomputed constants
    double A, B, N, C, D;

    void computeConstants() {
        A = std::pow(n / std::abs(alpha), n) * std::exp(-0.5 * alpha * alpha);
        B = n / std::abs(alpha) - std::abs(alpha);
        C = n / std::abs(alpha) * (1.0 / (n - 1.0)) * std::exp(-0.5 * alpha * alpha);
        D = std::sqrt(M_PI / 2.0) * (1 + std::erf(alpha / std::sqrt(2.0)));
        N = 1.0 / (sigma * (C + D));
    }

public:
    // Constructor
    NegativeCrystalBallDistribution(double x_bar_, double sigma_, double alpha_, double n_)
        : x_bar(x_bar_), sigma(sigma_), alpha(alpha_), n(n_) {
        if (alpha <= 0 || n <= 1) throw std::invalid_argument("alpha > 0 and n > 1 are required");
        computeConstants();
    }

    // Evaluate the PDF at a given x
    double evaluate(double x) const override {
        double z = (x - x_bar) / sigma;
        if (z > -alpha) {
            return N * std::exp(-0.5 * z * z);
        } else {
            return N * A * std::pow(B - z, -n);
        }
    }

};
