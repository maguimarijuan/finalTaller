#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "Rectangulo.h"

#define SIZE 100

using namespace std;

class Parser{
public:
	FILE* file;

	Parser(string path){
		file = fopen(path.c_str(), "r");
	}

	~Parser(){
		fclose(file);
	}

	int cargarRectangulos(Rectangulo (&rectangulos)[SIZE]){		
		char id[SIZE];
		int i = 0;
		bool eof = false;
		while (! eof){
			int status = fscanf(file, "%s %f %f %f %f\n", id, &rectangulos[i].infIzq.x, 
				&rectangulos[i].infIzq.y, &rectangulos[i].supDer.x, &rectangulos[i].supDer.y);
			rectangulos[i].id = id;
			i++;
			eof = feof(file);
		}
		return i;
	}
};