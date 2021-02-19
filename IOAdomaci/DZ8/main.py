from builtins import dict
import numpy as np
import random
import matplotlib.pyplot as plt
import math

def optfunckija(xpom):
    global s
    rez = 0
    for i in range(0, 64):
        rez = rez + (xpom[i]*s[i])
    rezultat = math.pow(2, 26) - rez
    if rezultat < 0:
        rezultat = math.pow(2, 26)
    return int(rezultat)


def generate_next_population():
    global currentpopulation
    global nextpopulation
    global my_dict
    global key_list
    global value_list
    global ukrvr
    global mutvr

    pom = np.zeros(400, dtype=int)
    for k in range(400):
        ind = value_list.index(min(my_dict.values()))
        pom[k] = key_list[value_list.index(min(my_dict.values()))]
        del my_dict[key_list[value_list.index(min(my_dict.values()))]]
        value_list.pop(ind)
        key_list.pop(ind)

    counter = 0

    while counter < 2000:
        prvi = pom[random.randint(0, 399)]
        drugi = pom[random.randint(0, 399)]
        while prvi == drugi:
            drugi = pom[random.randint(0, 399)]
        if random.uniform(0.0, 1.0) < ukrvr:
            prviniz = currentpopulation[prvi]
            druginiz = currentpopulation[drugi]
            granica = random.randint(0, 62)

            c1 = 0
            c2 = granica+1
            for k1 in prviniz:
                if c1 <= granica:
                    nextpopulation[counter][c1] = k1
                    c1 = c1 + 1
                else:
                    nextpopulation[counter+1][c2] = k1
                    c2 = c2 + 1

            c1 = granica + 1
            c2 = 0
            for k1 in druginiz:
                if c2 <= granica:
                    nextpopulation[counter+1][c2] = k1
                    c2 = c2 + 1
                else:
                    nextpopulation[counter][c1] = k1
                    c1 = c1 + 1

            if random.uniform(0.0, 0.3) < mutvr:
                kj = random.randint(0, 63)
                nextpopulation[counter][kj] = 1 - nextpopulation[counter][kj]

            if random.uniform(0.0, 0.3) < mutvr:
                kj = random.randint(0, 63)
                nextpopulation[counter + 1][kj] = 1 - nextpopulation[counter + 1][kj]

            counter = counter + 2

    currentpopulation = nextpopulation


s = np.array([173669, 275487, 1197613, 1549805, 502334, 217684, 1796841, 274708,
631252, 148665, 150254, 4784408, 344759, 440109, 4198037, 329673, 28602,
144173, 1461469, 187895, 369313, 959307, 1482335, 2772513, 1313997, 254845,
486167, 2667146, 264004, 297223, 94694, 1757457, 576203, 8577828, 498382,
8478177, 123575, 4062389, 3001419, 196884, 617991, 421056, 3017627, 131936,
1152730, 2676649, 656678, 4519834, 201919, 56080, 2142553, 326263, 8172117,
2304253, 4761871, 205387, 6148422, 414559, 2893305, 2158562, 465972, 304078,
1841018, 1915571])

alli = np.zeros(100000, dtype=int)
localmin = 0
localx = []
globalmin = -1
globalx = []
ukrvr = 0.8
mutvr = 0.1

for pokretanje in range(20):

    currentpopulation = np.random.randint(0, 2, (2000, 64))
    nextpopulation = np.random.randint(0, 2, (2000, 64))
    single = np.zeros(100000, dtype=int)
    my_dict = {}
    cnt = 0

    localmin = 0
    localx = []

    for i in range(2000):
        currentpopulation[i] = np.random.randint(0, 2, 64)
        my_dict[i] = optfunckija(currentpopulation[i])
        if i == 0:
            localmin = my_dict[i]
            localx = currentpopulation[i].copy()
        else:
            if my_dict[i] < localmin:
                localmin=my_dict[i]
                localx = currentpopulation[i].copy()
        single[cnt] = localmin
        alli[cnt] = (alli[cnt] + localmin)
        cnt = cnt + 1

    key_list = list(my_dict.keys())
    value_list = list(my_dict.values())

    for i in range(49):
        generate_next_population()
        my_dict = {}
        for m in range(2000):
            my_dict[m] = optfunckija(currentpopulation[m])
            if my_dict[m] < localmin:
                localmin = my_dict[m]
                localx = currentpopulation[m].copy()
            single[cnt] = localmin
            alli[cnt] = (alli[cnt] + localmin)
            cnt = cnt + 1

        key_list = list(my_dict.keys())
        value_list = list(my_dict.values())


    xrez = np.linspace(0, 100000, 100000)
    plt.plot(xrez, single, label='run#' + str(pokretanje+1))
    plt.yscale("log")
    plt.xscale("log")

    if globalmin == -1 or localmin < globalmin:
        globalmin = localmin
        globalx=localx


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