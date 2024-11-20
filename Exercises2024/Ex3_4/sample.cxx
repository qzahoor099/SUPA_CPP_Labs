#include <iostream>
<<<<<<< HEAD
#include <fstream>
#include <vector>
#include <cmath>
#include <numeric>

// Function to calculate the mean
double calculateMean(const std::vector<double>& data) {
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

// Function to calculate the standard deviation
double calculateStdDev(const std::vector<double>& data, double mean) {
    double sum = 0.0;
    for (double value : data) {
        sum += std::pow(value - mean, 2);
    }
    return std::sqrt(sum / data.size());
}

// Function to perform normal distribution
std::vector<double> normalDistribution(const std::vector<double>& data, double mean, double stdDev) {
    std::vector<double> normalizedData;
    for (double value : data) {
        double z = (value - mean) / stdDev;
        normalizedData.push_back(z);
    }
    return normalizedData;
}

int main() {
    std::ifstream inputFile("MysteryData01202.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::vector<double> data;
    double value;
    while (inputFile >> value) {
        data.push_back(value);
    }
    inputFile.close();

    if (data.empty()) {
        std::cerr << "No data found in the file!" << std::endl;
        return 1;
    }

    double mean = calculateMean(data);
    double stdDev = calculateStdDev(data, mean);
    std::vector<double> normalizedData = normalDistribution(data, mean, stdDev);

    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Standard Deviation: " << stdDev << std::endl;
    std::cout << "Normalized Data: ";
    for (double z : normalizedData) {
        std::cout << z << " ";
    }
    std::cout << std::endl;

    return 0;
}

=======
#include <cmath>
#include <random>
#include <vector>

const double PI = 3.14159265358979323846;

// Generate normal distribution samples
std::vector<double> generate_normal_distribution(int n, double mu, double sigma) {
    std::vector<double> samples;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(mu, sigma);

    for (int i = 0; i < n; ++i) {
        samples.push_back(dist(gen));
    }

    return samples;
}

// Generate Cauchy-Lorentz distribution samples
std::vector<double> generate_cauchy_distribution(int n, double x0, double gamma) {
    std::vector<double> samples;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-PI, PI);

    for (int i = 0; i < n; ++i) {
        double u = dist(gen);
        double x = x0 + gamma * tan(u);
        samples.push_back(x);
    }

    return samples;
}

// Generate negative Crystal Ball distribution samples
std::vector<double> generate_crystal_ball_distribution(int n, double x_bar, double sigma, double alpha, double n_param) {
    std::vector<double> samples;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> norm_dist(x_bar, sigma);
    std::uniform_real_distribution<> uniform_dist(0.0, 1.0);

    for (int i = 0; i < n; ++i) {
        double x = norm_dist(gen);
        double z = (x - x_bar) / sigma;
        
        if (z > -alpha) {
            samples.push_back(x); // Normal distribution part
        } else {
            double A = pow(n_param / fabs(alpha), n_param) * exp(-0.5 * pow(fabs(alpha), 2));
            double B = n_param / fabs(alpha) - fabs(alpha);
            double y = A * pow(B - z, -n_param);
            samples.push_back(x); // Crystal ball tail part
        }
    }

    return samples;
}

int main() {
    // Normal distribution example (mu = 0, sigma = 1)
    int num_samples = 1000;
    double mu = 0, sigma = 1;
    auto normal_samples = generate_normal_distribution(num_samples, mu, sigma);
    std::cout << "Normal Distribution Sample: " << normal_samples[0] << std::endl;

    // Cauchy-Lorentz distribution example (x0 = 0, gamma = 1)
    double x0 = 0, gamma = 1;
    auto cauchy_samples = generate_cauchy_distribution(num_samples, x0, gamma);
    std::cout << "Cauchy-Lorentz Distribution Sample: " << cauchy_samples[0] << std::endl;

    // Negative Crystal Ball distribution example (x_bar = 0, sigma = 1, alpha = 2, n_param = 2)
    double x_bar = 0, alpha = 2, n_param = 2;
    auto crystal_ball_samples = generate_crystal_ball_distribution(num_samples, x_bar, sigma, alpha, n_param);
    std::cout << "Crystal Ball Distribution Sample: " << crystal_ball_samples[0] << std::endl;

    return 0;
}
>>>>>>> e60f428 (now start working on the recent changes)
