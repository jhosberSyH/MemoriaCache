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
void cachePorConjuntos();
void cacheCompletamenteAsociativa();
void cacheDirecta();
/*****************************************************************************************************************************************************/
void cachePorConjuntos(int numeroBloques,int sizeBloques,int numeroConjuntos);
void cacheCompletamenteAsociativa(int numeroBloques,int sizeBloques);
void cacheDirecta(int numeroBloques,int sizeBloques);
int menu();
int validarNumero(string num);
void todas();

int main() {
    int iniciar = 0;
    cout<<"\t\tBienvenido"<<endl<<endl;
	do{
		iniciar = menu();
	}while((iniciar < 1) || (iniciar > 4));

	switch(iniciar){
		case 1:
			cacheDirecta();
			break;
		case 2:
			cachePorConjuntos();
			break;
		case 3:
			cacheCompletamenteAsociativa();
			break;
		case 4:
			todas();
			break;		
	}
	
    return 0;
}

void cachePorConjuntos(){
	int archivo,numeroBloques = 0,sizeBloques = 0,numeroConjuntos = 0,contFallos = 0;
    char *byte;
    struct stat statbf;
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
    
    cout<<endl<<"\tIngrese el Numero de Bloques:";
    cin>>numeroBloques;
    cout<<endl<<"\tIngrese el tamaño de Palabra:";
    cin>>sizeBloques;
    cout<<endl<<"\tIngrese el Numero de Conjuntos:";
    cin>>numeroConjuntos;
    
    Simulador memoriaCache(numeroBloques,sizeBloques);//numerode bloques && tam de bloques
    float porcentaje = 0;
	unsigned long int valor = 0,direccion = 0,auxDireccion = 0,totales = 0;
    string campo;
    char unidad;
    bool preEncotrado = false;
    size_t size = statbf.st_size, contador=0;
    
    system("clear");
    
    cout<<"\t\tCargando..."<<endl;
    
    while(contador < size){
        unidad =*(byte++);
        if(unidad == ','){
        	direccion = memoriaCache.DirHexToDec(campo);
        	preEncotrado = memoriaCache.preBusqueda(direccion);
        	if(preEncotrado){
        		memoriaCache.MemoriaAsociativaConjuntos(direccion,numeroConjuntos,preEncotrado);
			}else{
				if(contFallos > 1){
        			memoriaCache.MemoriaAsociativaConjuntos(auxDireccion,numeroConjuntos,preEncotrado);
        			contFallos--;	
				}else{
					contFallos++;
				}
				auxDireccion = direccion;
			}
        	campo = "";
		}else{
			campo += unidad;
		}
			contador++;
    }
    
    close(archivo);
    totales = memoriaCache.getMiss() + memoriaCache.getHit();
    porcentaje = ((float)memoriaCache.getHit()/totales)*100;
    
    system("clear");
    
    cout<<endl<<"\t+------------------------------------------+"<<endl;
    cout<<"\t|     Cache Asociativa Por Conjuntos       |"<<endl;
    cout<<"\t|------------------------------------------|"<<endl;
    cout<<"\t|                                          |"<<endl;
    cout<<"\t| Fallos:"<<memoriaCache.getMiss()<<"                            |"<<endl;
    cout<<"\t| Acierto:"<<memoriaCache.getHit()<<"                          |"<<endl;
    cout<<"\t|                                          |"<<endl;
    cout<<"\t|------------------------------------------|"<<endl;
    cout<<"\t| Porcentaje De Acierto: "<<porcentaje<<"%          |"<<endl;
    cout<<"\t+------------------------------------------+"<<endl;
}


void cacheCompletamenteAsociativa(){
	int archivo,numeroBloques = 0,sizeBloques = 0,contFallos = 0;
    char *byte;
    struct stat statbf;
    
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
    cout<<endl<<"\tIngrese el Numero de Bloques:";
    cin>>numeroBloques;
    cout<<endl<<"\tIngrese el tamaño de Palabra:";
    cin>>sizeBloques;
    
    Simulador memoriaCache(numeroBloques,sizeBloques);//numerode bloques && tam de bloques
    float porcentaje = 0;
	unsigned long int valor = 0,totales = 0,direccion = 0, auxDireccion = 0;
    string campo;
    char unidad;
    bool preEncotrado = false;
    size_t size = statbf.st_size, contador=0;
    
    system("clear");
    
    cout<<"\t\tCargando..."<<endl;
    
    while(contador < size){
        unidad =*(byte++);
        if(unidad == ','){
        	direccion = memoriaCache.DirHexToDec(campo);
        	preEncotrado = memoriaCache.preBusqueda(direccion);
        	if(preEncotrado){
        		memoriaCache.MemoriaCompletamenteAsociativa(direccion,preEncotrado);
			}else{
				if(contFallos > 1){
        			memoriaCache.MemoriaCompletamenteAsociativa(auxDireccion,preEncotrado);
        			contFallos--;	
				}else{
					contFallos++;
				}
				auxDireccion = direccion;
			}
        	campo = "";
		}else{
			campo += unidad;
		}
			contador++;
    }
    
    close(archivo);
    
    totales = memoriaCache.getMiss() + memoriaCache.getHit();
    porcentaje = ((float)memoriaCache.getHit()/totales)*100;
    
    system("clear");
    
    cout<<endl<<"\t+------------------------------------------+"<<endl;
    cout<<"\t|     Cache Completamente Asociativa       |"<<endl;
    cout<<"\t|------------------------------------------|"<<endl;
    cout<<"\t|                                          |"<<endl;
    cout<<"\t| Fallos:"<<memoriaCache.getMiss()<<"                            |"<<endl;
    cout<<"\t| Acierto:"<<memoriaCache.getHit()<<"                          |"<<endl;
    cout<<"\t|                                          |"<<endl;
    cout<<"\t|------------------------------------------|"<<endl;
    cout<<"\t| Porcentaje De Acierto: "<<porcentaje<<"%          |"<<endl;
    cout<<"\t+------------------------------------------+"<<endl;
}

void cacheDirecta(){
	int archivo,numeroBloques = 0,sizeBloques = 0,contFallos = 0;
    char *byte;
    struct stat statbf;
	
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
    cout<<endl<<"\tIngrese el Numero de Bloques:";
    cin>>numeroBloques;
    cout<<endl<<"\tIngrese el tamaño de Palabra:";
    cin>>sizeBloques;
    
    Simulador memoriaCache(numeroBloques,sizeBloques);//numerode bloques && tam de bloques
    float porcentaje = 0;
	unsigned long int valor = 0,totales = 0,direccion = 0,auxDireccion = 0;
    string campo;
    char unidad;
    bool preEncotrado = false;
    size_t size = statbf.st_size, contador=0;
    
    system("clear");
    
    cout<<"\t\tCargando..."<<endl;
    
    while(contador < size){
        unidad =*(byte++);
        if(unidad == ','){
        	direccion = memoriaCache.DirHexToDec(campo);
        	preEncotrado = memoriaCache.preBusqueda(direccion);
        	if(preEncotrado){
        		memoriaCache.MemoriaDirecta(direccion,preEncotrado);
			}else{
				if(contFallos > 1){
        			memoriaCache.MemoriaDirecta(auxDireccion,preEncotrado);
        			contFallos--;	
				}else{
					contFallos++;
				}
				auxDireccion = direccion;
			}
        	campo = "";
		}else{
			campo += unidad;
		}
			contador++;
    }
    
    close(archivo);
    
    totales = memoriaCache.getMiss() + memoriaCache.getHit();
    porcentaje = ((float)memoriaCache.getHit()/totales)*100;
    
    system("clear");
    
    cout<<endl<<"\t+------------------------------------------+"<<endl;
    cout<<"\t|            Cache Directa                 |"<<endl;
    cout<<"\t|------------------------------------------|"<<endl;
    cout<<"\t|                                          |"<<endl;
    cout<<"\t| Fallos:"<<memoriaCache.getMiss()<<"                            |"<<endl;
    cout<<"\t| Acierto:"<<memoriaCache.getHit()<<"                          |"<<endl;
    cout<<"\t|                                          |"<<endl;
    cout<<"\t|------------------------------------------|"<<endl;
    cout<<"\t| Porcentaje De Acierto: "<<porcentaje<<"%          |"<<endl;
    cout<<"\t+------------------------------------------+"<<endl;
}
/******************************************************************************************************************************************************/
void cachePorConjuntos(int numeroBloques,int sizeBloques,int numeroConjuntos){
	int archivo,contFallos = 0;
    char *byte;
    struct stat statbf;
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
    
    
    Simulador memoriaCache(numeroBloques,sizeBloques);//numerode bloques && tam de bloques
    float porcentaje = 0;
	unsigned long int valor = 0,direccion = 0,auxDireccion = 0,totales = 0;
    string campo;
    char unidad;
    bool preEncotrado = false;
    size_t size = statbf.st_size, contador=0;
    
    
    while(contador < size){
        unidad =*(byte++);
        if(unidad == ','){
        	direccion = memoriaCache.DirHexToDec(campo);
        	preEncotrado = memoriaCache.preBusqueda(direccion);
        	if(preEncotrado){
        		memoriaCache.MemoriaAsociativaConjuntos(direccion,numeroConjuntos,preEncotrado);
			}else{
				if(contFallos > 1){
        			memoriaCache.MemoriaAsociativaConjuntos(auxDireccion,numeroConjuntos,preEncotrado);
        			contFallos--;	
				}else{
					contFallos++;
				}
				auxDireccion = direccion;
			}
        	campo = "";
		}else{
			campo += unidad;
		}
			contador++;
    }
    
    close(archivo);
    
    totales = memoriaCache.getMiss() + memoriaCache.getHit();
    porcentaje = ((float)memoriaCache.getHit()/totales)*100;
    
    cout<<endl<<"\t+------------------------------------------+"<<endl;
    cout<<"\t|     Cache Asociativa Por Conjuntos       |"<<endl;
    cout<<"\t|------------------------------------------|"<<endl;
    cout<<"\t|                                          |"<<endl;
    cout<<"\t| Fallos:"<<memoriaCache.getMiss()<<"                            |"<<endl;
    cout<<"\t| Acierto:"<<memoriaCache.getHit()<<"                          |"<<endl;
    cout<<"\t|                                          |"<<endl;
    cout<<"\t|------------------------------------------|"<<endl;
    cout<<"\t| Porcentaje De Acierto: "<<porcentaje<<"%          |"<<endl;
    cout<<"\t+------------------------------------------+"<<endl;
}


void cacheCompletamenteAsociativa(int numeroBloques,int sizeBloques){
	int archivo,contFallos = 0;
    char *byte;
    struct stat statbf;
    
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
    
    Simulador memoriaCache(numeroBloques,sizeBloques);//numerode bloques && tam de bloques
    float porcentaje = 0;
	unsigned long int valor = 0,totales = 0,direccion = 0, auxDireccion = 0;
    string campo;
    char unidad;
    bool preEncotrado = false;
    size_t size = statbf.st_size, contador=0;
    

    
    while(contador < size){
        unidad =*(byte++);
        if(unidad == ','){
        	direccion = memoriaCache.DirHexToDec(campo);
        	preEncotrado = memoriaCache.preBusqueda(direccion);
        	if(preEncotrado){
        		memoriaCache.MemoriaCompletamenteAsociativa(direccion,preEncotrado);
			}else{
				if(contFallos > 1){
        			memoriaCache.MemoriaCompletamenteAsociativa(auxDireccion,preEncotrado);
        			contFallos--;	
				}else{
					contFallos++;
				}
				auxDireccion = direccion;
			}
        	campo = "";
		}else{
			campo += unidad;
		}
			contador++;
    }
    
    close(archivo);
    
    totales = memoriaCache.getMiss() + memoriaCache.getHit();
    porcentaje = ((float)memoriaCache.getHit()/totales)*100;
    
    cout<<endl<<"\t+------------------------------------------+"<<endl;
    cout<<"\t|     Cache Completamente Asociativa       |"<<endl;
    cout<<"\t|------------------------------------------|"<<endl;
    cout<<"\t|                                          |"<<endl;
    cout<<"\t| Fallos:"<<memoriaCache.getMiss()<<"                            |"<<endl;
    cout<<"\t| Acierto:"<<memoriaCache.getHit()<<"                          |"<<endl;
    cout<<"\t|                                          |"<<endl;
    cout<<"\t|------------------------------------------|"<<endl;
    cout<<"\t| Porcentaje De Acierto: "<<porcentaje<<"%          |"<<endl;
    cout<<"\t+------------------------------------------+"<<endl;
}

void cacheDirecta(int numeroBloques,int sizeBloques){
	int archivo,contFallos = 0;
    char *byte;
    struct stat statbf;
	
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
    
    Simulador memoriaCache(numeroBloques,sizeBloques);//numerode bloques && tam de bloques
    float porcentaje = 0;
	unsigned long int valor = 0,totales = 0,direccion = 0,auxDireccion = 0;
    string campo;
    char unidad;
    bool preEncotrado = false;
    size_t size = statbf.st_size, contador=0;
    
    system("clear");
    cout<<"\t\tCargando..."<<endl;
    
    while(contador < size){
        unidad =*(byte++);
        if(unidad == ','){
        	direccion = memoriaCache.DirHexToDec(campo);
        	preEncotrado = memoriaCache.preBusqueda(direccion);
        	if(preEncotrado){
        		memoriaCache.MemoriaDirecta(direccion,preEncotrado);
			}else{
				if(contFallos > 1){
        			memoriaCache.MemoriaDirecta(auxDireccion,preEncotrado);
        			contFallos--;	
				}else{
					contFallos++;
				}
				auxDireccion = direccion;
			}
        	campo = "";
		}else{
			campo += unidad;
		}
			contador++;
    }
    
    close(archivo);
    
    totales = memoriaCache.getMiss() + memoriaCache.getHit();
    porcentaje = ((float)memoriaCache.getHit()/totales)*100;
    cout<<endl<<"\t+------------------------------------------+"<<endl;
    cout<<"\t|            Cache Directa                 |"<<endl;
    cout<<"\t|------------------------------------------|"<<endl;
    cout<<"\t|                                          |"<<endl;
    cout<<"\t| Fallos:"<<memoriaCache.getMiss()<<"                            |"<<endl;
    cout<<"\t| Acierto:"<<memoriaCache.getHit()<<"                          |"<<endl;
    cout<<"\t|                                          |"<<endl;
    cout<<"\t|------------------------------------------|"<<endl;
    cout<<"\t| Porcentaje De Acierto: "<<porcentaje<<"%          |"<<endl;
    cout<<"\t+------------------------------------------+"<<endl;
    
}
/*******************************************************************************************************************************************************/
int validarNumero(string num){
    int i, len;
    len = num.size();
    for (i = 0; i < len ; i++){
        if (!(isdigit(num[i]))){
            cout<<"!Solo se permiten numeros!"<<endl<<"Intente de nuevo: ";
            return 0;
        }
    }
	return 1;
}

int menu(){
	int numero = -1;
	string val;
	cout<<endl<<"\t+------------------ MENU ------------------+"<<endl;
    cout<<"\t|                                          |"<<endl;
    cout<<"\t| [1] Cache Directa                        |"<<endl;
    cout<<"\t| [2] Cache Asociativa Con Conjuntos       |"<<endl;
    cout<<"\t| [3] Cache Completamente Asociativa       |"<<endl;
    cout<<"\t| [4] Hacer todas                          |"<<endl;
    cout<<"\t|                                          |"<<endl;
    cout<<"\t+------------------------------------------+"<<endl;
    cout<<"Opcion: ";
    do{
        cin>>val;
    	numero = validarNumero(val);
    }while(numero == 0);
    
    numero = stoi(val);
    system("clear");
    
    return numero;
}

void todas(){
	int numeroBloques = 0,numeroConjuntos = 0,sizeBloques = 0,numero = 0;
	string val;
	do{
		cout<<endl<<"\tIngrese el Numero de Bloques:";
        cin>>val;
    	numero = validarNumero(val);
    }while(numero == 0);
    numeroBloques = stoi(val);
    
    do{
		cout<<endl<<"\tIngrese el size de Palabra:";
        cin>>val;
    	numero = validarNumero(val);
    }while(numero == 0);
    sizeBloques = stoi(val);
     
    do{
		cout<<endl<<"\tIngrese el Numero de Conjuntos:";
        cin>>val;
    	numero = validarNumero(val);
    }while(numero == 0);
    numeroConjuntos = stoi(val);
        
	cacheDirecta(numeroBloques,sizeBloques);
	cachePorConjuntos(numeroBloques,sizeBloques,numeroConjuntos);
	cacheCompletamenteAsociativa(numeroBloques,sizeBloques);
}
