resultados.png: plot_solutions.py resultados.txt
		python plot_solutions.py

resultados.txt: volterra_lotka.x
		./volterra_lotka.x

volterra_lotka.x: volterra_lotka.c
		cc volterra_lotka.c -o volterra_lotka.x -lm

clean:
	rm *.x *.txt *.png
