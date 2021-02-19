import numpy as np
import random
import math


def optfunckija(x):
    global A
    global B
    global C
    global D

    S1 = [x[0], x[1], x[2]]
    S2 = [x[3], x[4], x[5]]

    rezultat = 0
    rezultat = rezultat + math.sqrt(math.pow(A[0]-S1[0], 2) + math.pow(A[1]-S1[1], 2) + math.pow(A[2]-S1[2], 2))
    rezultat = rezultat + math.sqrt(math.pow(B[0] - S1[0], 2) + math.pow(B[1] - S1[1], 2) + math.pow(B[2] - S1[2], 2))
    rezultat = rezultat + math.sqrt(math.pow(S1[0] - S2[0], 2) + math.pow(S1[1] - S2[1], 2) + math.pow(S1[2] - S2[2], 2))
    rezultat = rezultat + math.sqrt(math.pow(C[0] - S2[0], 2) + math.pow(C[1] - S2[1], 2) + math.pow(C[2] - S2[2], 2))
    rezultat = rezultat + math.sqrt(math.pow(D[0] - S2[0], 2) + math.pow(D[1] - S2[1], 2) + math.pow(D[2] - S2[2], 2))

    return rezultat


Dimenzija = 6
Npopulacije = 10 * Dimenzija

A = [1, 5, 1]
B = [3, 2, 0]
C = [5, 7, 1]
D = [6, 3, 3]

c1 = 1.494
c2 = 1.494
w = 0.729

gbest = -1
gbestector = np.zeros(Dimenzija, dtype=float)

pbest = np.zeros(Npopulacije, dtype=float)
pbestvector = np.zeros((Npopulacije, Dimenzija), dtype=float)

Xn = np.random.uniform(-7.0, 7.0, (Npopulacije, Dimenzija))
Vn = np.random.uniform(-1.5, 1.5, (Npopulacije, Dimenzija))

vmax = 1.5
vmin = -1.5


for i in range(Npopulacije):
    x = Xn[i]
    razdaljina = optfunckija(x)
    pbestvector[i] = x.copy()
    pbest[i] = razdaljina

    if razdaljina < gbest or gbest == -1:
        gbest = razdaljina
        gbestector = x.copy()


for i in range(5000):
    for j in range(Npopulacije):
        Vn[j] = w * Vn[j] + c1 * random.uniform(0, 1)*(pbestvector[j] - Xn[j]) + c2 * random.uniform(0, 1) * (gbestector - Xn[j])

        for k in range(Dimenzija):
            if Vn[j][k] > vmax:
                Vn[j][k] = vmax
            elif Vn[j][k] < vmin:
                Vn[j][k] = vmin

        Xn[j] = Xn[j] + Vn[j]
        razdaljina = optfunckija(Xn[j])

        if razdaljina < pbest[j]:
            pbest[j] = razdaljina
            pbestvector[j] = Xn[j].copy()
            if razdaljina < gbest:
                gbest = razdaljina
                gbestector = Xn[j].copy()

print("")
print("S1(" + str(gbestector[0]) + ", " + str(gbestector[1]) + ", " + str(gbestector[2]) + ")")
print("S2(" + str(gbestector[3]) + ", " + str(gbestector[4]) + ", " + str(gbestector[5]) + ")")
print(gbest)