#include <iostream>

using namespace std;

class Vec{
public:
	float x, y;

	Vec(){
		x = y = 0;
	}

	Vec(const Vec& vec){
		x = vec.x;
		y = vec.y;
	}
	
	Vec(float x, float y){
		this->x = x;
		this->y = y;
	}

	~Vec(){}

	Vec operator-(){
		return Vec(-x, -y);
	}

	Vec operator+(Vec vec){
		return Vec(x + vec.x, y + vec.y);
	}

	Vec operator-(Vec vec){
		return Vec(x - vec.x, y - vec.y);
	}

	float long2(){
		return x*x + y*y;
	}

	void print(bool endline){
		if (endline)
			cout << "(" << x << ";" << y << ")" << endl;
		else
			cout << "(" << x << ";" << y << ")";
	}
};