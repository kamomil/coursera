#(Difficulty: \star\star⋆⋆) Write some code in your preferred programming language that implements the following CCDE:

# y[n] + 2 y[n-1] = x[n+1] - 0.5x[n]

# Use y[n] = 0, for n<0 as initial conditions and run the algorithm for
# x[n]=δ[n]+0.5δ[n−1].

# import matplotlib as plt
import matplotlib.pyplot as plt

class CCDE:
    def __init__(self):
        self.n = -1
        self.y = 0

    def eval_x(self,n):
        x = 0
        if n == 0:
            x = 1
        if n == 1:
            x = 0.5
        return x

    def next(self):
        self.n +=1
        y = 2*self.y+self.eval_x(self.n+1)-0.5*self.eval_x(self.n)
        self.y = y
        return y

    def get_n(self):
        return self.n

a = []
ccde = CCDE()
for i in range(100):
    a.append(ccde.next())
    if ccde.get_n() == 5:
        print("y[5] = "+str(a[-1]))

    if ccde.get_n() == 50:
        print("y[50] = "+str(a[-1]))

    if ccde.get_n() == 4:
        print("y[4] = "+str(a[-1]))


plt.stem(a)
plt.show()
