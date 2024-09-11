//
// Solution to problem 7 of project 1 in FYS3150.
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

// In order to solve the equation Av = g we need to define all the properties which we have discretized through 
// problem 3, 4 and 6. 

// the x values we discretized in problem 3. there we defined x_i = x_min + i * delta_x
double x_i(int i, double x_min, double delta_x) {
    return x_min + i * delta_x;
}

// To define the g values we need to use the equation g_i = delta_x^2 * f_i as derived in problem 4. Therefore we need the 
// discretized functions for f_i and g_i.

double f_i(int i, double x_min, double delta_x) {
    return 100 * exp(-10 * x_i(i, x_min, delta_x));
}

double g_i(int i, int n_steps, double x_min, double delta_x) {
    return delta_x * delta_x * f_i(i, x_min, delta_x);
}  

// To test our approximation we need the values of equation 
// u_i = 1 - (1 - exp(-10)) * x_i - exp(-10 * x_i) as derived in problem 3.
double u_i(int i, int n_steps,double x_min, double delta_x) {
    if (i == 0 || i == n_steps) {
        return 0;
    } else {
        return 1 - (1 - exp(-10)) * x_i(i, x_min, delta_x) - exp(-10 * x_i(i, x_min, delta_x));   
    }
}

// lastly (before a main function) we need the thomas algorithm to solve the tridiagonal matrix.
// As shown through problem 6 we dont need the full matrix. We therefor assume that we are passed
// vectors of the same size into the function. 

vec thomas_alg(
    vec subdiag,
    vec diag,
    vec supdiag,
    vec gvec
) {

    // We use the dimension of the matrix as a property.
    int dim_A = subdiag.n_elem;
    // check if the diagonals are of the correct size
    for (auto& vec : {subdiag, diag, supdiag, gvec}) {
        if (vec.n_elem != dim_A) {
            throw std::invalid_argument("All vectors must be of the same length");
        }
    }

    // next we create the vector to store temporary diagonal values tilde(b_j) and tilde(g_j)
    // and the solution vector v
    vec tilde_diag(dim_A, fill::zeros);
    vec tilde_gvec(dim_A, fill::zeros);
    vec vvec(dim_A, fill::zeros);

    // now we start with the forward substitution
    // for j = 0 we set tilde(b_0) = b_0 and tilde(g_0) = g_0
    // for the remaining j's we subtract the a_j/tilde(b_j-1) * tilde(x_j-1), 
    // where x is either b or g depending on which vector we are working on
    for (int j = 0; j < dim_A; j++) {
        if (j == 0){
        	tilde_diag(j) = diag(j);
            tilde_gvec(j) = gvec(j);
        } else {
        	tilde_diag(j) = diag(j) - ( (subdiag(j) / tilde_diag(j-1)) * supdiag(j-1));
            tilde_gvec(j) = gvec(j) - ( (subdiag(j) / tilde_diag(j-1)) * tilde_gvec(j-1));
        } 
    }
    
    // next we performe the backwards substitution
    // for j = dim(A)-1 we set v_j = tilde(g_j) / tilde(b_j)
    // for the remaining j's we subtract the factor c_j * v_j+1 / tilde(b_j)
    for (int j = dim_A-1; j > -1; j--){
		if (j == dim_A-1){
        	vvec(j) = tilde_gvec(j) / tilde_diag(j);
            tilde_diag(j) = tilde_diag(j) / tilde_diag(j);
        } else {
        	vvec(j) = ( tilde_gvec(j) - ( supdiag(j) * vvec(j+1) ) ) / tilde_diag(j);
        }
    }
    
    // lastly we set the ends to 0 for the approximation
    vvec = join_cols(zeros(1), vvec, zeros(1));
    
    return vvec;
}

// to evaluate the approximation we also define functions to calculat the error
vec absolut_error(vec v1, vec v2) {
    return abs(v1 - v2);
}
vec relative_error(vec v1, vec v2) {
    // removes the endpoint before calculation
    vec rel_error = abs(v1.subvec(1, v1.n_elem-2) - v2.subvec(1, v2.n_elem-2)) / abs(v1.subvec(1, v1.n_elem-2));
    // add NaN to the ends
    rel_error = join_cols(zeros(1), rel_error, zeros(1));
    return rel_error;
}

// and a function that writes to an oss
string generateDataString(vec& xvals, vec& uvals, vec& vvals, vec& abs_error, vec& rel_error, int width, int prec) {
    ostringstream oss; // Create an output string stream (oss)

    // Write the header
    oss << "x u v abs_error rel_error" << std::endl;

    // Write the data
    for (size_t i = 0; i < xvals.n_elem; ++i) {
        oss << std::setw(width) << std::setprecision(prec) << std::scientific << xvals(i)
            << std::setw(width) << std::setprecision(prec) << std::scientific << uvals(i) 
            << std::setw(width) << std::setprecision(prec) << std::scientific << vvals(i)
            << std::setw(width) << std::setprecision(prec) << std::scientific << abs_error(i)
            << std::setw(width) << std::setprecision(prec) << std::scientific << rel_error(i)
            << std::endl;
    }

    // Return the string with the data
    return oss.str();
}

// now can write the main function 
int main() {

    double x_min = 0.;
    double x_max = 1.;

    // in the main we need to loop over the n_steps configurations we want
    for (double n_steps : {10., 100., 1000., 10000., 100000., 1000000., 10000000.}) {   


        int dim_A = n_steps-1; // dimension of the matrix is n_steps - 1 as shown in problem 4
        double delta_x = (x_max - x_min) / n_steps; // delta_x is (x_max - x_min) / n_steps as shown in problem 3
        
        // create discretized x values
        vec xvec(n_steps+1);
        for (int j = 0; j < n_steps+1; j++) {
        	xvec[j] = x_i(j, x_min, delta_x);
        }
        
		// create the diagonals
        vec subdiag = zeros(dim_A) - 1.;
        subdiag(0) = 0.;        
        vec diag = zeros(dim_A) + 2.;
        vec supdiag = zeros(dim_A) - 1.;
        supdiag(dim_A-1) = 0.;
        
        // then the vector of g_j's 
        vec gvec(dim_A);
        for (int j = 0; j < dim_A; j++) {
        	gvec[j] = g_i(j+1, n_steps, x_min, delta_x);
        }
        
        // for referencing of the approximation we us the analytical solution
        vec uvec(n_steps+1);
        for (int j = 0; j < n_steps+1; j++) {
        	uvec[j] = u_i(j, n_steps, x_min, delta_x);
        } 
        
        // now we solve the tridiagonal matrix using the thomas algorithm
        vec vvec = thomas_alg(subdiag, diag, supdiag, gvec);
        
        //cout << "length:" << vvec.n_elem << endl << vvec << endl;
        
        // next we evaluate the approximation
     	vec abs_error = absolut_error(uvec, vvec);
        vec rel_error = relative_error(uvec, vvec);  
        
        // now we can write the data to file
        int width = 15;
        int prec = 8;
        string dataString = generateDataString(xvec, uvec, vvec, abs_error, rel_error, width, prec);
        cout << dataString << endl;
    }
    return 0;

}
