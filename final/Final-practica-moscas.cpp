#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

class Mosca
{
    private:
        bool muerta = false;
        int id;

    public:

    double velocidad = 10.00/1000000.00;
    double xi,yi,xd,yd;


    void mover(){
        this->xi -= velocidad;
        this->xd -= velocidad;

    }

    void setPosicion(double x, double y, int id){
        this->xi = x;
        this->yi = y;
        this->xd = x + 1.00;
        this->yd = y + 1.00;
        this->id = id;
    }

    void matar(){
        muerta = true;
    }

    bool estaMuerta(){
        return muerta;
    }
};

class Personaje
{

    private:
        string id;
        int vida;
        bool muerto = false;
    public:

            double xi, xd, yd, xInicial, velocidad;

        void setDatos(string id, double xi, double xd, double yd, double velocidad, int vida){
            this->id = id;
            this->xInicial = xi;
            this->xi = xi;
            this->xd = xd;
            this->yd = yd;
            this->velocidad = velocidad;
            this->vida = vida;
        }

        bool colision(Mosca* mosca, bool empezado){

            bool impactoDerecho = mosca->xi <= xd && mosca->xd >= xd;
            bool dentroDelPersonaje = mosca->xi >= xi && mosca->xd <= xd;
            bool impactoIzquierdo = mosca->xi <= xi && mosca->xd >= xi;
            bool mismaAltura = mosca->yi <= yd;

            if( ( impactoIzquierdo || impactoDerecho || dentroDelPersonaje )  && mismaAltura  ){
                this->quitarVida();
                mosca->matar();
                return true;
            }
            else return false;

        }

        void quitarVida(){
            vida -= 1;
            if(vida <= 0) muerto = true;
        }

        bool estaMuerto(){
            return muerto;
        }

        double distanciaRecorrida(){
            return xi - xInicial;
        }

        void mover(){
            this->xi += velocidad;
            this->xd += velocidad;
        }

        string getId(){
            return id;
        }
};

class Juego
{
    private:
        vector<Personaje*> personajes;
        vector<Mosca*> moscas;
        bool empezado = false;

    public:

        Personaje* funcionDeComparacion(Personaje* pj1, Personaje* pj2){
        if(pj1->distanciaRecorrida() <= pj2->distanciaRecorrida()) return pj1;
        return pj2;
        }

        Juego(vector<Personaje*> personajes, vector<Mosca*> moscas){
            this->personajes = personajes;
            this->moscas = moscas;
        }

        void play(int cantSegundos){

            int segundos = 0;
            vector< Personaje* > muertos;

            while(segundos < cantSegundos){
                if(segundos > 0) empezado = true;
                if(empezado){
                    for(auto mosca:moscas) if(!mosca->estaMuerta()) mosca->mover();
                    for(auto personaje:personajes) if(!personaje->estaMuerto()) personaje->mover();
                }
                for(auto personaje:personajes){
                    for(auto mosca:moscas){

                        if(personaje->estaMuerto()) break;
                        if(mosca->estaMuerta()) continue;

                        personaje->colision(mosca, empezado);
                        if(personaje->estaMuerto()){
                            muertos.push_back(personaje);
                        }
                    }
                }
                segundos ++;
            }

            for(auto muerto:muertos){
                cout << muerto->getId() << " duro: " << muerto->distanciaRecorrida() << endl;
            }
        }

};

vector<string> split(string linea){
    vector<string> palabras;
    string palabra = "";
    for(int i = 0; i <= linea.size() ; i++){
        if(linea[i] == ' ' or linea[i] == '\0'){
            palabras.push_back(palabra);
            palabra = "";
        }
        else palabra = palabra + linea[i];
    }
    return palabras;
}


vector<Personaje*> cargarPersonajes(string path){

    fstream archivo(path);
    string linea;
    vector<Personaje*> personajes;
    vector<string> datos;

    if(!archivo.is_open()) archivo.open(path, ios::in);

     while(getline(archivo, linea)){
        datos = split(linea);
        Personaje* personaje = new Personaje();
        string id = datos[0];
        double xi = atof(datos[1].c_str());
        double xd = atof(datos[2].c_str());
        double yd = atof(datos[3].c_str());
        double velocidad = atof(datos[4].c_str()) / 1000000.00;
        int vida = stoi(datos[5]);
        personaje->setDatos(id, xi, xd, yd, velocidad, vida);

        personajes.push_back(personaje);
    }
    archivo.close();
    return personajes;
}

vector<Mosca*> cargarMoscas(string path){

    fstream archivo(path);
    string linea;
    vector<Mosca*> moscas;
    vector<string> datos;

    if(!archivo.is_open()) archivo.open(path, ios::in);
    int id = 0;
     while(getline(archivo, linea)){
        datos = split(linea);
        Mosca* mosca = new Mosca();
        double x = atof(datos[0].c_str());
        double y = atof(datos[1].c_str());
        mosca->setPosicion(x, y, id);
        moscas.push_back(mosca);
        id ++;
    }
    archivo.close();
    return moscas;
}

int main(){

    string linea;
    vector<Personaje*> personajes;
    vector<Mosca*> moscas;

    personajes = cargarPersonajes("personajes.txt");
    moscas = cargarMoscas("moscas.txt");

    Juego* juego = new Juego(personajes, moscas);
    juego->play(5000000);
}









