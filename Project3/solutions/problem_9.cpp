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
// define constants
// -------------------
// seed
//int seed = 1;
//::set_seed(seed);
// particle parameters
double q = 1.;                  // Ca+ charge in elementary charge
double m_Ca = 40.078;           // Ca+ mass in u
// trap parameters
double B0 = 9.65*1e1;           // magnetic field strength in Tesla
double V0 = 2.41*1e6;            // applied potential
double d = 500.;                  // characteristic length of the trap
bool time_dependent_applied_potential = true;
// simulation parameters
double t_start = 0.;             // start time in microseconds
double simulation_time = 500.;    // simulation time in microseconds


vector<Particle> create_particles(int n_particles) {

    vector<Particle> particles;
    for (int i = 0; i < n_particles; ++i) {
        vec r = vec(3).randn() * .1 * d;
        vec v = vec(3).randn() * .1 * d;
        Particle p = Particle(q, m_Ca, r, v, true);
        particles.push_back(p);
    }
    return particles;
}
void fill_penningtrap(PenningTrap& trap, int n_particles) {

    vector<Particle> particles = create_particles(n_particles);
    for (int i = 0; i < particles.size(); ++i) {
        trap.add_particle(particles[i]);
    }
}


int main () {

    // variables
    double f;
    //vec f_vec = {.1, .4, .7};
    vec f_vec = {.4};
    double omega_v;
	//vec omega_v_vec = regspace<vec>(0.2, 0.02, 2.5); // for full range scan
    vec omega_v_vec = regspace<vec>(0.64, 0.01, .74); // for finer range
    vector<Particle> particles;
    bool interacting_particles = true;
    int num_in_trap;
    double frac_in_trap;


    ostringstream oss;
    int width = 15;
    int prec = 8;
    cout << "interactions,f,omega_v,frac_in_trap" << endl;
    for (int i = 0; i < f_vec.size(); i++) {
        f = f_vec(i);

        for (int j = 0; j < omega_v_vec.size(); j++) {
            omega_v = omega_v_vec(j);
            particles = create_particles(100);
            PenningTrap trap = PenningTrap(B0, V0, d, particles, interacting_particles, time_dependent_applied_potential, f, omega_v, t_start);
            Solver solver = Solver("rk4", t_start, simulation_time, 16000);

            solver.simulate(trap);
            num_in_trap = trap.num_particles();
            frac_in_trap = (double)num_in_trap / 100.;

            cout << interacting_particles <<"," << f << "," << omega_v << "," << frac_in_trap << endl;
        }
    }

    return 0;
}