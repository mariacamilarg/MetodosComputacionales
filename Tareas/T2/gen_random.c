#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv){
  
  int n=atoi(argv[1]);
  int m=atoi(argv[2]);

  double x;
  int i;
  int j;
  
  FILE *archivo = fopen(argv[3], "w");

  srand48(time(NULL));

  for (i=0;i<n; i++){
    for (j=0;j<m;j++){
      x=(double) drand48();
      if(j!=m-1){
	fprintf(archivo, "%f \t", x);
      }
      else{
	fprintf(archivo, "%f", x);
      }
    }
    if(i!=n-1){
      fprintf(archivo, "%s", "\n");
    }
  }
  
    
  fclose(archivo);
  
  return 0;
}
