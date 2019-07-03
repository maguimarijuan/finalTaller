
#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <string>
#include "math.h"
#include <bits/stdc++.h>

using namespace std;

class Posicion
{
    public:
        Posicion(float xi, float yi, float ancho, float largo);
        ~Posicion() = default;
        void mover(float sentido, float velocidad);
        vector<float> obtenerInformacionX(); //devuelve el x izquierdo inferior y el ancho
        vector<float> obtenerInformacionY();
        float getDistanciaRecorrida();

    private:
    float xi; // coordenada x del lado inferior izquierdo
    float xi_inicial;
    float yi; // coordnada y del lado inferior izquierdo
    float ancho;
    float largo;
};


Posicion::Posicion(float xi, float yi, float ancho, float largo)
{
    this->xi = xi;
    this->xi_inicial = xi;
    this->yi = yi;
    this->ancho = ancho;
    this->largo = largo;
}

void Posicion::mover(float sentido, float velocidad)
{
    xi = xi + sentido * velocidad;
}

vector<float> Posicion::obtenerInformacionX()
{
    return {xi, ancho};
}

vector<float> Posicion::obtenerInformacionY()
{
    return {yi, largo};
}


float Posicion::getDistanciaRecorrida(){
    float distanciaRecorrida;
    distanciaRecorrida = xi_inicial - xi;
    if (distanciaRecorrida < 0) distanciaRecorrida*= -1;
    return distanciaRecorrida;
}

class Personaje
{
    public:
        Personaje(Posicion* posicion, int vida, int sentido, int velocidad, string nombre);
        ~Personaje() = default;
        void mover();
        Posicion* getPosicion();
        void restarVida();
        bool estaMuerto();
        bool colisionaCon(Posicion* posicion2);
        string getNombre();
        float getDistanciaRecorrida();

    private:
        Posicion* posicion;
        int vida;
        int sentido;
        int velocidad;
        string nombre;
};


Personaje::Personaje(Posicion* posicion, int vida, int sentido, int velocidad, string nombre)
{
        this->posicion = posicion;
        this->vida = vida;
        this->sentido = sentido;
        this->velocidad = velocidad;
        this->nombre = nombre;
}

void Personaje::mover()
{
    posicion->mover(sentido, velocidad);
}

string Personaje::getNombre()
{
    return nombre;
}
Posicion* Personaje::getPosicion()
{
    return posicion;
}

void Personaje::restarVida()
{
    if (vida == 0 ) return;
    vida -- ;
}

bool Personaje::estaMuerto(){
    return (vida == 0);
}

bool Personaje::colisionaCon(Posicion* posicion2)
{
    //posicion2 es la posicion de un enemigo
    bool colisionanEnX = false;
    bool colisionanEnY = false;

    //informacion sobre las coordanadas en x
    vector<float> informacion = posicion->obtenerInformacionX();// devuelve el x inferior izquierdo y el ancho
    vector<float> informacion2 = posicion2->obtenerInformacionX();

    float xi1 = informacion[0];  //x izquierda de 1
    float xi2 = informacion2[0]; //x izquierda de 2
    float xd1 = informacion[0] + informacion[1]; //x derecha de 1
    float xd2 = informacion2[0] + informacion[1]; //x derecha de 2;

    if(xi1 <= xd2 && xi1 >= xi2) colisionanEnX = true;
    if(xd1 <= xd2 && xd1 >= xi2) colisionanEnX = true;

    informacion = posicion->obtenerInformacionY();// devuelve el y inferior izquierdo y el ancho
    informacion2 = posicion->obtenerInformacionY();

    float y1 = informacion[0] + informacion[1];
    float y2 = informacion2[0] + informacion[1];

    if (y1 >= y2) colisionanEnY = true;

    return(colisionanEnX && colisionanEnY);

}

float Personaje::getDistanciaRecorrida(){
    return posicion->getDistanciaRecorrida();
}

struct desaparecido{
    string nombre;
    float distanciaRecorrida;
};

class Juego
{
    public:
        Juego();
        ~Juego() = default;
        void gameLoop();
        vector<struct desaparecido> getDesaparecidos();

    private:
    int cantidadDeEnemigos;
    int cantidadDeEnemigosVivos;
    int cantidadDePersonajes;
    int cantidadDePersonajesVivos;
    Personaje* personajeDerecha;
    Personaje* personajeIzquierda;
    vector<Personaje*> personajes;
    vector<Personaje*> enemigos;
    vector<struct desaparecido> desaparecidos;
    void setPersonajesDerechaIzquierda();

};


Juego::Juego()
{
    FILE* enemigosArch;
    FILE* personajesArch;


    enemigosArch = fopen("moscas.txt", "r");
    if(enemigosArch == NULL) cout <<"te re cabio";
    int i;
    bool eof = false;
    for(i = 0; !eof; i++)
    {
       float xi;
       float yi;
       fscanf(enemigosArch, "%f %f\n", &xi, &yi);
       Posicion* posicionEnemigo = new Posicion(xi, yi, 1, 1);
       Personaje* enemigo = new Personaje(posicionEnemigo, 1, -1, 10, "enemigo");
       enemigos.push_back(enemigo);
       eof = feof(enemigosArch);
    }
    fclose(enemigosArch);
    cantidadDeEnemigos = i;
    cantidadDeEnemigosVivos = i;

    personajesArch = fopen("personajes.txt", "r");
    for(i = 0; !feof(enemigosArch); i++)
    {
        char* nombre;
        float xi;
        float xd;
        float yd;
        int velocidad;
        int vidas;
        fscanf(personajesArch, "%s %f %f %f %d %d", nombre, &xi, &xd, &yd, &velocidad, &vidas);
        string nombre_ = nombre;
        float ancho = xi - xd;
        if(ancho <  0) ancho*=-1;
        Posicion* posicionPersonaje = new Posicion(xi, yd,ancho, yd);
        Personaje* personaje = new Personaje(posicionPersonaje,vidas, 1, velocidad, nombre_);
        personajes.push_back(personaje);
    }
    fclose(personajesArch);
    cantidadDePersonajes = i;
    cantidadDePersonajesVivos = i;
    this->setPersonajesDerechaIzquierda();

}

void Juego::setPersonajesDerechaIzquierda(){

    personajeDerecha = personajes[0]; // el personaje que va a la derecha que está más a la izquierda;

    for(int j = 1; j < cantidadDePersonajes; j++)
    {
        if(personajes[j]->estaMuerto()) continue;
        Posicion* poscAnterior = personajeDerecha->getPosicion();
        Posicion* posc = personajes[j]->getPosicion();

        if ((poscAnterior->obtenerInformacionX())[0] > (posc->obtenerInformacionX())[0]) personajeDerecha = personajes[j];

    }

    personajeIzquierda = enemigos[0];

     for(int j = 1; j < cantidadDeEnemigos; j++)
    {
        if(enemigos[j]->estaMuerto()) continue;
        Posicion* poscAnterior = personajeIzquierda->getPosicion();
        Posicion* posc = enemigos[j]->getPosicion();

        if ((poscAnterior->obtenerInformacionX())[0] < (posc->obtenerInformacionX())[0]) personajeIzquierda = enemigos[j];
    }
}


void Juego::gameLoop()
{

    for (int x = 0; x < 10; x++){
        /*
        if (cantidadDePersonajesVivos == 0 || cantidadDeEnemigosVivos == 0) return;
        Posicion* poscDerecha = personajeDerecha->getPosicion();
        Posicion* poscIzquierda = personajeIzquierda->getPosicion();
        //los ultimos se separaron tonto que es imposible que haya otra colision
        if((poscDerecha->obtenerInformacionX())[0] > (poscIzquierda->obtenerInformacionX())[0]) return;
        */
        if (cantidadDeEnemigosVivos == 0) return;
        for(int i = 0; i < cantidadDePersonajes; i ++)
        {
            if (personajes[i]->estaMuerto()) continue;
            for(int j = 0; j < cantidadDeEnemigos; j++)
            {
                if (enemigos[j]->estaMuerto()) continue;
                if(personajes[i]->colisionaCon(enemigos[j]->getPosicion())){
                    personajes[i]->restarVida();
                    if(personajes[i]->estaMuerto()) cantidadDePersonajesVivos--;
                    personajes[i]->mover();
                    this->setPersonajesDerechaIzquierda();
                }
            }
        }
    }
}

int compararDistancias(desaparecido elemento1, desaparecido elemento2)
{
    return (elemento1.distanciaRecorrida >  elemento2 . distanciaRecorrida) ? 1: -1;
}

vector<struct desaparecido> Juego::getDesaparecidos()
{

    for(int i = 0; i < cantidadDePersonajes; i ++)
    {
        if(personajes[i]->estaMuerto())
        {
            struct desaparecido aux;
            aux.nombre = personajes[i]->getNombre();
            aux.distanciaRecorrida = personajes[i]->getDistanciaRecorrida();
            desaparecidos.push_back(aux);
        }
    }
    //int size_ = cantidadDePersonajes - cantidadDeEnemigosVivos;
    sort(desaparecidos.begin() ,desaparecidos.end(), compararDistancias);
    return desaparecidos;
}

int main()
{
    Juego* juego = new Juego();
    juego->gameLoop();
    vector<struct desaparecido> desaparecidos = juego->getDesaparecidos();
    vector<struct desaparecido>::iterator desaparecidos_it;
    for(desaparecidos_it = desaparecidos.begin(); desaparecidos_it!= desaparecidos.end(); ++desaparecidos_it){
        cout<< (*desaparecidos_it).nombre<< " " << (*desaparecidos_it).distanciaRecorrida << "\n";
    }
    return 0;
}
