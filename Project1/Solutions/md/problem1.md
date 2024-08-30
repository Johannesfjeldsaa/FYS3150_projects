# Problem description
Check analytically that an exact solution to the poisson_eq is given by
$$
u(x) = 1 - (1 - e^{-10}) x - e^{-10 x}.
$$
# Solution
Given the boundary value problem 
$$
- \frac{d²{u}}{d{x²}} = f(x)
$$
where 
- $f(x) = 100e^{-10x}$
- $x\in[0, 1]$
- $u(x=0)=u(x=1)= 0$
we check if $u(x)$ is a solution by confirming that the left hand side equals the right hand side after the derivatives are taken. 

Only assessing the LHS we get 
$$
\begin{align*}
- \frac{d²{u(x)}}{d{x²}}  & =  
- \frac{d²}{d{x²}} \left[
1 - (1- e^{-10})x - e^{-10x}  
\right]  \\ 
& =  
- \frac{d{}}{d{x}}\left[
\frac{d{}}{d{x}} 1 -  (1-e^{-10})\frac{d{x}}{d{x}} - \frac{d{}}{d{x}}e^{-10x}
\right] \\
& = 
- \frac{d{}}{d{x}}\left[
-1 + e^{10} + 10e^{-10x}
\right] \\
&= 100 e^{-10x} &(= RHS) \quad .
\end{align*} 
$$

