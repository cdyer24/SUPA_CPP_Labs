#ifndef CUSTOMFUNCTIONS_H
#define CUSTOMFUNCTIONS_H
// Include libraries for variable type
#include <vector>  
#include <string>  

using namespace std;

// Declare functions
bool readdatafromFile(const string&, vector<float>&, vector<float>&);

void displayData(const vector<float>&, const vector<float>&, int);

void calculateMagnitudes(const vector <float>&, const vector<float>&, vector<float>&);

void calculateMagnitude(const vector <float>&, const vector<float>&, vector<float>&);

int getUserInput();

void leastSquaresFitting(const vector<float>&, const vector<float>&, const vector <float>&, vector <float>&, int, float);

float calculatePower(float  , int );

void Displayx_powy(const vector <float>&, const vector <float>&, vector <int> &);

void writetoFile( const string, const string);

#endif  // CUSTOMFUNCTIONS_H
