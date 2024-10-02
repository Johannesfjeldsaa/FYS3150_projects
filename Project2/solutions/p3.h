#ifndef P3_H
#define P3_H

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

// Declare the function prototype
double max_offdiag_symmetric(const arma::mat& A, int& k, int& l);

#endif // P3_H