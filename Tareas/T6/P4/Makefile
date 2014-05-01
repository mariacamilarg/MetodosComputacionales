all: plot_nbody.py

plot_nbody.py: posicion_tiempo.dat
	python plot_nbody.py

posicion_tiempo.dat: nbody.x
	./nbody.x

nbody.x: nbody.c
	cc nbody.c -o nbody.x -lm

clean:
	rm *.dat *.x *.png
