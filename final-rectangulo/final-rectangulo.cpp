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
  char id_rec1[20];
  char id_rec2 [20];
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

  if(rect1.xii >= rect2.xsd || rect1.yii >= rect2.ysd) return false;
  if(rect1.xsd <= rect2.xii || rect1.ysd <= rect2.yii) return false;
  return true;
}

Rectangulo obtenerRectanguloInterno(Rectangulo rect1, Rectangulo rect2){
  Rectangulo aux;
  aux.xii = max(rect1.xii, rect2.xii);
  aux.yii = max(rect1.yii, rect2.yii);

  aux.xsd = min(rect1.xsd, rect2.xsd);
  aux.ysd = min(rect1.ysd, rect2.ysd);

  aux.xid = aux.xsd;
  aux.yid = aux.yii;
  aux.xsi = aux.xii;
  aux.ysi = aux.ysd;

  strcpy(aux.id_rec, "aux");
  return aux;
}

void obtenerRectanguloInterno(PreResultado* preResultados, int cantPresultados, Rectangulo rect1, Rectangulo rect2){
  Rectangulo aux = obtenerRectanguloInterno(rect1, rect2);
  strcpy(preResultados[cantPresultados].id_rec1, rect1.id_rec);
  strcpy(preResultados[cantPresultados].id_rec2,rect2.id_rec);

  preResultados[cantPresultados].rect = aux;
  return;

}

bool estaEnPreResultado(Rectangulo rect, PreResultado preResultado){
  if(strcmp(rect.id_rec, preResultado.id_rec1) == 0) return true;
  if(strcmp(rect.id_rec, preResultado.id_rec2) == 0) return true;
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
  Rectangulo aux = obtenerRectanguloInterno(rect,preResultado.rect);

  float base = aux.xid - aux.xii;
  cambiarNegativo(&base);

  float altura = aux.ysd - aux.yid;
  cambiarNegativo(&altura);
  return(base * altura);
}

float obtenerDistancia(Rectangulo rect, PreResultado preResultado){
  Rectangulo  aux = obtenerRectanguloInterno(preResultado.rect, rect);
  float distancia = sqrt(pow(aux.xsi,2) + pow(aux.ysi,2));
  return distancia;
}


int procesarRectangulos(Rectangulo* rectangulos, int cantidadDeRectangulos, Resultado* resultados){

  PreResultado preResultados [20];
  int cantPreResultados = 0;

  for(int i = 0; i < cantidadDeRectangulos; i++){
    for(int j = i+1; j < cantidadDeRectangulos; j++){
      if (i == j) continue;
      if(colisionan(rectangulos[i],rectangulos[j])){
        obtenerRectanguloInterno(preResultados, cantPreResultados, rectangulos[i], rectangulos[j]);
        cantPreResultados++;
      }
    }
  }
  int cantidadDeResultados = 0;
  for(int i = 0; i < cantPreResultados; i++){
    for(int j = 0;  j < cantidadDeRectangulos; j++){
      if(estaEnPreResultado(rectangulos[j], preResultados[i])) continue;
      if(colisionan(rectangulos[j], preResultados[i])){
        float area = obtenerAreaResultado(rectangulos[j], preResultados[i]);
        float distancia = obtenerDistancia(rectangulos[j], preResultados[i]);
        resultados[cantidadDeResultados].distancia = distancia;
        resultados[cantidadDeResultados].area = area;
        strcpy(resultados[cantidadDeResultados].id_rec1,preResultados[i].id_rec1);
        strcpy(resultados[cantidadDeResultados].id_rec2,preResultados[i].id_rec2);
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

typedef struct{
  char id_rec1[20];
  char id_rec2[20];
  char id_rec3[20];
  bool repetido;
} IDS;

bool sonIguales(IDS ids1, IDS ids2){
  bool id_rec1 = false;
  bool id_rec2 = false;
  bool id_rec3 = false;
  if(strcmp(ids1.id_rec1, ids2.id_rec1) == 0 ||
    strcmp(ids1.id_rec1, ids2.id_rec2) == 0 ||
    strcmp(ids1.id_rec1, ids2.id_rec3) == 0 ) id_rec1 = true;
  if(strcmp(ids1.id_rec2, ids2.id_rec1) == 0 ||
    strcmp(ids1.id_rec2, ids2.id_rec2) == 0 ||
    strcmp(ids1.id_rec2, ids2.id_rec3) == 0 ) id_rec2 = true;
  if(strcmp(ids1.id_rec3, ids2.id_rec1) == 0 ||
    strcmp(ids1.id_rec3, ids2.id_rec2) == 0 ||
    strcmp(ids1.id_rec3, ids2.id_rec3) == 0 ) id_rec3 = true;
  return id_rec1&&id_rec2&&id_rec3;

}

int eliminarRepetidos(Resultado* resultados, int cantidadDeResultados, Resultado* resultadosSinRepetidos){
  int cantidadDeResultadosSinRepetidos = 0;
  IDS ids [20];
  for(int i = 0; i < cantidadDeResultados; i ++){
    strcpy(ids[i].id_rec1, resultados[i].id_rec1);
    strcpy(ids[i].id_rec2, resultados[i].id_rec2);
    strcpy(ids[i].id_rec3, resultados[i].id_rec3);
    ids[i].repetido = false;

  }
  for(int i = 0; i < cantidadDeResultados; i++){
    for(int j = i+1; j < cantidadDeResultados; j++){
      if(i == j) continue;
      if(sonIguales(ids[i], ids[j])) ids[j].repetido = true;
    }
  }

  for(int i = 0; i <cantidadDeResultados; i++){
    if(ids[i].repetido) continue;
    resultadosSinRepetidos[cantidadDeResultadosSinRepetidos].distancia =resultados[i].distancia;
    resultadosSinRepetidos[cantidadDeResultadosSinRepetidos].area = resultados[i].area;
    strcpy(resultadosSinRepetidos[cantidadDeResultadosSinRepetidos].id_rec1, resultados[i].id_rec1);
    strcpy(resultadosSinRepetidos[cantidadDeResultadosSinRepetidos].id_rec2, resultados[i].id_rec2);
    strcpy(resultadosSinRepetidos[cantidadDeResultadosSinRepetidos].id_rec3, resultados[i].id_rec3);
    cantidadDeResultadosSinRepetidos++;
  }
  return cantidadDeResultadosSinRepetidos;
}

int main(){
  Rectangulo rectangulos[20];
  int cantidadDeRectangulos = leerRectangulos(rectangulos);
  Resultado resultados[20];
  int cantidadDeResultados = procesarRectangulos(rectangulos,cantidadDeRectangulos,resultados);
  Resultado resultadosSinRepetidos [20];
  cantidadDeResultados =  eliminarRepetidos(resultados, cantidadDeResultados,resultadosSinRepetidos);
  qsort(resultadosSinRepetidos, cantidadDeResultados, sizeof(Resultado), comparar);
  cout<<"DISTANCIA"<<"\t\t"<<"AREA"<<"\t\t"<<"ID REC 1"<<"\t\t"<<"ID REC 2"<<"\t\t"<<"ID REC 3"<< endl;
  for(int i = 0; i < cantidadDeResultados; i++){
    cout<<resultadosSinRepetidos[i].distancia<<"\t\t"<< resultadosSinRepetidos[i].area<<"\t\t"<< resultadosSinRepetidos[i].id_rec1<<"\t\t"<< resultadosSinRepetidos[i].id_rec2<<"\t\t"<< resultadosSinRepetidos[i].id_rec3<<endl;
  }
}
