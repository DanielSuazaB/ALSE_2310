#include <iostream>
#include <math.h>
#include "complejo.h"

using namespace std;

bool Complejo::setRe( double r ){ 
  re = r; 
  return true;
}

bool Complejo::setIm( double i ){ 
  im = i; 
  return true;
}

double Complejo::distancia( const Complejo &b ){
    double x = b.re - re;
    double y = b.im - im;
    return sqrt( x * x  + y * y );
}

double Complejo::angulo(){
  return atan2(im, re);
}

double Complejo::magnitud(){
  return sqrt(re*re + im*im);
}

Complejo Complejo::operator+(Complejo &a){
    Complejo c;
    c.re = re + a.re;
    c.im = im + a.im;
    return c;
  }

ostream& operator<< (ostream& out, Complejo &a){
  out  << a.re << (a.im < 0? " - ":" + ") << abs(a.im) << "j";
  return out;
}
  

Complejo::Complejo()
{
    re = im = 0.;
}

Complejo::Complejo(Complejo &a)
{
  re = a.re;
  im = a.im;
}

Complejo::Complejo(double r, double i)
{
  re = r;
  im = i;
}

double   Complejo::getRe(){
  return re;
}

double    Complejo::getIm(){
  return im;
}

Complejo  Complejo::operator-(Complejo &a){
  Complejo c;
  c.re = re - a.re;
  c.im = im - a.im;
  return c;
}

Complejo  Complejo::operator*(Complejo &a){
  Complejo c;
  c.re = re * a.re - im * a.im;
  c.im = re * a.im + im * a.re;
  return c;
}

Complejo  Complejo::conjugado(){
  Complejo c;
  c.re = re;
  c.im = -im;
  return c;
}

Complejo  Complejo::inverso(){
  Complejo c;
  double d = re * re + im * im;
  c.re = re / d ;
  c.im = -im / d;
  return c;
}






