#include <iostream>
#include <cmath>
#include <complex>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

/*  La forma de llamar al programa será:
    eje10 ../datos.txt
*/

int main(int argc, char** argv){
//  cout << argc << endl;
  if( argc != 2 ){
    cout << "Debe pasar la url del archivo que contiene los números complejos.";
    return 1;
  }
  
  int i=0;
  size_t pos=0;
  string a, b;
  double r, im;
  bool again;
  complex<double> aux;

  string   texto;
  vector< complex<double> > vec;

  ifstream input( argv[1] );

  while( getline( input, texto) ){
    // Aquí se leyó la línea y ahora falta procesarla para extraer la
    // parte real y a parte imaginaria  ej: -3.14 + 2.67j

//    cout << texto << endl;
    pos = texto.find_first_not_of(".,0123456789", 1 );
    a = texto.substr( 0, pos);
    a.erase( remove( a.begin(), a.end(), ' '), a.end() );
    b =  texto.substr( pos, texto.length() - pos - 1);
    b.erase( remove( b.begin(), b.end(), ' ' ), b.end() );
    r = stod( a.c_str());
    im = stod( b.c_str() );
    aux.real( r );
    aux.imag( im );
//    cout << aux << endl;
    vec.push_back( aux );
//    cout << i++ << endl;
  }
  
  input.close();
  


  do{
    again = false;
      
    for( size_t i = 0; i < vec.size(); i++){
      if ( arg( vec[i] ) > arg( vec[i+1] ) ){
        aux = vec[i];
        vec[i] = vec[i+1];
        vec[i+1] = aux;
        again = true;
      }else{
        if( arg( vec[i] ) == arg( vec[i+1] ) ){
          if( norm( vec[i] ) > norm( vec[i+1] ) ){
            aux =  vec[i];
            vec[i] = vec[i+1];
            vec[i+1] = aux;
            again = true;
          }
        }
      }
    }
  }while( again == true ); 


  ofstream output("output.txt");  // Se crea el objeto para abrir el archivo de escritura


  for(size_t  i = 0; i < vec.size(); i++ ){
    output << vec[i].real() << ( vec[i].imag() < 0? " - ": " + " ) << abs( vec[i].imag() ) << "j" << endl;
//    cout << vec[i] << " < " << arg( vec[i] ) << endl;
  }
  
  output.close();  // Se cierra el archivo de escritura.

  return 0;
}

