import numpy as np 


def f_omega_0(q, m, B0):
    return (q * B0) / m

def f_omega_z(q, m, V0_d2):
    return np.sqrt(V0_d2 * (( 2 * q ) / m))

def f_omega_p(omega_0, omega_z):
    return (omega_0 + np.sqrt( (omega_0**2) - (2 * omega_z**2) )) / 2

def f_omega_n(omega_0, omega_z):
    return (omega_0 - np.sqrt( (omega_0**2) - (2 * omega_z**2) )) / 2

def f_A_p(yspeed_0, omega_p, omega_n, x_0):
    return (yspeed_0 + (omega_n * x_0)) / (omega_n - omega_p)

def f_A_n(yspeed_0, omega_p, omega_n, x_0):
    return - (yspeed_0 + (omega_p * x_0)) / (omega_n - omega_p)

def f_phi_p():
    return 0
def f_phi_n():
    return 0

def f(t, A_p, A_n, omega_p, omega_n, phi_p, phi_n):
    exp_p = np.exp(-1.0j * (omega_p * t + phi_p))
    exp_n = np.exp(-1.0j * (omega_n * t + phi_n))
    return A_p * exp_p + A_n * exp_n

def z(t, z_0, omega_z):
    return z_0 * np.cos(omega_z * t)

def simulate_specific_solution(n_steps):

    
    # Define initial conditions and other parameters
    x_0 = 20                # initial position in x direction in microns
    z_0 = 20                # initial position in z direction in microns
    r_0 = np.array([x_0, 0, z_0])
    yspeed_0 = 25                # initial velocity in y direction in microns/microseconds
    v_0 = np.array([0, yspeed_0, 0])

    # particle parameters
    q = 1                   # Ca+ charge in elementary charge
    m_Ca = 40.078           # Ca+ mass in u
    # trap parameters
    B0 = 9.65*10**1
    V0_d2 = 9.65
    # simulation parameters
    t_start = 0
    simulation_time = 50    # simulation time in microseconds

    # solve
    omega_0 = f_omega_0(q, m_Ca, B0)
    omega_z = f_omega_z(q, m_Ca, V0_d2)
    omega_p = f_omega_p(omega_0, omega_z)
    omega_n = f_omega_n(omega_0, omega_z)
    A_p = f_A_p(yspeed_0, omega_p, omega_n, x_0)
    A_n = f_A_n(yspeed_0, omega_p, omega_n, x_0)
    phi_p = f_phi_p()
    phi_n = f_phi_n()

    h = (simulation_time - t_start) / n_steps
    t_vec = [round(t_start + i * h, 8) for i in range(n_steps+1)]
    z_vec = [z(t, z_0, omega_z) for t in t_vec] 
    f_vec = [f(t, A_p, A_n, omega_p, omega_n, phi_p, phi_n) for t in t_vec]
    x_vec = [np.real(f_val) for f_val in f_vec]
    y_vec = [np.imag(f_val) for f_val in f_vec]

    return t_vec, x_vec, y_vec, z_vec