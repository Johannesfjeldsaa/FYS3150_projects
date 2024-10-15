//
// script for testing src code functionality for code used in project 3
//

// import packages
#include "../include/Particle.hpp"
#include "../include/PenningTrap.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../build/armadillo_build/tmp/include/armadillo"
#include <cmath>

// define namespaces
using namespace std;
using namespace arma;


int main () {

   cout << "Problem 5" << endl;
   // create two particles
   double q = 1.6e-19;
   double m = 9.1e-31;
   vec position = {0., 0., 0.};
   vec velocity1 = {0., 0., 0.};
   vec velocity2 = {0., 0., 3.};

   Particle p1 = Particle(q, m, position, velocity1);
   p1.print_particle();

   Particle p2 = Particle(2*q, m, position, velocity2);

   cout << "Problem 6" << endl;
   // create a penning trap
   double B0 = 1.;
   double V0 = 25.;
   double d = 500.;

   vector<Particle> particles = {p1};

   PenningTrap trap = PenningTrap(B0, V0, d, particles);
   
   cout << "Penning trap configuration with p1:" << endl;
   trap.print_penningtrap();

   // add a particle
   cout << "Penning trap configuration with p1 and p2:" << endl;
   trap.add_particle(p2);
   trap.print_penningtrap();

   return 0;

}


