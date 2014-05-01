#include <stdio.h>

int main(){
  FILE * in;
  int c;
  int numlineas;
  int numcaracteres;
  in = fopen("ascii.c", "r");
  numlineas=0;
  numcaracteres=0;

  do{
    c = fgetc(in);
    printf("%d \n", c);
    if(c==-1){
      break;
    }
    if(c=='\n'){
      numlineas++;
    }
    numcaracteres++;
  }while(c!=EOF);
  
  printf("El numero de lineas es: %d \n", numlineas);
  printf("El numero de lineascaracteres es: %d \n", numcaracteres);

  fclose(in);
  return 0;
}
