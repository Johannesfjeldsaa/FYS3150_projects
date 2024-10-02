//
// Solution to problem 6 of project 2 in FYS3150.
// 

// import packages
#include "p2.h"
#include "p3.h"
#include "p4.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <variant>
#include <unordered_map>
#include "../build/armadillo_build/tmp/include/armadillo"
#include <cmath>


// define namespaces
using namespace std;
using namespace arma;



//! Calculates the i'th x value given the minimum value of x (x_min), 
//! the number of steps (n) and the step size (h).
double x_i(int i, const double x_min, const double h) {
    return x_min + i * h;
}

string generateDataString(vec x_vec, vec jacobi_eigenvalues, mat jacobi_eigenvectors, vec analytical_eigenvalues, mat analytical_eigenvectors, int width, int prec) {
    ostringstream oss; // Create an output string stream (oss)
 
    oss << "eigenvalues:" << endl;
    oss << "jacobi eigenvalues" << endl;
    oss << jacobi_eigenvalues.t() << endl;

    oss << "analytical eigenvalues" << endl;
    oss << analytical_eigenvalues.t() << endl;

    // Write the header
    oss << "eigenvectors:" << endl;
    oss << "x,j_v1,j_v2,j_v3,a_v1,a_v2,a_v3" << std::endl;

    // Write the data
    for (size_t i = 0; i < x_vec.n_elem; ++i) {
        oss << std::setw(width) << std::setprecision(prec) << std::scientific << x_vec(i) << "," 
            << std::setw(width) << std::setprecision(prec) << std::scientific << jacobi_eigenvectors(i, 0) << "," 
            << std::setw(width) << std::setprecision(prec) << std::scientific << jacobi_eigenvectors(i, 1) << "," 
            << std::setw(width) << std::setprecision(prec) << std::scientific << jacobi_eigenvectors(i, 2) << "," 
            << std::setw(width) << std::setprecision(prec) << std::scientific << analytical_eigenvectors(i, 0) << "," 
            << std::setw(width) << std::setprecision(prec) << std::scientific << analytical_eigenvectors(i, 1) << "," 
            << std::setw(width) << std::setprecision(prec) << std::scientific << analytical_eigenvectors(i, 2) << std::endl;
    }

    // Return the string with the data
    return oss.str();
}

int main() {

    // discretized x domain
    double xmin = 0.;
    double xmax = 1.;

    // if n = 10
    int n = 100; //10;
    int N = n - 1;
    double h = (xmax - xmin) / (double)n;

    vec x_vec = zeros<vec>(n+1);
    for (int i = 0; i < n+1; i++) {
        x_vec(i) = x_i(i, xmin, h);
    }

    double a = -1. / pow(h, 2.);
    double d = 2. / pow(h, 2.);
    mat A = create_symmetric_tridiagonal(N, a, d);

    // declare inputs to the jacobi_eigensolver 
    double epsilon = 1e-5;
    int maxiter = 10000000;
    vec jacobi_eigenvalues;
    mat jacobi_eigenvectors;
    int iterations = 0;
    bool converged = false;
    bool verbose = false;

    // calculate the eigenpairs using the jacobi_eigensolver
    jacobi_eigensolver(A, epsilon, jacobi_eigenvalues, jacobi_eigenvectors, maxiter, iterations, converged, verbose);

    uvec sort_order = arma::sort_index(jacobi_eigenvalues, "ascend");
    
    jacobi_eigenvalues = jacobi_eigenvalues(sort_order);
    vec jacobi_first_three_eigenvalues = jacobi_eigenvalues.subvec(0, 2);
    
    jacobi_eigenvectors = jacobi_eigenvectors.cols(sort_order);
    jacobi_eigenvectors.insert_rows(0, 1);
    jacobi_eigenvectors.insert_rows(jacobi_eigenvectors.n_rows, 1);

    mat jacobi_first_three_eigenvectors = jacobi_eigenvectors.cols(0, 2);
    
    vec analytical_eigenvalues = calculate_analytical_eigenvalues(N, a, d);
    vec analytical_first_three_eigenvalues = analytical_eigenvalues.subvec(0, 2);
    
    mat analytical_eigenvectors = calculate_analytical_eigenvectors(N);
    analytical_eigenvectors.insert_rows(0, 1);
    analytical_eigenvectors.row(0).zeros();
    analytical_eigenvectors.insert_rows(analytical_eigenvectors.n_rows, 1);
    analytical_eigenvectors.row(analytical_eigenvectors.n_rows-1).zeros();
    mat analytical_first_three_eigenvectors = analytical_eigenvectors.cols(0, 2);

    
    cout << generateDataString(
        x_vec, 
        jacobi_first_three_eigenvalues, 
        jacobi_first_three_eigenvectors, 
        analytical_first_three_eigenvalues, 
        analytical_first_three_eigenvectors, 
        15, 8) << endl;



    return 0;
}