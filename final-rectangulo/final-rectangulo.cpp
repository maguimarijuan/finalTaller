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
  char id_rec1 [20];
  char id_rec2 [20];
  float xii;
  float xid;
  float yid;
  float yii;
  float xsi;
  float xsd;
  float ysi;
  float ysd;
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

}

void obtenerRectanguloInterno(PreResultados* preresultados, int cantPresultados, Rectangulo rect1, Rectangulo rect2){

}

bool estaEnPreResultado(Rectangulo rect, PreResultado preResultado){

}

bool colisionan(Rectangulo rect, PreResultado preresultado){

}

float obtenerAreaResultado(Rectangulo rect, PreResultado preresultado){

}

float obtenerDistancia(Rectangulo rect, PreResultado preresultado){
  
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
        strcpy(resultados[cantidadDeResultados].id_rec1,preResultado[i].id_rec1);
        strcpy(resultados[cantidadDeResultados].id_rec2,preResultado[i].id_rec2);
        strcpy(resultados[cantidadDeResultados].id_rec3,rectangulo[j].id_rec);
        cantidadDeResultados ++;
      }
    }
  }

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
