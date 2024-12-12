//Courtney Dyer 12/12/24
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <numbers>
#include <math.h>
#include "FiniteFunctions.h"
#include "OtherDistributions.h"
#include <filesystem> //To check extensions in a nice way

#include "gnuplot-iostream.h" //Needed to produce plots (not part of the course) 

using std::filesystem::path;

//Empty constructor
normDist::normDist(){
    m_RMin = -5.0;
    m_RMax = 5.0;
    m_Integral = NULL;
    G_mean = 0;
    G_dev = 1;
}

// Initialised constructor

normDist::normDist(double range_min, double range_max, double mean, double dev, std::string outfile2){
    m_RMin = range_min;
    m_RMax = range_max;
    G_mean = mean;
    G_dev = dev;
    this -> checkPath(outfile2); //Use to name the file
}
// Destructor
normDist::~normDist(){
    Gnuplot gp; //Set up gnuplot object
    this->generatePlot(gp); //generates plot
}

//The normal distribution function

double normDist::Dist(double x, double mu, double sigma){
    return 1/(sigma*sqrt(2*M_PI)) * exp((-0.5)*pow((x-mu)/sigma, 2));

}

double normDist::callFunction(double x, double mu, double sigma) {
    return 1/(sigma*sqrt(2*M_PI)) * exp((-0.5)*pow((x-mu)/sigma, 2));
}

void normDist::printInfo() { //Overriding FiniteFunctions with Normal Distribution
    std::string m_FunctionName = "Normal Distribution";  // Name of function
    std::cout << "function: " <<m_FunctionName  << std::endl; //print the function name
}


// Cauchey-Lorentz distribution

//Empty constructor
CaucheyLorentz::CaucheyLorentz(){
    m_RMin = -5.0;
    m_RMax = 5.0;
    m_Integral = NULL;
    x0 = 0;
    CL_gamma = 1;
}

//Initialising constructor
CaucheyLorentz::CaucheyLorentz(double range_min, double range_max, double x0, double CL_gamma, std::string outfile3){ 
    m_RMin = range_min;
    m_RMax = range_max;
    x0 = x0;
    CL_gamma = CL_gamma;
    this -> checkPath(outfile3);
}

//Destructor
CaucheyLorentz::~CaucheyLorentz(){
    Gnuplot gp; //Set up gnuplot object
    this->generatePlot(gp);
}

//CaucheyLorentz Distribution function
double CaucheyLorentz::CaucheyFunc(double x, double x0, double CL_gamma){
    return 1/(M_PI * CL_gamma*(1+pow((x-x0)/CL_gamma, 2)));

}

double CaucheyLorentz::callFunction(double x, double mu, double sigma){
    return 1/(M_PI * sigma*(1+pow((x-mu)/sigma, 2)));
}

void CaucheyLorentz::printInfo(){
    std::string m_FunctionName = "Cauchey-Lorentz Distribution"; //Name of function/distribution
    std::cout << "Function: " << m_FunctionName << std::endl; //Print function name
}


// Crystal Ball distribution

//Empty constructors
CrystalBall::CrystalBall() {
    m_RMin = -5.0;
    m_RMax = 5.0;
    m_Integral = NULL;
    alpha_CB = 1;
    n_CB = 3;
}

//Initialising constructor
CrystalBall::CrystalBall(double range_min, double range_max, double mean, double dev, double alpha, double num, std::string outfile4) {
    m_RMin = range_min;
    m_RMax = range_max;
    G_mean = mean;
    G_dev = dev;
    alpha_CB = alpha;
    n_CB = num;
    this->checkPath(outfile4);  // Assuming checkPath is implemented somewhere
}

//Destructor
CrystalBall::~CrystalBall() {
    Gnuplot gp;  // Assuming Gnuplot is a valid class
    this->generatePlot(gp);  // Assuming generatePlot is implemented somewhere
}

double CrystalBall::callFunction(double x, double mu, double sigma) {
    return CrystalFunc(x, alpha_CB, n_CB, mu, sigma);  // Calls the CrystalFunc method
}

double CrystalBall::CrystalFunc(double x, double alpha, double n_CB, double mu, double sigma) { //Declares and calculates all variables needed
    double alpha_mag = std::abs(alpha); //absolute value of alpha
    double A = pow(n_CB / alpha_mag, n_CB) * exp(-pow(alpha_mag, 2) / 2);
    double B = n_CB / alpha_mag - alpha_mag;
    double C = (n_CB / alpha_mag) * (1 / (n_CB - 1)) * exp(-pow(alpha_mag, 2) / 2);
    double errfunc = erf(alpha_mag / sqrt(2)); //error function of absolute alpha and sqrt(2)
    double D = sqrt(M_PI / 2) * (1 + errfunc);
    double N = 1 / (sigma * (C + D));

    double condition = (x - mu) / sigma; //The formula is dependent on if this is greater than or less than - alpha
    double alphaneg = -alpha;

    if (condition > alphaneg) {
        return N * exp(-pow(x - mu, 2) / (2 * pow(sigma, 2))); // for condition > - alpha
    } else {
        return N * A * pow((B - ((x - mu) / sigma)), -n_CB); // for condition < -alpha
    }
}

void CrystalBall::printInfo(){
    std::string m_FunctionName = "Crystal Ball Distribution"; //Name of function/distribution
    std::cout << "Function " <<m_FunctionName << std::endl; //print function name
}
