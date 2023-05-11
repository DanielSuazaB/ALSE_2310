#include "db_local.h"
#include "medicion.h"
#include "sensor.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv){
    Medicion med, prom;
    DB_Local db;
    Sensor   sensor;
    
    while( true ){
        delay( 5000 );
        sensor.actualizar( med );
        db.Abrir_DB();
        db.Ingresar( med );
        db.Recuperar( prom );
        cout << "Promedio: "  << prom << endl;
        db.Cerar_DB();
     }
    return 0;
}
