#include <stdio.h>
#include <time.h>

int main(){
  float x;
  float y;
  float z;
  int i;

  srand(time(NULL));

  for (i=1;i<100;i++){
    x=(float) rand();
    y=(float) rand();
    z=(float) rand();
    printf("%f %f %f \n",x, y, z);
  }

  return 0;
}

