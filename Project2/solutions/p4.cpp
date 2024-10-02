//
// Solution to problem 4 of project 2 in FYS3150.
// 
// Contains:
//  jacobi_rotation: A function that performs the Jacobi rotation algorithm.
//  jacobi_eigensolver: A function that finds the eigenvalues and eigenvectors of a symmetric tridiagonal matrix using the Jacobi rotation algorithm.
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


// Performs a single Jacobi rotation, to "rotate away"
// the off-diagonal element at A(k,l).
// - Assumes symmetric matrix, so we only consider k < l
// - Modifies the input matrices A and R
void jacobi_rotate(mat& Ai, mat& Ri, int k, int l) {

    // get matrix cell values from Ai
    double a_kk = Ai(k, k);
    double a_ll = Ai(l, l);
    double a_kl = Ai(k, l);

    // compute tau
    double tau = (a_ll - a_kk) / ( 2. * a_kl );
    // compute t_theta
    double sign; if (signbit(tau)) { sign = -1.; } else { sign = 1.; }
    double t_theta = 1. / ( tau + (pow( 1. + pow(tau, 2.), .5 ) * sign) ); 

    // compute c_theta and s_theta
    double c_theta = 1. / pow( 1 + pow(t_theta, 2.) , .5 );
    double s_theta = c_theta * t_theta;

    // update Ai -> Ai_new, aka performe the Jacobi rotation
    mat Ai_old = Ai;
    mat Ai_new = Ai;
    Ai(k, k) = (
        a_kk * pow(c_theta, 2.) 
        - 2. * a_kl * c_theta * s_theta
        + a_ll * pow(s_theta, 2.)
    );
    Ai(l, l) = (
        a_ll * pow(c_theta, 2.) 
        + 2. * a_kl * c_theta * s_theta
        + a_kk * pow(s_theta, 2.)
    );
    Ai(k, l) = 0.;
    Ai(l, k) = 0.;
    for (int i=0; i<Ai.n_rows; i++) {
        if (i != k && i != l) {
            double ik = Ai_old(i, k) * c_theta - Ai_old(i, l) * s_theta;
            Ai(i, k) = ik;
            Ai(k, i) = ik;
            double il = Ai_old(i, l) * c_theta + Ai_old(i, k) * s_theta;
            Ai(i, l) = il;
            Ai(l, i) = il;
        }
    }

    // update the rotation matrix R
    mat Ri_old = Ri; 
    for (int i=0; i<Ri.n_rows; i++) {
        Ri(i, k) = Ri_old(i, k) * c_theta - Ri_old(i, l) * s_theta;
        Ri(i, l) = Ri_old(i, l) * c_theta + Ri_old(i, k) * s_theta;
    }

}

// Jacobi method eigensolver:
// - Runs jacobo_rotate until max off-diagonal element < eps
// - Writes the eigenvalues as entries in the vector "eigenvalues"
// - Writes the eigenvectors as columns in the matrix "eigenvectors"
//   (The returned eigenvalues and eigenvectors are sorted using arma::sort_index)
// - Stops if it the number of iterations reaches "maxiter"
// - Writes the number of iterations to the integer "iterations"
// - Sets the bool reference "converged" to true if convergence was reached before hitting maxiter
void jacobi_eigensolver(
    const mat& A, 
    const double eps, 
    vec& eigenvalues, 
    mat& eigenvectors, 
    const int maxiter, 
    int& iterations, 
    bool& converged, 
    bool verbose
    ) {

    int N = A.n_rows;
    mat Ai = A;
    mat Ri = mat(N, N, fill::eye);

    int k;
    int l;

    double maxval = max_offdiag_symmetric(Ai, k, l);
    
    while ( iterations <= maxiter ) { 
        jacobi_rotate(Ai, Ri, k, l);
        // update the k and l values
        maxval = max_offdiag_symmetric(Ai, k, l);

        iterations += 1;

        if (maxval < eps) {
            converged = true;
            if (verbose) {
                cout << "Converged in " << iterations << " iterations with maxval = " << maxval << "." << endl;
            }
            break;
        }
    }

    if (!converged && verbose) {
        cout << "Did not converge in " << iterations << " iterations with maxval = " << maxval << "." << endl;
    }


    eigenvalues = Ai.diag();
    uvec index = sort_index(eigenvalues, "descend");
    eigenvalues = eigenvalues(index);
    eigenvectors = Ri;
    eigenvectors = eigenvectors.cols(index);

}


#ifdef COMPILE_AS_MAIN
int main() {

    // Define the tridiagonal matrix and calculate its analytical eigenpairs
    int n = 7; // number of parts in discretization
    double h = 1. /(double)n; // step size
    int N = n - 1;
    double a = -1. / pow(h, 2.);
    double d = 2. / pow(h, 2.);

    mat A = create_symmetric_tridiagonal(N, a, d);
    cout << "Tridiagonal matrix:" << endl;
    cout << A << endl;

    vec analytical_eigenvalues = calculate_analytical_eigenvalues(N, a, d);
    cout << "Analytical eigenvalues:" << endl;
    cout << analytical_eigenvalues.t() << endl;

    mat analytical_eigenvectors = calculate_analytical_eigenvectors(N);
    cout << "Analytical eigenvectors:" << endl;
    cout << analytical_eigenvectors << endl;    

    // declare inputs to the jacobi_eigensolver
    double epsilon = 1e-5;
    vec jacobi_eigenvalues;
    mat jacobi_eigenvectors;
    int maxiter = 400;
    int iterations = 0;
    bool converged = false;
    bool verbose = true;
    
    // calculate the eigenpairs using the jacobi_eigensolver
    jacobi_eigensolver(A, epsilon, jacobi_eigenvalues, jacobi_eigenvectors, maxiter, iterations, converged, verbose);
    // report the eigensolve results
    cout << "Jacobi eigenvalues:" << endl;
    cout << jacobi_eigenvalues.t() << endl;
    cout << "Jacobi eigenvectors:" << endl;
    cout << jacobi_eigenvectors << endl;

    return 0;
}
#endif