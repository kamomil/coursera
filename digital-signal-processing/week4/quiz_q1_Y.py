# first our usual bookkeeping
import numpy as np

def cexp(omega):
    return np.exp(1j*omega)

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

for n in range(N):
    print(s(n))
