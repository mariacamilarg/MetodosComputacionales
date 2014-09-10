#include<stdlib.h>
#include<stdio.h>
#include<math.h>
//Definiendo constantes universales
#define G_GRAV 0.000004302 //Units kpc (km/s)2 msun-1
#define Y2S 31556926 // conversion years to seconds 
#define KPC2AU 206264806 // kpc to UA 
#define AU2KM 149597871 // UA to Km
#define PI 3.141592653589793 
//Definiendo métodos necesarios
float * get_memory(int n_points);
float acceleration(char coor, float x, float y, float z,float xo, float yo, float zo, float M);
float velocity(char coor, float vx, float vy, float vz);
float runge_kutta(char dato, char coor, float xant, float yant, float zant, float vxant, float vyant, float vzant,float *xo, float *yo, float *zo, float *M, float dt, int negras);

//main
int main(int argc, char **argv){
  
  //verificando número de argumentos
  if(argc != 4){
    printf("El número de argumentos debe ser de 3");
    end(1);
  }
  int i;
  //Guardando argumentos
  char *filename = argv[1];
  float tiempo = atof(argv[2]);//miles de millones de años 
  int momentos = atoi(argv[3]);
  FILE *in;
  // Definiendo constantes del problema y alocando memoria
  int n_div = 1000; //Divisiones entre momentos
  float dt = tiempo*1000/(n_div*(momentos-1)); //Paso de tiempo en  millones de años
  int m = (momentos-1)*n_div; //Numero de muestras 
  float *M; //masa del centro de la galaxia en Msun
  float *xo;// Distancias en Kpc
  float *yo;
  float *zo;
  float *vxo;//Velocidades en km/s
  float *vyo;
  float *vzo;
  float *ID; 

  //definiendo posiciones y velocidades. Todas las masas estarán en un solo array
  float *x;
  float *y;
  float *z;
  float *vx;
  float *vy;
  float *vz;
  
  //Obteniendo condiciones iniciales del archivo
  float N; //Numero de masas incluyendo los centros de las galaxias
  in = fopen(filename, "r");
  fscanf(in, "%f", &N);
  fclose(in);
  N = 0-N;
  
  //Alocando memoria
  M = get_memory(2*N+2);
  xo = get_memory(2*N+2);
  yo = get_memory(2*N+2);
  zo = get_memory(2*N+2);
  vxo = get_memory(2*N+2);
  vyo = get_memory(2*N+2);
  vzo = get_memory(2*N+2);
  ID = get_memory(2*N*m+2*m); 
  x = get_memory(2*N*m+2*m);
  y = get_memory(2*N*m+2*m);
  z = get_memory(2*N*m+2*m);
  vx = get_memory(2*N*m+2*m);
  vy = get_memory(2*N*m+2*m);
  vz = get_memory(2*N*m+2*m);
  
  
  //obteniendo condiciones iniciales
  float test;
  in = fopen(filename, "r");
  i = 0;
  do{
    test = fscanf(in, "%f %f %f %f %f %f %f %f\n", &ID[i], &xo[i], &yo[i], &zo[i],&vxo[i],&vyo[i],&vzo[i], &M[i]);
    if(test > -1){
      i++;}
  }while(test != EOF);
  fclose(in);
  N = i;
  
  //Declarando arrays de masas negras
  float *Mn = get_memory(N); //masa en msun
  float *nxo = get_memory(N);//posicion inicial en kpc
  float *nyo = get_memory(N);
  float *nzo = get_memory(N);
  int negras = 0;
  
  for(i = 0; i < N; i++){
  
    if(M[i] != 0){
      Mn[i]= M[i];
      nxo[i]=  xo[i];
      nyo[i] = yo[i];
      nzo[i] = zo[i];
      negras ++;
    }

  }
  

  int j;
  
  //Realizando ciclo integración
  for(i = 0; i < m; i++){
    int k = 0;
    for(j = 0; j < N; j++){
      if(i == 0){

	x[j*m + i] = xo[j];
	y[j*m+i] = yo[j];
	z[j*m+i] = zo[j];
	vx[j*m+i] = vxo[j]*Y2S*1000000/(AU2KM*KPC2AU);//KPC/My
	vy[j*m+i] = vyo[j]*Y2S*1000000/(AU2KM*KPC2AU);
	vz[j*m+i] = vzo[j]*Y2S*1000000/(AU2KM*KPC2AU);
				  	   
	}
      else{
	x[j*m + i] = runge_kutta('d','x',x[j*m + i -1],y[j*m + i -1], z[j*m + i -1], vx[j*m + i -1], vy[j*m + i -1], vz[j*m + i -1], nxo,nyo,nzo, Mn, dt, negras);
	y[j*m + i] = runge_kutta('d','y',x[j*m + i -1],y[j*m + i -1], z[j*m + i -1], vx[j*m + i -1], vy[j*m + i -1], vz[j*m + i -1], nxo,nyo,nzo, Mn, dt, negras);
	z[j*m + i] = runge_kutta('d','z',x[j*m + i -1],y[j*m + i -1], z[j*m + i -1], vx[j*m + i -1], vy[j*m + i -1], vz[j*m + i -1], nxo,nyo,nzo, Mn, dt, negras);
	vx[j*m + i] = runge_kutta('v','x',x[j*m + i -1],y[j*m + i -1], z[j*m + i -1], vx[j*m + i -1], vy[j*m + i -1], vz[j*m + i -1], nxo,nyo,nzo, Mn, dt, negras);
	vy[j*m + i] = runge_kutta('v','y',x[j*m + i -1],y[j*m + i -1], z[j*m + i -1], vx[j*m + i -1], vy[j*m + i -1], vz[j*m + i -1], nxo,nyo,nzo, Mn, dt, negras);
	vz[j*m + i] = runge_kutta('v','z',x[j*m + i -1],y[j*m + i -1], z[j*m + i -1], vx[j*m + i -1], vy[j*m + i -1], vz[j*m + i -1], nxo,nyo,nzo, Mn, dt, negras);
	if(M[j] != 0){
	  nxo[k] = x[j*m + i];
	  nyo[k] = y[j*m + i];
	  nzo[k] = z[j*m + i];
	  }
	  }
    }
  }
  

  //Exportando resultados
  
 for(j = 0; j < momentos; j++){
   char str[200];
   char jc[20];
   sprintf(jc,"%d",j);
   strcpy(str,"resultado_galaxia_");
   strcat(str,jc);
   strcat(str,".txt");
   in = fopen(str,"w");
   for(i = 0; i < N; i++){
    fprintf(in, "%f ", ID[i]);
    fprintf(in, "%f ", x[i*m + j*n_div]); 
    fprintf(in, "%f ", y[i*m + j*n_div]);
    fprintf(in, "%f ", z[i*m + j*n_div]); 
    fprintf(in, "%f ", vx[i*m + j*n_div]); 
    fprintf(in, "%f ", vy[i*m + j*n_div]); 
    fprintf(in, "%f ", vz[i*m + j*n_div]); 
    fprintf(in,"\n");
   }
   fclose(in);
 }
  
 return 0;
  
}
//Metodo de reserva de memoria
float * get_memory(int n_points){
  float *x;
  if(!(x = malloc(sizeof(float)*n_points))){
    printf("Problem with memory allocation");
    
}
  return x;
}
//Metodo de aceleracion para runge kutta.Distancias en KPC, aceleraciones en KPC/My2
float acceleration(char coor, float x, float y, float z,float xo, float yo, float zo, float M){
  float c;
  float co;
  if(coor == 'x'){
    c = x;
    co = xo;}
  if(coor == 'y'){
    c = y;
    co = yo;}
  if(coor == 'z'){
    c = z;
    co = zo;}
  if(pow(x-xo,2)+pow(y-yo,2)+pow(z-zo,2) > 0){
    return -1*G_GRAV*M*(c-co)*pow(1000000,2)*(1/pow(AU2KM*KPC2AU,2))*(Y2S*Y2S)/pow(pow(x-xo,2)+pow(y-yo,2)+pow(z-zo,2),1.5);}
  else{return 0.0;}
}
// Metodo de velocidad para runge kutta. Sale con las unidades que entra. 
float velocity(char coor, float vx, float vy, float vz){
 float c;
  if(coor == 'x'){
    c = vx;}
  if(coor == 'y'){
    c = vy;}
  if(coor == 'z'){
    c = vz;}
  return c;
}
// Metodo de integracion.distancias en AU, velocidades en AU/My
float runge_kutta(char dato, char coor, float xant, float yant, float zant, float vxant, float vyant, float vzant,float *xo, float *yo, float *zo, float *M, float dt, int negras){
  
  float c;
  float vc;
  
  if(coor == 'x'){
    c = xant;
    vc = vxant;}
  
  if(coor == 'y'){
    c = yant;
    vc = vyant;}
  if(coor == 'z'){
    c = zant;
    vc = vzant;}
  //Declarando pendientes
  float k_1_v = 0;
  float k_1_a = 0;
  float k_2_v = 0;
  float k_2_a = 0;
  float k_3_v = 0;
  float k_3_a = 0;
  float k_4_v = 0;
  float k_4_a = 0;
  int i;

  //Paso 0
  k_1_v = velocity(coor, vxant, vyant, vzant);
  for(i = 0; i < negras; i++){
  k_1_a += acceleration(coor , xant,yant,zant,xo[i], yo[i], zo[i],M[i]);
  }
  //Paso 1
  c += dt/2*k_1_v;
  vc += k_1_a*dt/2;
  if(coor == 'x'){
    xant = c;
    vxant = vc;
    k_2_v = velocity(coor, vxant, vyant, vzant);
    for(i = 0; i < negras; i++){
      k_2_a += acceleration(coor , xant,yant,zant,xo[i], yo[i], zo[i],M[i]);
    } 
  }
  if(coor == 'y'){
    yant = c;
    vyant = vc;
    k_2_v = velocity(coor, vxant, vyant, vzant);
    for(i = 0; i < negras; i++){
      k_2_a += acceleration(coor , xant,yant,zant,xo[i], yo[i], zo[i],M[i]);
    } 
  }
  if(coor == 'z'){
    zant = c;
    vzant = vc;
    k_2_v = velocity(coor, vxant, vyant, vzant);
    for(i = 0; i < negras; i++){
      k_2_a += acceleration(coor , xant,yant,zant,xo[i], yo[i], zo[i],M[i]);
    } 
  }
  
  //Paso 2
  c += -dt/2*k_1_v + dt/2*k_2_v;
  vc += -k_1_a*dt/2 + dt/2*k_2_a;
  if(coor == 'x'){
    xant = c;
    vxant = vc;
    k_3_v = velocity(coor, vxant, vyant, vzant);
     for(i = 0; i < negras; i++){
      k_3_a += acceleration(coor , xant,yant,zant,xo[i], yo[i], zo[i],M[i]);
    } 
  }
  if(coor == 'y'){
    yant = c;
    vyant = vc;
    k_3_v = velocity(coor, vxant, vyant, vzant);
    for(i = 0; i < negras; i++){
      k_3_a += acceleration(coor , xant,yant,zant,xo[i], yo[i], zo[i],M[i]);
    } 
  }
  if(coor == 'z'){
    zant = c;
    vzant = vc;
    k_3_v = velocity(coor, vxant, vyant, vzant);
    for(i = 0; i < negras; i++){
      k_3_a += acceleration(coor , xant,yant,zant,xo[i], yo[i], zo[i],M[i]);
    } 
  }

  //Paso 3
  c += -dt/2*k_2_v + dt*k_3_v;
  vc += -k_2_a*dt/2 + dt*k_3_a;
  if(coor == 'x'){
    xant = c;
    vxant = vc;
    k_4_v = velocity(coor, vxant, vyant, vzant);
    for(i = 0; i < negras; i++){
      k_4_a += acceleration(coor , xant,yant,zant,xo[i], yo[i], zo[i],M[i]);
    } 
  }
  if(coor == 'y'){
    yant = c;
    vyant = vc;
    k_4_v = velocity(coor, vxant, vyant, vzant);
   for(i = 0; i < negras; i++){
      k_4_a += acceleration(coor , xant,yant,zant,xo[i], yo[i], zo[i],M[i]);
    } 
  }
  if(coor == 'z'){
    zant = c;
    vzant = vc;
    k_4_v = velocity(coor, vxant, vyant, vzant);
    for(i = 0; i < negras; i++){
      k_4_a += acceleration(coor , xant,yant,zant,xo[i], yo[i], zo[i],M[i]);
    } 
  }
  //Paso 4
  float k_v_average = (k_1_v+2*k_2_v+2*k_3_v+k_4_v)/6;
  float k_a_average = (k_1_a+2*k_2_a+2*k_3_a+k_4_a)/6;
 
  c += -dt*k_3_v + dt*k_v_average;
  vc += -k_3_a*dt + dt*k_a_average;
 
  if(dato == 'd'){
    return c;}
  else{return vc;}
  
}
