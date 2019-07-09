// Final Taller (Superposicion Rect).cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Parser.h"

using namespace std;

typedef struct {
	float distancia;
	string id1, id2, id3;
}Resultado;

int comparar(const void* r1, const void* r2){
	float d1 = ((Resultado*)r1)->distancia;
	float d2 = ((Resultado*)r2)->distancia;

	if (d1 < d2) return -1;
	else if (d1 == d2) return 0;
	else return 1;
}

int main(){
	cout << "Hola Mundo!" << endl << endl;

	Resultado resultados[SIZE];
	int ml = 0;

	Rectangulo rectangulos[SIZE];

	Parser* parser = new Parser("rectangulos.txt");
	int cantidad = parser->cargarRectangulos(rectangulos);
	delete parser;

	for (int i = 0; i < cantidad-2; i++){
		for (int j = i+1; j < cantidad-1; j++){
			if (rectangulos[i].seSuperponen(rectangulos[j])){
				Rectangulo inter = rectangulos[i].interseccion(rectangulos[j]);
				for (int k = j+1; k < cantidad; k++){
					if (inter.seSuperponen(rectangulos[k])){
						resultados[ml].distancia = inter.interseccion(rectangulos[k]).distO();
						resultados[ml].id1 = rectangulos[i].id;
						resultados[ml].id2 = rectangulos[j].id;
						resultados[ml].id3 = rectangulos[k].id;
						ml++;
					}
				}
			}
		}
	}

	qsort(resultados, ml, sizeof(Resultado), comparar);

	for (int i = 0; i < ml; i++){
		cout << resultados[i].distancia << " " << resultados[i].id1.c_str() << " " << 
			resultados[i].id2.c_str() << " " << resultados[i].id3.c_str() << endl;
	}
	
	cout << endl << "Chau Mundo!" << endl;
	getchar();
	return 0;
}

