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



  for(int  i = 0; i < 5; i++ ){
    cout << vec[i] << endl;
  }

  return 0;
}

