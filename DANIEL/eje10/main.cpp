#include <iostream>
#include <cmath>
#include <complex>
#include <fstream>
#include <string>

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

  int      lineas = 0;
  string   texto, realnum, imagnum, signo;
  ifstream input( argv[1] );
  while( getline( input, texto) ){
    lineas++;
  }
  
  input.close();
  
  cout << "Leídas " << lineas << " líneas." << endl;
  complex<double> *vec = new complex<double>[lineas] ;


  input.open( argv[1] );

  for(int  i = 0; i < lineas; i++ ){
    //getline( input, texto);
    getline(input, texto);
    stringstream textolinea(texto);
    getline(textolinea,realnum, ' ');
    getline(textolinea, signo, ' ');
    getline(textolinea, imagnum, ' ');

    vec[i].real( stod( realnum ) );
    if (signo == "+"){
        vec[i].imag( stod( imagnum ) );
    }else{vec[i].imag( -1*(stod( imagnum) ) );}
  }
  input.close();
  bool again;
  complex<double> aux;

  do{
    again = false;
      
    for( int i = 0; i < 4; i++){


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
  for (int i = 0; i < lineas; i++){
      cout <<"elementos ordenados: " <<vec[i]<<endl;
  }
  ofstream output("output.txt");


  for(int  i = 0; i < lineas; i++ ){
    output << vec[i].real() << ( vec[i].imag() < 0? " - ": " + " ) << vec[i].imag() << "j" << endl;
    cout << vec[i] << "<" << arg( vec[i] ) << endl;
  }
  
  output.close();

  return 0;
}

