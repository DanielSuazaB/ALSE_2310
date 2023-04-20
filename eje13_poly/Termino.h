/**
 * Project Untitled
 */


#ifndef _TERMINO_H
#define _TERMINO_H
#include <iostream>

using namespace std;

class Termino {
public:
    Termino(float c, int p);

    float getC(){return _coeficiente;}
    int getP(){return _potencia;}
    void setC(float& c){_coeficiente = c;}
    void setCP(float& c, int& p){_coeficiente = c; _potencia = p;}
    void setSiguiente(Termino* ptr){ _siguiente = ptr;}
    Termino* getSiguiente(){return _siguiente;}

private:
    float       _coeficiente;
    int         _potencia;
    Termino*    _siguiente;
    Termino();
};

#endif //_TERMINO_H
