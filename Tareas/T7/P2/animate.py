import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

fig = plt.figure()
ax = plt.axes(xlim=(-80, 80), ylim=(0 , 0.05))
line, = ax.plot([], [], lw=2)

data = np.loadtxt("schroe.dat");

def init():
    line.set_data([], [])
    return line,

def animate(i):
    global data
    x = np.linspace(-80, 80, np.shape(data)[1])
    y = data[i,:]
    line.set_data(x, y)
    return line,


anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=np.shape(data)[0], interval=20, blit=True)

plt.show()

#anim.save('wave.mp4', fps=30, extra_args=['-vcodec', 'libx264'])
