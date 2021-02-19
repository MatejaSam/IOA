import numpy as np
import matplotlib.pyplot as plt
import random

BrTacaka = 10000

Tacka = np.random.uniform(-1.0, 1.0, (BrTacaka, 5))


for i in range(BrTacaka):
    while Tacka[i][0] * Tacka[i][1] + 0.25 < 0:
           Tacka[i][0] = random.uniform(-1.0, 1.0)
           Tacka[i][1] = random.uniform(-1.0, 1.0)

for i in range(BrTacaka):
    Tacka[i][2] = 2*(Tacka[i][0]**2) + Tacka[i][1]**2
    Tacka[i][3] = -((Tacka[i][0] - Tacka[i][1])**2)
    Tacka[i][4] = 1

for i in range(BrTacaka):
    for j in range(BrTacaka):
        if Tacka[j][2] < Tacka[i][2] and Tacka[j][3] < Tacka[i][3]:
            Tacka[i][4] = 0
            break

plt.figure("Zadatak 11")
plt.xlabel("f1")
plt.ylabel("f2")
plt.grid()

for i in range(BrTacaka):
    plt.plot(Tacka[i][2], Tacka[i][3], color="deepskyblue", marker=".")

for i in range(BrTacaka):
    if Tacka[i][4] == 1:
        plt.plot(Tacka[i][2], Tacka[i][3], color='orange', marker=".")

plt.show()