import numpy as np

datos=np.loadtxt("data.dat")

#imprime todo
#print datos

#imprime (numfilas, num columnas)
print np.shape(datos)

#imprime primera fila
print datos[0,:]

#imprime primera columna
print datos[:,0]
