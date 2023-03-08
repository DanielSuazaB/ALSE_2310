#include <iostream>
#include <math.h>
#include "complejo.h"

using namespace std;
// Utilizando los parámetros del main admita 4 valores el primero dos caracteres
// y luego cuatro valores reales que correspondan a dos números complejos
// ejemplo:  $> ./ej8 -a 3.14 4.68 8.55 6.68
//  los caracteres podrán ser -a -r -i -c para adición, resta, inverso y
//  conjugado. Dependiendo de estos dos caracteres, se debe ejecutar la 
//  operación correspondiente en el main y mostrar su resultado en pantalla 
//  hacendo uso de la estructura switch. Para convertir de cadena de texto a 
//  número real se puede utilizar la función atof.
//
//  Deberán implementar correctamente en el archivo complejo.cpp todos 
//  los métodos definidos en el archivo complejo.h

int main(int argc, char** argv){
//  cout << argc << endl;
  if( argc != 6 ){
    cout << "Debe pasar [-a, -i, -c, -r] y cuatro números";
    return 1;
  }

  Complejo a, b( a ), tercero(8.9, 9.8);
  double dist;

  a.setRe( atof( argv[2] ) );
  a.setIm( atof( argv[3] ) );
  b.setRe( atof( argv[4] ) );
  b.setIm( atof( argv[5] ) );

  switch( argv[1][1] ){
    case 'a':
      cout << "Adición" << endl;
      tercero = a + b;
      cout << "La suma de " << a << " + " << b << " es igual a " << tercero << endl;
      break;
    case 'i':
      tercero =  a.inverso();
      cout << "El inverso de " << a << " es " << tercero << endl;
      break;
    case 'r':
      tercero = a - b;
      cout << "La diferencia entre " << a << " y " << b << " es " << tercero << endl;
      break;
    case 'c':
      tercero = a.conjugado();
      cout << "El conjugado de " << a << " es " << tercero << endl;
      break;
    default:
      cout << "No reconozco la operación solicitada" << endl;
  }

  return 0;
}
