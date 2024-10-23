#ifndef P2_H
#define P2_H

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
mat create_tridiagonal(int N, double a, double d, double e);
mat create_symmetric_tridiagonal(int N, double a, double d);
vec calculate_analytical_eigenvalues(int N, double a, double d);
mat calculate_analytical_eigenvectors(int N);

#endif // P2_H
