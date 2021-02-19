import numpy as np
import random
import math


def postavikordinate():
    global R0
    global xkord
    global ykord
    global N
    for i in range(N):
        xkord[i] = R0 * math.cos((2 * math.pi * i) / N)
        ykord[i] = R0 * math.sin((2 * math.pi * i) / N)


def opfunkcija(xglobal):
    global R0
    global s
    global xkord
    global ykord
    if math.sqrt(math.pow(xglobal[0], 2) + math.pow(xglobal[1], 2)) >= R0 or math.sqrt(
                math.pow(xglobal[2], 2) + math.pow(xglobal[3], 2)) >= R0:
        return 100.0
    else:
        rezultat = 0.0
        for i in range(20):
            midrez = (xglobal[4] / math.sqrt(
                math.pow(xkord[i] - xglobal[0], 2) + math.pow(ykord[i] - xglobal[1], 2))) + (xglobal[5] / math.sqrt(
                math.pow(xkord[i] - xglobal[2], 2) + math.pow(ykord[i] - xglobal[3], 2))) - s[i]
            midrez = math.pow(midrez, 2)
            rezultat = rezultat + midrez
        return rezultat


def diferencijalna_evolucija():
    global tekucapopulacija
    global Npopulacije
    global D
    global CR
    global fopt
    global xopt
    global D

    for i in range(Npopulacije):
        x = tekucapopulacija[i]
        y = np.zeros(D, dtype=float)

        n1 = random.randint(0, Npopulacije - 1)
        while n1 == i:
            n1 = random.randint(0, Npopulacije - 1)
        xa = tekucapopulacija[n1]

        n2 = random.randint(0, Npopulacije - 1)
        while n2 == i or n2 == n1:
            n2 = random.randint(0, Npopulacije - 1)
        xb = tekucapopulacija[n2]

        n3 = random.randint(0, Npopulacije - 1)
        while n3 == i or n3 == n1 or n3 == n2:
            n3 = random.randint(0, Npopulacije - 1)
        xc = tekucapopulacija[n3]

        z = np.zeros(D, dtype=float)
        z = xa + F * (xb - xc)

        R = random.randint(0, D - 1)
        r = np.random.uniform(0, 1, D)

        for m in range(D):
            if r[m] < CR or m == R:
                y[m] = z[m]
            else:
                y[m] = x[m]

        if opfunkcija(y) < opfunkcija(x):
            tekucapopulacija[i] = y

        if opfunkcija(tekucapopulacija[i]) < fopt:
            fopt = opfunkcija(tekucapopulacija[i])
            xopt = tekucapopulacija[i]


s = [2.424595205726587e-01, 1.737226395065819e-01, 1.315612759386036e-01,
     1.022985539042393e-01, 7.905975891960761e-02, 5.717509542148174e-02,
     3.155886625106896e-02, -6.242228581847679e-03, -6.565183775481365e-02,
     -8.482380513926287e-02, -1.828677714588237e-02, 3.632382803076845e-02,
     7.654845872485493e-02, 1.152250132891757e-01, 1.631742367154961e-01,
     2.358469152696193e-01, 3.650430801728451e-01, 5.816044173713664e-01,
     5.827732223753571e-01, 3.686942505423780e-01]

F = 0.8
CR = 0.9
N = 20
R0 = 15
D = 6
Npopulacije = 10 * D

fopt = 100.0
xopt = np.zeros(6, dtype=float)

xkord = np.zeros(20, dtype=float)
ykord = np.zeros(20, dtype=float)
postavikordinate()

tekucapopulacija = np.random.uniform(-15.0, 15.0, (Npopulacije, D))

for j in range(1300):
    diferencijalna_evolucija()

print("Rezultat")
np.set_printoptions(precision=15)
print(xopt)
print(fopt)