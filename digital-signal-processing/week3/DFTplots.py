# first our usual bookkeeping
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

#x = np.arange(0, 1.02, 0.02)
x = np.ones(100)
x[::2] *= -1


#print(x.shape)
X = np.fft.fft(x);
plt.stem(abs(X));
plt.title("=== exam week 3 Q4 : DFT of (-1)^n ==== ")
plt.show()

x = np.arange(0,64,1)
y1 = 2*np.cos(x * (np.pi/8))
y2 = 0.5*np.sin(x * (np.pi/4))
y3 = np.ones(64)


x = y1+y2+y3

print("=== exam week 3 Q6 ==== ")
plt.plot(y1)
plt.plot(y2)
plt.plot(y3)
plt.plot(x)
#plt.show()

energy_x = np.sum(np.square(x))

fft2 = np.fft.fft(y2)
fft2[np.abs(fft2)<0.0000001] = 0
print("== fft2 ==")
print(fft2)

fft1 = np.fft.fft(y1)
fft1[np.abs(fft1)<0.0000001] = 0
print("== fft1 ==")
print(fft1)

fft3 = np.fft.fft(y3)
fft3[np.abs(fft3)<0.0000001] = 0
print("== fft3 ==")
print(fft3)

print("energy of x is: ")
print(energy_x)
