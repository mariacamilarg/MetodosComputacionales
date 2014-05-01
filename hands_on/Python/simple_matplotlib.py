import numpy as np
import matplotlib.pyplot as plt

n_points = 1000
x = np.random.random(n_points) 
y  = np.random.random(n_points)

#make a simple figure
fig = plt.figure()
ax = plt.axes()
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_title("Random Points")

plt.scatter(x,y, label="Hola Mundo")
ax.legend()

filename = 'random' 
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.close()


#pimp it
fig = plt.figure(figsize=(9.5,9.0))
ax = plt.axes()

ax.set_xlabel("$y$",fontsize=25)
ax.set_ylabel("$x$",fontsize=25)
ax.set_title("$\mathrm{Random\ Points}$", fontsize=25)

ticklabels_x = ax.get_xticklabels()
ticklabels_y = ax.get_yticklabels()
for label_x in ticklabels_x:
    label_x.set_fontsize(22)
    label_x.set_family('serif')
for label_y in ticklabels_y:
    label_y.set_fontsize(22)
    label_y.set_family('serif')

plt.scatter(x,y, s=80.0, alpha=0.5, color='red', label="$f(x)=x^2+x_0$")

ax.legend(loc=0, scatterpoints=1, prop={'size':22})

filename = 'random_latex' 
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.close()
