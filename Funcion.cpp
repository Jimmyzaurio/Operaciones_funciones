#include "Funcion.h"

Funcion::Funcion() {}

Funcion::Funcion(std::string &data, int centro) : origen(centro) {
    std::stringstream ss(data);
    std::string token;

    while (std::getline(ss, token, ',')) {
        // PONER VALIDACION DE BASURA
        muestras.push_back(Fraccion(token));
    }
}

std::vector<Fraccion> Funcion::get_muestras() { return muestras; }

int Funcion::get_origen() { return origen; }

void Funcion::diezmar(int k) {
    if (k < 2) return;

    int ini = origen;
    while (ini - k >= 0) 
        ini -= k;
    
    int idx = 0;
    while (ini < muestras.size()) {
        if (ini == origen) origen = idx;
        muestras[idx++] = muestras[ini];
        ini += k;
    }

    muestras.resize(idx);
}

void Funcion::interpolar_Cero(int k) {
    origen = k * origen;
    
    std::vector<Fraccion> temp;
    for (int i = 0; i < muestras.size() - 1; ++i) {
        temp.push_back(muestras[i]);

        for (int j = 1; j < k; ++j)
            temp.push_back(Fraccion());
    }

    temp.push_back(muestras.back());
    muestras = temp;
}

void Funcion::interpolar_Escalon(int k) {
    origen = k * origen;

    std::vector<Fraccion> temp;
    for (int i = 0; i < muestras.size() - 1; ++i) {
        temp.push_back(muestras[i]);

        for (int j = 1; j < k; ++j)
            temp.push_back(muestras[i]);
    }

    temp.push_back(muestras.back());
    muestras = temp;
}

void Funcion::interpolar_Lineal(int k) {
    if (k < 2) return;
    origen = k * origen;

    std::vector<Fraccion> temp;
    for (int i = 0; i < muestras.size() - 1; ++i) {
        temp.push_back(muestras[i]);

        Fraccion promedio = (muestras[i + 1] - muestras[i]) / Fraccion(k, 1);
        for (int j = 1; j < k; ++j)
            temp.push_back(muestras[i] + Fraccion(j, 1) * promedio);
    }

    temp.push_back(muestras.back());
    muestras = temp;
}

void Funcion::desplazar(int k) {
    if (origen + k >= muestras.size()) {
        while (origen + k >= muestras.size())
            muestras.push_back(Fraccion());
    } else if (origen + k  < 0) {
        while (origen + k < 0)
            muestras.insert(muestras.begin(), Fraccion()), ++origen;
    }

    origen += k;
}

void Funcion::reflejar() {
    std::reverse(muestras.begin(), muestras.end());
    origen = muestras.size() - origen - 1;
}

Funcion Funcion::operator-() const {
    Funcion aux;
    aux.origen = origen;
    aux.muestras = muestras;

    for (int i = 0; i < aux.muestras.size(); ++i)
        aux.muestras[i] = aux.muestras[i] * Fraccion(-1, 1);

    return aux;
}

Funcion Funcion::operator+(const Funcion& b) {
    int tam_A = this->muestras.size();
    int tam_B = b.muestras.size();

    int tam = std::max(this->origen, b.origen) + 
              std::max(tam_A - this->origen, tam_B - b.origen);

    std::vector<Fraccion> res(tam);

    int i = this->origen;
    int j = b.origen;

    while (i >= 0 || j >= 0) {
        Fraccion suma;
        if (i >= 0) suma = suma + this->muestras[i];
        if (j >= 0) suma = suma + b.muestras[j];

        res[std::max(i, j)] = suma;
        
        --i, --j;
    }

    i = this->origen + 1;
    j = b.origen + 1;

    while (i < tam_A || j < tam_B) {
        Fraccion suma;
        if (i < tam_A) suma = suma + this->muestras[i];
        if (j < tam_B) suma = suma + b.muestras[j];

        res[std::max(i, j)] = suma;
        
        ++i, ++j;
    }
    
    Funcion g;
    g.origen = std::max(this->origen, b.origen);
    g.muestras = res;

    return g;
}

Funcion Funcion::operator-(const Funcion& f) {
    return *this + -f; // a - b = a + (-b)
}

Funcion Funcion::operator*(const Funcion& b) {
    int tam_A = this->muestras.size();
    int tam_B = b.muestras.size();

    int tam = std::max(this->origen, b.origen) + 
              std::max(tam_A - this->origen, tam_B - b.origen);

    std::vector<Fraccion> res(tam);

    int i = this->origen;
    int j = b.origen;

    while (i >= 0 || j >= 0) {
        Fraccion h, k;
        if (i >= 0) h = this->muestras[i];
        if (j >= 0) k = b.muestras[j];

        res[std::max(i, j)] = h * k;
        
        --i, --j;
    }

    i = this->origen + 1;
    j = b.origen + 1;

    while (i < tam_A || j < tam_B) {
        Fraccion h, k;
        if (i < tam_A) h = this->muestras[i];
        if (j < tam_B) k = b.muestras[j];

        res[std::max(i, j)] = h * k;
        
        ++i, ++j;
    }
    
    Funcion g;
    g.origen = std::max(this->origen, b.origen);
    g.muestras = res;

    return g;
}

