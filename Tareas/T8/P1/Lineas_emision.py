# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <codecell>

import numpy as np
import matplotlib.pyplot as plt
import os

# <codecell>

data = np.loadtxt("energy_counts.dat")
data = data.T
#plot(data[0],data[1])

# <codecell>

# Calcula el chi**2 de una grupo de valores calculados respecto a los valores reales
# Modificar la likelihood y normalizarla
def the_haki( real_y, model_y ):
    lol = (1.0/2.0)*np.sum((real_y-model_y)**2.0)
    return lol

# <codecell>

# Calcula la funcion de puntos dados los parametros y un conjunto de puntos x
def the_model_y( x, A, B, E0, sigma, alpha ):
    return A*(x**alpha) + B*np.exp( - ( ( ( x - E0 )/( np.sqrt(2.0) * sigma ) )**2.0 ) )

# <codecell>

# Cadena de Markov para encontrar el mejor modelo (con mas likelihood)
# nami =  numero de iteraciones
# choper = desviacion de la gausiana de los pasos aleatorios (diferente para cada uno)
def MCMC( nami, choper, data ):
    # Inicializa las contenedoras de las variables del fit
    A_model = []
    B_model = []
    E0_model = []
    sigma_model = []
    alpha_model = []
    luffylihood = []
    
    # Los primeros parametros del modelo --> aleatorio
    A_model.append(guess[0])
    B_model.append(guess[1])
    E0_model.append(guess[2])
    sigma_model.append(guess[3])
    alpha_model.append(guess[4])
    
    # Calcula N del primer modelo aproximado
    funcN_init = the_model_y(data[0], A_model[0], B_model[0],
                             E0_model[0], sigma_model[0], alpha_model[0])
    
    # El primer chi**2
    luffylihood.append(the_haki(data[1], funcN_init))
    
    for i in range(nami):
        
        # Prueba variando los parametros
        A_temp = np.random.normal(A_model[i], choper[0])
        B_temp = np.random.normal(B_model[i], choper[1])
        E0_temp = np.random.normal(E0_model[i], choper[2])
        sigma_temp = np.random.normal(sigma_model[i], choper[3])
        alpha_temp = np.random.normal(alpha_model[i], np.abs(choper[4]))
        
        # Calcula la funcion con los nuevos parametros
        newFunc = the_model_y(data[0], A_temp, B_temp, E0_temp, sigma_temp, alpha_temp)
        
        # Calcula la nueva likelihood
        luffy = the_haki( data[1], newFunc )
        
        # Si la likelihood es mejor que la anterior, actualiza los parametros
        if luffy < luffylihood[i] :
            A_model.append(A_temp)
            B_model.append(B_temp)
            E0_model.append(E0_temp)
            sigma_model.append(sigma_temp)
            alpha_model.append(alpha_temp)
            luffylihood.append(luffy)
            
        # Si no, se deja a la suerte
        robin = np.log(np.random.random())
        sanji = -(luffy - luffylihood[i])      
        if robin <= sanji:
            A_model.append(A_temp)
            B_model.append(B_temp)
            E0_model.append(E0_temp)
            sigma_model.append(sigma_temp)
            alpha_model.append(alpha_temp)
            luffylihood.append(luffy)  
        else:
            A_model.append(A_model[i])
            B_model.append(B_model[i])
            E0_model.append(E0_model[i])
            sigma_model.append(sigma_model[i])
            alpha_model.append(alpha_model[i])
            luffylihood.append(luffylihood[i])
        
    return np.array([luffylihood, A_model, B_model, E0_model, sigma_model, alpha_model])

# <codecell>

guess = np.array([1.0*10.0**16.0, 1000.0, 1000.0, 100.0, -4.0])
choper =  np.array([1.0*10.0**13.0, 200.0, 500.0, 10.0, 0.00005])
zoro = MCMC(1000000, choper, data)
# Pitico para avisarme q termino
os.system('play --no-show-progress --null --channels 1 synth %s sine %f' % ( 1, 880.0))

# <codecell>

#plot(np.linspace(0,1,len(zoro[0])), zoro[0])

# <codecell>

index = np.argmin(zoro[0])
arreglada_func = the_model_y(data[0], zoro[1][index], zoro[2][index], zoro[3][index], zoro[4][index], zoro[5][index])

# <codecell>

# Incertidumbres
# Escoge valores cercanos
indexes = np.where( (np.abs(zoro[1][index] - zoro[1] ) <= 0.1*np.abs(zoro[1])) &  (np.abs(zoro[2][index] - zoro[2] ) <= 0.1*np.abs(zoro[2]) )
& (np.abs(zoro[3][index] - zoro[3] ) <= 0.1*np.abs(zoro[3])) & (np.abs(zoro[4][index] - zoro[4] ) <= 0.1*np.abs(zoro[4])) &
(np.abs(zoro[5][index] - zoro[5] ) <= 0.1*np.abs(zoro[5]) ) )

indexes =indexes[0]
# Para A
franky_A = zoro[1][indexes] - zoro[1][index]
chis_A = zoro[0][indexes]
sigmas_A = np.sqrt(((franky_A)**2)/(2*chis_A))
print "La incertidumbre de A es : " + str(np.max(sigmas_A))

# Para B
franky_A = zoro[2][indexes] - zoro[2][index]
chis_A = zoro[0][indexes]
sigmas_A = np.sqrt(((franky_A)**2)/(2*chis_A))
print "La incertidumbre de B es : " + str(np.max(sigmas_A))

# Para E0
franky_A = zoro[3][indexes] - zoro[3][index]
chis_A = zoro[0][indexes]
sigmas_A = np.sqrt(((franky_A)**2)/(2*chis_A))
print "La incertidumbre de E0 es : " + str(np.max(sigmas_A))

# Para sigma
franky_A = zoro[4][indexes] - zoro[4][index]
chis_A = zoro[0][indexes]
sigmas_A = np.sqrt(((franky_A)**2)/(2*chis_A))
print "La incertidumbre de sigma es : " + str(np.max(sigmas_A))

# Para alpha
franky_A = zoro[5][indexes] - zoro[5][index]
chis_A = zoro[0][indexes]
sigmas_A = np.sqrt(((franky_A)**2)/(2*chis_A))
print "La incertidumbre de alpha es : " + str(np.max(sigmas_A))

# <codecell>

#plot(data[0], data[1])
print "A = " + str(zoro[1][index])
print "B = " + str(zoro[2][index])
print "E0 = " + str(zoro[3][index])
print "sigma = " + str(zoro[4][index])
print "alpha = " + str(zoro[5][index])
#plot(data[0], gauss(data[0], zoro[2][index], zoro[3][index], zoro[4][index]))
#plot(data[0], exponential(data[0], zoro[1][index], zoro[5][index]))
fig = plt.figure()
ax = fig.add_subplot(111)
ax.set_xlabel("Energy")
ax.set_ylabel("Counts")
ax.set_title(" Datos experimentales + Fit ")
ax.plot(data[0], arreglada_func)    
ax.plot(data[0], data[1])
filename = "Energy_Counts_fit"
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
#plt.close()

# <codecell>

def gauss( x, B, E0, sigma ):
    return B*np.exp( - ( ( ( x - E0 )/( np.sqrt(2) * sigma ) )**2 ) )

def exponential( x, A, alpha ):
    return A*(x**alpha)

# <codecell>

names = [ "lol", "A", "B", "E0", "sigma", "alpha" ]

# <codecell>

for n in range(1,6):
    for m in range(n+1,6):
        npoints = 100
        matrix = np.zeros((npoints,npoints))
        min1 = np.min(zoro[n])
        min2 = np.min(zoro[m])
        max1 = np.max(zoro[n])
        max2 = np.max(zoro[m])
        linspace1 = np.linspace(min1,max1, npoints+1)
        linspace2 = np.linspace(min2,max2, npoints+1)
        
        for i in range(npoints):
            for j in range(npoints):
                k = npoints - j
                index = np.where( (zoro[n] >= linspace1[i]) & (zoro[n] < linspace1[i+1]) & (zoro[m] <= linspace2[k]) & (zoro[m] > linspace2[k-1]) )
                matrix[i][j] = len(index[0])
                
        # grafica y guarda
        fig1 = plt.figure()
        ax1 = plt.axes()
        ax1.set_title(names[m] + " vs " + names[n])
        plt.imshow(matrix, extent=(min1,max1,min2,max2), aspect='auto')
        filename = names[m] + " vs " + names[n]
        plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
        plt.close()

# <codecell>

os.system('play --no-show-progress --null --channels 1 synth %s sine %f' % ( 2, 880.0))

# <codecell>



#imshow(matrix)

# <codecell>


