##Tarea 8 - Punto 2
##Lotka-Volterra Experimental
##Por: Maria Camila Remolina Gutierrez

from numpy import *
from matplotlib.pyplot import *
import resolverED as rED

##FUNCIONES

def likelihood(observacion_x, modelo_x, observacion_y, modelo_y):
    chi_squared_x = (1.0/2.0)*sum((observacion_x - modelo_x)**2)
    chi_squared_y = (1.0/2.0)*sum((observacion_y - modelo_y)**2)    
    return (-chi_squared_x)+(-chi_squared_y)

def modelo(ts_obs, x_0, y_0, num, alfa, beta, gama, delta):

    ts, xs, ys = rED.resolverED(alfa, beta, gama, delta, x_0, y_0)

    iter_tiempo = size(ts)

    xs_modelo = zeros(num)
    ys_modelo = zeros(num)

    for i in range(num):
        lista_diferencias = abs(ts - ts_obs[i])
        indice = argmin(lista_diferencias)
        xs_modelo[i] = xs[indice]
        ys_modelo[i] = ys[indice]

    return xs_modelo, ys_modelo

##DATOS

data = loadtxt("./lotka_volterra_obs.dat")

ts_obs = data[:,0]
xs_obs = data[:,1]
ys_obs = data[:,2]
x_0 = xs_obs[0]
y_0 = ys_obs[0]

#Guardo grafica obs
fig = figure()
title("y vs x (observacion)")
xlabel("x")
ylabel("y")
scatter(xs_obs, ys_obs)
savefig('lotka_volterra_obs.png')    
close()

num = size(ts_obs)
    
##PROCESO

#Arreglos vacios para ir guardando los pasos
alfa_walk = empty((0)) 
beta_walk = empty((0))
gama_walk = empty((0))
delta_walk = empty((0))
l_walk = empty((0))

#Empiezo con valores cercanos, estimados a ojo para que la likelihood no empiece tan lejos
alfa_walk = append(alfa_walk, 30)
beta_walk = append(beta_walk, 5)
gama_walk = append(gama_walk, 50)
delta_walk = append(delta_walk, 2)

xs_iniciales, ys_iniciales = modelo(ts_obs, x_0, y_0, num, alfa_walk[0], beta_walk[0], gama_walk[0], delta_walk[0])
l_walk = append(l_walk, likelihood(xs_obs, xs_iniciales, ys_obs, ys_iniciales))

#Ahora si el ciclo

num_iteraciones = 1000

for i in range(num_iteraciones):

    if (i%200 == 0):
        print "Voy en la iteracion #", i, "de", num_iteraciones, "del MCMC"
    
    alfa_prima = random.normal(alfa_walk[i], 0.1) 
    beta_prima = random.normal(beta_walk[i], 0.1)
    
    gama_prima = random.normal(gama_walk[i], 0.1)
    delta_prima = random.normal(delta_walk[i], 0.1)

    xs_iniciales, ys_iniciales = modelo(ts_obs, x_0, y_0, num, alfa_walk[i], beta_walk[i], gama_walk[i], delta_walk[i])
    xs_prima, ys_prima = modelo(ts_obs, x_0, y_0, num, alfa_prima, beta_prima, gama_prima, delta_prima)
    
    l_inicial = likelihood(xs_obs, xs_iniciales, ys_obs, ys_iniciales)
    l_prima = likelihood(xs_obs, xs_prima, ys_obs, ys_prima)

    a = l_prima / l_inicial
    
    if(a <= 1.0):
        alfa_walk  = append(alfa_walk, alfa_prima)
        beta_walk  = append(beta_walk, beta_prima)
        gama_walk  = append(gama_walk, gama_prima)
        delta_walk  = append(delta_walk, delta_prima)
        
        l_walk = append(l_walk, l_prima)

    else:
        
        b = random.random()
        
        if( log(b) <= -a):
            alfa_walk = append(alfa_walk,alfa_prima)
            beta_walk = append(beta_walk,beta_prima)
            gama_walk = append(gama_walk,gama_prima)
            delta_walk = append(delta_walk,delta_prima)
            
            l_walk = append(l_walk, l_prima)
            
        else:
            alfa_walk = append(alfa_walk,alfa_walk[i])
            beta_walk = append(beta_walk,beta_walk[i])
            gama_walk = append(gama_walk,gama_walk[i])
            delta_walk = append(delta_walk,delta_walk[i])
            
            l_walk = append(l_walk, l_inicial)

#Grafico con los mejores alfa, beta, gama, delta encontrados

alfa_mejor = alfa_walk[-1]
beta_mejor = beta_walk[-1]
gama_mejor = gama_walk[-1]
delta_mejor = delta_walk[-1]

xs_mejores, ys_mejores = modelo(ts_obs, x_0, y_0, num, alfa_mejor, beta_mejor, gama_mejor, delta_mejor)

#Guardo grafica con los mejores parametros.
fig = figure()
title("y vs x (modelo)")
xlabel("x")
ylabel("y")
scatter(xs_mejores, ys_mejores)
savefig('lotka_volterra_mod.png')    
close()

fig = figure()
title("x vs t (rojo) -  y vs t (azul)")
xlabel("t")
ylabel("x - y")
scatter(ts_obs, xs_mejores, c='r')
scatter(ts_obs, ys_mejores)
savefig('txty.png')    
close()

fig = figure()
title("alfa vs chi**2")
xlabel("alfa")
ylabel("chi**2")
scatter(alfa_walk, -l_walk)
savefig('alfa_l.png')    
close()

fig = figure()
title("beta vs chi**2")
xlabel("beta")
ylabel("chi**2")
scatter(beta_walk, -l_walk)
savefig('beta_l.png')    
close()

fig = figure()
title("gama vs chi**2")
xlabel("gama")
ylabel("chi**2")
scatter(gama_walk, -l_walk)
savefig('gama_l.png')    
close()

fig = figure()
title("delta vs chi**2")
xlabel("delta")
ylabel("chi**2")
scatter(delta_walk, -l_walk)
savefig('delta_l.png')    
close()

print "Los valores de alfa, beta, gama y delta son:", alfa_mejor, beta_mejor, gama_mejor, delta_mejor, "respectivamente."

#Ahora las incertidumbres
d_alfa=alfa_mejor/50
d_beta=beta_mejor/50
d_gama=gama_mejor/50
d_delta=delta_mejor/50

#1. Alfa

indices = where( (abs(beta_walk-beta_mejor)<d_beta) & (abs(gama_walk-gama_mejor)<d_gama) & (abs(delta_walk-delta_mejor)<d_delta))
alfas = alfa_walk[indices] - alfa_mejor
chis_alfa = (-1)*l_walk[indices]

sigmas_alfa = sqrt(((alfa_mejor-alfas)**2)/(2*chis_alfa**2))

print "La incertidumbre en alfa es: ", amax(sigmas_alfa)

#2. Beta

indices = where( (abs(alfa_walk-alfa_mejor)<d_alfa) & (abs(gama_walk-gama_mejor)<d_gama) & (abs(delta_walk-delta_mejor)<d_delta))
betas = beta_walk[indices] - beta_mejor
chis_beta = (-1)*l_walk[indices]

sigmas_beta = sqrt(((beta_mejor - betas)**2)/(2*chis_beta**2))

print "La incertidumbre en beta es: ", amax(sigmas_beta)

#3. Gama

indices = where( (abs(alfa_walk-alfa_mejor)<d_alfa) & (abs(beta_walk-beta_mejor)<d_beta) & (abs(delta_walk-delta_mejor)<d_delta))
gamas = gama_walk[indices] - gama_mejor
chis_gama = (-1)*l_walk[indices]

sigmas_gama = sqrt(((gama_mejor - gamas)**2)/(2*chis_gama**2))

print "La incertidumbre en gama es: ", amax(sigmas_gama)

#4. Delta

indices = where( (abs(alfa_walk-alfa_mejor)<d_alfa) & (abs(beta_walk-beta_mejor)<d_beta) & (abs(gama_walk-gama_mejor)<d_gama))
deltas = delta_walk[indices] - delta_mejor
chis_delta = (-1)*l_walk[indices]

sigmas_delta = sqrt(((delta_mejor - deltas)**2)/(2*chis_delta**2))

print "La incertidumbre en delta es: ", amax(sigmas_delta)

savetxt('l.dat', l_walk)
savetxt('alfa.dat', alfa_walk)
savetxt('beta.dat', alfa_walk)
savetxt('gama.dat', alfa_walk)
savetxt('delta.dat', alfa_walk)

#Por ultimo los histogramas bidimensionales

from scipy.interpolate import griddata

min_alfa = min(alfa_walk)
min_beta = min(beta_walk)
min_gama = min(gama_walk)
min_delta = min(delta_walk)

max_alfa = max(alfa_walk)
max_beta = max(beta_walk)
max_gama = max(gama_walk)
max_delta = max(delta_walk)

npoints = 20
matrix = zeros((npoints,npoints))

#1. Alfa - Beta

linspace1 = linspace(min_alfa,max_alfa, npoints+1)
linspace2 = linspace(min_beta,max_beta, npoints+1)
        
for i in range(npoints):
	for j in range(npoints):
        	k = npoints - j
                index = where( (alfa_walk >= linspace1[i]) & (alfa_walk < linspace1[i+1]) & (beta_walk <= linspace2[k]) & (beta_walk > linspace2[k-1]) )
                matrix[i][j] = len(index[0])
                
fig = figure()
title("Densidad alfa - beta")
xlabel("alfa")
ylabel("beta")
imshow(matrix, extent=(min_alfa,max_alfa,min_beta,max_beta), aspect='auto')
savefig('densidad_alfa_beta.png')
close()

#2. Alfa - Gama

linspace1 = linspace(min_alfa,max_alfa, npoints+1)
linspace2 = linspace(min_gama,max_gama, npoints+1)
        
for i in range(npoints):
	for j in range(npoints):
        	k = npoints - j
                index = where( (alfa_walk >= linspace1[i]) & (alfa_walk < linspace1[i+1]) & (gama_walk <= linspace2[k]) & (gama_walk > linspace2[k-1]) )
                matrix[i][j] = len(index[0])
                
fig = figure()
title("Densidad alfa - gama")
xlabel("alfa")
ylabel("gama")
imshow(matrix, extent=(min_alfa,max_alfa,min_gama,max_gama), aspect='auto')
savefig('densidad_alfa_gama.png')
close()

#3. Alfa - Delta

linspace1 = linspace(min_alfa,max_alfa, npoints+1)
linspace2 = linspace(min_delta,max_delta, npoints+1)
        
for i in range(npoints):
	for j in range(npoints):
        	k = npoints - j
                index = where( (alfa_walk >= linspace1[i]) & (alfa_walk < linspace1[i+1]) & (delta_walk <= linspace2[k]) & (delta_walk > linspace2[k-1]) )
                matrix[i][j] = len(index[0])

fig = figure()
title("Densidad alfa - delta")
xlabel("alfa")
ylabel("delta")
imshow(matrix, extent=(min_alfa,max_alfa,min_delta,max_delta), aspect='auto')
savefig('densidad_alfa_delta.png')
close()

#4. Beta - Gama

linspace1 = linspace(min_beta,max_beta, npoints+1)
linspace2 = linspace(min_gama,max_gama, npoints+1)
        
for i in range(npoints):
	for j in range(npoints):
        	k = npoints - j
                index = where( (beta_walk >= linspace1[i]) & (beta_walk < linspace1[i+1]) & (gama_walk <= linspace2[k]) & (gama_walk > linspace2[k-1]) )
                matrix[i][j] = len(index[0])

fig = figure()
title("Densidad beta - gama")
xlabel("beta")
ylabel("gama")
imshow(matrix, extent=(min_beta,max_beta,min_gama,max_gama), aspect='auto')
savefig('densidad_beta_gama.png')
close()

#5. Beta - Delta

linspace1 = linspace(min_beta,max_beta, npoints+1)
linspace2 = linspace(min_delta,max_delta, npoints+1)
        
for i in range(npoints):
	for j in range(npoints):
        	k = npoints - j
                index = where( (beta_walk >= linspace1[i]) & (beta_walk < linspace1[i+1]) & (delta_walk <= linspace2[k]) & (delta_walk > linspace2[k-1]) )
                matrix[i][j] = len(index[0])

fig = figure()
title("Densidad beta - delta")
xlabel("beta")
ylabel("delta")
imshow(matrix, extent=(min_beta,max_beta,min_delta,max_delta), aspect='auto')
savefig('densidad_beta_delta.png')
close()

#6. Gama - Delta

linspace1 = linspace(min_gama,max_gama, npoints+1)
linspace2 = linspace(min_delta,max_delta, npoints+1)
        
for i in range(npoints):
	for j in range(npoints):
        	k = npoints - j
                index = where( (gama_walk >= linspace1[i]) & (gama_walk < linspace1[i+1]) & (delta_walk <= linspace2[k]) & (delta_walk > linspace2[k-1]) )
                matrix[i][j] = len(index[0])

fig = figure()
title("Densidad gama - delta")
xlabel("gama")
ylabel("delta")
imshow(matrix, extent=(min_gama,max_gama,min_delta,max_delta), aspect='auto')
savefig('densidad_gama_delta.png')
close()


print "FIN :)"
