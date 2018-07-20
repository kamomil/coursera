f = 0;
g = 0;
for n in range(0, L-1):
    y[n] = x[n] + f;
    g = -f;
    f = -x[n] + 0.5 * y[n] + g;
