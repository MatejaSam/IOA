import scipy.special as sp
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import minimize
import math


def o(x, w_array):
    yout = 0
    for i in range(5):
        wk = w_array[i] * x
        mk = math.tanh(wk)
        yout += (w_array[i + 5] * mk)
    yout = math.tanh(yout)
    return yout


def optimizacija(w_array):
    f = 0
    x_array = np.arange(-1.0, 1.1, 0.1)
    for i in x_array:
        ytraining = 0.5 * (math.sin(math.pi * i))
        yout = o(i, w_array)
        pom = yout - ytraining
        k = pom ** 2
        f += k
    r = math.sqrt(f)
    return r


w_array = np.array([2.50734576, -1.9556475, -2.60164801, -2.52456033, -9.02998646, -0.49999466, 8.25776386, -8.85854527, -5.4591513, 6.12881616])
rez = minimize(optimizacija, w_array, method='Nelder-Mead', options={'ftol': 10e14})

while rez.fun >= 1e-2:
    rez = minimize(optimizacija, w_array, method='Nelder-Mead', options={'ftol': 10e14})

print(rez.nit)
rezultat = np.array(rez.x)
for i in rezultat:
    print("% .15f" % i)
print(rez.fun)

x_arr = np.linspace(-1, 1, 10000)
nizout = []
niztrening = []

for i in x_arr:
    nizout.append(o(i, rezultat))
    niztrening.append(0.5 * (math.sin(math.pi * i)))

plt.figure()
plt.plot(x_arr, nizout, label='Y out(x)')
plt.plot(x_arr, niztrening, label='Y trening(x)')
plt.legend()
plt.grid()
plt.show()
