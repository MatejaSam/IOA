import numpy as np
from scipy.special import spherical_jn
import matplotlib.pyplot as plt


x = np.linspace(0, 20, 1000)

for n in range(1, 3):
    j = spherical_jn(n, x)
    plt.plot(x, j, label='j' + str(n))

plt.legend()
plt.title('SFERNE BESELOVE FUNCKIJE')
plt.xlabel('x')
plt.ylabel('jn(x)')

plt.grid()
plt.show()
