#include <string>
#include <vector>
#include "gnuplot-iostream.h"
#include "FiniteFunctions.h"
#pragma once

class FiniteFunction;

//Normal distribution as a child class of FiniteFunction

class normDist: public FiniteFunction{

public: 
    normDist();
    normDist(double range_min, double range_max, double G_mean, double G_dev , std::string outfile); //Define variables needed and file name
    ~normDist();

    virtual double callFunction(double x, double mu, double sigma) override; //override to call Normal distribution
    virtual void printInfo() override; //print info about distribution

    double Dist(double x, double mu, double sigma); //Defining the normal distribution

protected:

    double G_mean;
    double G_dev;

};

class CaucheyLorentz : public FiniteFunction{
public:
    CaucheyLorentz();
    CaucheyLorentz(double range_min, double range_max, double x0, double CL_gamma,std::string outfile); //Define variables needed and name of file
    ~CaucheyLorentz();

    virtual double callFunction(double x, double mu, double sigma) override; // Override so that CaucheyLorentz is called

    virtual void printInfo() override ; //CaucheyLorentz info printed
    double CaucheyFunc(double x, double x0, double CL_gamma); //CaucheyLorentz function variable declaration



protected:

    double x0;
    double CL_gamma;


};

class CrystalBall : public FiniteFunction{

public: 
    CrystalBall();
    CrystalBall(double range_min, double range_max, double G_mean, double G_dev,double alpha, double n_CB, std::string outfile ); // Define variables needed and name of file
    ~CrystalBall();

    virtual double callFunction(double x, double mu, double sigma) override; //Overrides callfunction for Crystal Ball Distribution
    virtual void printInfo() override ; // Prints Crystal Ball distribution info

    double CrystalFunc(double x, double alpha, double n_CB, double mu, double sigma); // Crystal Ball function


protected:
    double alpha_CB;
    double n_CB;
    double G_mean;
    double G_dev;


};