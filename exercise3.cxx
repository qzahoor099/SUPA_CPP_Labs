#include <iostream>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;

int main()
 {
    double x, y;

    cout << "You have to calculate the magnitude of a vector." << endl;
    cout << "Enter the value of the variable x: ";
    cin >> x;
    cout << "Enter the value of the variable y: ";
    cin >> y;

    // Calculate the magnitude of the vector
    double magnitude = std::sqrt(x * x + y * y);

    cout << "The magnitude of the vector is: " << magnitude << endl;
    return 0;
}

   
         
