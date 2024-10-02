//
// Solution to problem 2 of project 2 in FYS3150.
// 
// Contains:
//  create_tridiagonal: A function that crates a N*N tridiagonal matrix using tree different floats.
//  create_symmetric_tridiagonal: A function that crates a N*N symmetric tridiagonal matrix using two different floats.
//  calculate_analytical_eigenvalues: A function that calculates the analytical eigenvalues for a symmetric tridiagonal matrix.
//  calculate_analytical_eigenvectors: A function that calculates the analytical eigenvectors for a symmetric tridiagonal matrix.
//

// import packages
#include "p2.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../build/armadillo_build/tmp/include/armadillo"
#include <cmath>

// define namespaces
using namespace std;
using namespace arma;
double pi = M_PI;


// Create a tridiagonal matrix tridiag(a,d,e) of size N*N, 
// from scalar input a, d, and e. That is, create a matrix where
// - all N-1 elements on the subdiagonal have value a
// - all N elements on the diagonal have value d
// - all N-1 elements on the superdiagonal have value e
mat create_tridiagonal(int N, double a, double d, double e)
{
    // Create an m x m matrix filled with zeros
    mat A = mat(N, N, fill::zeros);

    // Fill the sub, main and superdiagonal
    A.diag(-1) = vec(N-1, fill::value(a));
    A.diag() = vec(N, fill::value(d));
    A.diag(1) = vec(N-1, fill::value(e));

    return A;
}


// Create a symmetric tridiagonal matrix tridiag(a,d,a) of size m*m
// from scalar input a and d.
mat create_symmetric_tridiagonal(int N, double a, double d) {
  // Call create_tridiagonal and return the result
  return create_tridiagonal(N, a, d, a);
}


// Calculate the analytical eigenvalues for the symmetric tridiagonal matrix of size N*N
vec calculate_analytical_eigenvalues(int N, double a, double d) {
  
  double eigenval;
  vec eigenvalues = zeros<vec>(N);


  for (int j = 1; j < N+1; j++) {
    eigenval = d + (
      2 * a * cos( (j * pi) / (N + 1) )
    );
    eigenvalues(j-1) = eigenval;
  }

  return eigenvalues;
}

mat calculate_analytical_eigenvectors(int N) {
  
  vec eigenvec;
  mat eigenvectors = zeros<mat>(N, N);


  for (int j = 1; j < N+1; j++) {
    eigenvec = zeros<vec>(N);

    for (int k = 1; k < N+1; k++) {
      eigenvec(k-1) = sin( (k * pi * j) / (N + 1));
    }

    eigenvectors.col(j-1) = normalise(eigenvec);
  }

  return eigenvectors;
}

// Set up the tridiagonal matrix A for N=6 
// Solves the eigenvalue problem Av=lv 
#ifdef COMPILE_AS_MAIN
int main() {

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


  vec eigval;
  mat eigvec;

  eig_sym(eigval, eigvec, A);

  cout << "Armadillo eigenvalues:" << endl;
  cout << eigval.t() << endl;
  cout << "Armadillo eigenvectors:" << endl;
  cout << eigvec << endl;
  
  return 0;
}
#endif
