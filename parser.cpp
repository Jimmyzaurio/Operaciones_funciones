#include <iostream>
#include "Funcion.h"

void print(Funcion &info) {
    for (auto &var : info.get_muestras()) {
        std::cout << var.get_num();
        if (var.get_den() > 1)
            std::cout << '/' << var.get_den();
        std::cout << ' ';
    }

    std::cout << std::endl;
    std::cout << info.get_origen() << std::endl;
}

void modifica(std::string &operaciones, Funcion &f) {
    std::stringstream ss(operaciones);
    std::string token;
    
    std::vector<std::string> data;
    while (ss >> token) data.push_back(token);
    
    if (data.size() != 3) return;
    
    Fraccion valor(data.back());
    int ini = data[0].find("-") + 1;
    int fin = data[0].find("n");

    int coeficiente = 1;
    if (ini < fin)
        coeficiente = stoi(data[0].substr(ini, fin - ini));

    int signo = 1;
    if (data[1][0] == '-')
        signo = -1;

    int interpolar = valor.get_den();
    int desplazar  = signo * valor.get_num();
    int diezmar    = valor.get_den() * coeficiente;

    f.interpolar_Lineal(interpolar);
    f.desplazar(desplazar);
    f.diezmar(diezmar);

    if (data[0][0] == '-')
        f.reflejar();
}

int main() {
    //std::string operaciones = "n   -   1/2";
    std::string operaciones = "-n   -  0";
    //std::string muestras = "-23, 0.5, 5/7, -4/1, 45";
    std::string muestras = "-3, 0.5, 0.75, 3/2, -1, 11, 4, 2, 10";

    Funcion info(muestras, 2);
    modifica(operaciones, info);
    print(info);
    return 0;
}

