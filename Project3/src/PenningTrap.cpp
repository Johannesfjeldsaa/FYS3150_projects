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

// -----------------------
// Define the constants
// -----------------------
double k_e = 1.38935333e+5;         // Boltzmann constant in (u * micron³) / (microsecond² * e)

// --------------
// Constructor
// --------------
PenningTrap::PenningTrap(
   // public
   double B0,                      // magnetic field strength, unit: Tesla      
   double V0_d2,                   // applied potential over d squared 
   vector<Particle> particles,     // list of particles
   bool interacting_particles       // interaction between particles on or of
   ) :
      B0(B0), 
      V0_d2(V0_d2),
      interacting_particles(interacting_particles)
   {
      if (!particles.empty()) {
         for (auto& particle : particles) {
            particle.in_trap = true;
         }
         this->particles = particles;
      } 
   }

// ----------
// Methods
// ----------
// Print the particle
void PenningTrap::print_penningtrap() const {
   cout << "Magnetic field strength, B0: " << B0 << endl;
   cout << "List of particles,: " << endl;
   for (const auto& particle : particles) {
      particle.print_particle();
   }
}

/**
 * Add a particle to the penning trap
 * 
 * Parameters:
 *  - p_in: particle to add
 * 
 * Returns:
 *  - void 
 */
void PenningTrap::add_particle(
   Particle p_in
) {
   p_in.in_trap = true;        // run trapped routine
   particles.push_back(p_in);             // add particle to Penning trap
}

/**
 * Get the external electric field at point r=(x,y,z)
 * 
 * Parameters:
 *   r: point (x,y,z) to calculate the external electric field at
 * 
 * Returns:
 *   vec: the external electric field at point r=(x,y,z)
 */
vec PenningTrap::external_E_field(
   vec r                          // point (x,y,z)
) {
   return V0_d2 * vec({r(0), r(1), -2*r(2)});
}

/**
 * Get the external magnetic field at point r=(x,y,z)
 * 
 * Parameters:
 *   r: point (x,y,z) to calculate the external magnetic field at
 * 
 * Returns:
 *   vec: the external magnetic field at point r=(x,y,z)
 */
vec PenningTrap::external_B_field(
   vec r                          // point (x,y,z)
) {
   return vec({0, 0, B0});
}

/**
 * Calculate the total force on particle_i from the external fields
 * 
 * Parameters:
 *  - i: index of the particle to calculate the force for
 * 
 * Returns:
 *  - vec: the total force on particle_i from the external electromagnetic fields
 * 
 * Notes:
 *  - The external fields are calculated using the position and velocity of particle_i
 */
vec PenningTrap::total_force_external(
   int i                           // force on particle_i 
) {
   // get particle properties
   vec postition = particles[i].position;
   vec velocity = particles[i].velocity;
   double charge = particles[i].q;
   double mass = particles[i].m;
   // calculate external electromagnetic field strength
   vec external_E = external_E_field(postition);
   vec external_B = external_B_field(postition);

   // calculate and return total force
   return charge  * (external_E + arma::cross(velocity, external_B));
}

/**
 * Calculate the electric force on particle_i from particle_j
 * 
 * Parameters:
 *  - i: index of the particle to calculate the force for
 *  - j: index of the particle from which the force originates
 * 
 * Returns:
 *  - vec: the electric field acting on particle_i from particle_j
 */
vec PenningTrap::force_particle(
   int i,                          // force on particle_i
   int j                           // from particle_j
) {
   vec pos_i = particles[i].position;
   vec pos_j = particles[j].position;

   vec electric_field;
   if ( all(pos_i == pos_j) ) {
      electric_field = zeros<vec>(3);
   } else {
      
      double charge_j = particles[j].q;
      vec r_ij = pos_i - pos_j;
      double r_ij3 = pow(norm(r_ij), 3);

      electric_field = ( k_e * charge_j ) * r_ij / r_ij3;    
   }

   return particles[i].q * electric_field;
}


// Calculate the total force on particle_i from all other particles in the Penning trap.
//
// Input:
//   i - index of particle to calculate force for
//
// Output:
//   vec - total force on particle_i from fields set up by all other particles in the penning trap
vec PenningTrap::total_force_particles(
   int i                           // force on particle_i 
) {
   vec total_force = zeros<vec>(3);

   for (int j = 0; j < particles.size(); j++) {
      if ( i != j ) {
         total_force += force_particle(i, j);   
      }
      
   }
   return total_force;
}

vec PenningTrap::total_force(
   int i                           // force on particle_i 
) {
   if ( interacting_particles) {
      return total_force_particles(i) + total_force_external(i);
   } else {
      return total_force_external(i);
   }
} 