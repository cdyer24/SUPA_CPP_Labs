//Courtney Dyer 12/12/24
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "FiniteFunctions.h"
#include "OtherDistributions_1.h"
#include <filesystem>
#include <fstream>
#include "gnuplot-iostream.h"

using std::filesystem::path;
using namespace std;

int main() {

    string myInput = "Outputs/data/MysteryData03140.txt"; //import data
    vector <double> data;
    std::ifstream data_file(myInput);
    std::string line;

    if(!data_file){
        std::cerr << "Error file could not be opened" << myInput << std::endl; //Show error if data cannot be opened
        exit(1);
    }

    while(std::getline(data_file, line)) {
        data.push_back(std::stod(line)); //Get data from file
    }

    auto xminmax = minmax_element(data.begin(), data.end()); // find the max & min values of data

    double xmin = *xminmax.first;
    //cout << xmin << endl;
    double xmax = *xminmax.second;

    double step;

    //Normal Distribution

    FiniteFunction finitef(xmin, xmax, "Inverse x squared");

    finitef.printInfo();

    double xsum;
    for(int i = 0; i <data.size(); i++){
        double mu,sigma = 0;
        xsum += data[i]; //Calculate the sum of data
    }


    bool isdata;

    // Now we need to calculate the mean (mu) and standard deviation (sigma) of the data set

    double n = data.size();

    double mu = xsum / n ; //mean of data

    double sigma;
    for(int i = 0; i<n; i++){
        sigma += pow(data[i]-mu, 2);
    }
    sigma = sqrt(sigma/n); //The standard deviation

    normDist nd(xmin, xmax, mu,sigma,"Normal Distribution");  //Normal distribution function


    std::cout << mu <<" " << sigma << std::endl;
    Gnuplot gp;
    nd.printInfo();


//plot finitefunction
    finitef.plotFunction();
    finitef.plotData(data,1000,isdata);


//plot normal distribution
    nd.printInfo();
    nd.plotData(data, 100, isdata);
    nd.plotFunction();

    //Cauchey-Lorentz Distribution

    double x0 = xsum/ n;
    double CL_gamma = 2; //guess
    CaucheyLorentz C(xmin, xmax, x0, CL_gamma, "Cauchey-Lorentz"); //Cauchey-Lorentz distribution function

//Cauchey-Lorentz plotting
    C.printInfo();
    C.plotData(data,100, isdata);
    C.plotFunction();


//Crystal Ball distribution
    double alpha = 2.3; //guess
    double num = 2.2;  //guess


    CrystalBall Crystal(xmin, xmax, mu, sigma, alpha, num, "Crystal Ball" ); //Crystal ball distribution function

//Plotting the Crystal ball distribution
    Crystal.printInfo();
    Crystal.plotData(data,100,isdata);
    Crystal.plotFunction();




// Sampling

srand(time(0)); 

//Generate random x

double x_rand = (rand() % 11) - 5; //Generates a random number between -5 and 5

// x_rand is the centre of the distribution

//arbitrary standard deviation

double arb_dev = 1;

//Generate random y



vector <double> vect_sample(n);
for(int i = 0; i < n; i++){
    vect_sample[i] = nd.callFunction(data[i], x_rand, arb_dev);
    

}

double max_y = *max_element(vect_sample.begin(), vect_sample.end());

std::cout << "Max y" << max_y << std::endl;

//Generate random y based on distribution

srand(time(0)); 


double value_rand = static_cast<double>(rand()) / RAND_MAX ;
std::cout << value_rand << std::endl;

double y_rand = value_rand * max_y;


// Print/Display random x and random y

std::cout << "Random value of x = " << x_rand << std::endl;
std::cout << "Random value of y = " << y_rand << std::endl;
}
