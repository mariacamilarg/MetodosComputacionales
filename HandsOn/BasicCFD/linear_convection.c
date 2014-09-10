/*
 * linear_convection.c
 * Author: María Camila
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void copy(float *fuente, float *destino, int num_elementos);

int main(void) {

	//Archivos

	//primera linea: xs
	//resto lineas: us
	FILE *f = fopen("linear_convection.dat","w");


	//CONVECCION LINEAL

	int n_x = 80;
	int n_t = 300;
	float c = 1;

	//distribuyo xs

	float *xs=malloc(sizeof(float)*n_x);
	float *ts=malloc(sizeof(float)*n_t);
	float *us=malloc(sizeof(float)*n_x);
	float *us_past=malloc(sizeof(float)*n_x);

	float dt = 0.001;
	float dx=2/n_x;

	int i;
	for (i=0;i<n_x;i++){
		xs[i]=i*dx;
		fprintf(f,"%f\t",i*dx);
		if(i*dx<1.25 || i*dx>0.75){
			us[i]=2;
		}
		else{
			us[i]=1;
		}
	}
	fprintf(f,"\n");

	float num;
	int j;
	for (i=0;i<n_t;i++){
		copy(us, us_past, n_x);

		for (j=0;j<n_x;j++){
			num=us_past[j]- c*dt/dx*(us_past[i]-us_past[i-1]);
			us[j]=num;

			fprintf(f,"%f\t",num);
		}

		fprintf(f,"\n");
	}

	return 0;
}

void copy(float *fuente, float *destino, int num_elementos){

	int i;
	for (i=0;i<num_elementos;i++){
		destino[i]=fuente[i];
	}
}



