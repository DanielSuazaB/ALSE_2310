/**
 * Project Untitled
 */

#include <iostream>
#include <sstream>

using namespace std;
#include "Polinomio.h"

/**
 * Polinomio implementation
 */


Polinomio::Polinomio() {
    _grado = -1;
    _variable = 0;
}

Polinomio::Polinomio(string pol) {
    _grado = -1;
    _variable = 0;
    redefinir( pol );
}

Polinomio::Polinomio(Polinomio& pol) {
    redefinir( pol.getString() );
}

Polinomio::~Polinomio() {
    borrar();
}

void Polinomio::nuevoTermino(float c, int p) {
    termino a(p,c);
    _terminoL.push_back( a );
    return;
}

void Polinomio::simplificar() {
    std::list<termino>::const_iterator it1, it2;

    float coef= 0.;
    int pot= 0;
    bool suma = false;
    it1 = it2 = _terminoL.begin();
    while( it1 != _terminoL.end() ){
        coef = it1->second;
        it2 = it1;
        ++it2;

        while( it2 != _terminoL.end() ) {
            if( it1->first == it2->first ){
                coef += it2->second;
                pot = it1->first;
                //std::cout << "Simplificar" << pot << std::endl;

                it2 = _terminoL.erase( it2 );
                --it2;
                suma = true;
            }
            ++it2;
            //std::cout << it1->first << ", " << it2->first << std::endl;
            //std::cout << _terminoL.size() << std::endl;
        }

        if( suma ){
            it1 = _terminoL.erase( it1 );
            --it1;
            if (coef != 0. ) _terminoL.insert( it1, termino(pot,coef) );
            suma = false;
        }
        ++it1;
    }
    ordenar();
    return;
}

bool Polinomio::ordenar() {

    _terminoL.sort();
    _terminoL.reverse();

    return true;
}

Polinomio Polinomio::operator +(Polinomio& p) {
    Polinomio c( this->getString() );

    std::list<termino>::const_iterator it;
    for( it = p._terminoL.begin(); it != p._terminoL.end(); ++it)
        c.nuevoTermino( it->second, it->first );

    c.simplificar();
    return c;
}

/**
 * @param p
 * @return Polinomio&
 */
Polinomio Polinomio::operator -(Polinomio& p) {
    Polinomio c( this->getString() );

    std::list<termino>::const_iterator it;
    for( it = p._terminoL.begin(); it != p._terminoL.end(); ++it)
        c.nuevoTermino( - it->second, it->first );

    c.simplificar();
    return c;
}

/**
 * @param p
 * @return Polinomio&
 */
Polinomio Polinomio::operator  *(Polinomio& p) {
    Polinomio res;
    res._variable = _variable;
    std::list<termino>::const_iterator it1, it2;
    for( it1 = _terminoL.begin(); it1 != _terminoL.end(); ++it1 ){
        for( it2 = p._terminoL.begin(); it2 != p._terminoL.end(); ++it2 ){
            res.nuevoTermino( it1->second * it2->second, it1->first + it2->first );
        }
    }

    res.simplificar();
    return res;
}

/**
 * @param f
 * @return Polinomio
 */
Polinomio Polinomio::operator /(float f) {
    Polinomio c;

    c._variable = _variable;
    std::list<termino>::const_iterator it;
    for( it = _terminoL.begin(); it != _terminoL.end(); ++it)
        c.nuevoTermino( it->second / f, it->first );

    c.simplificar();
    return c;
}

ostream& operator << (ostream& stream, Polinomio& p){
    return stream << p.getString();
}
/**
 * @return bool
 */
bool Polinomio::borrar() {
    _terminoL.clear();
    _grado = -1;
    return true;
}

/**
 * @param pol
 * @return bool
 */
bool Polinomio::redefinir(string pol) {
    borrar();
    string term;
    //cout << pol << endl;
    size_t posT1, posT2, found;
    posT1 = posT2 = 0;
    float coeff = 0.;
    int power = 0;

    while( posT2 != string::npos ){
        // Encontrando cada termino
        posT2 = pol.find_first_of("+-", posT2 + 1 );

        //cout << posT1 << " " << posT2 << endl;
        term = pol.substr( posT1, posT2 - posT1 );
        posT1 = posT2;
       // cout << term << endl;

        // Porcesando el termino
        if(_variable == 0){
            //cout << "variable" << endl;
            found = term.find_first_not_of("+-1234567890.,");
            //cout << term[found] << endl;
            if (found != std::string::npos)
              _variable = term[found] ;
        }

        found = term.find( _variable );
        if( found == string::npos ){
            //cout << "independiente" << endl;
            coeff = atof( term.c_str() );
            power = 0;
        }else{
            found = term.find( '^' );
            if( found != string::npos ){ // Tiene potencia > 1
                //cout << "pot >1" << endl;
                power = atoi( term.substr( found+1 ).c_str() );
                coeff = atof( term.substr( 0, term.size() - found +1 ).c_str() );
            }else{
                power = 1;
                coeff = atof( term.substr( 0, term.size() - 1 ).c_str() );
            }
        }

        //cout << "coeff: " << coeff << " y power: " << power << endl;
        // Adicionar el término encontrado
        nuevoTermino( coeff, power );
        _grado = power > _grado ? power : _grado ;
    }
    //cout << getString() << endl;
    return true;
}

string  Polinomio::getString(){
    stringstream stream;
    std::list<termino>::iterator it;
    for(it = _terminoL.begin(); it != _terminoL.end(); ++it){
        if(it != _terminoL.begin() && it->second > 0) stream << "+";
            stream << it->second ;
        if(it->first > 0 ){
            stream << _variable;
            if( it->first > 1 )
                stream << "^" << it->first;
        }
    }
    return stream.str();
}

int Polinomio::getOrden() {
    return _grado;
}

char Polinomio::getVariable() {
    //cout << "Leyendo la variable" << endl;
    return _variable;
}

void Polinomio::setVariable(char value) {
    //cout << "Asignando la variable" << endl;
    _variable = value;
}

