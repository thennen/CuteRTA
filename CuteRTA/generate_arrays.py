# Generate temperature and RGB arrays for use in AVR program
# We will heat up using a sine integral, and cool down with an exponential
from matplotlib import pyplot as plt
import numpy as np

# Length of arrays

n_init = 15
n_heating = 15
n_setpoint = 15
n_hot = 15
n_cooling = 35
n = sum((n_init, n_heating, n_setpoint, n_hot, n_cooling))

# Temperature will be mapped to this colormap
cmap = plt.cm.hot

T0 = 293
T1 = 1000
T2 = 500

def exp_decay(val1, val2, n, t=10):
    return val1 - (val1 - val2) * (1 - np.exp(-np.linspace(0, t, n)))

# Define heating/cooling curve.  Dumb version here
T_init = np.repeat(T0, n_init)
T_heating = np.linspace(T0, T1, n_heating)
#T_setpoint = exp_decay(T1, T2, n_setpoint)
T_setpoint = np.repeat(T1, n_setpoint)
#T_hot = np.repeat(T2, n_hot)
T_hot = np.repeat(T1, n_hot)
#T_cooling = exp_decay(T2, T0, n_cooling)
T_cooling = exp_decay(T1, T0, n_cooling)

T = np.concatenate((T_init, T_heating, T_setpoint, T_hot, T_cooling))
T += np.random.randn(n)
T_cstring = '{' + ', '.join([format(int(t), 'd') for t in T]) + '}'

colors = cmap((T - T0) / (T1 - T0))

# Drop the alpha channel
colors = colors[:,:-1]

# Convert to 8 bit values
colors = np.uint8(colors * 255)

colors_cstring = '{' + ', '.join(['{{{}, {}, {}}}'.format(*c) for c in colors]) + '}'

# Convert to c string
with open('carrays.c', 'w') as f:
    f.write(f'float T[{n}] = {T_cstring};\n')
    f.write(f'int colors[{n}][3] = {colors_cstring};\n')
