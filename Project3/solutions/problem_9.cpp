//
// script for solving problem 8 in project 3
//

// ------------------
// import packages
// ------------------
#include "../include/Particle.hpp"
#include "../include/PenningTrap.hpp"
#include "../include/Solver.hpp"
#include "../build/armadillo_build/tmp/include/armadillo"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <complex>


// --------------------
// define namespaces
// --------------------
using namespace std;
using namespace arma;
using namespace std::complex_literals;


// -------------------
// define variables
// -------------------
// initial conditions particle 1
double x_0 = 20.;                // initial position in x direction in microns
double z_0 = 20.;                // initial position in z direction in microns
vec r_0 = {x_0, 0., z_0};
double yspeed_0 = 25.;           // initial velocity in y direction in microns/microseconds
vec v_0 = {0., yspeed_0, 0.};
// particle parameters
double q = 1.;                  // Ca+ charge in elementary charge
double m_Ca = 40.078;           // Ca+ mass in u
// trap parameters
double B0 = 9.65*1e1;           // magnetic field strength in Tesla
double V0_d2 = 9.65;            // potential/d² in u / microsecond² e
// simulation parameters
double t_start = 0.;             // start time in microseconds
double simulation_time = 50.;    // simulation time in microseconds

int main () {

    
    return 0;
}