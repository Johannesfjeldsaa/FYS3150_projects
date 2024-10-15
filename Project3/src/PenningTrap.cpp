//
// The penning trap object
//

// ------------------
// import packages
// ------------------
#include "Particle.hpp"
#include "PenningTrap.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../build/armadillo_build/tmp/include/armadillo"
#include <cmath>

// --------------------
// define namespaces
// --------------------
using namespace std;
using namespace arma;


// --------------
// Constructor
// --------------
PenningTrap::PenningTrap(
   // public
   double B0,                      // magnetic field strength, unit: Tesla      
   double V0,                      // applied potential, unit: milliVolts
   double d,                       // characteristic dimension, unit: micrometers
   vector<Particle> particles      // list of particles
   ) :
      B0(B0), 
      V0(V0), 
      d(d), 
      particles(particles)
   {
   }

// ----------
// Methods
// ----------
// Print the particle
void PenningTrap::print_penningtrap() const {
   cout << "Magnetic field strength, B0: " << B0 << endl;
   cout << "Applied potential, V0: " << V0 << endl;
   cout << "characteristic dimension, d: " << d << endl;
   cout << "List of particles,: " << endl;
   for (const auto& particle : particles) {
      particle.print_particle();
   }
}

// add particle
void PenningTrap::add_particle(
   Particle p_in
) {
   particles.push_back(p_in);
}

// Get the external electric field at point r=(x,y,z)
vec external_E_field(
   vec r                          // point (x,y,z)
) {
   
}