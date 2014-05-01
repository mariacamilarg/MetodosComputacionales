
# In[14]:

#Importando librerias necesarias
import matplotlib.pyplot as plt
import numpy as np


# In[15]:

#Importando datos
i = 0
data = []
while True:
    try:
        data.append(np.loadtxt("resultado_galaxia_"+str(i)+".txt"))
        i = i +1
    except IOError:
        break
datos =[]
for i in data:
    i = i.T
    datos.append(i)


        
        


# In[16]:

#Graficando datos
j = 0
for i in datos:
    plt.scatter(i[1],i[2])
    plt.title("Resultado galaxia momento" + str(j))
    plt.xlabel("Posicion eje x (UA)")
    plt.ylabel("Posicion eje y (UA)")
    plt.savefig("Resultado_galaxia_momento_" + str(j) + ".pdf")
    j = j + 1
    plt.show()

# In[7]:




# In[ ]:



