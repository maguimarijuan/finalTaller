#include "Vec.h"
#include <string.h>

using namespace std;

float max(float a, float b){
	if (a < b) return b;
	else return a;
}

float min(float a, float b){
	if (a < b) return a;
	else return b;
}

class Rectangulo{
public:
	Vec infIzq, supDer;
	string id;

	Rectangulo(){
		infIzq = Vec();
		supDer = Vec();
		id = "-";
	}

	Rectangulo(const Rectangulo& rect){
		infIzq = rect.infIzq;
		supDer = rect.supDer;
		id = rect.id;
	}

	Rectangulo(string id, Vec inf, Vec sup){
		infIzq = inf;
		supDer = sup;
		this->id = id;
	}

	~Rectangulo(){}

	void print(){
		cout << id.data() << "\t";
		infIzq.print(false);
		cout << "\t";
		supDer.print(true);
	}

	bool seSuperponen(const Rectangulo &r){
		if (infIzq.x >= r.supDer.x || infIzq.y >= r.supDer.y)
			return false;
		if (supDer.x <= r.infIzq.x || supDer.y <= r.infIzq.y)
			return false;
		return true;
	}

	Rectangulo interseccion(const Rectangulo &r){	// Esta mal, ver bien
		Vec inf;
		inf.x = max(infIzq.x, r.infIzq.x);
		inf.y = max(infIzq.y, r.infIzq.y);
		Vec sup;
		sup.x = min(supDer.x, r.supDer.x);
		sup.y = min(supDer.y, r.supDer.y);
		return Rectangulo("INTER", inf, sup);
	}

	float distO(){
		Vec supIzq(infIzq.x, supDer.y);
		return sqrt(supIzq.long2());
	}
};