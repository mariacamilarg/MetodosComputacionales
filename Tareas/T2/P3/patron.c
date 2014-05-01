#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>

int main(){

  //----------FASE1----------
  
  int n=5;
  int m=pow(10,4);

  char *con1;
  char *con2;
  int max1=1;
  int max2=1;
  int num;
  int i;
  int j;
  char *arreglo;
  
  FILE *archivo = fopen("Vibrio_cholerae.txt", "r");
  FILE *concatenaciones = fopen("concatenaciones.txt", "w");

  arreglo=malloc((m+20)*sizeof(char));
  con1=malloc((n+20)*sizeof(char));
  con2=malloc((n+20)*sizeof(char));

  //Añado todas las letras a un arreglo de letras

  for (i=0;i<m; i++){
    fscanf(archivo, "%c", &(arreglo[i]));
  }

  //Creo un txt con todas las concatenaciones de n letras separadas por \n
  for (i=0;i<m-n+1;i++){
    if (i+n-1==m){
      break;
    }
    for(j=i;j<n+i;j++){
      fprintf(concatenaciones,"%c",arreglo[j]);
    }
    fprintf(concatenaciones,"\n");
  }

  fclose(concatenaciones);

  //----------FASE 2---------
   
  char *linea;
  char *linea2; 
  linea=malloc((n+20)*sizeof(char));
  linea2=malloc((n+20)*sizeof(char));

  if(!linea){
    fprintf(stderr, "problema!");
    exit(1);
  }

  FILE *leer = fopen("concatenaciones.txt", "r");  
  if(!leer){
    fprintf(stderr, "problem opening file\n");
    exit(1);
  }

  //Comparo todas para saber cual se repite mas
  for (i=0;i<m-n+1;i++){
    num=1;
    rewind(leer);

    for(j=0;j<i+1;j++){
      fscanf(leer, "%s\n",linea);
    }   

    for(j=i+1;j<m-n+1;j++){
      fscanf(leer, "%s\n",linea2);
      if(strcmp(linea, linea2)==0){
	num++;
      }
    }

    if(num>max1){
      max2=max1;
      strcpy(con2,con1);
      max1=num;
      strcpy(con1,linea);
    }

    else if(num>max2 && strcmp(linea, con1)!=0){
      max2=num;
      strcpy(con2,linea);
    }    
  }

  //Imprimo las dos que mas se repiten

  if(max2!=1){
    printf("Los dos patrones de %i bases consecutivas que mas se encuentren en las primeras %i bases del genoma de la Vibrio cholerae son:  %s (que sale %d veces) y %s (que sale %d veces)\n", n, m,con1,max1,con2,max2);
  }

  else if(max1!=1){
    printf("Solo hay un patron que se repite de %i bases consecutivas en las primeras %i bases del genoma de la Vibrio cholerae y es: %s\n", n, m, con1);
  }
  
  else{
    printf("No hay un patron que se repite de %i bases consecutivas en las primeras %i bases del genoma de la Vibrio cholerae :(\n", n, m);
  }

  fclose(archivo);
  fclose(concatenaciones);
  
  return 0;
}
