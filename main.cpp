#include <iostream>
#include <string>
#include <bitset>
#include "Simulador.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
using namespace std;

int main() {
    int archivo;
    char *byte;
    struct stat statbf;
	cout<<"\t\tBienvenido"<<endl<<endl;
    archivo = open( "steam_games2023.csv" , O_RDONLY ); 
    
    if( archivo == -1 ){
        cout << "No se entrar al steam_games"<<endl;
        exit(1);
    }

    if( fstat( archivo , &statbf ) == -1 ){ 
        cout << "Error al intentar obtener informacion de la estructura de datos."<<endl;
        exit(1);
    }

    byte = (char*) mmap( NULL , statbf.st_size, PROT_READ, MAP_PRIVATE, archivo, 0); 

    if( byte == MAP_FAILED ){
        cout << "Hubo un error al mapear el steam_games en memoria"<<endl; exit(1);
    }
    Simulador memoriaCache(4,0);//numerode bloques && tam de bloques
    float porcentaje = 0;
	unsigned long int valor = 0,totales = 0,direccion = 0;
    int nAciertos=0, nFallos=0;
    string campo;
    char unidad;
    size_t size = statbf.st_size, contador=0;
    
    cout<<"\t\tCargando..."<<endl;
    
    while(contador < size){
        unidad =*(byte++);
        if(unidad == ','){
        	//cout<<campo<<endl;
        	//cout<<"paso 1"<<endl;
        	direccion = memoriaCache.DirHexToDec(campo);
        	memoriaCache.MemoriaAsociativaConjuntos(direccion,2);
        	//cout<<direccion<<endl;
        	totales++;
        	campo = "";
		}else{
			campo += unidad;
		}
			contador++;
    }
    
    close(archivo);
    porcentaje = ((float)memoriaCache.getHit()/totales)*100;
    
	cout<<"\tFallos:"<<memoriaCache.getMiss()<<endl;
	cout<<"\tAcierto:"<<memoriaCache.getHit()<<endl;
	cout<<"\tPorcentaje De Acierto: "<<porcentaje<<"%"<<endl;
	
    return 0;
}




