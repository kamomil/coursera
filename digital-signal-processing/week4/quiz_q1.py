# first our usual bookkeeping
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

def cexp(omega):
    return np.exp(1j*omega)

def cexp2(omega):
    return np.cos(omega)+1j*np.sin(omega)

#x = np.arange(0, 1.02, 0.02)
x = np.ones(3)
om = (2*np.pi)/3
y = 0.5*np.array([cexp(om*0),cexp(om*1),cexp(om*2)])
y2 = 0.5*np.array([cexp2(om*0),cexp2(om*1),cexp2(om*2),cexp2(om*3) ])

print(y2)
print(y)

X = np.fft.fft(x+y);
plt.stem(abs(X));
plt.title("=== exam week 3 Q4 : DFT of (-1)^n ==== ")
plt.show()


N = 20

def a1(n):
    return cexp(n*np.pi/2)

def a2(n):
    return cexp(n*2*np.pi/3)

def a3(n):
    return cexp(n*5*np.pi/6)

def a4(n):
    return cexp(n*np.pi)

def s(n):
    return 0.75*a1(n)+0.25*a2(n)+0.5*a3(n)+a4(n)

for n in range(20):
    print(s(n))
