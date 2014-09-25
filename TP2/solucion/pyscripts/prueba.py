import numpy as np
import matplotlib.pyplot as plt

def f(t):
    return np.exp(-t) * np.cos(2*np.pi*t)

t1 = np.arange(0.0, 5.0, 0.1)
t2 = np.arange(0.0, 5.0, 0.02)

plt.figure(1, figsize=(12, 5))
plt.subplot(121)
plt.plot(t1, f(t1), 'bo', t2, f(t2), 'k')
plt.title("subplot1")

plt.subplot(122)
plt.plot(t2, np.cos(2*np.pi*t2), 'r--')
plt.title("subplot2")
plt.show()
