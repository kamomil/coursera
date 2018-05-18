# first our usual bookkeeping
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

# the dft of a pulse train is a pulse train (if the PERIOD devides the vector length)
# in this example we take a pulse train and add random noise to it.
# that is we take a vectors of zeros and there is a '1' every PERIOD
# then we choose NOISE_SIZE random indexes to also have the value 1
#then in the DFT, we can see the pulse train plus other values influenced
# by the noise.

LENGTH = 128
NOISE_SIZE = 10
PERIOD = LENGTH/16

print("PERIOD = %d, NOISE_SIZE = %d, LENGTH = %d" % (PERIOD,NOISE_SIZE,LENGTH))
rand_indexes = np.random.randint(LENGTH,size = NOISE_SIZE, dtype = 'uint8')
good_indexes = np.arange(0,LENGTH,PERIOD, dtype = 'int8')
print(good_indexes)
arr = np.zeros(LENGTH)
arr[rand_indexes] = 1
arr[good_indexes] = 1

scale = np.arange(0,LENGTH,1)

X = np.fft.fft(arr)

plt.plot(scale,arr,'b-',label='1')
plt.plot(scale,abs(X),'r-',label='2')
plt.show()

