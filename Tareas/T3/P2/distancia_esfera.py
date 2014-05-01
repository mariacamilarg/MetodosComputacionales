from numpy import *
import sys

#Manejo de errores y obtencion de parametros

try:
    lat1=float(sys.argv[1])
    lon1=float(sys.argv[2])
    lat2=float(sys.argv[3])
    lon2=float(sys.argv[4])
except IndexError:
    sys.exit("Se tiene que usar asi: python distancia_esfera.py lat1 lon1 lat2 lon2")
except ValueError:
    sys.exit("Las latidutes y longitudes deben ser float, si es Sur se le pone menos (-)")

if (absolute(lat1)>90):
    sys.exit("La latitud de la ciudad 1 debe estar entre -90 y 90")

if (absolute(lon1)>180):
    sys.exit("La longitud de la ciudad 1 debe estar entre -180 y 180")

if (absolute(lat2)>90):
    sys.exit("La latitud de la ciudad 2 debe estar entre -90 y 90")

if (absolute(lon2)>180):
    sys.exit("La longitud de la ciudad 2 debe estar entre -180 y 180")

#Radio de la Tierra en km
R=6367.5

#Redefino latitudes y longitudes a radianes
nlat1=lat1*(pi/180)
nlon1=lon1*(pi/180)
nlat2=lat2*(pi/180)
nlon2=lon2*(pi/180)

#Se halla la distancia usando la formula de Haversine

geodesica=2*R*arcsin(sqrt((sin((nlat2-nlat1)/2))**2+cos(nlat1)*cos(nlat2)*(sin((nlon2-nlon1)/2))**2))

print "La distancia mas corta entre las dos ciudades es:", geodesica,"km"
