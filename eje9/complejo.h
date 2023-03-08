#include <iostream>
#include <math.h>
using namespace std;

class Complejo{
  double re,im;

public:
  Complejo();
  Complejo( Complejo &a );
  Complejo(double r, double i );
  double   getRe();
  bool     setRe( double r );
  double   getIm();
  bool     setIm( double i );
  double   distancia( const Complejo &b );
  double   angulo();
  double   magnitud();
  Complejo operator+(Complejo &a);
  Complejo operator-(Complejo &a);
  Complejo operator*(Complejo &a);
  Complejo conjugado();
  Complejo inverso();
  friend   ostream& operator<< (ostream& out, Complejo &a);
};

