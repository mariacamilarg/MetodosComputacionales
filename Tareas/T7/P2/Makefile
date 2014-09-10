animate.py : schroe.dat
	python animate.py

schroe.dat : a.out
	rm -f schroe.dat
	./a.out > schroe.dat
	
a.out : schroe.c
	cc schroe.c -lm 

clean:
	rm ./a.out schroe.dat
