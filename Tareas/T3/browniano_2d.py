import matplotlib.pyplot as plt
from numpy import *
import sys

try:
    n=int(sys.argv[1])
except ValueError:
    sys.exit("Se tiene que poner un entero despues!")

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
ax.set_title("Mov. Browniano")

plt.scatter(iteraciones, distancias, label="Hola Mundo")
ax.legend()

filename = 'browniano_2D_'+str(n)
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.close()
