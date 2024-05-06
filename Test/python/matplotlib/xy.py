import numpy as np
import matplotlib.pyplot as plt


X = [1, 2, 3, 4, 5, 6, 7, 8]
Y = [20, 30, 45, 62, 88, 54, 62, 40]

plt.xlim(0, 10)
plt.ylim(0, 100)

#plt.plot(X, Y)
plt.plot(X, Y, color="r", linewidth=1.5, marker=".", linestyle="solid")

plt.title("TEST")

plt.show()
