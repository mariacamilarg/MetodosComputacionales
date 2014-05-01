all: grafica3cuerpos.py

grafica3cuerpos.py: posicion_tiempo.dat
	python grafica3cuerpos.py

posicion_tiempo.dat: 3cuerpos.x
	./3cuerpos.x

3cuerpos.x: 3cuerpos.c
	cc 3cuerpos.c -o 3cuerpos.x -lm

clean:
	rm *.dat *.x *.png
