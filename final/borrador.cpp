//#include "stdlib.h"
//#include "stdio.h"
//#include <string>
//#include <vector>
#include "bits/stdc++.h"

//user namespace std

struct Personaje
{
  float xpi;
  float ypi;
  float xpd;
  float ypd;
  int energia;
};

struct Ataque{
  std::string id;
  float x;
  float y;
  int energia;
  std::string accion;
};

struct Resultado{
  std::string id;
  float distancia;
  int energia;
};

struct Personaje leerArchivoJugador(std::string nombreArchivo)
{
  struct Personaje personaje;
  personaje.energia = 100;

  FILE* archivo = fopen(nombreArchivo.c_str(), "r");
  //while(
  float xpi;
  float xpd;
  float ypd;
  fscanf(archivo,"%f %f %f", &xpi, &xpd, &ypd);
  personaje.xpi = xpi;
  personaje.ypi = 0;
  personaje.xpd = xpd;
  personaje.ypd = ypd;
  fclose(archivo);
  return(personaje);
}

std::vector<struct Ataque> leerArchivosAtaques(std::string nombreArchivo)
{
  FILE* archivo = fopen(nombreArchivo.c_str(), "r");
  std::vector<struct Ataque> ataques;

  while(!feof(archivo)){
    char* id;
    float x;
    float y;
    int energia;
    char* accion;
    fscanf(archivo,"%c %f %f %d %c",id, &x, &y, &energia, accion);
    struct Ataque aux;
    aux.id = id;
    aux.x = x;
    aux.y = y;
    aux.energia = energia;
    aux.accion = accion;
    ataques.push_back(aux);
  }
  fclose(archivo);
  return ataques;
}

std::vector<struct Resultado> gameloop(std::vector<struct Ataque> ataques, struct Personaje personaje)
{
  std::vector<struct Resultado> resultados;
  std::vector<struct Ataque>::iterator itr = ataques.begin();
  bool huboColision = false;

  bool estaVivo= true;


  for(itr; itr != ataques.end(); ++itr)
  {
    float xpi_personaje = personaje.xpi;
    float ypi_personaje = personaje.ypi;
    float xpd_personaje = personaje.xpd;
    float ypd_personaje = personaje.ypd;
    int energia = personaje.energia;
    if(energia < 0) estaVivo = false;

    std::string accion = (*itr).accion;
    float y_ataque = (*itr).y;
    float x_ataque = (*itr).x;
    std::string id_ataque = (*itr).id;
    int energia_ataque = (*itr).energia;

    if(strcmp(accion.c_str(), "A") == 0)
    {
      ypd_personaje -= 20;
    }
    if(strcmp(accion.c_str(), "S") == 0)
    {
      ypi_personaje += 13;
      ypd_personaje += 13;
    }
    if(strcmp(accion.c_str(), "D") == 0){
      xpi_personaje -= 10;
    }

    struct Resultado resultado;
    if(y_ataque <= ypd_personaje && y_ataque >= ypd_personaje) huboColision = true;

    if(huboColision & estaVivo){
      resultado.id =  id_ataque;
      float distancia = xpi_personaje - x_ataque;
      if (distancia < 0) distancia *= -1;
      resultado.distancia = distancia;
      personaje.energia = energia - energia_ataque;
      resultado.energia = personaje.energia;
    }
    else
    {
      resultado.id = "NO TOCO";
      resultado.distancia = -1;
      resultado.energia = energia;
    }
    resultados.push_back(resultado);
  }
  return resultados;
}
int main()
{

  struct Personaje personaje = leerArchivoJugador("personajes.txt");
  std::vector<struct Ataque> ataques = leerArchivosAtaques("ataques.txt");
  std::vector<struct Resultado> resultados = gameloop(ataques, personaje);

  std::vector<struct Resultado>::iterator itr = resultados.begin();
  for(itr; itr != resultados.end(); ++itr){
    std::cout<<(*itr).id << " "<< (*itr).distancia << " " << (*itr).energia << std::endl;
  }
  return 0;
}
