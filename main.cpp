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
    Simulador memoriaCache(16,16);//numerode bloques && tam de bloques
    long int valor = 0,totales = 0,direccion = 0;
	float porcentaje = 0;
        int fd;
        char *byteAddr;
        struct stat statbf;
		cout<<"Bienvenido";
        fd = open( "steam_games2023.csv" , O_RDONLY ); 

        if( fd == -1 ){
            cout << "No se pudo devolver el descriptor de archivo"<<endl;
            exit(1);
        }

        if( fstat( fd , &statbf ) == -1 ){ 
            cout << "Error al intentar obtener informacion de la estructura de datos."<<endl;
            exit(1);
        }

        byteAddr = (char*) mmap( NULL , statbf.st_size, PROT_READ, MAP_PRIVATE, fd, 0); 

        if( byteAddr == MAP_FAILED ){
            cout << "Hubo un error al mapear el fichero en memoria"<<endl; exit(1);
        }

        float tasa_aciertos=0;
        int nAciertos=0, nFallos=0;
        string campo;
        char c;
        size_t aSize = statbf.st_size, cont=0;

        while(cont < 5000)
        {
        	c =*(byteAddr++);
        	if(c == ','){
        		//cout<<campo<<endl;
        		//cout<<"paso 1"<<endl;
        		direccion = memoriaCache.DirHexToDec(campo);
        		memoriaCache.MemoriaDirecta(direccion);
        		//cout<<direccion<<endl;
        		totales++;
        		campo = "";
			}else{
				campo += c;
			}
			cont++;
        }

        close(fd);
	cout<<"\tFallos:"<<memoriaCache.getMiss()<<endl;
	cout<<"\tAcierto:"<<memoriaCache.getHit()<<endl;
	porcentaje = ((float)memoriaCache.getHit()/totales)*100;
	cout<<"\tPorcentaje De Acierto: "<<porcentaje<<"%"<<endl;	
    return 0;
}




