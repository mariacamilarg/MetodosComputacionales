#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float dydx(float y);

int main(){
  float x_min=0;
  float x_max=1;
  int num_puntos=int((x_min-x_max)*1000);
  
  float *xs=malloc(sizeof(float)*num_puntos);
  float *ys=malloc(sizeof(float)*num_puntos);

  int i=0;

  for (i=0;i<num_puntos;++){



  }



  return 0;
}

float dydx(float y){
  return 1+pow(y,2);
}

