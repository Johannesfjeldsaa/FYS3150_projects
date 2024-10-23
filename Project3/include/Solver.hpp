// Solver class

#ifndef __Solver_hpp__
#define __Solver_hpp__

// import packages
#include "PenningTrap.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../build/armadillo_build/tmp/include/armadillo"
#include <cmath>

// define namespaces
using namespace std;
using namespace arma;

class Solver {
public:
    // Constructor
    Solver(
        string method,
        double t_0,
        double t_sim,
        int n_steps
    );

    // Methods
    void print_solver() const;
    void set_parameters(double t_0, double t_sim, int n_steps);
    void simulate(PenningTrap& trap);
    void forward_euler_step(PenningTrap& trap);
    void rk4_step(PenningTrap& trap);
    // Access functions
    double get_t();

private:
    // Member variables
    string method;
    double t_0;
    double t_sim;
    int n_steps;
    double h;
    double t_end;
    double t;

    // Member functions
    function<void(PenningTrap&)> step_function;

    // Private methods    
    void set_step_function(string method);

};

#endif // __Solver_hpp__