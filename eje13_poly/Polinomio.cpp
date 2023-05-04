#include "Polinomio.h"
#include "Termino.h"

#include <sstream>

Polinomio::Polinomio(){
    _grado = -1;
    _variable = 'X';
    _polCabeza = NULL;
}

Polinomio::Polinomio(std::string pol){
    _grado = -1;
    _variable = 'X';
    _polCabeza = NULL;
    redefinir( pol );
}

Polinomio::Polinomio(const Polinomio &p){
    if( this != &p ){
        _grado = p._grado;
        _variable = p._variable;
        _polCabeza = NULL;

        Termino *ptr = p._polCabeza;
        while( ptr != NULL ){
            nuevoTermino( ptr->getC(), ptr->getP() );
            ptr = ptr->getSiguiente();
        }
    }
}

Polinomio::~Polinomio(){
    borrar();
}

bool Polinomio::redefinir(std::string pol) {
    borrar();

    if( pol == "" ) return true;

    bool vardefinida = false;
    std::string term;
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
        //cout << term << endl;

        // Porcesando el termino
        if( vardefinida == false ){
            //cout << "variable" << endl;
            found = term.find_first_not_of("+-1234567890.,");

            if (found != std::string::npos){
              //cout << term[found] << endl;
              _variable = term[found] ;
              vardefinida = true;
            }
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
    //std::cout << getString() << endl;
    return true;
}

Polinomio Polinomio::operator +(Polinomio &p){
    Polinomio c;
    c.redefinir( getString() );
    
    Termino* temp = p._polCabeza;
    
    while( temp != nullptr ){
        c.nuevoTermino(temp->getC(), temp->getP() );
        temp = temp->getSiguiente();
    }
    c.simplificar();
    return c;
}

Polinomio Polinomio::operator *(Polinomio &p){
   Polinomio c;
   return c;
}

void Polinomio::operator =(Polinomio &p){
    redefinir( p.getString() );
}

Polinomio Polinomio::operator -(Polinomio &p){
    Polinomio c;
    Termino* temp = _polCabeza;
    
    while( temp != nullptr ){
        c.nuevoTermino(temp->getC(), temp->getP() );
        temp = temp->getSiguiente();
    }
    
    temp = p._polCabeza;
    while( temp != nullptr ){
        c.nuevoTermino(- temp->getC(), temp->getP() );
        temp = temp->getSiguiente();
    }

    c.simplificar();
    return c;
}

Polinomio Polinomio::operator /(float f){
    Polinomio c;
    Termino* temp = _polCabeza;
    
    while( temp != nullptr ){
        c.nuevoTermino( temp->getC() / f , temp->getP() );
        temp = temp->getSiguiente();
    }
    
    return c;
}

std::ostream& operator<<(std::ostream &stream, Polinomio &p){
    //cout << "entrando <<" << std::endl;
    return stream << p.getString();
}

bool Polinomio::borrar(){
    Termino *ptr, *ptr2;
    ptr = _polCabeza;

    while( ptr != NULL ){
       ptr2 = ptr->getSiguiente();
       delete ptr;
       ptr = ptr2;
    }

    _polCabeza = NULL;
    _grado = -1;
    return true;
}

int Polinomio::getGrado(){
   return _grado;
}

char Polinomio::getVariable(){
   return _variable;
}

void Polinomio::nuevoTermino(float c, int p){
    Termino* nuevo = new Termino(c,p);
    //cout << nuevo << endl;
    //cout << nuevo->getSiguiente() << endl;

    if( _polCabeza == NULL )
        _polCabeza = nuevo;
    else{
        Termino* temp = _polCabeza;
        while(temp->getSiguiente() != NULL){
           temp = temp->getSiguiente();
           //cout << temp << endl;
        }

        //cout << "agregando al final" << endl;

        temp->setSiguiente( nuevo );
        //cout << nuevo << " y " << temp->getSiguiente() << endl;
        //nuevo->setSiguiente( NULL );
    }
    _grado = _grado < p ? p : _grado;
}

void Polinomio::simplificar(){
  Termino *t1, *t2, *t3;
  t1 = _polCabeza;

  while(t1 != NULL){
    t2 = t1->getSiguiente();
    while(t2 != NULL){
      if(t1->getP() == t2->getP() ){
        t1->setC( t1->getC() + t2->getC() );  // Actualizo el valor de C del primer término
        // Ahora debo borrar el segundo término sin perder la conexión de la lista
        t3 = t1->getSiguiente();
        while(t3->getSiguiente() != t2 ){
          t3 = t3->getSiguiente();
        }
        t3->setSiguiente( t2->getSiguiente() );
        delete t2;
        t2 = t3;
      }
      t2 = t2->getSiguiente();
    }
    t1 = t1->getSiguiente();
  }

}

bool Polinomio::ordenar(){
    Termino *t1, *t2, *temp, *aux;
    int cont = 1, p;
    t1 = _polCabeza;
    while (cont != 0){
        cont = 0;
        while (t1 != nullptr ){
            t2 = t1 -> getsiguiente();
            if (t2 != nullptr && t1->getP() < t2->getP()){
                temp = t2->getSiguiente();
                t2->setSiguiente(t1);
                t1->setSiguiente( temp );
                if(t1 == _polCabeza){
                    _polCabeza = t2;
                }else{
                    aux = _polCabeza;
                    while (aux->getSiguiente() != t1 )
                        aux = aux->getSiguiente();
                    
                    aux->setSiguiente(t2);
                }
                t2 = temp;
                cont++;
            }
            t1 = t2;
        }
    }
    
    return true;
}

std::string Polinomio::getString() {
    //cout << "Entrando a getString()" << endl;
    stringstream stream;
    Termino* temp = _polCabeza;
    while( temp != NULL ){
        if(temp != _polCabeza && temp->getC() > 0) stream << "+";
        stream << temp->getC();
        if(temp->getP() > 0 ){
            stream << _variable;
            if( temp->getP() > 1 )
                stream << "^" << temp->getP();
        }
        temp = temp->getSiguiente();
    }
    return stream.str();
}
