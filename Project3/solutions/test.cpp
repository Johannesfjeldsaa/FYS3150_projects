//
// script for testing src code functionality for code used in project 3
//

// ------------------
// import packages
// ------------------
#include "../include/Particle.hpp"
#include "../include/PenningTrap.hpp"
#include "../include/Solver.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../build/armadillo_build/tmp/include/armadillo"
#include <cmath>
#include <complex>


// --------------------
// define namespaces
// --------------------
using namespace std;
using namespace arma;
using namespace std::complex_literals;


// -------------------
// define constants
// -------------------
// physical constants
//double k_e = 1.38935333e+5;         // Boltzmann constant in (u * micron³) / (microsecond² * e)
double tesla = 9.64852558e+1;       // tesla in (u) / (microsecond * e)
double volt = 9.64852558e+7;        // volt in (u * micron²) / (microsecond² * e)
double elementary_charge = 1.;      // elementary charge in e 
// defult Penning trap
double B0 = 1. * tesla;
double V0_d2 = 9.65;                // potential/d² in  u / microsecond² e
// defult particle: singly-charged Calcium ion Ca+
double q = elementary_charge;       // Ca+ means 
double m = 40.078;                  // Ca mass in u. Ca⁺~Ca 
// initial position
double x_0;
double y_0 = 0.;
double z_0;
vec pos_vec_0 = {x_0, y_0, z_0};
// initial velocity
double v_0;
double vx_0 = 0.;
double vy_0 = v_0;
double vz_0 = 0.;
vec vel_vec_0 = {vx_0, vy_0, vz_0};


// -------------------
// define functions
// -------------------
// specific solutions
double z(Particle particle, double t) {
   
   double omega_z = particle.omega_z;
   double z_0 = particle.initial_position(2);

   return z_0 * cos(omega_z * t);
};

complex<double> f(Particle particle, double t) {
   double omega_0 = particle.omega_0;
   double omega_z = particle.omega_z;
   double omega_p = particle.omega_p;
   double omega_n = particle.omega_n;

   double phi_p = 0.;
   complex<double> exp_p = std::exp(-1.0i * (omega_p * t + phi_p));

   double phi_n = 0.;
   complex<double> exp_n = exp( -1.i * ( omega_n * t + phi_n ) );

   double A_p = ( v_0 + ( omega_n * x_0 )) / ( omega_n - omega_p );
   double A_n = - ( v_0 + ( omega_p * x_0 )) / ( omega_n - omega_p );

   return A_p * exp_p + A_n * exp_n;
}


int main () {

   cout << "Problem 5" << endl;
   // create two particles
   vec position1 = {2., 0., 3.};
   vec position2 = {0., 0., 0.};
   vec velocity1 = {0., 0., 0.};
   vec velocity2 = {0., 0., 3.};

   Particle p1 = Particle(q, m, position1, velocity1, false);
   p1.print_particle();

   Particle p2 = Particle(2*q, m, position2, velocity2, false);

   cout << "Problem 6" << endl;
   // create a penning trap
   double B0 = 1.;
   double V0 = 25.;
   double d = 500.;

   vector<Particle> particles = {p1};

   PenningTrap trap = PenningTrap(B0, V0_d2, particles, false);
   
   cout << "Penning trap configuration with p1:" << endl;
   trap.print_penningtrap();

   // add a particle
   cout << "Penning trap configuration with p1 and p2:" << endl;
   trap.add_particle(p2);
   trap.print_penningtrap();

   // check that the frequencies are calculated and are dependent on the particle
   cout << "The omega_0 is " << trap.particles.at(0).omega_0 << " for p1" << 
           " and omaga_z is " << trap.particles.at(1).omega_z << " for p2." << endl;

   // calculate the total force on particle_0
   vec pos_vec_0 = trap.particles.at(0).position;
   vec external_E = trap.external_E_field(pos_vec_0);
   vec external_B = trap.external_B_field(pos_vec_0);

   cout << "The external E field is " << external_E << endl;
   cout << "The external B field is " << external_B << endl;

   // calculate the between particle forces
   vec force_particle_0 = trap.force_particle(0, 1);
   cout << "The force between particle_0 and particle_1 is " << force_particle_0 << endl;

   vec total_between_particles = trap.total_force_particles(0);

   cout << "The total force between particle_0 and all other particles is " << total_between_particles << endl;

   vec total_force_particle_0 = trap.total_force(0);

   cout << "The total force on particle_0 is " << total_force_particle_0 << endl;

   // ----------------------------
   // test for the solver class
   // ----------------------------
   
   cout << endl << "Problem 8" << endl;

   // create a euler integrator 
   string method = "FE";
   double t_0 = 0.;
   double t_sim = 50.;
   int n_steps = 100;
   Solver FE_solver = Solver(method, t_0, t_sim, n_steps);
   FE_solver.print_solver();
   FE_solver.simulate(trap);

   return 0;
}


