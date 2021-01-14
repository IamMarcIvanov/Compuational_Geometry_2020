import random
import math
from matplotlib import pyplot as plt
from shapely.geometry.polygon import LinearRing


def angle(point):
    dx = point[0]
    dy = point[1]
    c = (dx * dx + dy * dy) ** 0.5
    theta = math.acos(dx/c)
    if dy > 0:
        return 360 - math.degrees(theta)
    else:
        return 360 - math.degrees(math.pi * 2 - theta)


p = []
n = 20
a = 3000
while len(p) < n:
    px, py = random.uniform(-a, a), random.uniform(-a, a)
    d = (px * px + py * py) ** 0.5
    p.append((px, py))
p = sorted(p, key=lambda t: angle(t))
with open("input.txt", 'w') as file:
    for pt in p:
        file.write(str(pt[0]) + ' ' + str(pt[1]) + '\n')
ring = LinearRing(p + [p[0]])
x, y = ring.xy

fig = plt.figure(1, figsize=[14, 7.5])
ax = fig.add_subplot(111)
ax.plot(x, y, color='#000000', alpha=0.7,
        linewidth=1, zorder=2)
ax.set_title('Polygon')
plt.show()