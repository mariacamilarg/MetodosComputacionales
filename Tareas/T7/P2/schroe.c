#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define FLOAT double
#define PI  3.14159265359

/******************************************
 *Solucionar la ecuacion de Schroedinger 1D
 *dependiente del tiempo
 *Ver capitulo 18.6 de Landau, Paez, Bordeianu
 ******************************************/




/******************************************
 *Apartar memoria para n_points FLOAT
 ******************************************/

FLOAT *getmemory(int n_points){
  return malloc( n_points*sizeof(FLOAT) );
}


/******************************************
 * Copiar or en dest
 ******************************************/

void copy( FLOAT *dest, FLOAT *or , int length){
  
  int i;
  for( i = 0 ; i<length ; i++){
    dest[i] = or[i];
  }

}


/******************************************
 * Condiciones iniciales en u
 ******************************************/

void init(FLOAT *reu , FLOAT *imu ,FLOAT xi , FLOAT dx , FLOAT n_x){

  int i;
  FLOAT x = xi;
  for( i=0 ; i<n_x ; i++){
    reu[i] = exp( -(1/2.0)*pow( (1/0.05)*(x-5.0) , 2.0) )*cos(16.0*PI*x);
    imu[i] = exp( -(1/2.0)*pow( (1/0.05)*(x-5.0) , 2.0) )*sin(16.0*PI*x);
    x = x+dx;
  }

}

/******************************************
 * Potencial en un punto
 ******************************************/

FLOAT pot(FLOAT x){
  return (1/2.0)*pow( x , 2.0);
}

/******************************************
 * Solucionar e imprimir
 ******************************************/

void solve( FLOAT *reu_initial , FLOAT *imu_initial, FLOAT dt , 
	    FLOAT xi , FLOAT dx , int n_t , int n_x){


  int i;
  int j;
  FLOAT  x = xi;
/* Calcular potencial  */
  FLOAT *v = getmemory(n_x);
  for ( i=0 ; i<n_x ; i++){
    v[i] = pot(x);
    x = x + dx;
  }

/* Solucionar e imprimir */
  FLOAT *reu = reu_initial;
  FLOAT *imu = imu_initial;
  FLOAT *reu_future = getmemory(n_x);
  FLOAT *imu_future = getmemory(n_x);

  //condiciones de frontera
  reu[0] = 0.0; 
  imu[0] = 0.0;
  reu[n_x-1] = 0.0;
  imu[n_x-1] = 0.0;
  reu_future[0] = 0.0;
  reu_future[n_x-1] = 0.0;
  //Solucion 
  FLOAT alpha = dt/(2*pow( dx , 2.0));
  for( j=0 ; j<n_t ; j++){
 
    for( i=1 ; i<n_x-1 ; i++){
      reu_future[i] = reu[i] - 2*( alpha*(imu[i+1]+imu[i-1]) - 2*(alpha + v[i]*dt)*imu[i] );
      if( j%500 == 0 && i%10 ){//imprimir cada 1000dx y 100dt
      	printf("%f " , reu[i]*reu_future[i] + pow(imu[i],2));
      }
      /* printf("%f " , reu[i]*reu_future[i] + pow(imu[i],2)); */
    }
    /* printf("\n"); */
    if(j%100 == 0 ){//imprimir cada 100dt
      printf("\n");
    }
    for( i=1 ; i<n_x-1 ; i++){
      imu_future[i] = imu[i] + 2*( alpha*(reu_future[i+1]+reu_future[i-1]) - 2*(alpha + v[i]*dt)*reu_future[i] ); 
    }


    //actualizar tiempos
    copy( reu , reu_future , n_x );
    copy( imu , imu_future , n_x );
  }


}

/*****************************************
 *main
 *****************************************/
int main(){

/* variables */
  FLOAT xi = -80.0; 
  FLOAT xf = 80.0;
  int  n_x = 25000; 
  FLOAT dx = (xf-xi)/n_x;
  int n_t = 200000;
  FLOAT dt = (1/3.0)*pow(dx,2.0);
  FLOAT *reu = getmemory(n_x);//Parte real de la funcion
  FLOAT *imu = getmemory(n_x);//Parte imaginaria de la funcion
/* accion */
  init(reu , imu , xi, dx , n_x);
  solve(reu , imu , dt, xi ,  dx , n_t , n_x);

  return 0;
}
