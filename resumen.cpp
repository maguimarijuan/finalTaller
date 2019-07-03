/* ============ SINTAXIS IMPORTANTE ============ */

#include "stdio.h"
#include "stdlib.h"
#include <iostream>

#include <vector> // para usar vectores
#include <string> // para usar strings
#include <map> // para usar diccionarios

#include "math.h" // para usar operaciones matemáticas
#include "algorithm.h" //para usar sort, heap

#include <bits/stdc++.h> // esto incluye todo, es por si nos olvidamos el nombre
// de una librería importante.

using namespace std; // esto es para utilizar las cosas de la librería estandar
/* ========== CLASES ===========*/

class NombreClase:: public NombreClaseMadre
{
public:
  // los métodos deben ser publicos
  NombreClase(); // constructor
  ~NombreClase() = default; // destructor, definido por defecto.
  // lo que se redefine de la clase padre debe llevar un override
  void metodoRedefinido() override;
  // los metodos que deben ser redefinidos por los hijos llevan un virtual
  virtual void metodoARedefinir();

private:
  // los atributos deben ser privados

protected:
  // privados para otras clases pero no para clases hijas

}; // no olvidar este punto y coma

/* =========== STRUCTS ============*/
struct NombreStruct{
  //atributos
}; // no olvidar este punto y coma

/*=========== VECTORES Y DICCIONARIOS ============*/

// Para agregar a un vector:

vector <int> vectorDeNumeros;
int unNumero = 5;
vectorDeNumeros.push_back(unNumero);

//tambien puede ser:
vector <int> vectorDeNumeros = {5,6,7};

//Para iterar un vector necesitamos de un iterador

vector <int>::iterator vectorDeNumeros_itr = vectorDeNumeros.begin();
for (vectorDeNumeros_itr; vectorDeNumeros_itr =! vectorDeNumeros.end(), vectorDeNumeros_itr++){
  (*vectorDeNumeros) = 6; // con esto entramos a la posición que apunta el vector
}


//Para agregar a un diccionarios
map <string, int> diccionario;
diccionario["uno"] = 1;
diccionario["dos"] = 2;
//...

//Para acceder a un diccionario:
map <string, int> ::iterator diccionario_itr;

diccionario_itr = diccionario.find("uno");
int valor buscado = diccionario_itr->second();


/* ========== SORT =========== */
// Para ordenar un vector de estructuras:

struct persona{
  string Nombre;
  int edad;
}

int compararEdades(struct persona persona1, struct persona persona2){
  return (persona1.edad > persona2.edad) ? 1: -1; // creo que se podrían haber
  //usado ternarios
}

vector<struct persona> vectorDePersonas;
sort(vectorDePersonas.begin() ,vectorDePersonas.end(), compararEdades);


/* ========== HEAP =========== */
// esto está extraído de nuestro hermoso tp
struct Comp {
    bool operator()(Renderable *&renderable1, Renderable *&renderable2) {
        return renderable1->getZIndex() > renderable2->getZIndex();
    }
};

    Comp comp;
    std::make_heap(renderables.begin(),renderables.end(), comp);
    int size = renderables.size();

    for (int i = 0; i < size; i++){
        std::pop_heap(renderables.begin(), renderables.end(), comp);
        Renderable* rend = renderables.back();
        rend->render();
        renderables.pop_back();
    }

/* =========== PARA LEER ARCHIVOS =========== */

FILE * unArchivo;
unArchivo = fopen("elArchivo.txt", "r");  // luego de esta operacion puede controlarse si es NULL

// esta es una manera de hacerlo -> MAGUI's WAY
for(i = 0; !feof(unArchivo); i++)
{
    char* nombre;
    float xi;
    float xd;
    float yd;
    int velocidad;
    int vidas;
    fscanf(unArchivo, "%s %f %f %f %d %d", nombre, &xi, &xd, &yd, &velocidad, &vidas);
}

// esta es otra mandera de hacerlo -> FER'S WAY
string linea;
while(getline(unArchivo, linea)){
  string nombre = linea[0];
  float xi = atof(linea[1].c_str());
  float xd = atof(linea[2].c_str());
  float yd = atof(linea[3].c_str()); // atoi y atof funcionan con char*
  // una opcion
  int velocidad = atoi(linea[4].c_str());
  int vidas = atoi(linea[5].c_str());
  // otra operacion
  int velocidad = stoi(linea[4]);
  int vidas = stoi(linea[5]);
  // queda en manos del lector fijarse si existe stof # me da paja
}

// IMPORTANTE -> CERRAR EL ARCHIVO:

fclose(unArchivo);




// para compilar, lo ponemos todo en un archivo y hacemos:

g++ -g -o exec *-cpp

// el -g es para usar GDB

// Comandos básicos de GDB

r: run
si: step into
n: next line
b: breapoint
p: para imprimir variables
x/: para inspecionar la memoria
