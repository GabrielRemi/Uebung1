import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("tabelle.txt")

x, y = np.zeros(2000), np.zeros(2000)

for i in range(2000):
    x[i] = data[i][0]
    y[i] = data[i][1]
    
plt.subplots(figsize = (6, 5))
plt.title("dataset2 Werte")
plt.xlabel("$A_i$")
plt.ylabel("$\\sin A_i$")
plt.plot(x, y)

plt.show()
    