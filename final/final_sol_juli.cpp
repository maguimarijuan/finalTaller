#include "bits/stdc++.h"
using namespace std;

/* Precondiciones mias y de enunciado*/
const int MAX_LONG_ID = 100;
const int MAX_ATAQUES = 1000;
const int CANTIDAD_PERSONAJES = 1;
const float ALTURA_INICIAL = 0;
const float VIDA_INICIAL = 100.0;

const int letraA = 65;
const int letraD = 68;
const int letraN = 78;
const int letraS = 83;

/* Definiciones de structs */

typedef struct{
  float Xpi;
  float Ypi;
  float Xpd;
  float Ypd;
  float vida;
}Personaje;

typedef struct{
  char id[MAX_LONG_ID];
  float x;
  float y;
  int energia;
  char accion[2];
}Ataque;

/* Lectura de ambos archivos */

int lecturaPersonaje(Personaje* personaje){
  int i=0;
  FILE* file;

  file = fopen("personajes.txt","r");

  for(;!feof(file);i++){
    fscanf(
      file,
      "%f %f %f",
      &personaje[0].Xpi,
      &personaje[0].Xpd,
      &personaje[0].Ypd);
  }

  fclose(file);
  //Solo como una validacion de que el archivo tiene un solo personaje
  return i;
}

int lecturaAtaques(Ataque* ataques){
  int i=0;
  FILE* file;

  file = fopen("ataques.txt","r");

  for(;!feof(file);i++){
    fscanf(
      file,
      "%s %f %f %d %s",
      ataques[i].id,
      &ataques[i].x,
      &ataques[i].y,
      &ataques[i].energia,
      ataques[i].accion);
  }
  fclose(file);

  return i;
}


/*Seteo condiciones iniciales
 faltantes en el archivo, del personaje*/
void completarPersonaje(Personaje* personaje){
  personaje[0].vida = VIDA_INICIAL;
  personaje[0].Ypi = ALTURA_INICIAL;
}


/* Proceso todo */
void procesarAtaques(Personaje* personaje, Ataque* ataques, int numAtaques){
  Personaje p = personaje[0];
  for(int i = 0; i<numAtaques; i++){
    Ataque a = ataques[i];

    float auxXpi=p.Xpi;
    float auxYpi=p.Ypi;
    float auxYpd=p.Ypd;

    if(a.accion[0]==letraA)
      auxYpd-= 20;

    if(a.accion[0]==letraD)
      auxXpi+= 10;

    if(a.accion[0]==letraS){
      auxYpi+=13;
      auxYpd+=13;
    }

    if(auxYpi<=a.y && a.y<=auxYpd &&p.vida>0){
      //Hubo impacto
      float distancia = auxXpi-a.x;
      p.vida-= a.energia;
      printf("%s\t\t\t%.3f\t\t\t%.3f\n", ataques[i].id, distancia, p.vida );

    }
    else{
      printf("%s\t\t\tNO TOCO\n", ataques[i].id);
    }

  }

}




int main(int argc, char* argv[]){

  Personaje personaje[CANTIDAD_PERSONAJES];
  Ataque ataques[MAX_ATAQUES];

  lecturaPersonaje(personaje);
  completarPersonaje(personaje);

  int numAtaques = lecturaAtaques(ataques)-1;
  //Lo hago para sacar la linea de mas que me agrega atom al txt

  // header para stdout
  printf("ID_ATAQUE\t\tDISTANCIA\t\tVIDA_REST\n");
  procesarAtaques(personaje, ataques, numAtaques);

  return 0;
}
