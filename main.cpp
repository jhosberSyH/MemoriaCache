#include <iostream>
#include <string>
#include <bitset>
#include "Simulador.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
using namespace std;
/*****************************************************************************************************************************************************/
											//EJECUTADOR
											
void cachePorConjuntos(int numeroBloques,int sizeBloques,int numeroConjuntos); //Ejecuta la Cache por conjunto e imprime resultados
void cacheCompletamenteAsociativa(int numeroBloques,int sizeBloques); //Ejecuta la Cache Completamente Asociativa e imprime resultados
void cacheDirecta(int numeroBloques,int sizeBloques); //Ejecuta la Cache Directa e imprime resultados

/*****************************************************************************************************************************************************/
											//AUXILIARES PIDE VALORES Y VERIFICA
											
void cachePorConjuntos(); //Pide los valores y verifica suvalor antes de entrar al ejecutor de Cache por Conjuntos
void cacheCompletamenteAsociativa(); //Pide los valores y verifica suvalor antes de entrar al ejecutor de Cache Completamente Asociativas
void cacheDirecta(); //Pide los valores y verifica suvalor antes de entrar al ejecutor de Cache Directa
void todas(); //ejecuta las tres Caches Juntas

/*****************************************************************************************************************************************************/
											//OTROS
											
int menu(); //Menu para Interacturar Con el Usuario devuelve el valor de la opcion que eligio
int validarNumero(string num); //Validacion para saber si ingreso un numero

/*****************************************************************************************************************************************************/


int main() {
    int iniciar = 0;
    cout<<"\t\tBienvenido"<<endl<<endl; //Mensaje de Bienvenida
	do{
		iniciar = menu(); //Menu para Interacturar Con el Usuario devuelve el valor de la opcion que eligio
	}while((iniciar < 1) || (iniciar > 4)); //validacion para que no escoja un numero fuera del rango

	switch(iniciar){ //selecionador para operar una de las 4 opciones 
		case 1:
			cacheDirecta(); //Pide los valores y verifica suvalor antes de entrar al ejecutor de Cache Directa
			break;
		case 2:
			cachePorConjuntos(); //Pide los valores y verifica suvalor antes de entrar al ejecutor de Cache por Conjuntos
			break;
		case 3:
			cacheCompletamenteAsociativa(); //Pide los valores y verifica suvalor antes de entrar al ejecutor de Cache Completamente Asociativas
			break;
		case 4:
			todas(); //ejecuta las tres Caches Juntas
			break;		
	}
	
    return 0;
}

/*****************************************************************************************************************************************************/
											//AUXILIARES PIDE VALORES Y VERIFICA

void cachePorConjuntos(){
	int numeroBloques = 0,numeroConjuntos = 0,sizeBloques = 0,numero = 0; //Se declara variables
	string val; //Se declara variables
	do{
		cout<<endl<<"\tIngrese el Numero de Bloques:"; //mensaje para el Usuario
        cin>>val; //lectura estandar de un string
    	numero = validarNumero(val); // Valida si es numero
    }while(numero == 0); // si es diferente de 0 se repite
    numeroBloques = stoi(val); //transforma un string en entero
    
    do{
		cout<<endl<<"\tIngrese el size de Palabra:"; //mensaje para el Usuario
        cin>>val; //lectura estandar de un string
    	numero = validarNumero(val); // Valida si es numero
    }while(numero == 0); // si es diferente de 0 se repite
    sizeBloques = stoi(val); //transforma un string en entero
     
    do{
		cout<<endl<<"\tIngrese el Numero de Conjuntos:"; //mensaje para el Usuario
        cin>>val; //lectura estandar de un string
    	numero = validarNumero(val); // Valida si es numero
    }while(numero == 0); // si es diferente de 0 se repite
    numeroConjuntos = stoi(val); //transforma un string en entero
    
	system("clear"); //borra la pantalla
    cout<<"\t\tCargando..."<<endl; //mensaje para el Usuario
    
	cachePorConjuntos(numeroBloques,sizeBloques,numeroConjuntos); //Ejecuta la Cache por conjunto e imprime resultados
}


void cacheCompletamenteAsociativa(){
	int numeroBloques = 0,sizeBloques = 0,numero = 0; //Se declara variables
	string val; //Se declara variables
	do{
		cout<<endl<<"\tIngrese el Numero de Bloques:"; //mensaje para el Usuario
        cin>>val; //lectura estandar de un string
    	numero = validarNumero(val); // Valida si es numero
    }while(numero == 0); // si es diferente de 0 se repite
    numeroBloques = stoi(val); //transforma un string en entero
    
    do{
		cout<<endl<<"\tIngrese el size de Palabra:"; //mensaje para el Usuario
        cin>>val; //lectura estandar de un string
    	numero = validarNumero(val); // Valida si es numero
    }while(numero == 0); // si es diferente de 0 se repite
    sizeBloques = stoi(val);
         
	system("clear"); //borra la pantalla
    cout<<"\t\tCargando..."<<endl; //mensaje para el Usuario
    
	cacheCompletamenteAsociativa(numeroBloques,sizeBloques); //Ejecuta la Cache Completamente Asociativa e imprime resultados
} 


void cacheDirecta(){
	int numeroBloques = 0,sizeBloques = 0,numero = 0; //Se declara variables
	string val; //Se declara variables
	do{
		cout<<endl<<"\tIngrese el Numero de Bloques:"; //mensaje para el Usuario
        cin>>val; //lectura estandar de un string
    	numero = validarNumero(val); // Valida si es numero
    }while(numero == 0); // si es diferente de 0 se repite
    numeroBloques = stoi(val); //transforma un string en entero
    
    do{
		cout<<endl<<"\tIngrese el size de Palabra:"; //mensaje para el Usuario
        cin>>val; //lectura estandar de un string
    	numero = validarNumero(val); // Valida si es numero
    }while(numero == 0); // si es diferente de 0 se repite
    sizeBloques = stoi(val); //transforma un string en entero
       
	system("clear"); //borra la pantalla
    cout<<"\t\tCargando..."<<endl; //mensaje para el Usuario
    
	cacheDirecta(numeroBloques,sizeBloques); //Ejecuta la Cache Directa e imprime resultados
}


void todas(){
	int numeroBloques = 0,numeroConjuntos = 0,sizeBloques = 0,numero = 0; //Se declara variables
	string val; //Se declara variables
	do{
		cout<<endl<<"\tIngrese el Numero de Bloques:"; //Mensaje al Usuario
        cin>>val; //lectura estandar de un string
    	numero = validarNumero(val); // Valida si es numero
    }while(numero == 0); // si es diferente de 0 se repite
    numeroBloques = stoi(val); //transforma un string en entero
    
    do{
		cout<<endl<<"\tIngrese el size de Palabra:"; //Mensaje al Usuario
        cin>>val; //lectura estandar de un string
    	numero = validarNumero(val); // Valida si es numero
    }while(numero == 0); // si es diferente de 0 se repite
    sizeBloques = stoi(val); //transforma un string en entero
     
    do{
		cout<<endl<<"\tIngrese el Numero de Conjuntos:"; //Mensaje al Usuario
        cin>>val; //lectura estandar de un string
    	numero = validarNumero(val); // Valida si es numero
    }while(numero == 0); // si es diferente de 0 se repite
    numeroConjuntos = stoi(val); //transforma un string en entero
    
    system("clear"); //borra la pantalla
    cout<<"\t\tCargando..."<<endl; //Mensaje al Usuario
    
	cacheDirecta(numeroBloques,sizeBloques); //Ejecuta la Cache Directa e imprime resultados
	cachePorConjuntos(numeroBloques,sizeBloques,numeroConjuntos); //Ejecuta la Cache por conjunto e imprime resultados
	cacheCompletamenteAsociativa(numeroBloques,sizeBloques); //Ejecuta la Cache Completamente Asociativa e imprime resultados
} //Cierre de ejecutar todas las Cache

/******************************************************************************************************************************************************/
											//EJECUTADOR

void cachePorConjuntos(int numeroBloques,int sizeBloques,int numeroConjuntos){
	int archivo,contFallos = 0; //Se declara variables
    char *byte; //Se declara variables
    struct stat statbf; //Se declara variables
    archivo = open( "steam_games2023.csv" , O_RDONLY ); //Se abre el Archivo
    
    if( archivo == -1 ){ //Si el Archivo devuelve -1 significa que no se abrio el archivo
        cout << "No se entrar al steam_games"<<endl; //Mensaje al Usuario
        exit(1); //cierra el programa
    }

    if( fstat( archivo , &statbf ) == -1 ){ //Si devuelve -1 significa que no se Pudo Obtener la informacion de la estructura de datos (stat)
        cout << "Error al intentar obtener informacion de la estructura de datos."<<endl; //Mensaje al Usuario
        exit(1); //Cierra el programa
    }

    byte = (char*) mmap( NULL , statbf.st_size, PROT_READ, MAP_PRIVATE, archivo, 0); //Mapea la informacion en el apuntador a caracter

    if( byte == MAP_FAILED ){ //Si no se pudo mapear salta el mensaje al ususario 
        cout << "Hubo un error al mapear el steam_games en memoria"<<endl; //Mensaje al Usuario
		exit(1); //Sale del Programa
    }
    
    
    Simulador memoriaCache(numeroBloques,sizeBloques);//numerode bloques && tam de bloques //Se declara variables
    float porcentaje = 0; //Se declara variables
	unsigned long int valor = 0,direccion = 0,auxDireccion = 0,totales = 0; //Se declara variables
    string campo; //Se declara variables
    char unidad; //Se declara variables
    bool preEncotrado = false; //Se declara variables
    size_t size = statbf.st_size, contador=0; //Se declara variables
    
    
    while(contador < size){ ///mietras no sea el el size total del archivo hacer:
        unidad =*(byte++); //unidad guarda un caracter
        if(unidad == ','){ //si se consigue con el caracter ',' procesa la cadena
        	direccion = memoriaCache.DirHexToDec(campo); //tranforma una direccion de memoria del string a un entero(Para trabajarlo mejor como binario)
        	preEncotrado = memoriaCache.preBusqueda(direccion); //funcion para hacer la pre-busqueda y aumentar la taza de exitos
        	if(preEncotrado){ //si prebusqueda es verdad
        		memoriaCache.MemoriaAsociativaConjuntos(direccion,numeroConjuntos,preEncotrado); //ejecuto el metodo del simulador para la Cache por Conjuntos
			}else{
				if(contFallos > 1){ //si contador de fallos es mayor a 1 entra
        			memoriaCache.MemoriaAsociativaConjuntos(auxDireccion,numeroConjuntos,preEncotrado); ////ejecuto el metodo del simulador para la Cache por Conjuntos
        			contFallos--; //descrementa el contador de fallos
				}else{
					contFallos++; //aumenta el contador de fallos
				}
				auxDireccion = direccion; //guardo la direccion en un auxiliar para asi ejecutar n-1 en caso de fallo
			}
        	campo = ""; //Reinicio el string
		}else{
			campo += unidad; // sumo el caracter a la variable del string para unirlas 
		}
			contador++; // aumento contador
    }
    
    close(archivo); // Cierro Archivo 
    
    totales = memoriaCache.getMiss() + memoriaCache.getHit(); //Calculo el total de la suma de los Acierto y Fallos
    porcentaje = ((float)memoriaCache.getHit()/totales)*100; //saco el porcentaje de Aciertos
    
    cout<<endl<<"\t+------------------------------------------+"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t|     Cache Asociativa Por Conjuntos       |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t|------------------------------------------|"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t|                                          |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t| Fallos:"<<memoriaCache.getMiss()<<"                             |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t| Acierto:"<<memoriaCache.getHit()<<"                          |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t|                                          |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t|------------------------------------------|"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t| Porcentaje De Acierto: "<<porcentaje<<"%          |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t+------------------------------------------+"<<endl; //Mensaje al Usuario (tabla de repuestas)
    
} // Fin de Cache Asociativa Por Conjuntos


void cacheCompletamenteAsociativa(int numeroBloques,int sizeBloques){
	int archivo,contFallos = 0; //Se declara variables
    char *byte; //Se declara variables
    struct stat statbf; //Se declara variables
    
    archivo = open( "steam_games2023.csv" , O_RDONLY ); //Se abre el archivo
    
    if( archivo == -1 ){ //Si el Archivo devuelve -1 significa que no se abrio el archivo
        cout << "No se entrar al steam_games"<<endl; //Mensaje al Usuario
        exit(1); //Cierra el Programa
    }

    if( fstat( archivo , &statbf ) == -1 ){ //Si devuelve -1 significa que no se Pudo Obtener la informacion de la estructura de datos (stat)
        cout << "Error al intentar obtener informacion de la estructura de datos."<<endl; //Mensaje al Usuario
        exit(1); //Cierra el programa
    }

    byte = (char*) mmap( NULL , statbf.st_size, PROT_READ, MAP_PRIVATE, archivo, 0); //Mapea la informacion en el apuntador a caracter

    if( byte == MAP_FAILED ){ //Si no se pudo mapear salta el mensaje al ususario 
        cout << "Hubo un error al mapear el steam_games en memoria"<<endl; //Mensaje al Usuario
		exit(1); //Cierra el programa
    }
    
    Simulador memoriaCache(numeroBloques,sizeBloques);//numerode bloques && tam de bloques //Se declara variables
    float porcentaje = 0; //Se declara variables
	unsigned long int valor = 0,totales = 0,direccion = 0, auxDireccion = 0; //Se declara variables
    string campo; //Se declara variables
    char unidad; //Se declara variables
    bool preEncotrado = false; //Se declara variables
    size_t size = statbf.st_size, contador=0; //Se declara variables
    

    
    while(contador < size){ //mietras no sea el el size total del archivo hacer:
        unidad =*(byte++); //unidad guarda un caracter
        if(unidad == ','){ //si se consigue con el caracter ',' procesa la cadena
        	direccion = memoriaCache.DirHexToDec(campo); //tranforma una direccion de memoria del string a un entero(Para trabajarlo mejor como binario)
        	preEncotrado = memoriaCache.preBusqueda(direccion); //funcion para hacer la pre-busqueda y aumentar la taza de exitos
        	if(preEncotrado){ //si prebusqueda es verdad
        		memoriaCache.MemoriaCompletamenteAsociativa(direccion,preEncotrado); //ejecuto el metodo del simulador para la Cache Completamente Asociativa
			}else{
				if(contFallos > 1){ //si contador de fallos es mayor a 1 entra
        			memoriaCache.MemoriaCompletamenteAsociativa(auxDireccion,preEncotrado); //ejecuto el metodo del simulador para la Cache Completamente Asociativa
        			contFallos--; //descrementa el contador de fallos	
				}else{
					contFallos++; //aumenta el contador de fallos
				}
				auxDireccion = direccion; //guardo la direccion en un auxiliar para asi ejecutar n-1 en caso de fallo
			}
        	campo = ""; //Reinicio el string
		}else{
			campo += unidad; // sumo el caracter a la variable del string para unirlas
		}
			contador++; // aumento contador
    }
    
    close(archivo); // Cierro Archivo 
    
    totales = memoriaCache.getMiss() + memoriaCache.getHit(); //Calculo el total de la suma de los Acierto y Fallos
    porcentaje = ((float)memoriaCache.getHit()/totales)*100; //saco el porcentaje de Aciertos
    
    cout<<endl<<"\t+------------------------------------------+"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t|     Cache Completamente Asociativa       |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t|------------------------------------------|"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t|                                          |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t| Fallos:"<<memoriaCache.getMiss()<<"                             |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t| Acierto:"<<memoriaCache.getHit()<<"                          |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t|                                          |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t|------------------------------------------|"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t| Porcentaje De Acierto: "<<porcentaje<<"%          |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t+------------------------------------------+"<<endl; //Mensaje al Usuario (tabla de repuestas)
} //Fin de Cache Completamente Asociativa


void cacheDirecta(int numeroBloques,int sizeBloques){
	int archivo,contFallos = 0; //Se declara variables
    char *byte; //Se declara variables
    struct stat statbf; //Se declara variables
	
    archivo = open( "steam_games2023.csv" , O_RDONLY ); //Se abre el archivo
    
    if( archivo == -1 ){ //Si el Archivo devuelve -1 significa que no se abrio el archivo
        cout << "No se entrar al steam_games"<<endl; //Mensaje al Usuario
        exit(1); //Cierra el programa
    }

    if( fstat( archivo , &statbf ) == -1 ){ //Si devuelve -1 significa que no se Pudo Obtener la informacion de la estructura de datos (stat)
        cout << "Error al intentar obtener informacion de la estructura de datos."<<endl; //Mensaje al Usuario
        exit(1); //Cierra el programa
    }

    byte = (char*) mmap( NULL , statbf.st_size, PROT_READ, MAP_PRIVATE, archivo, 0); //Mapea la informacion en el apuntador a caracter

    if( byte == MAP_FAILED ){ //Si no se pudo mapear salta el mensaje al ususario 
        cout << "Hubo un error al mapear el steam_games en memoria"<<endl; //Mensaje al Usuario
		exit(1); //Cierra el programa
    }
    
    Simulador memoriaCache(numeroBloques,sizeBloques);//numerode bloques && tam de bloques //Se declara variables
    float porcentaje = 0; //Se declara variables
	unsigned long int valor = 0,totales = 0,direccion = 0,auxDireccion = 0; //Se declara variables
    string campo; //Se declara variables
    char unidad; //Se declara variables
    bool preEncotrado = false; //Se declara variables
    size_t size = statbf.st_size, contador=0; //Se declara variables
       
    while(contador < size){ //mietras no sea el el size total del archivo hacer:
        unidad =*(byte++); //unidad guarda un caracter
        if(unidad == ','){ //si se consigue con el caracter ',' procesa la cadena
        	direccion = memoriaCache.DirHexToDec(campo); //tranforma una direccion de memoria del string a un entero(Para trabajarlo mejor como binario)
        	preEncotrado = memoriaCache.preBusqueda(direccion); //funcion para hacer la pre-busqueda y aumentar la taza de exitos
        	if(preEncotrado){ //si prebusqueda es verdad
        		memoriaCache.MemoriaDirecta(direccion,preEncotrado); //ejecuto el metodo del simulador para la Cache Directa
			}else{
				if(contFallos > 1){ //si contador de fallos es mayor a 1 entra
        			memoriaCache.MemoriaDirecta(auxDireccion,preEncotrado); //ejecuto el metodo del simulador para la Cache Directa
        			contFallos--; //descrementa el contador de fallos
				}else{
					contFallos++; //aumenta el contador de fallos
				}
				auxDireccion = direccion; //guardo la direccion en un auxiliar para asi ejecutar n-1 en caso de fallo
			}
        	campo = ""; //Reinicio el string
		}else{
			campo += unidad; // sumo el caracter a la variable del string para unirlas
		}
			contador++; // aumento contador
    }
    
    close(archivo); // Cierro Archivo 
     
    totales = memoriaCache.getMiss() + memoriaCache.getHit(); //Calculo el total de la suma de los Acierto y Fallos
    porcentaje = ((float)memoriaCache.getHit()/totales)*100; //saco el porcentaje de Aciertos
    cout<<endl<<"\t+------------------------------------------+"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t|            Cache Directa                 |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t|------------------------------------------|"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t|                                          |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t| Fallos:"<<memoriaCache.getMiss()<<"                             |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t| Acierto:"<<memoriaCache.getHit()<<"                          |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t|                                          |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t|------------------------------------------|"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t| Porcentaje De Acierto: "<<porcentaje<<"%          |"<<endl; //Mensaje al Usuario (tabla de repuestas)
    cout<<"\t+------------------------------------------+"<<endl; //Mensaje al Usuario (tabla de repuestas)
    
} //Fin de Cache Directa
/*******************************************************************************************************************************************************/

/*******************************************************************************************************************************************************/
										//OTROS
										
int validarNumero(string num){
    int i, len; //Se declara variables
    len = num.size(); //len va a contener el size del string
    for (i = 0; i < len ; i++){ //recorre desde la posicion 0 hasta el size del string
        if (!(isdigit(num[i]))){ //verifica que sea numero 
            cout<<"!Solo se permiten numeros!"<<endl<<"Intente de nuevo: "; //Mensaje al Usuario
            return 0; // retorna 0 si consiguio un caracter
        }
    }
	return 1; //retorna 1 si todos los caracteres son numeros
}


int menu(){
	int numero = -1; //Se declara variables
	string val; //Se declara variables
	cout<<endl<<"\t+------------------ MENU ------------------+"<<endl; //Mensaje al Usuario (MENU)
    cout<<"\t|                                          |"<<endl; //Mensaje al Usuario (MENU)
    cout<<"\t| [1] Cache Directa                        |"<<endl; //Mensaje al Usuario (MENU)
    cout<<"\t| [2] Cache Asociativa Con Conjuntos       |"<<endl; //Mensaje al Usuario (MENU)
    cout<<"\t| [3] Cache Completamente Asociativa       |"<<endl; //Mensaje al Usuario (MENU)
    cout<<"\t| [4] Hacer todas                          |"<<endl; //Mensaje al Usuario (MENU)
    cout<<"\t|                                          |"<<endl; //Mensaje al Usuario (MENU)
    cout<<"\t+------------------------------------------+"<<endl; //Mensaje al Usuario (MENU)
    cout<<"Opcion: "; //Mensaje al Usuario
    do{
        cin>>val; //lectura estandar de un string
    	numero = validarNumero(val); // Valida si es numero
    }while(numero == 0); // si es diferente de 0 se repite
    
    numero = stoi(val); //transforma un string en entero
    system("clear"); //borra la pantalla
    
    return numero; //retorna el numero entero 
}


