#include<math.h>
#include<stdlib.h>
#include<stdio.h>
//Definiendo constantes universales
#define G_GRAV 0.000004302 //Units kpc (km/s)2 msun-1
#define Y2S 31556926 // conversion years to seconds 
#define KPC2AU 206264806 // kpc to UA 
#define AU2KM 149597871 // UA to Km
#define PI 3.141592653589793 
//Definiendo métodos necesarios
float * get_memory(int n_points);
//Main
int main(int argc, char **argv){
  //Verificando el número de argumentos
  if(argc != 10){
    printf("El número de argumentos es de %i y debe ser 9",argc - 1);
    end(1);
  }
  //Convirtiendo los argumentos y definiendo constantes del problema
  //Posiciones y velocidades iniciales centro galaxia en kpc, velocidades en km/s
  float xo = atof(argv[1]);
  float yo = atof(argv[2]);
  float zo = atof(argv[3]);
  float vxo = atof(argv[4]);
  float vyo = atof(argv[5]);
  float vzo = atof(argv[6]);
  //Dimensiones galaxia
  float M = atof(argv[7]); // Masa del centro de la galaxia en msun
  float R = atof(argv[8]); // Radio de la galaxia en kpc
  float N = atoi(argv[9]); // Número de estrellas en la galaxia

  //Creando arrays y reservando memoria
  float *x = get_memory(N);
  float *y = get_memory(N);
  float *z = get_memory(N);
  float *vx = get_memory(N);
  float *vy = get_memory(N);
  float *vz = get_memory(N);
  //inicializando posiciones y velocidades
  int i;
  for(i = 0; i < N; i++){
    //Definiendo geometría
    float theta = drand48()*2*PI;
    float r = drand48()*(R-R/100);
    //Inicializando posición en unidades de kpc 
    x[i] = xo + r*cos(theta);
    y[i] = yo + r*sin(theta);
    z[i] = zo;
    //Inicializando velocidad en unidades de km/s 
    float V = sqrt(G_GRAV*M/r);
    vx[i] = vxo - V*sin(theta);
    vy[i] = vyo + V*cos(theta);
    vz[i] = vzo;
  }
  //Escribiendo datos
  FILE *in;
  //Escribiendo centro de la galaxia
  char archivo[200];
  char convert[20];
  sprintf(convert, "%i",(int)(vyo));
  strcpy(archivo, "condiciones_galaxia_");
  strcat(archivo, convert);
  strcat(archivo, ".txt");
  in = fopen(archivo, "w");
  fprintf(in,"%f %f %f %f %f %f %f %f\n",-N,xo, yo,zo,vxo,vyo,vzo, M);
  //Escribiendo datos masas
  for(i = 0; i < N; i++){
    fprintf(in,"%i %f %f %f %f %f %f %f\n", i+1, x[i],y[i],z[i],vx[i],vy[i],vz[i],0.0);
  } 
  //cerrando archivo
  fclose(in);
  return 0;
}
float * get_memory(int n_points){
  float *x;
  if(!(x = malloc(sizeof(float)*n_points))){
    printf("Probleam with memory allocation");
}
  return x;
}
