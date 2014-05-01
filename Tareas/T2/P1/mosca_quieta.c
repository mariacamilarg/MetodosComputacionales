#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){

  //Todos los datos estan con unidades del SI
 
  double R=0.3;
  double x_max=200/9;

  //Coordenadas 

  double x;
  double y;
  double t;

  //Se crea el archivo

  FILE *archivo = fopen("mosca_quieta.txt", "w");

  //Se avanza hasta que haya pasado 1 seg, es decir x_max y se imprime en el txt

  t=0;

  do{
    x=R*(t-sin(t));
    y=R*(1-cos(t));
    t+=0.01;

    fprintf(archivo, "%f\t%f \n",x,y);
  }while(x<x_max);

  
  //Se cierra el archivo
    
  fclose(archivo);
  
  return 0;
}
