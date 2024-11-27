#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include "CUSTOMFUNCTIONS_H.h"

using namespace std;

// read x and y data from input_2D, and save x and y values
bool readdatafromFile(const string& filename, vector<float>& data_x, vector<float>& data_y) {
    std::ifstream data_file(filename);

    if (!data_file) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return false;  // Returns an error if file cannot be opened 
    }

    std::string line; // Declare variable line to contain x,y data

    while (std::getline(data_file, line)) {
        std::stringstream ss(line); // Declare ss as a string stream, using (line) as a stream of data to read from
        float x, y; // Declare x,y variables
        if (ss >> x && ss.ignore(1, ',') && ss >> y) {  // This assigns x to the charcters up to the ',', then assigns the characters post the ',' to y. Giving the x, y data.
            data_x.push_back(x); //adds the x-values to data_x
            data_y.push_back(y); // "   " but for y
        }
    }

    return true;
}

// display the x and y data received from readdatafromFile
void displayData(const vector<float>& data_x, const vector<float>& data_y, int n) {
    for (int i = 0; i < n && i < data_x.size(); i++) { // when the integer is less than the n given and less than the total number of datapoints
        cout << "x - values: " << data_x[i] << ", y-values: " << data_y[i] << endl; //print x-values and y-values
    }
}

// calculate magnitudes of vectors from the x and y data
void calculateMagnitudes(const vector<float>& data_x, const vector<float>& data_y, vector<float>& magnitudes) {
    int datapoints = data_x.size();
    vector<float> magnitude_x(datapoints), magnitude_y(datapoints);

    for (int i = 0; i < datapoints; i++) {
        magnitude_x[i] = data_x[i] * data_x[i];  // Calculate x squared
        magnitude_y[i] = data_y[i] * data_y[i];  // Calculate y squared
    }

    for (int i = 0; i < datapoints; i++) {  // whilst i is less than no. of datapoints
        magnitudes[i] = sqrt(magnitude_x[i] + magnitude_y[i]);  // Calculate magnitude using the previously calculated square of x and y
        writetoFile("magnitude.txt", to_string(magnitudes[i])); //write these magnitudes to file
    }
}


// calculate the magnitudes of vectors from data_x and data_y without write function
void calculateMagnitude(const vector<float>& data_x, const vector<float>& data_y, vector<float>& magnitudes) {
    int datapoints = data_x.size();
    vector<float> magnitude_x(datapoints), magnitude_y(datapoints);

    for (int i = 0; i < datapoints; i++) {
        magnitude_x[i] = data_x[i] * data_x[i];  // Calculate x squared
        magnitude_y[i] = data_y[i] * data_y[i];  // Calculate y squared 
    }

    for (int i = 0; i < datapoints; i++) {
        magnitudes[i] = sqrt(magnitude_x[i] + magnitude_y[i]);  // Calculate magnitude using the previously calculated squares of x and y
 
    }
}

// get user input on the number of data points they want to process (n)
int getUserInput() {
    string user_input;
    cout << "Enter the number of data points to process: ";
    cin >> user_input;
    return std::stoi(user_input);  // Returns the user input as an integer
}

// calculate the straight line values for y using least squares fitting, then by calculated X show that this is not a good fit.
void leastSquaresFitting(const vector <float>& data_x, const vector <float>& data_y,const vector <float>& magnitude_x, vector <float>& y_line, int n, float X_2_NDF){
    // Declare variables
    int datapoints = data_x.size();
    float sum_xy = 0;
    float sum_y = 0;
    float sum_x = 0;
    float sum_x2 = 0;
    float sum_x_2 = 0;
    float p;
    float q;


    for(int i = 0; i < datapoints; i++){
        sum_xy += data_x[i] * data_y[i];  // sum of (x*y)
        sum_y += data_y[i];               // sum of y
        sum_x += data_x[i];               // sum of x
        sum_x2 += data_x[i] * data_x[i];  // sum of x^2
        
    }

    sum_x_2 = sum_x * sum_x;            // (sum of x) squared
    cout << sum_xy <<" " << sum_y<< " " << sum_x << " "<< sum_x2 << " "<< sum_x_2 << endl; //print these sums

    p = ((n* sum_xy) - (sum_y * sum_x)) / ((n*sum_x2)- sum_x_2);  // calculate p as given in question
    q = ((sum_x2 * sum_y) - (sum_xy * sum_x)) / ((n* sum_x2) - (sum_x_2)); // calculate q as given in question


    writetoFile("straightline.txt", "Expected y-values"); // Writes to file "expected y-values"
    
    for (int i = 0; i<datapoints; i++){
        y_line[i] = (p * data_x[i]) + q;  // Expected y-value calculation
        writetoFile("straightline.txt", to_string(y_line[i])); //Write to file the expected y-value

    }

    string myerr = "error2D_float.txt"; // 2D error file 
    vector <float> err_x, err_y;

    if (!readdatafromFile(myerr, err_x, err_y)){
        return;
    }
    float X_2 = 0; // Declare chi-squared as X_2
    for (int i = 0; i < datapoints; i++){
        X_2 += ((data_y[i] - y_line[i])*(data_y[i]- y_line[i])) / (err_y[i]* err_y[i]); // calculate chi-squared through iterations
    }

    cout << X_2 << endl; // print chi-squared

    int NDF = datapoints - 1; // The number of degrees of freedom (NDF)

    X_2_NDF = X_2 / NDF; // Calculate the chi-squared / Number of degrees of freedom

    writetoFile("straightline.txt", "Chi-squared / NDF: " + to_string(X_2_NDF)); //Write to file chi-squared/NDF

}

// calculate x to the power y without using function
float calculatePower( float data_x,  int  whole_y){
    if (whole_y == 0) {
        return 1;
    }

    else if (whole_y > 0) {
        return data_x * calculatePower(data_x, whole_y-1); //recursion multiplies x by itself y times
    }

    else{
        return 1.0f / calculatePower(data_x, -whole_y);  // for negative values it becomes 1/ (x^y)
    }
}


// calculate x to the power y for our vector values of x and y using the power function created
void Displayx_powy(const vector <float>& data_x, const vector <float>& data_y,vector <int>& x_power_y){
    int datapoints = data_x.size();
    //vector <int> x_power_y;
    x_power_y.resize(datapoints);
    vector <int> whole_y(datapoints);

    for (int i= 0; i < datapoints; i++){
        whole_y[i] = round(data_y[i]); //rounds the y data to nearest whole number

    }

    string filename = "x^y.txt";

    for (int i = 0; i < datapoints; i++){
        //cout << "The value for x^y of the " << i << "datapoint " << x_power_y[i] << endl;
        
        x_power_y[i] = calculatePower(data_x[i], whole_y[i]);
        writetoFile(filename, to_string(x_power_y[i])); // write x to the power y to file
    }

}


// write to file function
void writetoFile(const string filename,const string data){
    ofstream outStream(filename, std::ios::app); // app allows for appending file

    if (!outStream.is_open()){
        cout << "Error" << endl; // If file does not open
        return;
    }

    outStream << data << endl;  // Prints data to file
    outStream.close();
}



