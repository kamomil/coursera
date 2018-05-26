# first our usual bookkeeping
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

N = 1000
M = int(N/2)

x = np.zeros(N)
x[M] = 1
x[M+1] = -1

y = np.zeros(N)
y[M-1] = 1
y[M] = -1
y[M+1] = 1

X = np.fft.fft(x)
Y = np.fft.fft(y)
H = np.divide(Y,X)
H[0] = H[-1]
h = np.fft.ifft(H)
print(H)
plt.figure(1)
plt.plot(x,'b-',label='1')
plt.plot(abs(X),'r-',label='2')
plt.plot(abs(Y),'g-',label='3')
plt.plot(abs(H),'k-',label='4')
plt.plot(abs(h),'y-',label='5')
plt.legend(['x','X','Y','H','h'])

#plt.show()
h = np.zeros(N)
a = 0
h[0:M-2] = a
h[M-1] = a+1
h[M] = a
h[M+1:] = a+1

c = np.convolve(x,h)

plt.figure(2)

plt.stem(c)
plt.show()
