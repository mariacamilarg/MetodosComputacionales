#include <stdio.h>
#include <stdlib.h>


int main(){
  FILE *in;
  float a[100];
  float b[100];
  int i;
  
  in= fopen("salida.dat", "r");

  if (in==0){
    printf("Problemow \n");
    exit(1);
  }

  for(i=0; i<100; i++){
    fscanf(in, "%f %f", &(a[i]), &(b[i]));
  }

  for(i=0; i<100; i++){
    printf("%f %f \n", a[i],b[i]);
  }

  fclose(in);

  return 0;
}
