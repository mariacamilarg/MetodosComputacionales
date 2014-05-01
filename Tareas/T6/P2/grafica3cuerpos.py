from numpy import *
from matplotlib.pyplot import *
from mpl_toolkits.mplot3d import Axes3D

#Importo datos
matriz_ET=loadtxt('energia_tiempo.dat')
matriz=loadtxt('posicion_tiempo.dat')

#Armo arreglos
tiempo=matriz_ET[:,0]
energia=matriz_ET[:,1]
x1=matriz[:,1]
y1=matriz[:,2]
z1=matriz[:,3]
x2=matriz[:,4]
y2=matriz[:,5]
z2=matriz[:,6]
x3=matriz[:,7]
y3=matriz[:,8]
z3=matriz[:,9]

#Armo la figura
fig=figure()
ax=fig.gca(projection='3d')
ax.plot(x1,y1,z1)
ax.plot(x2,y2,z2)
ax.plot(x3,y3,z3)

#Guardo la figura
savefig('trayectoria.png')

#Armo la figura
fig=figure()
plot(tiempo, energia)

#Guardo la figura
savefig('energia.png')

