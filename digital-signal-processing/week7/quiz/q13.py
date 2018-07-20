import numpy as np
import matplotlib.pyplot as plt

class Chrip:
    def __init__(self,f0,f1,t1):
        self.f0 = f0
        self.f1 = f1
        self.t1 = t1
        self.alpha = (f1 - f0 ) / t1

    def samples(self,Fs,start,end):
        T = 1/Fs
        ind = np.arange(start,end+T,T)
        ind2 = np.square(ind)
        x = np.cos(2*np.pi*self.f0*ind + self.alpha*np.pi*ind2)
        #for s in x:
        #    print(s)
        #m = np.r_[True, x[1:] < x[:-1]] & np.r_[x[:-1] < x[1:], True]
        #M = [ind[i] for i in range(len(m)) if m[i]]

        #d = np.diff(M)
        #plt.plot(np.reciprocal(d))
        #plt.show()
        #print(x[-1])
        plt.plot(ind,x)
        plt.show()
        #a = [i for i in range(len(ind)) if x[i] == 0]
        #print(a)

C = Chrip(0,10,2)
C.samples(8000,0,2)
