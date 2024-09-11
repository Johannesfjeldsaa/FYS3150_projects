# just a scetch used to test dimensions etc for the thomas algorithm. Not runnable per now.

# $n\_steps = 10$ gives 11 points $i = 0, 1, ..., 10$ with unknowns at $i = 1, 2, ..., 9$ that is, we have 9 unknown $v_i$s. This yields us that dim(A) is $9\times 9$ or $n\_steps-1$.
#accordingly we get that:
#- subdiagonal vector: 
#    - uses indexes $i = 2, 3, ..., 9$ and
#    - and is size 8
#- diagonal vector $b$:
#    - uses indexes $i = 1, 2, ..., 9$
#    - and is size 9
#- superdiagonal vector $c$:
#    - uses indexes $i = 1, 2, ..., 8$
#    - and is size 8
#- the vector for the solution $g$:
#    - uses indexes $i = 1, 2, ..., 9$
#    - and is size 9

def thomas_algorithm(subdiag, diag, superdiag, gvec, verbose=False):
    
    dim_A = len(gvec)
    # check if the diagonals are of the correct size
    for vec in [subdiag, diag, superdiag, gvec]:
        if len(vec) != dim_A:
            raise ValueError("All vectors must be of the same length")
        
    # initialize
    tilde_diag = np.zeros(dim_A, dtype=np.float64)
    tilde_gvec = np.zeros(dim_A, dtype=np.float64)
    vvec = np.zeros(dim_A, dtype=np.float64)


    # forward substitution
    for i in np.arange(dim_A):
        if i == 0:
            tilde_diag[i] = diag[i]
            tilde_gvec[i] = gvec[i]
        else:
            tilde_diag[i] = diag[i] - ( (subdiag[i] / tilde_diag[i - 1]) * superdiag[i - 1] ) 
            tilde_gvec[i] = gvec[i] - ( (subdiag[i] / tilde_diag[i - 1]) * tilde_gvec[i - 1] )

    #print(np.diag(subdiag[1:], -1) + np.diag(tilde_diag, 0) + np.diag(superdiag[:-1], 1))
    
    # backward substitution
    for i in np.arange(dim_A-1, -1, -1):
        print(i)
        if i == dim_A-1:
            vvec[i] = tilde_gvec[i] / tilde_diag[i]
            tilde_diag[i] = tilde_diag[i] / tilde_diag[i]
        else:
            vvec[i] = (tilde_gvec[i] - ( superdiag[i] * vvec[i + 1] ) ) / tilde_diag[i]
            
    
    vvec = np.insert(vvec, 0, 0)
    vvec = np.append(vvec, 0)


    return vvec

def x_i(i, x_min, delta_x):
    return x_min + i * delta_x
    
def f_i(i, x_min, delta_x):
    return 100 * np.exp(-10 * x_i(i, x_min, delta_x))

def g_i(i, n_steps, delta_x):
    if i == 0 or i == n_steps:
        pass
    else:
        return  delta_x ** 2 * f_i(i, x_min, delta_x)
    
def u_i(i, n_steps, delta_x, x_min):
    if i == 0 or i == n_steps:
        return 0
    else:
        return 1 - (1 - np.exp(-10)) * x_i(i, x_min, delta_x) - np.exp(-10 * x_i(i, x_min, delta_x))
    
x_min = 0
x_max = 1
n_steps_configs = [10]

vvec_xvec_pairs = {}
for n_steps in n_steps_configs:

    delta_x = (x_max - x_min) / n_steps

    dim_A = n_steps - 1
    subdiag = np.insert(
        np.array([-1 for _ in np.arange(2, dim_A+1)]), 0, 0
    )
    diag = np.array([2 for _ in np.arange(1, dim_A+1)])
    superdiag = np.append(
        np.array([-1 for _ in np.arange(1, dim_A)]), 0
    )
    gvec = np.array([g_i(i, n_steps, delta_x) for i in np.arange(1, dim_A+1)])
    #gvec = np.array([0,0,1,0])

    uvec = np.array([u_i(i, n_steps, delta_x, x_min) for i in np.arange(1, dim_A+1)])

    print(
        f'dim(a) = {np.shape(subdiag)}, a = {subdiag}\n'
        f'dim(b) = {np.shape(diag)}, b = {diag}\n'
        f'dim(c) = {np.shape(superdiag)}, c = {superdiag}\n'
        f'dim(g) = {np.shape(gvec)}, g = {gvec}\n'
        f'dim(u) = {np.shape(uvec)}, u = {uvec}\n'
    )

    vvec_xvec_pairs[n_steps] = {
        'vvec': thomas_algorithm(subdiag, diag, superdiag, gvec, dim_A), 
        'xvec': np.array([x_i(i, x_min, (x_max - x_min) / n_steps) for i in np.arange(0, n_steps+1)])
        }



for n_steps in n_steps_configs:
    
    xvec = vvec_xvec_pairs[n_steps]['xvec']
    vvec = vvec_xvec_pairs[n_steps]['vvec']
    
    plt.plot(xvec, vvec, label=rf'$v(x)$, n_steps = {n_steps}', linewidth=0.5)

plt.legend(loc='upper right')

plt.savefig(os.path.join('Illustrations', 'problem7fig.pdf'), bbox_inches='tight')

plt.show()
