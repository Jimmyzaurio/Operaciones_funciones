#include "Fraccion.h"

long Expo(long a, long n) {
    long ans = 1;

    for (; n; n >>= 1) {
        if (n & 1) ans *= a;
        a *= a;
    }

    return ans;
}

Fraccion::Fraccion() : num(0), den(1) {}

Fraccion::Fraccion(std::string cad) {
    int idx_division = cad.find("/");
    int idx_decimal  = cad.find(".");

    if (idx_decimal > 0) {
        int tam   = cad.size();
        int punto = cad.find(".");
        Fraccion ans(stol(cad.substr(0, punto)), 1);

        int cycle = cad.find("(");
        int  L = (cycle < 0 ? tam : cycle) - punto - 1;
        long n = (L > 0 ? stol(cad.substr(punto + 1, L)) : 0);
        ans    = ans + Fraccion(n, Expo(10, L));

        int offset = L;
        L   = tam - cycle - 2;
        n   = (cycle > 0 ? stol(cad.substr(cycle + 1, L)) : 0);
        ans = ans + Fraccion(n, stol(std::string(L, '9')) * Expo(10, offset));

        num = ans.num;
        den = ans.den;
    } else {
        num = std::stol(cad.substr(0, idx_division));
        den = 1;
        if (idx_division > 0)
            den = std::stol(cad.substr(idx_division + 1, cad.size() - idx_division - 1));
    }
}

Fraccion::Fraccion(long n, long d) {
    if (d < 0) n = -n, d = -d;
    long gcd = std::__gcd(abs(n), abs(d));
    num = n / gcd, den = d / gcd;
}

long Fraccion::get_num() {
    return num;
}

long Fraccion::get_den() {
    return den;
}

/*
std::string Fraccion::toDecimal() {
    std::string decimal = to_std::string(num/den) + '.';
    if (num % den == 0)
        return decimal += "0";
    
    int rem = num % den;
    unordered_set<int> rept;
    vector<int> digit, R; // R -> residuos

    while (rem && !rept.count(rem)) {
        rept.insert(rem);
        R.push_back(rem);
        rem *= 10;
        digit.push_back(rem / den);
        rem %= den; 
    }

    for (int i = 0; i < digit.size(); ++i) {
        if (rem && R[i] == rem) // Empieza lo periodico
            decimal += '(';
        decimal += (digit[i] + '0');
    }
    if (rem)
        decimal += ')';
    return decimal;
}
*/

Fraccion Fraccion::operator-() const {
    return Fraccion(-num, den);
}

Fraccion Fraccion::operator+(const Fraccion& f) {
    long gcd = std::__gcd(den, f.den);
    return Fraccion(
        num * (f.den / gcd) +
        f.num * (den / gcd),
        den * (f.den / gcd)
    );
}

Fraccion Fraccion::operator-(const Fraccion& f) {
    return *this + -f; // a - b = a + (-b)
}

Fraccion Fraccion::operator*(const Fraccion& f) {
    return Fraccion(num * f.num, den * f.den);
}

Fraccion Fraccion::operator/(const Fraccion& f) {
    return Fraccion(num * f.den, den * f.num);
}

bool Fraccion::operator<(const Fraccion& cmp) {
    long gcd = std::__gcd(den, cmp.den);
    return num * (cmp.den / gcd) <
           cmp.num * (den / gcd);
}

bool Fraccion::operator==(const Fraccion& cmp) {
    long gcd = std::__gcd(den, cmp.den);
    return num * (cmp.den / gcd) ==
           cmp.num * (den / gcd);
}

