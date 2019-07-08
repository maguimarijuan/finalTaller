#include"bits/stdc++.h"
using namespace std;

typedef struct
{
  char idPozo[20];
  float x;
  float y;
  float radio;
} Pozo;

typedef struct
{
  char idTanque[20];
  float xii;
  float yii;
  float xid;
  float yid;
  float xsi;
  float ysi;
  float xsd;
  float ysd;
  bool caido;
} Tanque;

typedef struct
{
  char idTanque[20];
  char idPozo[20];
  float distancia;
} Resultado;

int cargarPozos(Pozo pozos[])
{
  FILE* archivo = fopen("pozos.txt","r");
  int i;
  for (i = 0; !feof(archivo); i++)
  {
    fscanf(archivo,"%s %f %f %f",pozos[i].idPozo, &pozos[i].x, &pozos[i].y, &pozos[i].radio);
  }
  fclose(archivo);
  return i;
}

int cargarTanques(Tanque tanques[])
{
  FILE* archivo = fopen("tanques.txt","r");
  int i;
  for(i = 0; !feof(archivo); i++){
     fscanf(archivo, "%s %f %f %f %f", tanques[i].idTanque, &tanques[i].xii, &tanques[i].yii,
                                                                    &tanques[i].xsd, &tanques[i].ysd);
    tanques[i].xsi = tanques[i].xii;
    tanques[i].ysi = tanques[i].ysd;
    tanques[i].xid = tanques[i].xsd;
    tanques[i].yid = tanques[i].yii;
    tanques[i].caido = false;
  }
  return i;
}

bool entraVerticeEnPozo(float x, float y, Pozo pozo)
{
  return (sqrt(pow(x-pozo.x,2) + pow(y-pozo.y,2)) <= pozo.radio);
}

bool entraTanqueEnPozo(Tanque tanque, Pozo pozo)
{
  bool vii = entraVerticeEnPozo(tanque.xii, tanque.yii, pozo);
  bool vid = entraVerticeEnPozo(tanque.xid, tanque.yid, pozo);
  bool vsi = entraVerticeEnPozo(tanque.xsi, tanque.ysi, pozo);
  bool vsd = entraVerticeEnPozo(tanque.xsd, tanque.ysd, pozo);
  return (vii && vid && vsi && vsd);
}
float cambiarSigno(float numero)
{
  if (numero < 0) numero *= -1;
  return numero;
}
void modificarPosicion(Tanque* tanque, float xii){
  float ancho = cambiarSigno(tanque->xid -tanque->xii );
  tanque->xii = xii;
  tanque->xsi = xii;
  tanque->xid = xii + ancho;
  tanque->xsd = tanque->xid;
}


int gameLoop(Pozo* pozos, int cantidadDePozos, Tanque* tanques, int cantidadDeTanques, Resultado*resultados)
{
  int cantidadDeResultados = 0;
  for(int i = 0; i < cantidadDeTanques; i++)
  {
    float xii = tanques[i].xii;
    float distanciaRecorridaActual = 1000000000000000;
    Resultado aux;
    strcpy(aux.idTanque, "no toco");
    strcpy(aux.idPozo, "no toco");
    aux.distancia = -1;
    for(int j = 0; j < cantidadDePozos; j++)
    {
      bool termino = false;
      float movimiento = pozos[j].x-pozos[j].radio;
      modificarPosicion(&tanques[i],movimiento);
      while(!termino){
        if(entraTanqueEnPozo(tanques[i], pozos[j])){
          if(cambiarSigno(xii-tanques[i].xii) < distanciaRecorridaActual)
          {
            strcpy(aux.idTanque, tanques[i].idTanque);
            strcpy(aux.idPozo, pozos[j].idPozo);
            aux.distancia = cambiarSigno(xii-tanques[i].xii);
            distanciaRecorridaActual = aux.distancia;
            termino = true;
          }
        }
        movimiento += 0.0001;
        modificarPosicion(&tanques[i], movimiento);
        if(tanques[i].xii > (pozos[j].x + pozos[j].radio))
        {
          termino = true;
        }
      }
    }
    if(strcmp(aux.idTanque, "no toco") == 1) {
      strcpy(resultados[cantidadDeResultados].idTanque, aux.idTanque);
      strcpy(resultados[cantidadDeResultados].idPozo, aux.idPozo);
      resultados[cantidadDeResultados].distancia = aux.distancia;
      cantidadDeResultados++;
    }
  }
  return cantidadDeResultados;
}

int main()
{
  Pozo pozos[20];
  int cantidadDePozos = cargarPozos(pozos);
  Tanque tanques[20];
  int cantidadDeTanques = cargarTanques(tanques);
  Resultado resultados[20];
  int cantidadDeResultados = gameLoop(pozos, cantidadDePozos, tanques,cantidadDeTanques, resultados);
  cout<< "ID TANQUE" << "/t/t" << "ID POZO"<< "/t/t" << "DISTANCIA" << endl;
  for(int i = 0; i < cantidadDeResultados; i++){
    cout<< resultados[i].idTanque << "/t/t" <<  resultados[i].idPozo << "/t/t" <<  resultados[i].distancia <<endl;
  }

}
