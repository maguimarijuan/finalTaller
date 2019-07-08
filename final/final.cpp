
#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <string>
#include "math.h"
#include <bits/stdc++.h>

using namespace std;

typedef struct
{
  float xpi;
  float ypi;
  float xpd;
  float ypd;
  int energia;
}Personaje;

typedef struct{
  char id [20];
  float x;
  float y;
  int energia;
  char accion [20];
} Ataque;

typedef struct{
  char id [20];
  float distancia;
  int energia;
} Resultado;

Personaje  leerArchivoJugador(std::string nombreArchivo)
{

  FILE* archivo = fopen(nombreArchivo.c_str(), "r");
  Personaje aux;
  float xpi;
  float xpd;
  float ypd;
  fscanf(archivo,"%f %f %f", &aux.xpi, &aux.xpd, &aux.ypd);
  aux.ypi = 0;
  aux.energia = 100;

  fclose(archivo);
  return(aux);
}

int leerArchivosAtaques(std::string nombreArchivo, Ataque* ataques)
{
  FILE* archivo = fopen(nombreArchivo.c_str(), "r");
  int i = 0;
  while(!feof(archivo)){
    fscanf(archivo,"%s %f %f %d %s",ataques[i].id , &ataques[i].x, &ataques[i].y, &ataques[i].energia, ataques[i].accion);
    i++;
  }
  fclose(archivo);
  return i;
}

int  gameloop(Ataque* ataques, Personaje personaje,
   int cantidadDeAtaques, Resultado* resultados)
{


  int i;
  for(i = 0; i < cantidadDeAtaques-1; i++)
  {
    bool huboColision = false;
    bool estaVivo= true;
    float xpi_personaje = personaje.xpi;
    float ypi_personaje = personaje.ypi;
    float xpd_personaje = personaje.xpd;
    float ypd_personaje = personaje.ypd;
    int energia = personaje.energia;

    if(energia < 0) estaVivo = false;

    char* accion = ataques[i].accion;
    float y_ataque = ataques[i].y;
    float x_ataque = ataques[i].x;
    char* id_ataque = ataques[i].id;
    int energia_ataque = ataques[i].energia;

    if(strcmp(accion, "A") == 0)
    {
      ypd_personaje -= 20;
    }
    if(strcmp(accion, "S") == 0)
    {
      ypi_personaje += 13;
      ypd_personaje += 13;
    }
    if(strcmp(accion, "D") == 0){
      xpi_personaje += 10;
    }
    if(y_ataque <= ypd_personaje && y_ataque >= ypi_personaje) huboColision = true;


    if(huboColision && estaVivo){
      strcpy(resultados[i].id ,ataques[i].id);
      float distancia = xpi_personaje - x_ataque;
      if (distancia < 0) distancia *= -1;
      resultados[i].distancia = distancia;
      personaje.energia = energia - energia_ataque;
      resultados[i].energia = personaje.energia;
    }
    if(!huboColision || !estaVivo)
    {
      strcpy(resultados[i].id,ataques[i].id);
      resultados[i].distancia = -1;
      resultados[i].energia = energia;
    }
  }
  return i;
}
int main()
{

  Ataque ataques[20];
  Personaje personaje = leerArchivoJugador("personajes.txt");
  int cantidadDeAtaques = leerArchivosAtaques("ataques.txt", ataques);

  Resultado resultados[20];
  int cantidadDeResultados = gameloop(ataques, personaje, cantidadDeAtaques, resultados);

  for(int i = 0; i < cantidadDeResultados; i++){
    if (resultados[i].distancia == -1){
      cout<<resultados[i].id << "\t\t"<< "NO TOCO" << "\t\t" << resultados[i].energia << endl;
    }
    else{
      cout<<resultados[i].id << "\t\t"<< resultados[i].distancia << "\t\t" << resultados[i].energia << endl;
    }
  }
  return 0;
}
