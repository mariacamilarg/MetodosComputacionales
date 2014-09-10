##Tarea 8 - Punto 2
##Solucion ED
##Por: Maria Camila Remolina Gutierrez

from numpy import *
from matplotlib.pyplot import *

#FUNCIONES

def dxdt(x, y, alfa, beta):
    return x*alfa - x*y*beta
    
def dydt(x, y, gama, delta):
    return -y*gama + delta*x*y

def RungeKuttaCuartoOrden_x(dt, ts, xs, ys, indiceIteracionActual, alfa, beta):

    x_old = xs[indiceIteracionActual-1]
    y_old = ys[indiceIteracionActual-1]
    t_old = ts[indiceIteracionActual-1]
    
    k_0 = dxdt(x_old, y_old, alfa, beta)
    
    #primer paso
    x_1 = x_old + (dt/2)
    t_1 = t_old + (dt/2)*k_0
    k_1 = dxdt(x_1, y_old, alfa, beta)
    
    #segundo paso
    x_2 = x_old + (dt/2)
    y_2 = y_old + (dt/2)*k_1
    k_2 = dxdt(x_2, y_old, alfa, beta)
        
    #tercer paso
    x_3 = x_old + dt
    t_3 = t_old + dt*k_2
    k_3 = dxdt(x_3, y_old, alfa, beta)
    
    #cuarto paso
    prom_k = (k_0 + 2*k_1 + 2*k_2 + k_3)/6.0
    
    x_new = x_old + dt*prom_k
    xs[indiceIteracionActual] = x_new

    
def RungeKuttaCuartoOrden_y(dt, ts, xs, ys, indiceIteracionActual, gama, delta):
    
    x_old = xs[indiceIteracionActual-1]
    y_old = ys[indiceIteracionActual-1]
    t_old = ts[indiceIteracionActual-1]
    k_0 = dydt(x_old, y_old, gama, delta)
    
    #primer paso
    y_1 = y_old + (dt/2)
    t_1 = t_old + (dt/2)*k_0
    k_1 = dydt(x_old, y_1, gama, delta)
    
    #segundo paso
    y_2 = y_old + (dt/2)
    t_2 = t_old + (dt/2)*k_1
    k_2 = dydt(x_old, y_2, gama, delta)
        
    #tercer paso
    y_3 = y_old + dt
    t_3 = t_old + dt*k_2
    k_3 = dydt(x_old, y_3, gama, delta)
    
    #cuarto paso
    prom_k = (k_0 + 2*k_1 + 2*k_2 + k_3)/6.0
    
    y_new = y_old + dt*prom_k
    ys[indiceIteracionActual] = y_new
   
def resolverED(alfa, beta, gama, delta, x_0, y_0):

    t_max = 0.8
    iter_tiempo = 10000
    dt = t_max/iter_tiempo
    
    xs = zeros(iter_tiempo)
    ys = zeros(iter_tiempo)
    ts = zeros(iter_tiempo)

    xs[0] = x_0
    ys[0] = y_0

    t=0
    ts[0] = t   

    t=dt
    for j in range(1, iter_tiempo):
        #Ejecutar RungeKuttas que actualizan xs, ys
        RungeKuttaCuartoOrden_x(dt, ts, xs, ys, j, alfa, beta)
        RungeKuttaCuartoOrden_y(dt, ts, xs, ys, j, gama, delta)
        ts[j] = t
        t += dt

    return ts, xs, ys
