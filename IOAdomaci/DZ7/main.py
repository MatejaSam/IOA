import numpy as np
import math as math
import matplotlib.pyplot as plt
import random


def optfunckija(xpom):
    global s
    rez = 0
    for i in range(0, 64):
        rez = rez + (xpom[i]*s[i])
    rezultat = math.pow(2, 26) - rez
    if rezultat < 0:
        rezultat = math.pow(2, 26)
    return int(rezultat)


def hemming(iter):
    hmin = 1
    hmax = 63
    itot = 100000
    return int((hmin - hmax) / (itot - 1) * (iter - 1) + hmax)


def generatearray(h):
    global x
    global x1
    x1 = x.copy()
    pom1 = [i for i in range(64)]
    pom1 = random.sample(pom1, int(h))
    for i in pom1:
        x1[i] = 1 - x1[i]


def pvalue(e):
    global T
    if e == 0:
        return 0.5
    else:
        return math.pow(math.exp(1), -1*(e / T))

s = np.array([173669, 275487, 1197613, 1549805, 502334, 217684, 1796841, 274708,
631252, 148665, 150254, 4784408, 344759, 440109, 4198037, 329673, 28602,
144173, 1461469, 187895, 369313, 959307, 1482335, 2772513, 1313997, 254845,
486167, 2667146, 264004, 297223, 94694, 1757457, 576203, 8577828, 498382,
8478177, 123575, 4062389, 3001419, 196884, 617991, 421056, 3017627, 131936,
1152730, 2676649, 656678, 4519834, 201919, 56080, 2142553, 326263, 8172117,
2304253, 4761871, 205387, 6148422, 414559, 2893305, 2158562, 465972, 304078,
1841018, 1915571])
alli = np.zeros(100000, dtype=int)
a = 0.91
localmin = 0
globalmin=-1
globalx=[]
localx=[]

for i in range(20):
    x = np.random.randint(0, 2, 64)
    x1 = x
    single = np.zeros(100000, dtype=int)

    cnt = 0
    T = 32 * 1024 * 1024
    pom1 = 0
    pom2 = 0

    localmin = optfunckija(x)
    localx=x.copy()
    while cnt < 100000 and optfunckija(x) != 0:
        pom1 = optfunckija(x)
        single[cnt] = localmin
        alli[cnt] = (alli[cnt] + localmin)
        generatearray(hemming(cnt))
        pom2 = optfunckija(x1)
        T = a * T
        if pom2 < pom1:
            x = x1
            if pom2 < localmin:
                localmin = pom2
                localx=x1.copy()
        elif pom2 > pom1:
            p = pvalue(pom2-pom1)
            if np.random.random(1)[0] <= p:
                x = x1
        cnt = cnt + 1
        pom2 = 0
        pom1 = 0

    xrez = np.linspace(0, 100000, 100000)
    plt.plot(xrez, single, label='run#' + str(i+1))
    plt.yscale("log")
    plt.xscale("log")

    if globalmin == -1 or localmin < globalmin:
        globalmin = localmin
        globalx = localx



print(globalx)
print(globalmin)

plt.legend()
plt.title("Cumulative minimum")
plt.xlabel('Iter')
plt.ylabel('Cumulative minimum(cost-function)')
plt.grid()
plt.show()

for i in range(100000):
    alli[i] = int(alli[i] / 20)

xrez = np.linspace(0, 100000, 100000)
plt.plot(xrez, alli)
plt.yscale("log")
plt.xscale("log")
plt.title("Average Cumulative minimum")
plt.xlabel('Iter')
plt.ylabel('Average Cumulative minimum(cost-function)')
plt.grid()
plt.show()
