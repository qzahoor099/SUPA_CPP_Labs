#include <iostream>
#include <cmath>  // For the sqrt function

int main() {
    // Declare and initialize variables
    double x = 2.3;
    double y = 4.5;
    double z = 3.5;
    
    // Calculate the magnitude of the vector
    double magnitude = std::sqrt(x * x + y * y= z*z);
    
    // Print the result
    std::cout << "The magnitude of the vector is: " << magnitude << std::endl;
    
    return 0;
}

