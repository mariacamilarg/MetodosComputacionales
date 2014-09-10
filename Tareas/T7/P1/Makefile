animacion_cuerda_vibrando.py: cuerda_vibrando.dat
		python animacion_cuerda_vibrando.py

cuerda_vibrando.dat: cuerda_vibrando.x
		./cuerda_vibrando.x

cuerda_vibrando.x: cuerda_vibrando.c
		cc cuerda_vibrando.c -o cuerda_vibrando.x -lm

clean:
	rm *.x *.dat
