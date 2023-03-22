#include <iostream>
#include <math.h>
#include "punto2d.h"

using namespace std;

bool Punto2D::X( double r ){ 
  x = r; 
  return true;
}

bool Punto2D::X( double i ){ 
  y = i; 
  return true;
}

double Punto2D::distancia( const Punto2D &b ){
    double dx = b.x - x;
    double dy = b.y - y;
    return sqrt( dx * dx  + dy * dy );
}

double Punto2D::angulo(){
  return atan2(y, x);
}

double Punto2D::magnitud(){
  return sqrt(x*x + y*y);
}

Punto2D Punto2D::operator+(Punto2D &a){
    Punto2D c;
    c.x = x + a.x;
    c.y = y + a.y;
    return c;
  }

ostream& operator<< (ostream& out, Punto2D &a){
  out  << "( " << a.x << ", " << a.y << " )";
  return out;
}
  

Punto2D::Punto2D()
{
    x = y = 0.;
}

Punto2D::Punto2D(Punto2D &a)
{
  x = a.x;
  y = a.y;
}

Punto2D::Punto2D(double r, double i)
{
  x = r;
  y = i;
}

double   Punto2D::X(){
  return re;
}

double    Punto2D::Y(){
  return im;
}

Punto2D  Punto2D::operator-(Punto2D &a){
  Complejo c;
  c.re = re - a.re;
  c.im = im - a.im;
  return c;
}







