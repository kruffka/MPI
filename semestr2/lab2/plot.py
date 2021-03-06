# 2 3 4 5 6      7          8          9         10        11         12            13
# 0 0 0 0 0.0009 0.000999   0.008998   0.070996  0.881000  09.602000  01.46.031000  15.23.201000

# 2         3        4        5         6        7         8        9        10       11       12       13       14       15       16           17          18         19
# 0.000000  0.000000 0.000000 0.000000  0.000000 0.001000  0.001000 0.002001 0.006000 0.016000 0.037998 0.105001 0.318000 0.727001 01.539002    03.577000   08.306132  18.893000

# in seconds
naive = [0, 0, 0, 0, 0.0009, 0.000999,   0.008998,   0.070996,  0.881000,  09.602000,  106.031000,  923.201000]
dynamic = [0.000000,  0.000000, 0.000000, 0.000000,  0.000000, 0.001000,  0.001000, 0.002001, 0.006000, 0.016000, 0.037998, 0.105001, 0.318000, 0.727001, 01.539002,    03.577000,   08.306132,  18.893000]

from matplotlib import pyplot as plt

x = [i + 2 for i in range(len(naive))]
print(x)
plt.plot(x, naive)
plt.grid(linestyle='-', linewidth=0.5)
x = [i + 2 for i in range(len(dynamic))]
plt.plot(x, dynamic)
plt.show()