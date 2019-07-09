#include "bits/stdc++.h"

using namespace std;

typedef struct{
  char id_rec [20];
  float xii;
  float xid;
  float yid;
  float yii;
  float xsi;
  float xsd;
  float ysi;
  float ysd;
} Rectangulo;

typedef struct{
  char id_derecha [20];
  char id_izquierda [20];
  Rectangulo rect;
} PreResultado;

typedef struct{
  float distancia;
  float area;
  char id_rec1 [20];
  char id_rec2 [20];
  char id_rec3 [20];
}Resultado;

int leerRectangulos(Rectangulo* rectangulos){
  int i = 0;
  FILE* archivo = fopen("rectangulos.txt", "r");
  for (i; !feof(archivo); i++){
    fscanf(archivo,"%s %f %f %f %f",rectangulos[i].id_rec, &rectangulos[i].xii,
                                    &rectangulos[i].yii,  &rectangulos[i].xsd,  &rectangulos[i].ysd);
    rectangulos[i].xid = rectangulos[i].xsd;
    rectangulos[i].yid = rectangulos[i].yii;
    rectangulos[i].xsi = rectangulos[i].xii;
    rectangulos[i].ysi = rectangulos[i].ysd;
  }
  fclose(archivo);
  return i;
}

bool colisionan(Rectangulo rect1, Rectangulo rect2){
  bool colisionanEnX =  false;
  bool colisionanEnY = false;
  if(rect2.xsi <= rect1.xsd && rect2.xsi >= rect1.xsi) colisionanEnX = true;
  if(rect2.xsd <= rect1.xsd && rect2.xsd >= rect1.xsi) colisionanEnX = true;
  if(rect2.ysi <= rect1.ysd && rect2.ysi >= rect1.yid) colisionanEnY = true;
  if(rect2.yid <= rect1.ysd && rect2.yid >= rect1.yid) colisionanEnY = true;
  return(colisionanEnX && colisionanEnY);
}

Rectangulo obtenerRectanguloInterno(Rectangulo rectDerecha, Rectangulo rectIzquierda){
  Rectangulo aux;
  if (rectDerecha.ysi > rectIzquierda.ysi){
    // el de la derecha está arriba;
    aux.xii = rectDerecha.xii;
    aux.yii = rectDerecha.yii;
    aux.xid = rectIzquierda.xid;
    aux.yid = rectDerecha.yid;
    aux.xsi = rectDerecha.xsi;
    aux.ysi = rectIzquierda.ysd;
    aux.xsd = rectIzquierda.xsd;
    aux.ysd = rectIzquierda.xsd;
  }
  else{
    //el de la derecha está abajo
    aux.xii = rectDerecha.xii;
    aux.yii = rectIzquierda.yid;
    aux.xid = rectIzquierda.xid;
    aux.yid = rectIzquierda.yid;
    aux.xsi = rectDerecha.xsi;
    aux.ysi = rectDerecha.ysi;
    aux.xsd = rectIzquierda.xsd;
    aux.ysd = rectDerecha.ysd;
  }

  strcpy(aux.id_rec, "aux");
  return aux;
}

void obtenerRectanguloInterno(PreResultado* preResultados, int cantPresultados, Rectangulo rect1, Rectangulo rect2){
  Rectangulo aux;
  //el rectangulo 2 está a la derecha;
  if (rect2.xii < rect1.xid){
    aux = obtenerRectanguloInterno(rect2, rect1);
    strcpy(preResultados[cantPresultados].id_derecha, rect2.id_rec);
    strcpy(preResultados[cantPresultados].id_izquierda,rect1.id_rec);
  }
  // el rectangulo 1 está a la izquierda;
  else{
     aux = obtenerRectanguloInterno(rect1, rect2);
     strcpy(preResultados[cantPresultados].id_derecha, rect1.id_rec);
     strcpy(preResultados[cantPresultados].id_izquierda, rect2.id_rec);
   }
   preResultados[cantPresultados].rect = aux;
   return;

}

bool estaEnPreResultado(Rectangulo rect, PreResultado preResultado){
  if(strcmp(rect.id_rec, preResultado.id_derecha) == 0) return true;
  if(strcmp(rect.id_rec, preResultado.id_izquierda) == 0) return true;
  return false;
}

bool colisionan(Rectangulo rect, PreResultado preResultado){
  return(colisionan(rect, preResultado.rect));
}


void cambiarNegativo(float* numero){
  if(*numero < 0) {
    *numero = *numero * (-1);
  }
}

float obtenerAreaResultado(Rectangulo rect, PreResultado preResultado){
  Rectangulo aux;
  if (preResultado.rect.xii < rect.xid) aux = obtenerRectanguloInterno(preResultado.rect, rect);
  // el rectangulo 1 está a la izquierda;
  else aux = obtenerRectanguloInterno(rect, preResultado.rect);
  float base = aux.xid - aux. xii;
  cambiarNegativo(&base);
  float altura = aux.ysd - aux.yid;
  cambiarNegativo(&altura);
  return(base * altura);
}

float obtenerDistancia(Rectangulo rect, PreResultado preResultado){
  Rectangulo aux;
  if (preResultado.rect.xii < rect.xid) aux = obtenerRectanguloInterno(preResultado.rect, rect);
  // el rectangulo 1 está a la izquierda;
  else aux = obtenerRectanguloInterno(rect, preResultado.rect);
  float distancia = sqrt(pow(aux.xii,2) + pow(aux.yii,2));
  return distancia;
}


int procesarRectangulos(Rectangulo* rectangulos, int cantidadDeRectangulos, Resultado* resultados){

  PreResultado preResultados [20];
  int cantPresultados = 0;

  for(int i = 0; i < cantidadDeRectangulos; i++){
    for(int j = 0; j < cantidadDeRectangulos; j++){
      if (i == j) continue;
      if(colisionan(rectangulos[i],rectangulos[j])){
        obtenerRectanguloInterno(preResultados, cantPresultados, rectangulos[i], rectangulos[j]);
        cantPresultados++;
      }
    }
  }
  int cantidadDeResultados = 0;
  for(int i = 0; i < cantPresultados; i++){
    for(int j = 0;  j < cantidadDeRectangulos; j++){
      if(estaEnPreResultado(rectangulos[j], preResultados[i])) continue;
      if(colisionan(rectangulos[j], preResultados[i])){
        float area = obtenerAreaResultado(rectangulos[j], preResultados[i]);
        float distancia = obtenerDistancia(rectangulos[j], preResultados[i]);
        resultados[cantidadDeResultados].distancia = distancia;
        resultados[cantidadDeResultados].area = area;
        strcpy(resultados[cantidadDeResultados].id_rec1,preResultados[i].id_derecha);
        strcpy(resultados[cantidadDeResultados].id_rec2,preResultados[i].id_izquierda);
        strcpy(resultados[cantidadDeResultados].id_rec3,rectangulos[j].id_rec);
        cantidadDeResultados ++;
      }
    }
  }
  return cantidadDeResultados;

}

int comparar(const void* r1, const void* r2){
  float distancia1 = ((Resultado*) r1)-> distancia;
  float distancia2 = ((Resultado*) r2)-> distancia;
  if(distancia1 > distancia2) return 1;
  if(distancia1 == distancia2) return 0;
  return -1;
}


int main(){
  Rectangulo rectangulos[20];
  int cantidadDeRectangulos = leerRectangulos(rectangulos);
  Resultado resultados[20];
  int cantidadDeResultados = procesarRectangulos(rectangulos,cantidadDeRectangulos,resultados);
  qsort(resultados, cantidadDeResultados, sizeof(Resultado), comparar);
  cout<<"DISTANCIA"<<"\t\t"<<"AREA"<<"\t\t"<<"ID REC 1"<<"\t\t"<<"ID REC 2"<<"\t\t"<<"ID REC 3"<< endl;
  for(int i = 0; i < cantidadDeResultados; i++){
    cout<<resultados[i].distancia<<"\t\t"<< resultados[i].area<<"\t\t"<< resultados[i].id_rec1<<"\t\t"<< resultados[i].id_rec2<<"\t\t"<< resultados[i].id_rec3<<endl;
  }
}
