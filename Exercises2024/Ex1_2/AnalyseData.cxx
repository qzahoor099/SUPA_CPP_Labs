/*
name: Quratulain Zahoor 
Date: 21-Nov-2024
Email: s2718548@ed.ac.uk
*/
/*
Procedure to Run
make
./AnalyseData


*/


//including the libraries
#include <iostream> //this is to use for input/output stream 
#include <vector>  //this includes the vector 
#include "CustomFunctions.h" //this is my header file 
std::vector<float> errors; 
std::string error2D_float = "error2D_float.txt";  // this is my error file to be used for chi function

std::vector<std::pair<float, float>> data;  // fill it with data 
float m = 0.0;  // Slope initializion
float c = 0.0;  // Intercept initialization 

//start of the main program
int main() {
    std::vector<std::pair<float, float>> data;
    
    // Step1: Read data from input file that contains x, y pairs
    std::string filename = "input2D_float.txt";  
    readData(filename, data);
    // defining the multiple choices, which user can select what he wants to do, i havent added the saperate print and read functions
     
     // ask the user which function,you can see different options below
     int choice;
     bool keepRunning = true; //the input should be valid to keep it running


     while (keepRunning) {   //list of my input options
         std::cout << "Choose an action:\n";
        // std::cout << "Select an option:\n1. Print Data\n2. Calculate Magnitudes\nChoice: ";

         std::cout << "1. Print data\n";
         std::cout << "2. Calculate and print magnitudes\n";
         std::cout << "3. Perform least squares fit\n";
         std::cout << "4. Calculate x^y\n";
         std::cout << "5. Exit\n";
         std::cout << "Enter your choice: ";
         std::cin >> choice;       
         //create multiple cases what ever user choice it will go to the certain case and perform the task
         switch (choice) {
             case 1:  //will print the data once you selected the datasize you wanted to work
                 int n;
                 std::cout << "Enter number of lines to print: ";
                 std::cin >> n;
                 std::cout<<"the  number of lines selected:  "<< n<<std::endl;
                 printData(data, n); 
                 //writeToFile("data.txt", data);  //if someone want to print the data inside the file, but its optional
                 break;
             case 2:
                 {
                     auto magnitudes = calculateMagnitudes(data); //calculating the magnitude from my data
                     printMagnitude(magnitudes);  //print the magnitude inside the terminal
                     writeToFile("magnitudes.txt", magnitudes); //will store the results inside the file
                 }
                 break;
             case 3:
                 fitLine(data, "fitted_function.txt"); //make the fit using the slope y=mx+c
                 break;
             case 4:
                //void calculatePower(const std::vector<std::pair<float, float>>& data, const std::string& filename);

                 calculatePower(data, "x_to_the_y.txt");  //calculating the power
                 break;
             case 5:
                 keepRunning = false; //if the choice is not valid it will take it false and exit when you press 5
                 break;
             default:
                 std::cerr << "Invalid choice. Please try again.\n";  //if you enter the choice>5
           
         }
     }

     return 0;
 }

//I hope what i get the processing logic is okey