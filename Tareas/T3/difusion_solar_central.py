import matplotlib.pyplot as plt
from numpy import *
import sys

try:
    n=int(sys.argv[1])
except IndexError:
    sys.exit("Se tiene que usar asi: python difusion_solar_central.py, donde n es el numero de fotones a propagar.")
except ValueError:
    sys.exit("El numero n de iteraciones debe ser un entero.")

R=10**5
r=1
teta=0
fi=0
pasos=ones(n)

for i in range(n):
    num=0
    d=0
    x=0
    y=0
    z=0
    while(d<R):
        teta=random.random()*2*pi
        fi=random.random()*pi
        x+=r*sin(teta)*cos(fi)
        y+=r*sin(teta)*sin(fi)
        z+=r*cos(fi)
        d=sqrt(x**2+y**2+z**2)
        num+=1
    pasos[i]=num

#Ahora hay que hacer el histrograma

filename = 'histo_difusion_solar_central_'+str(n)

plt.figure()

plt.hist(pasos,bins=80)
plt.title("Histograma Difusion Solar")
plt.xlabel("Pasos")
plt.ylabel("Numero de Fotones")

plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)

plt.close()
