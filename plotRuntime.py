import matplotlib.pyplot as plt


y = []
x = []

with open('run_times.txt', 'r') as f:
    for line in f:
        a = list(map(float, line.strip().split()))
        y.append(a[0])
        x.append(a[1])


fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
line, = ax.plot(x, y, 'r-')
plt.scatter(x, y)
ax.set_yscale('log')
ax.set_xscale('log')
plt.xlabel('Time (milliseconds)')
plt.ylabel('Number of Points in Polygon')
plt.title('Polygon Triangulation')
plt.show()
