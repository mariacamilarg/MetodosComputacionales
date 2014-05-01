#include <stdio.h>
#include <math.h>

int main(){
  float x;
  float y;

  for (x=0;x<=1;x+=0.01){
    y=sqrt(1-pow(x,2));
    printf("%f %f \n",x/2,y/2);
  }



  return 0;
}

