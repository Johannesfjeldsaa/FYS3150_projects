//
// solver class
//

// ------------------
// import packages
// ------------------
#include "Solver.hpp"
#include <Particle.hpp>
#include <PenningTrap.hpp>
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
Solver::Solver(
    string method,
    double t_0,
    double t_sim,
    int n_steps
) : method(method),
    t_0(t_0),
    t_sim(t_sim),
    n_steps(n_steps)
{
    set_parameters(t_0, t_sim, n_steps);
    set_step_function(method);
}

// ----------
// Methods
// ----------
void Solver::print_solver() const {
    cout << "Method: " << method << endl;
    cout << "t_0, t_end, n_steps: " << t_0 << ", " << t_end << ", " << n_steps << endl; 
}

void Solver::set_parameters(double t_0, double t_sim, int n_steps) {
    this->t_0 = t_0;
    this->t_sim = t_sim;
    this->n_steps = n_steps;
    this->t = t_0;
    h = (t_sim - t_0) / n_steps;
    t_end = t_0 + t_sim;
}

void Solver::forward_euler_step(PenningTrap& trap) {
    for (int i = 0; i < trap.particles.size(); i++) {
        // calculate the force in the particle position
        vec force = trap.total_force(i);
        // calculate the acceleration of the particle F/m
        vec acceleration = force / trap.particles[i].m;
        
        // update the particle velocity then position (Euler chromer method)
        trap.particles[i].velocity += acceleration * h;
        trap.particles[i].position += trap.particles[i].velocity * h;
    }

    t += h;
}


void Solver::rk4_step(PenningTrap& trap) {

    // initiate the vectors for the k's by making a vector of vectors
    vector<vec> k_r1, k_r2, k_r3, k_r4, k_v1, k_v2, k_v3, k_v4;

    int num_particles = trap.particles.size();

    // calculate k_r1 and k_v1
    for (int i = 0; i < num_particles; i++) {
        vec force = trap.total_force(i);
        vec acceleration = force / trap.particles[i].m;

        k_r1.push_back(trap.particles[i].velocity * h);
        k_v1.push_back(acceleration * h);
    }
    
    // to calculate k_r2/k_v2 we need to step the system temporarily half a step forward
    // and estimate the position/velocity using k_r1/k_v1
    PenningTrap temporary_trap = trap;
    for (int i = 0; i < num_particles; i++) {
        temporary_trap.particles[i].position += k_r1[i] * 0.5;
        temporary_trap.particles[i].velocity += k_v1[i] * 0.5;
    }
    // calculate k_r2 and k_v2
    for (int i = 0; i < num_particles; i++) {
        vec force = temporary_trap.total_force(i);
        vec acceleration = force / temporary_trap.particles[i].m;

        k_r2.push_back(h * temporary_trap.particles[i].velocity);
        k_v2.push_back(h * acceleration);
    }

    // to calculate k_r3/k_v3 we need to step the system temporarily half a step forward
    // and estimate the position/velocity using k_r2/k_v2
    temporary_trap = trap;
    for (int i = 0; i < num_particles; i++) {
        temporary_trap.particles[i].position += k_r2[i] * 0.5;
        temporary_trap.particles[i].velocity += k_v2[i] * 0.5;
    }
    // calculate k_r3 and k_v3
    for (int i = 0; i < num_particles; i++) {
        vec force = temporary_trap.total_force(i);
        vec acceleration = force / temporary_trap.particles[i].m;  

        k_r3.push_back(h * temporary_trap.particles[i].velocity);
        k_v3.push_back(h * acceleration);
    }

    // to calculate k_r4/k_v4 we need to step the system temporarily a whole step forward
    // and estimate the position/velocity using k_r3/k_v3
    temporary_trap = trap;
    for (int i = 0; i < num_particles; i++) {
        temporary_trap.particles[i].position += k_r3[i];
        temporary_trap.particles[i].velocity += k_v3[i];
    }
    // calculate k_r4 and k_v4
    for (int i = 0; i < num_particles; i++) {
        vec force = temporary_trap.total_force(i);
        vec acceleration = force / temporary_trap.particles[i].m;

        k_r4.push_back(h * temporary_trap.particles[i].velocity);
        k_v4.push_back(h * acceleration);
    }

    // now we can update the positions and velocities from the k's using the rk4 formula
    for (int i = 0; i < num_particles; i++) {
        trap.particles[i].position += (k_r1[i] + 2 * k_r2[i] + 2 * k_r3[i] + k_r4[i]) / 6;
        trap.particles[i].velocity += (k_v1[i] + 2 * k_v2[i] + 2 * k_v3[i] + k_v4[i]) / 6;
    }

    t += h;

}

void Solver::set_step_function(string method) {
    if (method == "FE") {
        step_function = [this](PenningTrap& trap) { this->forward_euler_step(trap); };
    } else if (method == "rk4") {
        step_function = [this](PenningTrap& trap) { this->rk4_step(trap); };
    } else {
        throw invalid_argument("Invalid method specified. Use 'FE' or 'rk4'.");
    }
}

void Solver::simulate(PenningTrap& trap) {
    for (int i = 0; i < n_steps; ++i) {
        step_function(trap);

        cout << trap.particles[0].position << endl;
        // Here you can add code to save the state of the system,
        // e.g., particle positions and velocities
    }
}

double Solver::get_t() {
    return t;
}