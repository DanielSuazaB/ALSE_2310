#include <iostream>
#include <math.h>
#include "complejo.h"

using namespace std;

int main(int argc, char** argv){
//  cout << argc << endl;
  if( argc != 11 ){
    cout << "Debe pasar 5 números complejos.";
    return 1;
  }

  Complejo vec[5];

  for(int  i = 0; i < 5; i++ ){
    vec[i].setRe( atof( argv[2*i + 1] ) );
    vec[i].setIm( atof( argv[2*i + 2] ) );
  }

  bool again;
  Complejo aux;

  do{
    again = false;
      
    for( int i = 0; i < 4; i++){

      if ( vec[i].angulo() > vec[i+1].angulo() ){
        aux = vec[i];
        vec[i] = vec[i+1];
        vec[i+1] = aux;
        again = true;
      }else{
        if( vec[i].angulo() == vec[i+1].angulo() ){
          if( vec[i].magnitud() > vec[i+1].magnitud() ){
            aux =  vec[i];
            vec[i] = vec[i+1];
            vec[i+1] = aux;
            again = true;
          }
        }
      }
    }
  }while( again == true ); 

  for(int  i = 0; i < 5; i++ ){
    cout << vec[i] << "<" << vec[i].angulo() << endl;
  }

  return 0;
}

