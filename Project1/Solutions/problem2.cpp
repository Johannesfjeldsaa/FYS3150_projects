// 
// Solution to problem 2 of project 1 in FYS3150.
// 

// import packages
#include <iostream>
#include <vector>
#include <string>
#include <armadillo>
// ... and define namespaces
using namespace std;
using namespace arma;

// define functions
double u(double x, double xmin, double xmax) {
    if (x == xmin || x == xmax){
        return 0.
    } else if (xmin < x < xmax){       
        return  1. - (1. - std::exp(-10)*x - std::exp(-10 * x))
    } else {
        throw std::out_of_range("x is outside of the domain");
    }
}


// generate the discretised x domain 
double xmin = 0.
double xmax = 1.

arma::vec xvals = linspace<vec>(xmin, xmax, 100)

// generate the discretised u values coresponding to the x domain

arma::vec for (x in xvals){

}