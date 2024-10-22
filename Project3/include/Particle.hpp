// Particle class 

#ifndef __Particle_hpp__
#define __Particle_hpp__


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

// Declare the function prototype

class Particle {

    public:

        // ------------
        // variables
        // ------------
        double q;                   // charge, unit: Coulomb
        double m;                   // mass, unit: atomic mass unit
        double omega_0;             // trap frequency
        double omega_z;             // trap frequency
        double omega_p;             // 
        double omega_n;             //
        vec position;               // position vector, unit: micrometer
        vec initial_position;       // copy of position at initialization
        vec velocity;               // velocity vector, unit: micrometer/microsecond
        bool in_trap;               // flag if particle is in the trap defoult: false


        // --------------
        // Constructor
        // --------------
        Particle(
            double q,                   // charge, unit: Coulomb
            double m,                   // mass, unit: atomic mass unit
            vec position,               // position vector, unit: micrometer
            vec velocity,               // velocity vector, unit: micrometer/microsecond
            bool in_trap                // flag if particle is in the trap
        );
        
        // ----------
        // Methods
        // ----------    
        // Print the particle
        void print_particle() const;
};


#endif // __Particle_hpp__
