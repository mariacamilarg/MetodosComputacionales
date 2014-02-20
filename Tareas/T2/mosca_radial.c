#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){

  //Todos los datos estan con unidades del SI
 
  double R=0.3;
  double x_max=200/9;
  double v=200/9;
  double v_mosca=0.3;
  double delta_t=0.01;

  //Coordenadas 

  double x;
  double y;
  double t;
  double tiempo;
  double aumento_tiempo;
  double dx_centro;
  double x_centro;
  double x_centro2;
  double y_centro=R;
  double y_sig;
  double teta;
  double tanteta;
  double nx;
  double ny;
  double num;

  //Se crea el archivo

  FILE *archivo = fopen("mosca_radial.txt", "w");

  //Se halla dependiendo del delta_t el aumento del tiempo (t no es tiempo trancurrido sino la variable para aumentar precision)
 
  t=delta_t;
  x=R*(t-sin(t));
  y=R*(1-cos(t));
  dx_centro=sqrt(pow(R,2)-pow(y-R,2));
  x_centro=x+dx_centro;
    
  t=2*delta_t;
  x=R*(t-sin(t));
  y=R*(1-cos(t));
  dx_centro=sqrt(pow(R,2)-pow(y-R,2));
  x_centro2=x+dx_centro;  
  
  aumento_tiempo=(x_centro2-x_centro)/v;

 //Se avanza hasta que haya pasado 1 seg, es decir x_max y se imprime en el txt

  t=0;
  tiempo=0;
  x_centro=0;

  do{
    x=R*(t-sin(t));
    y=R*(1-cos(t));

    teta=(1.5)*3.14159265-v*tiempo/R;

    nx=x-v_mosca*tiempo*cos(teta);
    ny=y-v_mosca*tiempo*sin(teta);

    t+=delta_t;
    tiempo+=aumento_tiempo;  

    fprintf(archivo, "%f\t%f \n",nx,ny);

  }while(x<x_max && R>=0);

  //Se cierra el archivo
    
  fclose(archivo);
  
  return 0;
}
