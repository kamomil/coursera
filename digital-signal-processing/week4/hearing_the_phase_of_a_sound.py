import matplotlib
import matplotlib.pyplot as plt
import numpy as np
#import IPython
from scipy.io import wavfile

Fs = 16000 # sampling freqency
TWOPI = 2 * np.pi

def clarinet(f, phase = []):
    # length in seconds of audio clips
    T = 3

    # we will keep 5 harmonics and the fundamental
    # amplitude of components:
    ha = [0.75, 0.5, 0.14, 0.5, 0.12, 0.17]

    # phase
    phase = np.concatenate((phase, np.zeros(len(ha)-len(phase))))

    x = np.zeros((T * Fs))
    # clarinet has only odd harmonics
    n = np.arange(len(x))
    for k, h in enumerate(ha):
        x += h * np.sin(phase[k] + TWOPI * (2*k + 1) * (float(f)/Fs) * n)
    return x

def prepare(x, max_value = 3):
    N = len(x)
    # fade-in and fade-out times max 0.2 seconds
    tf = min(int(0.2 * Fs), int(0.1 * N))
    for n in range(0, tf):
        s = float(n) / float(tf)
        x[n] *= s
        x[N-n-1] *= s
        print(n,tf)
    # let's append an anti-normalization tail; drawback is one second of silence in the end
    print("to concat")
    x = np.concatenate((x, np.linspace(0, max_value, Fs/2), np.linspace(max_value, 0, Fs/2)))
    return x

p = prepare(np.zeros(100))
print("p")
print(p)
plt.plot(p)
plt.show()

# fundamental frequency: D4
D4 = 293.665
phase = [0,1,2,3,4,5]
x = clarinet(D4,phase)

# let's look at the waveform, nice odd-harmonics shape:
plt.plot(x[0:300])
plt.show()

# let's look at the waveform, nice odd-harmonics shape:
plt.plot(prepare(x[0:300]))
plt.show()
