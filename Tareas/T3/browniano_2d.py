import matplotlib.pyplot as plt
from numpy import *
import sys

try:
    n=int(sys.argv[1])
except IndexError:
    sys.exit("Se tiene que usar asi: python browniano_2D.py n, donde n es el numero de iteraciones")
except ValueError:
    sys.exit("El numero n de iteraciones debe ser un entero")

r=1
x=0
y=0
teta=0
distancias=ones(n)
iteraciones=ones(n)

for i in range(n):
    teta=random.random()*2*pi
    x+=r*cos(teta)
    y+=r*sin(teta)
    distancias[i]=sqrt(x**2+y**2)
    iteraciones[i]=i

fig = plt.figure()
ax = plt.axes()
ax.set_xlabel("n")
ax.set_ylabel("D")
ax.set_title("Movimiento Browniano")

plt.plot(iteraciones,distancias,label="Distancia al origen")
ax.legend()

filename = 'browniano_2D_'+str(n)
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.close()
