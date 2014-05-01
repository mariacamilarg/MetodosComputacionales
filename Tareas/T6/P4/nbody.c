/*
 ============================================================================
 Name        : nbody.c
 Author      : Maria Camila
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//DECLARACION DE FUNCIONES
//Encima de la implementación de cada funcion se describe que hace
void llenarPosicionesIniciales(float *xs, float *ys, float *zs, float R, int num_masas);
void llenarVelocidadesIniciales(float *vxs, float *vys, float *vzs, int num_masas);
float darEnergia(float *xs, float *ys, float *zs, float *vxs, float *vys, float *vzs, int num_masas, int indiceIteracionActual);
float d2xdt2(int indMasa, int indiceIteracionActual, float *xs, float *ys, float *zs, int num_masas);
float d2ydt2(int indMasa, int indiceIteracionActual, float *xs, float *ys, float *zs, int num_masas);
float d2zdt2(int indMasa, int indiceIteracionActual, float *xs, float *ys, float *zs, int num_masas);
float dxdt(float vx);
float dydt(float vx);
float dzdt(float vx);
void RungeKuttaCuartoOrden_x(int num_masas, float t, float dt, float* xs, float* ys, float* zs, float* vxs, int indiceIteracionActual);
void RungeKuttaCuartoOrden_y(int num_masas, float t, float dt, float* xs, float* ys, float* zs, float* vys, int indiceIteracionActual);
void RungeKuttaCuartoOrden_z(int num_masas, float t, float dt, float* xs, float* ys, float* zs, float* vzs, int indiceIteracionActual);

//MAIN
int main(void) {

	//Datos (en parsec, masas solares, años)
	float R=20;
	int num_masas=pow(10,4);
	float t=0;
	float t_max=pow(10,9);
	float dt=pow(10,7);
	int num_iteraciones= (int) t_max/dt;

	float *xs;
	float *ys;
	float *zs;
	float *vxs;
	float *vys;
	float *vzs;
	float *energias;
	float *tiempos;

	//Distribuir las posiciones iniciales de las n masas uniformemente en una esfera
	xs=malloc(num_iteraciones*num_masas*sizeof(float));
	ys=malloc(num_iteraciones*num_masas*sizeof(float));
	zs=malloc(num_iteraciones*num_masas*sizeof(float));

	llenarPosicionesIniciales(xs, ys, zs, R, num_masas);


	//Distribuir las velocidades iniciales de las n masas de tal manera que la energia sea 0.
	vxs=malloc(num_masas*sizeof(float));
	vys=malloc(num_masas*sizeof(float));
	vzs=malloc(num_masas*sizeof(float));

	llenarVelocidadesIniciales(vxs, vys, vzs, num_masas);

	//Arreglos que guardan la energia del sistema y el tiempo en cada iteracion.
	energias=malloc(sizeof(float)*num_iteraciones);
	tiempos=malloc(sizeof(float)*num_iteraciones);

	//Inicializo energia y tiempo inicial en 0
	energias[0]=0;
	tiempos[0]=0;

	//Avanzo dt en el tiempo para empezar a iterar
	t+=dt;

	//Ahora se puede empezar a integrar. Se recorre primero en el tiempo y adentro para cada uno de esos tiempos, se hace un ciclo para cada masa.

	int i;
	for (i=1;i<num_iteraciones;i++){

		printf("Avance: %f por ciento.\n",(float)i*100/num_iteraciones);

		//Ejecutar RungeKuttas que actualizan posiciones y velocidades
		RungeKuttaCuartoOrden_x(num_masas, t, dt, xs, ys, zs, vxs, i);
		RungeKuttaCuartoOrden_y(num_masas, t, dt, xs, ys, zs, vys, i);
		RungeKuttaCuartoOrden_z(num_masas, t, dt, xs, ys, zs, vzs, i);

		//Lleno arreglos de tiempo y energia con la iteracion actual
		energias[i]=darEnergia(xs,ys, zs, vxs, vys, vzs, num_masas, i);
		tiempos[i]=t;

		//Avanzo en el tiempo
		t+=dt;
	}

	//Voy a guardar en 2 archivos: energia_tiempo.dat y posicion_tiempo.dat. El formato es respectivamente:
	//tiempo  energia
	//tiempo  x1   y1   z1   x2   y2   z2   ...  xn   yn   zn

	FILE *f_et = fopen("energia_tiempo.dat", "w");
	FILE *f_pt = fopen("posicion_tiempo.dat", "w");

	int k;
	int l;
	for (k=0;k<num_iteraciones;k++){
		//energia-tiempo
	    fprintf(f_et, "%f %f\n", tiempos[k],energias[k]);

	    //posicion-tiempo
	    fprintf(f_pt, "%f ", tiempos[k]);

	    for (l=0;l<num_masas;l++){
	    	fprintf(f_pt, "%f %f %f", xs[num_masas*k+l],ys[num_masas*k+l],zs[num_masas*k+l]);
	    }

	    fprintf(f_pt, "\n");
	}

	fclose(f_et);
	fclose(f_pt);


	//Return 0
	return 0;
}


//FUNCIONES

//Funcion que rellena los arreglos que le llegan por parametro con valores de posiciones en x,y,z
//que corresponden a un punto dentro de una esfera de radio R
void llenarPosicionesIniciales(float *xs, float *ys, float *zs, float R, int num_masas){

	srand48(12);

	float a;
	float b;
	float c;
	float r;
	int contador=0;

	while(contador<=num_masas){

		a = (0.5-(float) drand48())*2*R;
		b = (0.5-(float) drand48())*2*R;
		c = (0.5-(float) drand48())*2*R;

		r=sqrt(pow(a,2)+pow(b,2)+pow(c,2));

		if(r<=R){
			xs[contador]=a;
			ys[contador]=b;
			zs[contador]=c;
			contador++;
		}
	}
}

//Funcion que rellena los arreglos de velocidades que le llegan por parametro con valores de velocidades iniciales en x,y,z
void llenarVelocidadesIniciales(float *vxs, float *vys, float *vzs, int num_masas){

	//Todas las velocidades empiezan en 0.

	int i;
	for (i=0;i<num_masas;i++){
		vxs[i]=0;
		vys[i]=0;
		vzs[i]=0;
	}
}

//Funcion que retorna la energia del sistema cuando se le dan posiciones y velocidades actuales de cada masa. Calcula: 2K+U
float darEnergia(float *xs, float *ys, float *zs, float *vxs, float *vys, float *vzs, int num_masas, int indiceIteracionActual){

	//Potencial

	float M = 1;
	float G = 4.48773427 * pow(10, -15); //en pc^3 Ms^-1 yr^-2
	float d_min=0.01;

	float potencial = 0;

	float xi;
	float yi;
	float zi;
	float xj;
	float yj;
	float zj;

	float d;

	int i;
	int j;

	for (i = 0; i < num_masas; i++) {

		xi = xs[num_masas*indiceIteracionActual+i];
		yi = ys[num_masas*indiceIteracionActual+i];
		zi = zs[num_masas*indiceIteracionActual+i];

		for (j = i + 1; j < num_masas; j++) {

			xj = xs[num_masas*indiceIteracionActual+j];
			yj = ys[num_masas*indiceIteracionActual+j];
			zj = zs[num_masas*indiceIteracionActual+j];

			d = sqrt(pow(xi - xj, 2) + pow(yi - yj, 2) + pow(zi - zj, 2))+d_min;

			potencial += G * pow(M, 2) / d;
		}
	}

	//Cinetica

	float cinetica=0;
	float v2;

	for (i=0;i<num_masas;i++){
		v2= pow(vxs[i], 2) + pow(vys[i], 2) + pow(vzs[i], 2);
		cinetica+=M*v2/2;
	}

	float energia=2*cinetica+potencial;

	return energia;
}

//Funcion que calcula la segunda derivada de x contra el tiempo para el indice de masa pedido
float d2xdt2(int indMasa, int indiceIteracionActual, float *xs, float *ys, float *zs, int num_masas){

	float d_min=0.01;
	float G = 4.48773427 * pow(10, -15); //en pc^3 Ms^-1 yr^-2
	float M = 1;

	float FsM=0;
	float d;
	float x=xs[indiceIteracionActual*num_masas+indMasa];
	float y=ys[indiceIteracionActual*num_masas+indMasa];
	float z=zs[indiceIteracionActual*num_masas+indMasa];

	int i;
	for (i=0; i<num_masas;i++){
		if(i!=indMasa){
			d=pow(xs[indiceIteracionActual*num_masas+i]-x,2)+pow(ys[indiceIteracionActual*num_masas+i]-y,2)+pow(zs[indiceIteracionActual*num_masas+i]-z,2)+d_min;
			FsM+=G*M*pow(xs[indiceIteracionActual*num_masas+i]-x,2)/pow(d,3/2);
		}
	}

	return FsM;
}

//Funcion que calcula la segunda derivada de x contra el tiempo para el indice de masa pedido
float d2ydt2(int indMasa, int indiceIteracionActual, float *xs, float *ys, float *zs, int num_masas){

	float d_min=0.01;
	float G = 4.48773427 * pow(10, -15); //en pc^3 Ms^-1 yr^-2
	float M = 1;

	float FsM = 0;
	float d;
	float x = xs[indiceIteracionActual * num_masas + indMasa];
	float y = ys[indiceIteracionActual * num_masas + indMasa];
	float z = zs[indiceIteracionActual * num_masas + indMasa];

	int i;
	for (i = 0; i < num_masas; i++) {
		if (i != indMasa) {
			d = pow(xs[indiceIteracionActual * num_masas + i] - x, 2)+ pow(ys[indiceIteracionActual * num_masas + i] - y, 2)+ pow(zs[indiceIteracionActual * num_masas + i] - z, 2)+d_min;
			FsM += G * M * pow(ys[indiceIteracionActual * num_masas + i] - y, 2)/ pow(d, 3 / 2);
		}
	}

	return FsM;
}

//Funcion que calcula la segunda derivada de x contra el tiempo para el indice de masa pedido
float d2zdt2(int indMasa, int indiceIteracionActual, float *xs, float *ys, float *zs, int num_masas){

	float d_min=0.01;
	float G = 4.48773427 * pow(10, -15); //en pc^3 Ms^-1 yr^-2
	float M = 1;

	float FsM = 0;
	float d;
	float x = xs[indiceIteracionActual * num_masas + indMasa];
	float y = ys[indiceIteracionActual * num_masas + indMasa];
	float z = zs[indiceIteracionActual * num_masas + indMasa];

	int i;
	for (i=0; i<num_masas;i++){
		if(i!=indMasa){
			d=pow(xs[indiceIteracionActual*num_masas+i]-x,2)+pow(ys[indiceIteracionActual*num_masas+i]-y,2)+pow(zs[indiceIteracionActual*num_masas+i]-z,2)++d_min;
			FsM+=G*M*pow(ys[indiceIteracionActual*num_masas+i]-y,2)/pow(d,3/2);
		}
	}

	return FsM;
}

//Funcion que me devuelve la velocidad en x
float dxdt(float vx){
  return vx;
}

//Funcion que me devuelve la velocidad en y
float dydt(float vy){
  return vy;
}

//Funcion que me devuelve la velocidad en z
float dzdt(float vz){
  return vz;
}

//RungeKutta de cuarto orden en x
void RungeKuttaCuartoOrden_x(int num_masas, float t, float dt, float* xs, float* ys, float* zs, float* vxs, int indiceIteracionActual) {

  int i;
  for(i=0;i<num_masas;i++){

    float tiempo=t;

    float x_old=xs[num_masas*indiceIteracionActual+i];
    float v_old=vxs[i];

    //k1 y k2 iniciales
    float kv_0=dxdt(vxs[i]);
    float ka_0=d2xdt2(i, indiceIteracionActual, xs, ys, zs, num_masas);

    //primer paso
    tiempo+=dt/2;
    xs[num_masas*indiceIteracionActual+i]=x_old+kv_0*dt/2;
    float v_1=v_old+ka_0*dt/2;
    float kv_1=dxdt(v_1);
    float ka_1=d2xdt2(i, indiceIteracionActual, xs, ys, zs, num_masas);

    //segundo paso
    xs[num_masas*indiceIteracionActual+i]=x_old+kv_1*dt/2;
    float v_2=v_old+ka_1*dt/2;
    float kv_2=dxdt(v_2);
    float ka_2=d2xdt2(i, indiceIteracionActual, xs, ys, zs, num_masas);

    //tercer paso
    tiempo+=dt/2;
    xs[i]=x_old+kv_2*dt;
    float v_3=v_old+ka_2*dt;
    float kv_3=dxdt(v_3);
    float ka_3=d2xdt2(i, indiceIteracionActual, xs, ys, zs, num_masas);

    //cuarto paso
    float prom_kv=(1/6)*(kv_0+2*kv_1+2*kv_2+kv_3);
    float prom_ka=(1/6)*(ka_0+2*ka_1+2*ka_2+ka_3);

    float x_new=x_old+dt*prom_kv*dt;
    float v_new=v_old+dt*prom_ka*dt;

    xs[num_masas*indiceIteracionActual+i]=x_new;
    vxs[i]=v_new;
  }
}

//RungeKutta de cuarto orden en y
void RungeKuttaCuartoOrden_y(int num_masas, float t, float dt, float* xs, float* ys, float* zs, float* vys, int indiceIteracionActual) {

  int i;
  for(i=0;i<num_masas;i++){

	float tiempo=t;

    float y_old=ys[num_masas*indiceIteracionActual+i];
    float v_old=vys[i];

    //k1 y k2 iniciales
    float kv_0=dydt(vys[i]);
    float ka_0=d2ydt2(i, indiceIteracionActual, xs, ys, zs, num_masas);

    //primer paso
    tiempo+=dt/2;
    ys[num_masas*indiceIteracionActual+i]=y_old+kv_0*dt/2;
    float v_1=v_old+ka_0*dt/2;
    float kv_1=dydt(v_1);
    float ka_1=d2ydt2(i, indiceIteracionActual, xs, ys, zs, num_masas);

    //segundo paso
    ys[num_masas*indiceIteracionActual+i]=y_old+kv_1*dt/2;
    float v_2=v_old+ka_1*dt/2;
    float kv_2=dydt(v_2);
    float ka_2=d2ydt2(i, indiceIteracionActual, xs, ys, zs, num_masas);

    //tercer paso
    tiempo+=dt/2;
    ys[i]=y_old+kv_2*dt;
    float v_3=v_old+ka_2*dt;
    float kv_3=dydt(v_3);
    float ka_3=d2ydt2(i, indiceIteracionActual, xs, ys, zs, num_masas);

    //cuarto paso
    float prom_kv=(1/6)*(kv_0+2*kv_1+2*kv_2+kv_3);
    float prom_ka=(1/6)*(ka_0+2*ka_1+2*ka_2+ka_3);

    float y_new=y_old+dt*prom_kv*dt;
    float v_new=v_old+dt*prom_ka*dt;

    xs[num_masas*indiceIteracionActual+i]=y_new;
    vys[i]=v_new;
  }
}

//RungeKutta de cuarto orden en z
void RungeKuttaCuartoOrden_z(int num_masas, float t, float dt, float* xs, float* ys, float* zs, float* vzs, int indiceIteracionActual) {

  int i;
  for(i=0;i<num_masas;i++){

	float tiempo=t;

    float z_old=zs[num_masas*indiceIteracionActual+i];
    float v_old=vzs[i];

    //k1 y k2 iniciales
    float kv_0=dzdt(vzs[i]);
    float ka_0=d2zdt2(i, indiceIteracionActual, xs, ys, zs, num_masas);

    //primer paso
    tiempo+=dt/2;
    zs[num_masas*indiceIteracionActual+i]=z_old+kv_0*dt/2;
    float v_1=v_old+ka_0*dt/2;
    float kv_1=dzdt(v_1);
    float ka_1=d2zdt2(i, indiceIteracionActual, xs, ys, zs, num_masas);

    //segundo paso
    zs[num_masas*indiceIteracionActual+i]=z_old+kv_1*dt/2;
    float v_2=v_old+ka_1*dt/2;
    float kv_2=dzdt(v_2);
    float ka_2=d2zdt2(i, indiceIteracionActual, xs, ys, zs, num_masas);

    //tercer paso
    tiempo+=dt/2;
    zs[i]=z_old+kv_2*dt;
    float v_3=v_old+ka_2*dt;
    float kv_3=dzdt(v_3);
    float ka_3=d2zdt2(i, indiceIteracionActual, xs, ys, zs, num_masas);

    //cuarto paso
    float prom_kv=(1/6)*(kv_0+2*kv_1+2*kv_2+kv_3);
    float prom_ka=(1/6)*(ka_0+2*ka_1+2*ka_2+ka_3);

    float z_new=z_old+dt*prom_kv*dt;
    float v_new=v_old+dt*prom_ka*dt;

    zs[num_masas*indiceIteracionActual+i]=z_new;
    vzs[i]=v_new;
  }
}
