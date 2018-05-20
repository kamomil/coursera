# first our usual bookkeeping
import numpy as np

def cexp(omega):
    return np.exp(1j*omega)

FREQ = 1.6666 * np.array([0,1,2,3,4,5])
#AMP = np.array([1,0.4,0.8,0.6,0.2,0.4])
AMP = np.array([0,0,0,0,1,0])

N = 6

def a(n,f,a):
    return a*cexp(n*f*np.pi)

def s(n):
    S = 0
    for i in range(0,6):
        S+= a(n,FREQ[i],AMP[i])
    return S

for n in range(30):
    print(n)
    print(s(n))
