#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv){
  
  int n=atoi(argv[1]);
  int m=atoi(argv[2]);
  FILE *archivo = fopen(argv[3], "r");

  if (archivo==0){
    printf("Hay un problema con el archivo \n");
    exit(1);
  }

  float max;
  float x;
  float matriz[n*m];
  int i;
  int j; 

  //Aca se meten todos los numeros en un arreglo de tamaño n*m

  for (i=0;i<n*m; i++){
    if(i%(n-1)!=0){
      fscanf(archivo, "%f /t", &(matriz[i]));
    }
    else{
      fscanf(archivo, "%f /n", &(matriz[i]));
    }
  }

  printf("%s \n", "El valor maximo para cada columna es:");

  //Aca se imprime el maximo de cada columna

  for(j=0;j<m; j++){
    max=0;
    x=0;
    for (i=j;i<n*m; i+=m){
      x=(float) matriz[i];
      if(x>max){
	max=x;
      }
    }
    if (j!=m-1){
      printf("%f \t", max);
    }
    else{
      printf("%f \n", max);
    }
  }
    
  fclose(archivo);
  
  return 0;
}
