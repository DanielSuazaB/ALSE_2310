#include <iostream>
#include <math.h>
using namespace std;

class Punto2D{
  double x,y;

public:
  Punto2D();
  Punto2D( Punto2D &a );
  Punto2D(double r, double i );
  double   X();
  bool     X( double r );
  double   Y();
  bool     Y( double i );
  double   distancia( const Complejo &b );
  double   angulo();
  double   magnitud();
  Punto2D operator+(Punto2D &a);
  Punto2D operator-(Punto2D &a);
  Punto2D operator*(Punto2D &a);
  friend   ostream& operator<< (ostream& out, Punto2D &a);
};

