from numpy import *
from matplotlib.pyplot import *
from mpl_toolkits.mplot3d import Axes3D

#Importo datos
energia = loadtxt("energia_tiempo.dat")
posicion = loadtxt("posicion_tiempo.dat")

t=energia[:,0]
e=energia[:,1]

t=(10**9-2)/20

#Hago 20 graficas de posicion vs tiempo
for i in range(20):

    fila = posicion[i*t,:]
    largo = len(fila)/2
    xs=zeros(largo)
    ys=zeros(largo)
    zs=zeros(largo)
    
    for j in range(largo):
        xs[j]=fila[3*j]
        ys[j]=fila[3*j+1]
        zs[j]=fila[3*j+2]
    
    fig = figure()
    ax=fig.gca(projection='3d')
    ax.scatter(xs,ys,zs)
    savefig('posicion_tiempo_'+str(i)+'.png')

#Grafico energia vs tiempo
fig = figure()
plot(t,e)
savefig("energia_tiempo.png")
