from numpy import *
import matplotlib.pyplot as plt
import sys

#Manejo de errores y obtencion de parametros

try:
    n=int(sys.argv[1])
except IndexError:
    sys.exit("Se tiene que usar asi: python plot_mandelbrot.py n, donde n es el numero de iteraciones para formar el fractal")
except ValueError:
    sys.exit("n debe ser un entero")

if (n<=0):
    sys.exit("n tiene que ser mayor que 0")

#Defino una funcion que me dice si pertenece al conjunto, recibe a y b partes real e imaginaria del complejo respectivamente. Luego n para saber cuantas veces debe iterar.

def perteneceAlConjunto(par_a,par_b,par_n):
    z=0
    c=complex(par_a,par_b)
    for i in range(par_n):
        z=z**2+c
        if abs(z) >= 2:
            return False
    return True


#Hallo para los complejos de la forma a+ib que voy a formar el avance para cada eje. El fractal esta acotado en x:(-2,1) y en y:(-1,1). 

resolucionx=1024
resoluciony=1024
avance_a=3.0/resolucionx
avance_b=2.0/resoluciony

a=-2.0
b=-1.0
#posiciones=zeros((resolucionx,resoluciony))
aes=zeros(resolucionx**2)
bes=zeros(resoluciony**2)
num=1

#Si el complejo pertenece al conjunto en la matriz se le asocia el uno.
for i in range(resolucionx):
    b=-1.0
    a+=avance_a
    for j in range(resoluciony):
        b+=avance_b
        if(perteneceAlConjunto(a,b,n)):
            #indice=(a,b)
            #posiciones[indice]=1
            aes[num]=a
            bes[num]=b
            num+=1
  
#Ahora grafico eso

filename = 'mandelbrot_'+str(n)

plt.figure()

plt.title("Conjunto de Mandelbrot")
plt.xlabel("Re(c)")
plt.ylabel("Im(c)")

plt.scatter(aes,bes,s=2,color='m',edgecolor='none')
#plt.imshow(posiciones)

plt.savefig(filename + '.pdf',format = 'pdf')

plt.close()
        

        
            
