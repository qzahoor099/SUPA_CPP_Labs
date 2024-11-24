#include <iostream>
#include <random>

double estimatePi(int radius, int n) {
    int inside_circle = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-radius, radius);

    for (int i = 0; i < n; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        if (x*x + y*y <= radius*radius) {
            inside_circle++;
        }
    }

    return 4.0 * inside_circle / n;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <radius> <n random>" << std::endl;
        return 1;
    }

    int radius = std::stoi(argv[1]);
    int n = std::stoi(argv[2]);
    double pi_estimate = estimatePi(radius, n);

    std::cout << "Estimated Pi: " << pi_estimate << std::endl;
    return 0;
}
