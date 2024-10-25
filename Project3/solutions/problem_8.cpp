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

    cout << "**** Initiate particle 1 ****" << endl;
    Particle p1 = Particle(q, m_Ca, r_0, v_0, false);
    p1.print_particle();

    cout << endl << "**** Initiate Penning trap ****" << endl;

    vector<Particle> particles = {p1};
    bool interacting_particles = false;
    PenningTrap trap = PenningTrap(B0, .0, 500., particles, interacting_particles, false);
    trap.print_penningtrap();

    // ----------------------------
    // test for the solver class
    // ----------------------------
    


    // create a forward Euler solver
    string method = "rk4";
    double t_0 = 0.;
    double t_sim = 50.;
    int n_steps = 1000;
    Solver rk4_solver = Solver(method, t_0, t_sim, n_steps);
    rk4_solver.print_solver();


    cout << endl <<"START **** 01 Simulate single particle for 50 miroseconds ****" << endl;
    cout << "t,z" << endl;
    cout << rk4_solver.get_t() << "," << trap.particles[0].position[2] << endl;
    for (int i = 0; i < n_steps; ++i) {
        rk4_solver.rk4_step(trap);

        cout << rk4_solver.get_t() << "," << trap.particles[0].position[2] << endl;
    }
    cout << "END **** 01 Simulate single particle for 50 miroseconds ****" << endl;

    cout << endl <<"START **** 02a Simulate two particles for 50 miroseconds with and without interacting ****" << endl;
    vec r_02 = {25., 25., 0.};
    vec v_02 = {0., 40., 5.};
    Particle p2 = Particle(q, m_Ca, r_02, v_02, false);

    particles = {p1, p2};
    PenningTrap trap_wo_inter = PenningTrap(B0, .0, 500., particles, false, false);
    Solver solver_wo_inter = Solver(method, t_0, t_sim, n_steps);
    PenningTrap trap_w_inter = PenningTrap(B0, .0, 500., particles, true, false);
    Solver solver_w_inter = Solver(method, t_0, t_sim, n_steps);

    
    // simulate using rk4 and return oss
    ostringstream oss;
    int width = 15;
    int prec = 8;
    oss << "t,x1_w,y1_w,z1_w,v_x1_w,v_y1_w,v_z1_w,x2_w,y2_w,z2_w,v_x2_w,v_y2_w,v_z2_w,x1_wo,y1_wo,z1_wo,v_x1_wo,v_y1_wo,v_z1_wo,x2_wo,y2_wo,z2_wo,v_x2_wo,v_y2_wo,v_z2_wo" << endl;
    

    oss << setw(width) << setprecision(prec) << scientific << solver_wo_inter.get_t() << ","
        << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[0].position[0] << ","
        << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[0].position[1] << ","
        << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[0].position[2] << ","
        << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[0].velocity[0] << ","
        << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[0].velocity[1] << ","
        << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[0].velocity[2] << ","
        << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[1].position[0] << ","
        << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[1].position[1] << ","
        << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[1].position[2] << ","
        << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[1].velocity[0] << ","
        << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[1].velocity[1] << ","
        << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[1].velocity[2] << ","
        << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[0].position[0] << ","
        << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[0].position[1] << ","
        << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[0].position[2] << ","
        << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[0].velocity[0] << ","
        << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[0].velocity[1] << ","
        << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[0].velocity[2] << ","
        << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[1].position[0] << ","
        << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[1].position[1] << ","
        << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[1].position[2] << ","
        << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[1].velocity[0] << ","
        << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[1].velocity[1] << ","
        << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[1].velocity[2] << endl;

    for (int i = 0; i < n_steps; ++i) {
        // evolve trap
        solver_w_inter.rk4_step(trap_w_inter);
        solver_wo_inter.rk4_step(trap_wo_inter);
        // wirte results
        oss << setw(width) << setprecision(prec) << scientific << solver_wo_inter.get_t() << ","
            << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[0].position[0] << ","
            << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[0].position[1] << ","
            << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[0].position[2] << ","
            << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[0].velocity[0] << ","
            << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[0].velocity[1] << ","
            << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[0].velocity[2] << ","
            << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[1].position[0] << ","
            << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[1].position[1] << ","
            << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[1].position[2] << ","
            << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[1].velocity[0] << ","
            << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[1].velocity[1] << ","
            << setw(width) << setprecision(prec) << scientific << trap_w_inter.particles[1].velocity[2] << ","
            << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[0].position[0] << ","
            << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[0].position[1] << ","
            << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[0].position[2] << ","
            << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[0].velocity[0] << ","
            << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[0].velocity[1] << ","
            << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[0].velocity[2] << ","
            << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[1].position[0] << ","
            << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[1].position[1] << ","
            << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[1].position[2] << ","
            << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[1].velocity[0] << ","
            << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[1].velocity[1] << ","
            << setw(width) << setprecision(prec) << scientific << trap_wo_inter.particles[1].velocity[2] << endl;

    }
    cout << oss.str();
    cout << "END **** 02a Simulate two particles for 50 miroseconds with and without interacting ****" << endl;


    cout << "START **** 03 Simulate for different number of steps ****" << endl;

    vec n_vals = {4000, 8000, 16000, 32000};
    
    for (int i = 0; i < n_vals.n_elem; ++i) {
        p1 = Particle(q, m_Ca, r_0, v_0, false);
        particles = {p1};
        PenningTrap rk4_trap = PenningTrap(B0, .0, 500., particles, interacting_particles, false);
        PenningTrap fe_trap = PenningTrap(B0, .0, 500., particles, interacting_particles, false);
        n_steps = n_vals(i);
        cout << "n_steps: " << n_steps << endl;
        oss.str("");
        oss.clear();
        oss << "t,x_rk4,y_rk4,z_rk4,x_fe,y_fe,z_fe" << endl;
        
        Solver rk4_solver = Solver("rk4", t_0, t_sim, n_steps);    
        Solver fe_solver = Solver("FE", t_0, t_sim, n_steps);
        oss << setw(width) << setprecision(prec) << scientific << rk4_solver.get_t() << ","
                << setw(width) << setprecision(prec) << scientific << rk4_trap.particles[0].position[0] << ","
                << setw(width) << setprecision(prec) << scientific << rk4_trap.particles[0].position[1] << ","
                << setw(width) << setprecision(prec) << scientific << rk4_trap.particles[0].position[2] << ","
                << setw(width) << setprecision(prec) << scientific << fe_trap.particles[0].position[0] << ","
                << setw(width) << setprecision(prec) << scientific << fe_trap.particles[0].position[1] << ","
                << setw(width) << setprecision(prec) << scientific << fe_trap.particles[0].position[2] << endl;

        for (int i = 0; i < n_steps; ++i) {
            rk4_solver.rk4_step(rk4_trap);
            fe_solver.forward_euler_step(fe_trap);
            
            oss << setw(width) << setprecision(prec) << scientific << rk4_solver.get_t() << ","
                << setw(width) << setprecision(prec) << scientific << rk4_trap.particles[0].position[0] << ","
                << setw(width) << setprecision(prec) << scientific << rk4_trap.particles[0].position[1] << ","
                << setw(width) << setprecision(prec) << scientific << rk4_trap.particles[0].position[2] << ","
                << setw(width) << setprecision(prec) << scientific << fe_trap.particles[0].position[0] << ","
                << setw(width) << setprecision(prec) << scientific << fe_trap.particles[0].position[1] << ","
                << setw(width) << setprecision(prec) << scientific << fe_trap.particles[0].position[2] << endl;
        }

        cout << oss.str();
    }
    
    cout << "END **** 03 Simulate for different number of steps ****" << endl;
    return 0;
}

