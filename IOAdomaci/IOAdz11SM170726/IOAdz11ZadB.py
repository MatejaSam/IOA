import random
import math
import matplotlib.pyplot as plt

#SM170726 Zadatak 11 pod b iz IOA
#Izvinjavam se unapred, malo sam ga zakomplikovao sa brojem matrica

n= 10000
#Pomocne funkcije
def funkcija1(x1,x2):
    return 2*math.pow(x1,2)+math.pow(x2,2)

def funkcija2(x1,x2):
    return 0-math.pow((x1-x2),2)
#-------------------------------------------------------------------------------------------

A=[[random.uniform(-1, 1) for i in range(2)] for j in range(n)]
Z=[[0 for x in range(2)] for y in range(n)]
Pareto=[[0 for x in range(2)] for y in range(n)]

for i in range(n):
    while(A[i][0]*A[i][1]+0.25)<0:
        A[i][0]=random.uniform(-1, 1)
        A[i][1]=random.uniform(-1, 1)


for i in range(n):
    a=A[i][0]
    b=A[i][1]
    Z[i][0]=funkcija1(a,b)
    Z[i][1]=funkcija2(a,b)
    Pareto[i][0]=funkcija1(a,b)
    Pareto[i][1] =funkcija2(a, b)

t=0
for i in range(n):
    for j in range(n):
        if Pareto[j][0] <  Pareto[i][0] and Pareto[j][1] < Pareto[i][1]:
            Pareto[i][0]=0
            Pareto[i][1]=0
            t = t + 1
            break
e=0

print(t)

Front=[[0 for x in range(2)] for y in range(n-t)]
for i in range(n):
    if Pareto[i][0]!=0 and Pareto[i][1]!=0:
        Front[e][0]=Pareto[i][0]
        Front[e][1] = Pareto[i][1]
        e=e+1
#-------------------------------------------------------------------------------------------

plt.title("Figura 2")
for i in range(n):
    plt.plot(Z[i][0],Z[i][1],color="blue",marker=".")
for i in range(n-t):
    plt.plot(Front[i][0],Front[i][1],color="red",marker=".")
plt.grid()
plt.show()