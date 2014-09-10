import numpy as np

n_points=100
a=np.random.random(n_points)
b=np.random.random(n_points)

out = open("data.dat", "w")

for i in range(n_points):
    out.write("%f %f\n"%(a[i],b[i]))

out.close
