import numpy as np
from scipy.optimize import linprog
import itertools

A = np.array([[1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1],
              [1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0], [0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0], [0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0], [0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1],
              [480, 650, 580, 390, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 480, 650, 580, 390, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0, 480, 650, 580, 390]])
b = np.array([10, 16, 8, 18, 15, 23, 12, 6800, 8700, 4300])
c = np.array([-310, -380, -350, -285, -310, -380, -350, -285, -310, -380, -350, -285])

x_bound = (0, None)

res = linprog(c, A_ub=A, b_ub=b, bounds=(x_bound, x_bound, x_bound, x_bound, x_bound, x_bound, x_bound, x_bound, x_bound, x_bound, x_bound, x_bound), method='simplex')

print('Total GFlops: ', -res.fun, '\nX:', res.x)


matrix = np.array([[3, 4, 5, 6, 7, 8, 9], [1, 2, 3, 4, 5, 6, 7], [3, 4, 5, 6, 7, 8, 9], [0, 0, 0, 1, 2, 3, 4]])


def maxvr(rex):
    por = 310 * (rex[0] + rex[4] + rex[8]) + 380 * (rex[1] + rex[5] + rex[9]) + 350 * (rex[2] + rex[6] + rex[10]) + 285 * (rex[3] + rex[7] + rex[11])
    return por

def provjera(rex2):
    if (rex2[0] + rex2[1] + rex2[3] + rex2[3]) > 10 or (rex2[4] + rex2[5] + rex2[6] + rex2[7]) > 16 or (rex2[8] + rex2[9] + rex2[10] + rex2[11]) > 8:
        return 0
    elif (480*rex2[0] + 650*rex2[1] + 580*rex2[3] + 390*rex2[3]) > 6800 or (480*rex2[4] + 650*rex2[5] + 580*rex2[6] + 390*rex2[7]) > 8700 or (480*rex2[8] + 650*rex2[9] + 580*rex2[10] + 390*rex2[11]) > 4300:
        return 0
    elif (rex2[0] + rex2[4] + rex2[8]) > 18 or (rex2[1] + rex2[5] + rex2[9]) > 15 or (rex2[2] + rex2[6] + rex2[10]) > 23 or (rex2[3] + rex2[7] + rex2[11]) > 12:
        return 0
    else:
        return 1


n = 7
k = 4
P = np.array([0, 0, 0, 0])
rez = np.array([0, 10, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0])
index = np.array([6, 7, 10, 11])
max = 0
q = 1

while q >= 0:
    pomniz = np.array([0, 10, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0])
    iter = 0
    for i in P:
        pomniz[index[iter]] = matrix[iter][P[iter]]
        iter = (iter+1)
    cur = maxvr(pomniz)
    if cur > max:
        if cur < 11915:
            if provjera(pomniz):
                rez = pomniz
                max = maxvr(pomniz)
    q = k - 1
    while q >= 0:
        P[q] = (P[q] + 1)
        if P[q] == n:
            P[q] = 0
            q = (q - 1)
        else:
            break

print("")
print('Total GFlops: ', max, '\nX:', rez)








