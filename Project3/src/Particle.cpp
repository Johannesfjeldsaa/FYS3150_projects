//
// The particle object
//

// ------------------
// import packages
// ------------------
#include "Particle.hpp"
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
Particle::Particle(
      // public
      double q,                   // charge, unit: Coulomb
      double m,                   // mass, unit: atomic mass unit
      vec position,               // position vector, unit: micrometer
      vec velocity,               // velocity vector, unit: micrometer/microsecond
      bool in_trap                // flag if particle is in the trap
   ) : 
      q(q), 
      m(m), 
      position(position), 
      velocity(velocity),
      in_trap(false)
   {
      initial_position = position;
   }

// ----------
// Methods
// ----------
// Print the particle
void Particle::print_particle() const {
   cout << "charge, q: " << q << endl;
   cout << "mass, m: " << m << endl;
   cout << "position: " << endl << position << endl;
   cout << "velocity: " << endl << velocity << endl;
   cout << "in_trap: " << in_trap << endl;
}

