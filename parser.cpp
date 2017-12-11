#include <iostream>
#include "Funcion.h"

int main() {
    std::string f = "n   -   1/2";
    std::string muestras = "-23, 0.5, 5/7, -4/1, 45";

    std::stringstream ss(f);
    std::string token;

    while (ss >> token)
        std::cout << token << std::endl;
    return 0;
 
    
    Funcion info(muestras);

    for (auto &var : info.get_muestras()) 
        std::cout << var.get_num() << '/' << var.get_den() << std::endl;

    return 0;
}

