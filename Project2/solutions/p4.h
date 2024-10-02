#ifndef P4_H
#define P4_H

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
void jacobi_rotate(mat& Ai, mat& Ri, int k, int l);
void jacobi_eigensolver(
    const mat& A, 
    const double eps, 
    vec& eigenvalues, 
    mat& eigenvectors, 
    const int maxiter, 
    int& iterations, 
    bool& converged, 
    bool verbose=false);


#endif // P4_H