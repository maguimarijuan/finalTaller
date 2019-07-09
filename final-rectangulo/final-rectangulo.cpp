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
  fclose("rectangulos.txt");
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

  strcpy(aux.idrec, "aux");
  return aux;
}

void obtenerRectanguloInterno(PreResultados* preresultados, int cantPresultados, Rectangulo rect1, Rectangulo rect2){
  Rectangulo aux;
  //el rectangulo 2 está a la derecha;
  if (rect2.xii < rect1.xid){
    aux = obtenerRectanguloInterno(rect2, rect1);
    strcpy(preResultado[cantPresultados].id_derecha, rect2.id_rec);
    strcpy(preResultado[cantPresultados].id_izquierda,rect1.id_rec);
  }
  // el rectangulo 1 está a la izquierda;
  else{
     aux = obtenerRectanguloInterno(rect1, rect2);
     strcpy(preResultado[cantPresultados].id_derecha, rect1.id_rec);
     strcpy(preResultado[cantPresultados].id_izquierda);
   }
   preResultado[cantPresultados].rect = aux;
   return;

}

bool estaEnPreResultado(Rectangulo rect, PreResultado preResultado){
  if(strcmp(rect.id_rec, preResultado.id_derecha) == 0) return true;
  if(strcmp(rect.id_rec, preResultado.id_izquierda) == 0) return true;
  return false;
}

bool colisionan(Rectangulo rect, PreResultado preresultado){
  return(colisionan(rect, preResultado.rect));
}


void cambiarNegativo(float* numero){
  if(*numero < 0) {
    *numero = *numero * (-1);
  }
}

float obtenerAreaResultado(Rectangulo rect, PreResultado preresultado){
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

float obtenerDistancia(Rectangulo rect, PreResultado preresultado){
  Rectangulo aux;
  if (preResultado.rect.xii < rect.xid) aux = obtenerRectanguloInterno(preResultado.rect, rect);
  // el rectangulo 1 está a la izquierda;
  else aux = obtenerRectanguloInterno(rect, preResultado.rect);
  float distancia = sqrt(pow(aux.xii,2) + pow(aux.yii,2))
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
        cantPresultados++:
      }
    }
  }
  int cantidadDeResultados = 0;
  for(int i = 0; i < cantPresultados; i++){
    for(int j = 0;  j < cantidadDeRectangulos; j++){
      if(estaEnPreResultado(rectangulo[j], preResultados[i]) continue;
      if(colisionan(rectangulo[j], preResultado[i])){
        float area = obtenerAreaResultado(rectangulo[j], preResultado[i]);
        float distancia = obtenerDistancia(rectangulo[j], preResultado[i]);
        resultados[cantidadDeResultados].distancia = distancia;
        resultados[cantidadDeResultados].area = area;
        strcpy(resultados[cantidadDeResultados].id_rec1,preResultado[i].id_derecha);
        strcpy(resultados[cantidadDeResultados].id_rec2,preResultado[i].id_izquierda);
        strcpy(resultados[cantidadDeResultados].id_rec3,rectangulo[j].id_rec);
        cantidadDeResultados ++;
      }
    }
  }
  return cantidadDeResultados;

}

int comparar(void* r1, void* r2){
  float distancia1 = (Resultado*) r1-> distancia;
  float distancia2 = (Resultado*) r2-> distancia;
  if(distancia1 > distancia2) return 1;
  if(distancia1 == distancia2) return 0;
  return -1;
}


int main(){
  Rectangulo rectangulos[20];
  int cantidadDeRectangulos = leerRectangulos(rectangulos);
  Resultados resultados[20];
  int cantidadDeResultados = procesarRectangulos(retangulos,cantidadDeRectangulos,Resultados);
  qsort(resultados, cantidadDeResultados, sizeof(Resultado), comparar);
  cout<<"DISTANCIA"<<"\t\t"<<"AREA"<<"\t\t"<<"ID REC 1"<<"\t\t"<<"ID REC 2"<<"\t\t"<<"ID REC 3"<< endl;
  for(int i = 0; i < cantidadDeResultados; i++){
    cout<<resultados[i].distancia<<"\t\t"<< resultados[i].area<<"\t\t"<< resultados[i].id_rec1<<"\t\t"<< resultados[i].id_rec2<<"\t\t"<< resultados[i].id_rec3<<endl;
  }
}
