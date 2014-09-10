from math import sqrt

out = open("puntospalo.dat","w")

x=1.0
y=0.0

while x>=0.0:
    y=sqrt(1-x**2)
    out.write("%f %f\n"%(x/2,y/2))
    x-=0.01

out.close()
