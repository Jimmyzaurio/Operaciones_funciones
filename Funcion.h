#pragma once
    
#include <vector>
#include <sstream>
#include "Fraccion.h"

class Funcion {
private:
    std::vector<Fraccion> muestras;
    int origen;

public:
    Funcion();
    Funcion(std::string&, int);
    std::vector<Fraccion> get_muestras();
    int get_origen();
    void diezmar(int k);
    void interpolar_Cero(int k);
    void interpolar_Lineal(int k);
    void interpolar_Escalon(int k);
    void desplazar(int k);
    void reflejar();

    Funcion operator-() const;
    Funcion operator+(const Funcion& f);
    Funcion operator-(const Funcion& f);
    Funcion operator*(const Funcion& f);
};

