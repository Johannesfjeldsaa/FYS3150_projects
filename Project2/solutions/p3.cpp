//
// Solution to problem 3 of project 2 in FYS3150.
// 
// Contains:
//  max_offdiag_symmetric: A function that finds the maximum off-diagonal element in a symmetric matrix.
//

// import packages
#include "p3.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../build/armadillo_build/tmp/include/armadillo"
#include <cmath>

// define namespaces
using namespace std;
using namespace arma;


// A function that finds the max off-diag element of a symmetric matrix A.
// - The matrix indices of the max element are returned by writing to the  
//   int references k and l (row and column, respectively)
// - The value of the max element A(k,l) is returned as the function
//   return value
double max_offdiag_symmetric(const mat& A, int& k, int& l) {

    if (A.is_square() && A.n_rows > 1) {

        int N = A.n_rows;  
        double maxval = .0;

        // Loop over the upper triangle 
        for (int row=0; row<N; row++) {
            for (int col=row+1; col<N; col++) {
                double celval = abs(A(row, col));
                if (celval > maxval) {
                    maxval = celval;
                    k = row;
                    l = col;
                }
            }
        }

        return maxval;

    } else {
        throw invalid_argument("max_offdiag_symmetric: Input matrix A must be a square matrix with at least 2 rows.");
    }
}

#ifdef COMPILE_AS_MAIN
int main() {

  // Define a 4x4 symmetric test matrix A
  mat A = { {1., 0., 0., .5},
            {0., 1., -.7, 0.},
            {0., -.7, 1., 0.},
            {.5, 0., 0., 1.} };

  int k, l;
  double maxval = max_offdiag_symmetric(A, k, l);
  
  cout << "The max absolute value off-diagonal element (assuming A is symmetric) is A(" << k << "," << l << ") = " << maxval << endl;

  return 0;
}
#endif