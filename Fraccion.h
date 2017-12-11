#pragma once

#include <stdlib.h>
#include <algorithm>

class Fraccion {
private:
    long num, den;

public:
    Fraccion();
    Fraccion(std::string);
    Fraccion(long n, long d);

    long get_num();
    long get_den();

    Fraccion operator-() const;
    Fraccion operator+(const Fraccion& f);
    Fraccion operator-(const Fraccion& f);
    Fraccion operator*(const Fraccion& f);
    Fraccion operator/(const Fraccion& f);
    bool operator<(const Fraccion& cmp);
    bool operator==(const Fraccion& cmp);
};

