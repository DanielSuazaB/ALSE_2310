#include "Polinomio.h"

int main(){
    Polinomio a("3X^2+5");
    Polinomio b("6X^2+8X^3-7");

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    b.ordenar();

    std::cout << "ordenado: " << b << std::endl;

    Polinomio c = b / 8.;
    std::cout << "Dividido por " << 8 << ": " << c << std::endl;

    Polinomio d = a + b;
    std::cout << "Sumandos: " << d << std::endl;

    Polinomio e = a - b;
    std::cout << "Restados: " << e << std::endl;
    return 0;
}
