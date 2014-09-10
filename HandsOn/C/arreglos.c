#include<stdio.h>
#include<stdlib.h>

int main(){
  int *a;
  int i;
  int n_points=10000000;

  a = malloc(10000000*sizeof(int));

  for (i=0;i<n_points;i++){
    a[i]=2*i;
  }

  for (i=0;i<n_points;i++){
    printf("%d \n", a[i]);
  }
 

  return 0;
}
