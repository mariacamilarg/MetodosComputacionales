#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float d2xdt2(float *masas, int num_masa, float *pos_x, float *pos_y, float *pos_z);
float d2ydt2(float *masas, int num_masa, float *pos_x, float *pos_y, float *pos_z);
float d2zdt2(float *masas, int num_masa, float *pos_x, float *pos_y, float *pos_z);
float dxdt(float vel_x);
float dydt(float vel_y);
float dzdt(float vel_z);
float energia(float m1, float m2, float m3, int num_masas, float *posx, float *posy, float *posz, float *velx, float *vely, float *velz);
void RungeKuttaCuartoOrden_x(float *masas, float num_masas, float t, float dt, float *x, float *y, float *z, float *x_p);
void RungeKuttaCuartoOrden_y(float *masas, float num_masas, float t, float dt, float *x, float *y, float *z, float *y_p);
void RungeKuttaCuartoOrden_z(float *masas, float num_masas, float t, float dt, float *x, float *y, float *z, float *z_p);

int main(){

  //Datos (en unidades astronomicas, masas solares y años):
  float G=39.38052;//ua**3 * m_solar**-1 * año **-2
  float R=100;
  float m=1;
  float tiempo=1000;
  float dt=0.1; //para mas precision se disminuye
  int num_posiciones=(int)tiempo/dt;
  int num_masas=3;

  //Posiciones
  float *xs=malloc(sizeof(float)*num_masas);
  float *ys=malloc(sizeof(float)*num_masas);
  float *zs=malloc(sizeof(float)*num_masas);
  
  //Velocidades
  float *vxs=malloc(sizeof(float)*num_masas);
  float *vys=malloc(sizeof(float)*num_masas);
  float *vzs=malloc(sizeof(float)*num_masas);

  //Masas
  float *masas=malloc(sizeof(float)*num_masas);
  masas[0]=m;
  masas[1]=m;
  masas[2]=m;

  //Los ubico en el plano x,y,z - Posiciones y Velocidades Iniciales

  float mag_v=sqrt(11*G*m/(sqrt(27)*R));

  ///Masa 1
  xs[0]=0;
  ys[0]=R;
  zs[0]=0;
  vxs[0]=-mag_v;
  vys[0]=0;
  vzs[0]=0;

  ///Masa 2
  xs[1]=-R*sqrt(3)/2;
  ys[1]=-R/2;
  zs[1]=0;
  vxs[1]=mag_v*sqrt(3)/2;
  vys[1]=-mag_v/2;
  vzs[1]=0;

  ///Masa 3
  xs[2]=R*sqrt(3)/2;
  ys[2]=-R/2;
  zs[2]=0;
  vxs[2]=mag_v*sqrt(3)/2;
  vys[2]=mag_v/2;
  vzs[2]=0;
  
  //Arreglos que guardan toda la trayectoria, la energia y el tiempo

  //guardan x1m1,x1m2,x1m3,x2m1,x2m2,x2m3,....
  float *pos_x=malloc(sizeof(float)*3*num_posiciones);
  float *pos_y=malloc(sizeof(float)*3*num_posiciones);
  float *pos_z=malloc(sizeof(float)*3*num_posiciones);

  //relleno con posiciones iniciales
  int j;
  for (j=0;j<num_masas;j++){
    pos_x[j]=xs[j];
    pos_y[j]=ys[j];
    pos_z[j]=zs[j];
  }

  float *energias=malloc(sizeof(float)*num_posiciones);
  float *tiempos=malloc(sizeof(float)*num_posiciones);

  //Energia y tiempo inicial

  energias[0]=energia(masas[0], masas[1], masas[2], num_masas, xs, ys, zs, vxs, vys, vzs);
  tiempos[0]=0;

  //Ahora a iterar

  float t=dt;
  int cont;
  for (cont=1;cont<num_posiciones;cont++){

    //la idea es iterar en el tiempo, hallar la fuerza en cada masa usando los arreglos xs,ys y zs que guardan la informacion de ellas 
    //y la van cambiando a medida que el tiempo avanza. Quiero guardar el avance de las posiciones en otros arreglos pos_x, pos_y, pos_Z

    //Recibir valor de RungeKuttas
    RungeKuttaCuartoOrden_x(masas, num_masas, t, dt, xs, ys, zs, vxs);
    RungeKuttaCuartoOrden_y(masas, num_masas, t, dt, xs, ys, zs, vys);
    RungeKuttaCuartoOrden_z(masas, num_masas, t, dt, xs, ys, zs, vzs);

    //Actualizar posiciones (lista grande)
    int i;
    for (i=0;i<num_masas;i++){
      pos_x[i+3*cont]=xs[i];
      pos_y[i+3*cont]=ys[i];
      pos_z[i+3*cont]=zs[i];
    }

    //Actualizar energias
    energias[cont]=energia(masas[0], masas[1], masas[2], num_masas, xs, ys, zs, vxs, vys, vzs);

    //Actualizar tiempos
    tiempos[cont]=t;

    //Avance en tiempo
    t+=dt;
  }

  //Voy a guardar en 2 archivos .dat con el formato:
  //tiempo  energia 
  //tiempo  x1   y1   z1   x2   y2   z2   x3   y3   z3

  FILE *f_et = fopen("energia_tiempo.dat", "w");
  FILE *f_pt = fopen("posicion_tiempo.dat", "w");

  int k;

  for (k=0;k<num_posiciones;k++){
   
    fprintf(f_et, "%f %f\n", tiempos[k],energias[k]);
    fprintf(f_pt, "%f %f %f %f %f %f %f %f %f %f\n", tiempos[k],pos_x[3*k],pos_y[3*k],pos_z[3*k],pos_x[3*k+1],pos_y[3*k+1],pos_z[3*k+1],pos_x[3*k+2],pos_y[3*k+2],pos_z[3*k+2]);
  }

  fclose(f_et);
  fclose(f_pt);

  return 0;
}

//FUNCIONES

//Funcion que calcula la segunda derivada de x_n contra el tiempo. Donde n es el num de la masa (1,2,3)

float d2xdt2(float *masas, int num_masa, float *pos_x, float *pos_y, float *pos_z){

  float G=39.38052;

  if(num_masa==1){
    float d_21=G*masas[1]*(pos_x[1]-pos_x[0])/pow( sqrt( pow(pos_x[1]-pos_x[0],2)+pow(pos_y[1]-pos_y[0],2)+pow(pos_z[1]-pos_z[0],2) ),3);
    float d_31=G*masas[2]*(pos_x[2]-pos_x[0])/pow( sqrt( pow(pos_x[2]-pos_x[0],2)+pow(pos_y[2]-pos_y[0],2)+pow(pos_z[2]-pos_z[0],2) ),3);
    return d_21 + d_31;
  }
  else if(num_masa==2){
    float d_12=G*masas[0]*(pos_x[0]-pos_x[1])/pow( sqrt( pow(pos_x[1]-pos_x[0],2)+pow(pos_y[1]-pos_y[0],2)+pow(pos_z[1]-pos_z[0],2) ),3);
    float d_32=G*masas[2]*(pos_x[2]-pos_x[1])/pow( sqrt( pow(pos_x[2]-pos_x[1],2)+pow(pos_y[2]-pos_y[1],2)+pow(pos_z[2]-pos_z[1],2) ),3);
    return d_12 + d_32;
  }
  else{
    float d_13=G*masas[0]*(pos_x[0]-pos_x[2])/pow( sqrt( pow(pos_x[2]-pos_x[0],2)+pow(pos_y[2]-pos_y[0],2)+pow(pos_z[2]-pos_z[0],2) ),3);
    float d_23=G*masas[1]*(pos_x[1]-pos_x[2])/pow( sqrt( pow(pos_x[2]-pos_x[1],2)+pow(pos_y[2]-pos_y[1],2)+pow(pos_z[2]-pos_z[1],2) ),3);
    return d_13 + d_23;
  }
}

//Funcion que calcula la segunda derivada de y_n contra el tiempo. Donde n es el num de la masa (1,2,3)

float d2ydt2(float *masas, int num_masa, float *pos_x, float *pos_y, float *pos_z){

  float G=39.38052;

  if(num_masa==1){
    float d_21=G*masas[1]*(pos_y[1]-pos_y[0])/pow( sqrt( pow(pos_x[1]-pos_x[0],2)+pow(pos_y[1]-pos_y[0],2)+pow(pos_z[1]-pos_z[0],2) ),3);
    float d_31=G*masas[2]*(pos_y[2]-pos_y[0])/pow( sqrt( pow(pos_x[2]-pos_x[0],2)+pow(pos_y[2]-pos_y[0],2)+pow(pos_z[2]-pos_z[0],2) ),3);
    return d_21 + d_31; 
  }
  else if(num_masa==2){
    float d_12=G*masas[0]*(pos_y[0]-pos_y[1])/pow( sqrt( pow(pos_x[1]-pos_x[0],2)+pow(pos_y[1]-pos_y[0],2)+pow(pos_z[1]-pos_z[0],2) ),3);
    float d_32=G*masas[2]*(pos_y[2]-pos_y[1])/pow( sqrt( pow(pos_x[2]-pos_x[1],2)+pow(pos_y[2]-pos_y[1],2)+pow(pos_z[2]-pos_z[1],2) ),3);
    return d_12 + d_32;
  }
  else{
    float d_13=G*masas[0]*(pos_y[0]-pos_y[2])/pow( sqrt( pow(pos_x[2]-pos_x[0],2)+pow(pos_y[2]-pos_y[0],2)+pow(pos_z[2]-pos_z[0],2) ),3);
    float d_23=G*masas[1]*(pos_y[1]-pos_y[2])/pow( sqrt( pow(pos_x[2]-pos_x[1],2)+pow(pos_y[2]-pos_y[1],2)+pow(pos_z[2]-pos_z[1],2) ),3);
    return d_13 + d_23;
  }
}

//Funcion que calcula la segunda derivada de z_n contra el tiempo. Donde n es el num de la masa (1,2,3)

float d2zdt2(float *masas,int num_masa, float *pos_x, float *pos_y, float *pos_z){

  float G=39.38052;

  if(num_masa==1){
    float d_21=G*masas[1]*(pos_z[1]-pos_z[0])/pow( sqrt( pow(pos_x[1]-pos_x[0],2)+pow(pos_y[1]-pos_y[0],2)+pow(pos_z[1]-pos_z[0],2) ),3);
    float d_31=G*masas[2]*(pos_z[2]-pos_z[0])/pow( sqrt( pow(pos_x[2]-pos_x[0],2)+pow(pos_y[2]-pos_y[0],2)+pow(pos_z[2]-pos_z[0],2) ),3);
    return d_21 + d_31;
  }
  else if(num_masa==2){
    float d_12=G*masas[0]*(pos_z[0]-pos_z[1])/pow( sqrt( pow(pos_x[1]-pos_x[0],2)+pow(pos_y[1]-pos_y[0],2)+pow(pos_z[1]-pos_z[0],2) ),3);
    float d_32=G*masas[2]*(pos_z[2]-pos_z[1])/pow( sqrt( pow(pos_x[2]-pos_x[1],2)+pow(pos_y[2]-pos_y[1],2)+pow(pos_z[2]-pos_z[1],2) ),3);
    return d_12 + d_32;
  }
  else{
    float d_13=G*masas[0]*(pos_z[0]-pos_z[2])/pow( sqrt( pow(pos_x[2]-pos_x[0],2)+pow(pos_y[2]-pos_y[0],2)+pow(pos_z[2]-pos_z[0],2) ),3);
    float d_23=G*masas[1]*(pos_z[1]-pos_z[2])/pow( sqrt( pow(pos_x[2]-pos_x[1],2)+pow(pos_y[2]-pos_y[1],2)+pow(pos_z[2]-pos_z[1],2) ),3);
    return d_13 + d_23;
  }
}

//Funcion que me devuelve la velocidad en x

float dxdt(float vel_x){
  return vel_x;
}

//Funcion que me devuelve la velocidad en y

float dydt(float vel_y){
  return vel_y;
}

//Funcion que me devuelve la velocidad en z

float dzdt(float vel_z){
  return vel_z;
}

//Funcion que calcula la energia del sistema a partir de sus posiciones y velocidades

float energia(float m1, float m2, float m3, int num_masas, float *posx, float *posy, float *posz, float *velx, float *vely, float *velz){
  
  float G=39.38052;

  float d_12=sqrt(pow(posx[0]-posx[1],2)+pow(posy[0]-posy[1],2)+pow(posz[0]-posz[1],2));
  float d_23=sqrt(pow(posx[1]-posx[2],2)+pow(posy[1]-posy[2],2)+pow(posz[1]-posz[2],2));
  float d_31=sqrt(pow(posx[2]-posx[0],2)+pow(posy[2]-posy[0],2)+pow(posz[2]-posz[0],2));

  float E_potencial=-G*(m1*m2/d_12 + m2*m3/d_23 + m3*m1/d_31);
    
  float v_1=pow(velx[0],2)+pow(vely[0],2)+pow(velz[0],2);
  float v_2=pow(velx[1],2)+pow(vely[1],2)+pow(velz[1],2);
  float v_3=pow(velx[2],2)+pow(vely[2],2)+pow(velz[2],2);

  float E_cinetica=0.5*(m1*v_1+m2*v_2+m3*v_3);

  return E_potencial+E_cinetica;
}

//RungeKuttas de cuarto orden en x,y,z

void RungeKuttaCuartoOrden_x(float *masas, float num_masas, float t, float dt, float *x, float *y, float *z, float *x_p){
  
  int i;
  float x_old;
  float x_new;
  float v_old;
  float v_new;
  float kv_0;
  float kv_1;
  float kv_2;
  float kv_3;
  float ka_0;
  float ka_1;
  float ka_2;
  float ka_3;
  float prom_kv;
  float prom_ka;
  float v_1;
  float v_2;
  float v_3;

  for(i=0;i<num_masas;i++){

    x_old=x[i];
    v_old=x_p[i];

    //k1 y k2 iniciales
    kv_0=dxdt(x_p[i]);
    ka_0=d2xdt2(masas,i+1, x, y, z);
    
    //primer paso
    v_1=v_old+ka_0*dt/2;
    kv_1=dxdt(v_1);
    ka_1=d2xdt2(masas,i+1, x, y, z);

    //segundo paso
    v_2=v_old+ka_1*dt/2;
    kv_2=dxdt(v_2);
    ka_2=d2xdt2(masas,i+1, x, y, z);

    //tercer paso
    v_3=v_old+ka_2*dt;
    kv_3=dxdt(v_3);
    ka_3=d2xdt2(masas,i+1, x, y, z);

    //cuarto paso
    prom_kv=(kv_0+2*kv_1+2*kv_2+kv_3)/6;
    prom_ka=(ka_0+2*ka_1+2*ka_2+ka_3)/6;

    x_new=x_old+prom_kv*dt;
    v_new=v_old+prom_ka*dt;

    x[i]=x_new;
    x_p[i]=v_new;
  }
}

void RungeKuttaCuartoOrden_y(float *masas,float num_masas, float t, float dt, float *x, float *y, float *z, float *y_p){
  
  int i;
  float y_old;
  float y_new;
  float v_old;
  float v_new;
  float kv_0;
  float kv_1;
  float kv_2;
  float kv_3;
  float ka_0;
  float ka_1;
  float ka_2;
  float ka_3;
  float prom_kv;
  float prom_ka;
  float v_1;
  float v_2;
  float v_3;

  for(i=0;i<num_masas;i++){

    y_old=y[i];
    v_old=y_p[i];

    //k1 y k2 iniciales
    kv_0=dydt(y_p[i]);
    ka_0=d2ydt2(masas,i+1, x, y, z);
    
    //primer paso
    v_1=v_old+ka_0*dt/2;
    kv_1=dydt(v_1);
    ka_1=d2ydt2(masas,i+1, x, y, z);

    //segundo paso
    v_2=v_old+ka_1*dt/2;
    kv_2=dydt(v_2);
    ka_2=d2ydt2(masas,i+1, x, y, z);

    //tercer paso
    v_3=v_old+ka_2*dt;
    kv_3=dydt(v_3);
    ka_3=d2ydt2(masas,i+1, x, y, z);

    //cuarto paso
    prom_kv=(kv_0+2*kv_1+2*kv_2+kv_3)/6;
    prom_ka=(ka_0+2*ka_1+2*ka_2+ka_3)/6;

    y_new=y_old+prom_kv*dt;
    v_new=v_old+prom_ka*dt;

    y[i]=y_new;
    y_p[i]=v_new;
  }
}

void RungeKuttaCuartoOrden_z(float *masas, float num_masas, float t, float dt, float *x, float *y, float *z, float *z_p){
  
  int i;
  float z_old;
  float z_new;
  float v_old;
  float v_new;
  float kv_0;
  float kv_1;
  float kv_2;
  float kv_3;
  float ka_0;
  float ka_1;
  float ka_2;
  float ka_3;
  float prom_kv;
  float prom_ka;
  float v_1;
  float v_2;
  float v_3;

  for(i=0;i<num_masas;i++){

    z_old=z[i];
    v_old=z_p[i];

    //k1 y k2 iniciales
    kv_0=dzdt(z_p[i]);
    ka_0=d2zdt2(masas,i+1, x, y, z);
    
    //primer paso
    v_1=v_old+ka_0*dt/2;
    kv_1=dzdt(v_1);
    ka_1=d2zdt2(masas,i+1, x, y, z);

    //segundo paso
    v_2=v_old+ka_1*dt/2;
    kv_2=dzdt(v_2);
    ka_2=d2zdt2(masas,i+1, x, y, z);

    //tercer paso
    v_3=v_old+ka_2*dt;
    kv_3=dzdt(v_3);
    ka_3=d2zdt2(masas,i+1, x, y, z);

    //cuarto paso
    prom_kv=(kv_0+2*kv_1+2*kv_2+kv_3)/6;
    prom_ka=(ka_0+2*ka_1+2*ka_2+ka_3)/6;

    z_new=z_old+prom_kv*dt;
    v_new=v_old+prom_ka*dt;

    z[i]=z_new;
    z_p[i]=v_new;
  }
}
