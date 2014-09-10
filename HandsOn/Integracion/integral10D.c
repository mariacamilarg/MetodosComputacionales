#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define USAGE "Se usa asi: ./integral10D.x num_puntos semilla(int_aleatorio)"

float f(float *xs);

int main(int argc, char **argv){

  int num_puntos;
  int seed;
  int i;
  int j;
  float valor=0;
  float *xs;

  if(argc!=3){
    printf("%s",USAGE);
    exit(1);
  }

  num_puntos=atoi(argv[1]);
  seed=atoi(argv[2]);

  xs=malloc(10*sizeof(float));
  
  srand48(seed);

  for (i=0;i<num_puntos;i++){  
  
    //Lleno xs con numeros entre 0 y 1
    for (j=0;j<10;j++){
      xs[j]=drand48();
    }

    valor+=f(xs);
  }

  valor=valor/num_puntos;
    
  printf("%f %s",valor,"\n");

  return 0;
}

float f(float *xs){
  
  float res=0;
  int i;

  for(i=0;i<10;i++){
    res+=xs[i];
  }

  return pow(res,2);
}
