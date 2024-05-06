import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()
X = np.arange(10)
Y = X * X - 10

plt.plot(X, Y, color= "red", linewidth=1.5, linestyle="solid")


plt.show()
