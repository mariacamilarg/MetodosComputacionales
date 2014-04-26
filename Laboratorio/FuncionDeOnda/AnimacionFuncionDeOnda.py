from numpy import *
from matplotlib.pyplot import *
from matplotlib import animation

#FUENTE:
#Ayuda para hacer la animacion
#http://jakevdp.github.com

#FUNCIONES

#IMPORTACION DATOS
data=loadtxt("funcion_onda.dat")
xs=data[0,:]

#Initialization function: plot the background of each frame
def init():
    line.set_data([], [])
    return line,

#Animation function.  This is called sequentially
def animate(i):
    us = data[1,:]
    line.set_data(xs, us)
    return line,

#PROCEDIMIENTO

# First set up the figure, the axis, and the plot element we want to animate
fig = figure()
ax = axes(xlim=(0, 1), ylim=(0, 1))
line, = ax.plot([], [], lw=2)

#Call the animator.  blit=True means only re-draw the parts that have changed.
anim = animation.FuncAnimation(fig, animate, init_func=init, frames=600, interval=50, blit=True)

show()
