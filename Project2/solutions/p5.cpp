//
// Solution to problem 5 of project 2 in FYS3150.
// 
// Contains:
//

// import packages
#include "p2.h"
#include "p3.h"
#include "p4.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../build/armadillo_build/tmp/include/armadillo"
#include <cmath>


// define namespaces
using namespace std;
using namespace arma;


string generateDataString(vec N_vec, vec conv_vec, vec iter_vec, vec matrixtype_vec, int width, int prec) {
    ostringstream oss; // Create an output string stream (oss)
 
    // Write the header
    oss << "N,Converged,Iterations,Type" << std::endl;

    // Write the data
    for (size_t i = 0; i < N_vec.n_elem; ++i) {
        oss << std::setw(width) << std::setprecision(prec) << std::scientific << N_vec(i) << "," 
            << std::setw(width) << std::setprecision(prec) << std::scientific << conv_vec(i) << "," 
            << std::setw(width) << std::setprecision(prec) << std::scientific << iter_vec(i) << ","  
            << matrixtype_vec(i) << endl;
    }

    // Return the string with the data
    return oss.str();
}

mat create_matrices(int N, int type) {
    if (type == 1) {

        int n = N + 1; // number of parts in discretization
        double h = 1. /(double)n; // step size
        double a = -1. / pow(h, 2.);
        double d = 2. / pow(h, 2.);
        return create_symmetric_tridiagonal(N, a, d);
    }
    else if (type == 2) {

        int n = N + 1; // number of parts in discretization
        double a = -1.; 
        double d = 2.;
        return create_symmetric_tridiagonal(N, a, d);
    }
    else if (type == 3) {
        mat A = mat(N, N).randn();    
        return arma::symmatu(A);
    }
    else {
        throw std::invalid_argument("Invalid matrix type");
    }
}

#ifdef COMPILE_AS_MAIN
int main() {

    // declare inputs to the jacobi_eigensolver that is constants
    double epsilon = 1e-5;
    int maxiter = 10000000;
    
    // Create a logarithmically spaced vector of N values
    vec N_vec = vec({2, 4, 8, 16, 32, 64}); // 128, 256, 512}); // only comment this out if you have alot of time
    vec conv_vec = zeros<vec>(3*N_vec.n_elem);
    vec iter_vec = zeros<vec>(3*N_vec.n_elem); 
    vec matrixtype_vec = zeros<vec>(3*N_vec.n_elem);   

    int vec_index = 0;
    for (int type = 1; type < 4; type++) {
        
    
        for (int i = 0; i < N_vec.n_elem; i++) {
        
            int N = N_vec(i);

            // create the tridiagonal matrix for the current value of N
            mat A = create_matrices(N, type);

            // declare inputs to the jacobi_eigensolver that should be reset for each value of N
            vec jacobi_eigenvalues;
            mat jacobi_eigenvectors;
            int iterations = 0;
            bool converged = false;
            bool verbose = true;

            // calculate the eigenpairs using the jacobi_eigensolver
            jacobi_eigensolver(A, epsilon, jacobi_eigenvalues, jacobi_eigenvectors, maxiter, iterations, converged, verbose);

            conv_vec(vec_index) = converged;
            iter_vec(vec_index) = iterations;
            matrixtype_vec(vec_index) = type;

            vec_index++;
        }
    }
    
    cout << generateDataString(repmat(N_vec, 3, 1), conv_vec, iter_vec, matrixtype_vec, 15, 8) << endl;
    return 0;
}
#endif