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

  float numero1;
  int pos1;
  float numero2;
  int pos2;
  float matriz[n*m];
  float nuevaMatriz[n*m];
  float columna1[2*n];
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

  //Hago un arreglo que tenga los numeros de la primera columna solos y su posición.

  for (i=0;i<n; i++){
    columna1[2*i]=matriz[i*m];
    columna1[2*i+1]=i;
  }

  //Hago un arreglo que tenga: (maximos ordenados, posicion del maximo en la columna) con el algoritmo de la burbuja

  for(i=n; i>0; i--){
    for(j=0; j<i-1; j++){
      numero1=columna1[2*j];
      pos1=columna1[2*j+1];
      numero2=columna1[2*j+2];
      pos2=columna1[2*j+3];
      
      //Si uno es mayor que el otro se intercambian

      if(numero1>numero2){
	columna1[2*j]=numero2;
	columna1[2*j+1]=pos2;
	columna1[2*j+2]=numero1;
	columna1[2*j+3]=pos1;
      }
    }
  }

  //Ya se la posicion entonces puedo armar el nuevo arreglo (max1, fila..., max2, fila..., ..., maxn, fila...) se llama nuevaMatriz
  
  int contador=0;
  int numFila;
  int suma1;
  
  for(i=0;i<n*m;i++){
    if(i%m==0){
      nuevaMatriz[i]=columna1[contador];
      numFila=columna1[contador+1];
      contador+=2;
      suma1=1;
    }
    else{
      nuevaMatriz[i]=matriz[numFila*m+suma1];
      suma1++;
    }
  }

  //Aca se imprime en pantalla la nuevaMatriz :D

  for (i=0;i<n*m; i++){
    if((i%m==0 && i!=0)){
      printf("%s", "\n");
    }
    printf("%f \t",nuevaMatriz[i]);
    if (i==n*m-1){
      printf("%s", "\n");
    }
  }

  return 0;

}
