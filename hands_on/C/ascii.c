#include<stdio.h>

int main(){

  int i;

  for (i=32;i<=126;i++){
    if('A'==i){
      printf("%d \n", i);
      break;
    }
  }
}
