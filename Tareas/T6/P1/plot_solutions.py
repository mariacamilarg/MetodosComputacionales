import matplotlib.pyplot as plt
import numpy as np

#Importando resultados de cazador y presa.
data = np.loadtxt("resultados.txt")

#Graficando resultados
x=30

for i in range(30):
    fig = plt.figure()
    plt.plot(data[:,2*i],data[:,2*i+1])
    plt.savefig('x'+str(x)+'.png')
    x-=1

