#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Declaracion Funciones
float dxdt(float x, float y);
float dydt(float x, float y);
void RungeKuttaCuartoOrden_x(float dt, float *x, float *y, int indiceIteracionActual);
void RungeKuttaCuartoOrden_y(float dt, float *x, float *y, int indiceIteracionActual);

int main(){

  //Datos
  float x_0=30;
  float y_0=20;
  int num_graficas=x_0;
  double t;
  double t_max=1;
  double dt=t_max/100;
  int iter_tiempo = (int) t_max/dt;

  //Posiciones
  //Van a tener xs de x_0=30, luego x_0=29, y asi.. Igual con ys
  float *xs=malloc(sizeof(float)*iter_tiempo*num_graficas);
  float *ys=malloc(sizeof(float)*iter_tiempo*num_graficas);

  //Voy a iterar de ultimo en las graficas, es decir variando x_0, y primero en el tiempo, entonces es un for de graficas y otro de x_0:

  int i;
  int j=0;
  for (i=0;i<num_graficas;i++){

    //Llenar posiciones iniciales
	
    xs[iter_tiempo*i]=x_0;
    ys[iter_tiempo*i]=y_0;

    t=dt;
       
    for (j=1;j<iter_tiempo;j++){

      //Ejecutar RungeKuttas que actualizan xs, ys
      RungeKuttaCuartoOrden_x(dt, xs, ys, i*iter_tiempo+j);
      RungeKuttaCuartoOrden_y(dt, xs, ys, i*iter_tiempo+j);

      //Avanzo en el tiempo
      t+=dt;
    }

    //Disminuyo en 1 x_0
    x_0-=1;
  }

  //Archivo
  //Voy a guardar en 1 archivo resultados.txt con el formato:
  //x y x y x y .... x y (para x_0=30, x_0=29, ... x_0=1) 

  FILE *f = fopen("resultados.txt", "w");

  int k;
  int l;
  for (l=0;l<iter_tiempo;l++){
    for (k=0;k<num_graficas;k++){    
      fprintf(f, "%f %f ", xs[iter_tiempo*k+l],ys[iter_tiempo*k+l]);
    }
    fprintf(f, "\n");
  }

  fclose(f);

  //Return 0
  return 0;
}

//FUNCIONES

//Funcion que me devuelve la primera derivada de x

float dxdt(float x, float y){
  return 20*x-x*y;
}

//Funcion que me devuelve la primera derivada de x

float dydt(float x, float y){
   return -30*y+x*y;
}

//RungeKuttas de cuarto orden en x,y

void RungeKuttaCuartoOrden_x(float dt, float *x, float *y, int indiceIteracionActual){

  float x_old;
  float x_new;
  float y_old;
  float x_1;	
  float x_2;
  float x_3;
  float y_1;	
  float y_2;
  float y_3;
  float k_0;
  float k_1;
  float k_2;
  float k_3;
  float prom_k;

  x_old=x[indiceIteracionActual-1];
  y_old=y[indiceIteracionActual-1];
  k_0 = dxdt(x_old,y_old);
    
  //primer paso
  x_1 = x_old + (dt/2);
  y_1 = y_old + (dt/2)*k_0;
  k_1 = dxdt(x_1, y_1);
    
  //segundo paso
  x_2 = x_old + (dt/2);
  y_2 = y_old + (dt/2)*k_1;
  k_2 = dxdt(x_2, y_2);
        
  //tercer paso
  x_3 = x_old + dt;
  y_3 = y_old + dt*k_2;
  k_3 = dxdt(x_3, y_3);
    
  //cuarto paso
  prom_k = (k_0 + 2*k_1 + 2*k_2 + k_3)/6;
    
  x_new=x_old+dt*prom_k;

  x[indiceIteracionActual] = x_new;
}

void RungeKuttaCuartoOrden_y(float dt, float *x, float *y, int indiceIteracionActual){

  float x_old;
  float y_old;
  float y_new;
  float x_1;	
  float x_2;
  float x_3;
  float y_1;	
  float y_2;
  float y_3;
  float k_0;
  float k_1;
  float k_2;
  float k_3;
  float prom_k;

  x_old=x[indiceIteracionActual-1];
  y_old=y[indiceIteracionActual-1];
  k_0 = dydt(x_old, y_old);
    
  //primer paso
  x_1 = x_old + (dt/2);
  y_1 = y_old + (dt/2)*k_0;
  k_1 = dydt(x_1, y_1);
    
  //segundo paso
  x_2 = x_old + (dt/2);
  y_2 = y_old + (dt/2)*k_1;
  k_2 = dydt(x_2, y_2);
        
  //tercer paso
  x_3 = x_old + dt;
  y_3 = y_old + dt*k_2;
  k_3 = dydt(x_3, y_3);
    
  //cuarto paso
  prom_k = (k_0 + 2*k_1 + 2*k_2 + k_3)/6;
    
  y_new=y_old+dt*prom_k;

  y[indiceIteracionActual] = y_new;
}
