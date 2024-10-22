// Penning trap class 

#ifndef __PenningTrap_hpp__
#define __PenningTrap_hpp__


// import packages
#include <Particle.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../build/armadillo_build/tmp/include/armadillo"
#include <cmath>

// define namespaces
using namespace std;
using namespace arma;

// Declare the function prototype

class PenningTrap {

    public:

        // ------------
        // variables
        // ------------
        double B0;                      // magnetic field strength, unit: Tesla
        double V0_d2;                      // applied potential over d squared
        vector<Particle> particles;     // list of particles
        bool interacting_particles;      // flag if interacting particles

        // --------------
        // Constructor
        // --------------
        PenningTrap(
            double B0,                      // magnetic field strength, unit: Tesla      
            double V0_d2,                   // applied potential over d squared
            vector<Particle> particles,     // list of particles in the trap
            bool interacting_particles      // flag if interacting particles
        );

        // ----------
        // Methods
        // ----------
        // Print the Penning trap configuration
        void print_penningtrap() const;

        // add particle
        void add_particle(
            Particle p_in
        );

        // Get the external electric field at point r=(x,y,z)
        vec external_E_field(
            vec r                          // point (x,y,z)
        );
        
        // Get the external magnetic field at point r=(x,y,z)
        vec external_B_field(
            vec r                          // point (x,y,z)
        );

        // Calculate the force on particle_i from particle_j
        vec force_particle(
            int i,                          // force on particle_i
            int j                           // force from particle_j
        );
        
        // Calculate the total force on particle_i from the external fields
        vec total_force_external(
            int i                           // force on particle_i 
        );
        
        // Calculate the total force on particle_i from the other particles
        vec total_force_particles(
            int i                           // force on particle_i
        );
        
        // Calculate the total force on particle_i from both external fields and other particles
        vec total_force(
            int i                           // force on particle_i
        );
};


#endif // __PenningTrap_hpp__