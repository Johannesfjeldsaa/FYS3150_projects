// 
// Solution to problem 2 of project 1 in FYS3150.
// 

// import packages
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../build/armadillo_build/tmp/include/armadillo"
#include <cmath>

// define namespaces
using namespace std;
using namespace arma;

// define function for analytical solution
double u(double x, double xmin, double xmax) {
    if (x == xmin || x == xmax) {
        return 0.;
    } else if (xmin < x && x < xmax) {     
        return 1. - (1. - exp(-10.)) * x - exp(-10. * x);
    } else {
        throw std::out_of_range("x is outside of the domain");
    }
}

string generateDataString(const arma::vec& xvals, const arma::vec& uvals, int width, int prec) {
    ostringstream oss; // Create an output string stream (oss)

    // Write the header
    oss << "x" << " " << "u" << std::endl;

    // Write the data
    for (size_t i = 0; i < xvals.n_elem; ++i) {
        oss << std::setw(width) << std::setprecision(prec) << std::scientific << xvals(i)
            << std::setw(width) << std::setprecision(prec) << std::scientific << uvals(i) << std::endl;
    }

    // Return the string with the data
    return oss.str();
}

// define main
int main() {

    // create discretized x values
    double xmin = 0.;
    double xmax = 1.;

    vec xvals = linspace<vec>(xmin, xmax, 100);
    
    // create discretized u values
    vec uvals = zeros<vec>(xvals.n_elem);
    for (int i = 0; i < xvals.n_elem; i++) {
        uvals(i) = u(xvals(i), xmin, xmax);
    }

    // write data to file
    int width = 15;
    int prec = 8;

    string dataString = generateDataString(xvals, uvals, width, prec);
    
    cout << dataString << endl;

    return 0;
}
