// Courtney Dyer 13/11/24
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <numeric>
#include <string>
#include <sstream>  
#include "CUSTOMFUNCTIONS_H.h"



int main(){
    int funct;
    bool go = true; // Declares variables that will be used in switch

    while (go){
        cout << "Select one of the following functions: \n Type 1 for print \n Type 2 for magnitude \n Type 3 for straight-line \n Type 4 for x to the power y \n";
        cin >> funct; // Get input from user on which function they would like to use

        switch (funct) {
        case 1:
            cout << "You have selected the print function " << endl; // Lets the user know which function they have selected 
            go = false;
            break;
    
        case 2:
            cout << "You have selected the magnitude function " << endl;
            go = false;
            break;
        
        case 3:
            cout << "You have selected the straight-line function " << endl;
            go = false;
            break;
        
        case 4:
            cout << "You have selected the x to the power y function " << endl;
            go = false;
            break;
        
        default:
            cout << "The input value was invalid" << endl; // If the input value is not 1-4 then this error message will be shown
            cout << "Exit loop" << endl; // Let user know that the loop is ending and to try again
            go = false;
            break;
        
        }
    }
        
    //cout << "Which function would you like to use?" << endl;
    //cin >> funct;

    
    string myInput = "input2D_float.txt";
    vector<float> data_x, data_y;

    // read x and y data from the file
    if (!readdatafromFile(myInput, data_x, data_y)) {
        return 1;  // exit if file cannot be read
    }

    // Declare datapoints as the size of data_x ie. number of lines of data
    int datapoints = data_x.size();
    cout << "Total datapoints: " << datapoints << endl;

    if (funct == 1){
        // user input for the number of data points they want to process
        int n = getUserInput();

        // Display the number of data points requesed by user
        if (n > datapoints) {
            cout << "Warning: The requested number of data points exceeds available data." << endl;
            displayData(data_x, data_y, 5);  // print first 5 lines
        } else {
            displayData(data_x, data_y, n);  // print the requested number of data points
        }
    }
    else if (funct == 2){

        vector<float> magnitudes(datapoints);
        calculateMagnitudes(data_x, data_y, magnitudes); // Use function to calculate magnitudes of vectors

        cout << "Magnitudes of the vectors:" << endl;
        for (int i = 0; i < datapoints; i++) {
            cout << "Magnitude of vector " << i + 1 << ": " << magnitudes[i] << endl; // print these vector magnitudes
        }

    }
    else if (funct == 3) {
        //Declare variables
        vector<float> magnitudes(datapoints);
        vector <float> y_line(datapoints);
        int n = datapoints;
        vector <float> magnitude_x(datapoints);
        float X_2_NDF;
        float X_2;
        calculateMagnitude(data_x, data_y, magnitudes); // Calculates magnitudes without writing to file
        leastSquaresFitting(data_x, data_y,magnitude_x,y_line, n, X_2_NDF); // Find the expected y using leastsquaresfitting

        for (int i = 0; i< datapoints; i++){

            cout << "Expected y-values: " << y_line[i] << endl;  //print expected y-values calculated
        }

        cout << "Chi-squared/ NDF = " << X_2_NDF << ", this is not a good fit." <<endl; // print chi-squared/ No. of degrees of freedom and if << 1 this is not a good fit
    
    }
    else if(funct == 4){
        vector <int> x_power_y(datapoints);

        Displayx_powy(data_x, data_y, x_power_y); // Displays x^y and contains in it the function to calculate x to the power y or any other power

        for (int i = 0; i < datapoints ; i++){
            cout << "x to the power y: " << x_power_y[i] << endl; // prints x to the power y
        }

     

    
    } // End of if loop after all 4 options



} // The end of main()