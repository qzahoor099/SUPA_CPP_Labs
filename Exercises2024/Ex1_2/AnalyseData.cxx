#include <iostream>
#include <vector>
#include "CustomFunctions.h"

int main() {
    std::vector<std::pair<float, float>> data;
    
    // Step 1: Read data from file
    std::string filename = "input2D_float.txt";  
    readData(filename, data);
    
    


    // Step 3: Ask the user for the number of vectors they want to analyze
//    int n;
  //  std::cout << "\nEnter the number of vectors you want to analyze: ";
   // if (!(std::cin >> n) || n <= 0) {
     //   std::cerr << "Invalid input. Please enter a positive integer.\n";
       // return 1;
    //}

    // Step 4: Validate user input
    //if (n > data.size()) {
      //  std::cerr << "Warning: The number of vectors exceeds the available data. Only analyzing the first " << data.size() << " vectors.\n";
        //n = data.size();
    //}

    // Step 5: Calculate and print the magnitude of the selected vectors
     int choice;
     bool keepRunning = true;

     while (keepRunning) {
         std::cout << "Choose an action:\n";
         std::cout << "1. Print data\n";
         std::cout << "2. Calculate and print magnitudes\n";
         std::cout << "3. Perform least squares fit\n";
         std::cout << "4. Calculate x^y\n";
         std::cout << "5. Exit\n";
         std::cout << "Enter your choice: ";
         std::cin >> choice;       
         switch (choice) {
             case 1:
                 int n;
                 std::cout << "Enter number of lines to print: ";
                 std::cin >> n;
                 printData(data, n);
                 //writeToFile("data.txt");
                 break;
             case 2:
                 {
                     auto magnitudes = calculateMagnitudes(data);
                     writeToFile("magnitudes.txt", magnitudes);
                 }
                 break;
             case 3:
                 fitLine(data, "fitted_function.txt");
                 break;
             case 4:
                //void calculatePower(const std::vector<std::pair<float, float>>& data, const std::string& filename);

                 calculatePower(data, "x_to_the_y.txt");
                 break;
             case 5:
                 keepRunning = false;
                 break;
             default:
                 std::cerr << "Invalid choice. Please try again.\n";
           //default:
             //    std::cerr << "Invalid choice. Please try again.\n";
         }
     }

     return 0;
 }


