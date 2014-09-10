#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define USAGE "Se usa asi: ./integralValorPi.x num_puntos"

float f(float x, float y);

int main(int argc, char **argv){

  float area=4;
  float area_adentro;
  int num_puntos;
  int num_puntos_adentro=0;
  int i;
  float valor;
  float *x;
  float *y;

  if(argc!=2){
    printf("%s",USAGE);
    exit(1);
  }

  num_puntos=atoi(argv[1]);

  x=malloc(num_puntos*sizeof(float));
  y=malloc(num_puntos*sizeof(float));
  
  srand48(time(NULL));

  for (i=0;i<num_puntos;i++){
    x[i]=(0.5-drand48())*2;
    y[i]=(0.5-drand48())*2;
    valor=f(x[i],y[i]);

    if(valor<=1){
      num_puntos_adentro++;
    }
  }

  area_adentro=area*num_puntos_adentro/num_puntos;
    
  printf("%s %f %s","El valor de pi es: ",area_adentro,"\n");

  return 0;
}

float f(float x, float y){
  return pow(x,2)+pow(y,2);
}
