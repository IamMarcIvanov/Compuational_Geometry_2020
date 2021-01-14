from matplotlib import pyplot as plt
from decimal import Decimal
from shapely.geometry.polygon import LinearRing

p = []
out_x = []
out_y = []
with open("input.txt", 'r') as f:
    for line in f:
        a = list(map(Decimal, line.strip().split()))
        p.append(a)

ring = LinearRing(p + [p[0]])
x, y = ring.xy
fig = plt.figure(1, figsize=[14, 7.5])
ax = fig.add_subplot(111)
ax.plot(x, y, color='#000000', linewidth=1)

with open("intermediate.txt", 'r') as f:
    for line in f:
        a = list(map(Decimal, line.strip().split()))
        out_x.append(a[0])
        out_y.append(a[1])
        out_x.append(a[2])
        out_y.append(a[3])
        ax.plot(out_x, out_y, color='#00ff00', linewidth=1)
        out_x = []
        out_y = []


ax.set_title('Polygon')
plt.show()