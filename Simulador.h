#ifndef Simulador_h
#define Simulador_h
#include<iostream>
#include "Cache.h"
#include <string>
#include <list>
#include<cmath>
#include <bitset>
#include <sstream>
using namespace std;
class Simulador{
	private:
		//atributos
		int numeroBloques; //bumero de Bloques
		int tamBloques; //size de bloques / palabra
		unsigned long int hit; // acierto
		unsigned long int miss; //fallo
		Cache cache[600]; //Memoria Cache
		unsigned long int buffer; // Buffer para pre-Busqueda
		list<unsigned long int> reciente[600]; //Vector statico de listas para La Cache por Conjuntos
	public:
/**********************************************************************************************************************************************************************/
	//Constructores
		Simulador(){ //inicializar
			this->numeroBloques = 0;
			this->tamBloques = 0;
			this->hit = 0;
			this->miss = 0;
			this->buffer = -1;
		}
		
		Simulador(int nBloques,int tBloques){ //inicializar con valores
			this->numeroBloques = nBloques;
			this->tamBloques = tBloques;
			this->hit = 0;
			this->miss = 0;
			this->buffer = -1;
			for(int i = 0;i<nBloques;i++){
				this->cache[i].setEtiqueta(-1);
				this->cache[i].setValidez(false);
			}
		}
		
		void reiniciar(){ //reiniciar vector cache
			for(int i = 0;i<this->numeroBloques;i++){
				this->cache[i].setEtiqueta(-1);
				this->cache[i].setValidez(false);
			}
		}
/*********************************************************************************************************************************************************************/
		//getters
		int getNumeroBloques(){ //obtener numero de bloques
			return (this->numeroBloques);
		}
		
		int getTamBloques(){ //Obetener size de bloques / palabras
			return (this->tamBloques);
		}
		
		long int getHit(){ // obtener acierto
			return (this->hit);
		}
		
		long int getMiss(){ //obtener fallos
			return (this->miss);
		}
		
		unsigned long int getBuffer(){ //obtener buffer
			return (this->buffer);
		}
		
/*********************************************************************************************************************************************************************/
		//Setters
		void setNumeroBloques(int nBloques){ //insertar numero de bloques
			this->numeroBloques = nBloques;
		}
		
		void setTamBloques(int tBloques){ //insertar size de bloques / palabras
			this->tamBloques = tBloques;
		}
		
		void setHit(int cambio){ //insertar acierto
			this->hit = cambio;
		} 
		
		void setMiss(int cambio){ //insertar fallos
			this->miss = cambio;
		}
		
		void setBuffer(unsigned long int buff){ //insertar buffer
			this->buffer = buff;
		}
		
/*********************************************************************************************************************************************************************/
										//METODO PARA CACHE DIRECTA		
										
		bool directa(unsigned long int direccion,bool preEncontrado){ //Metodo auxiliar
			unsigned long int auxEtiqueta; //declaro variables
			bool auxValidez,result = false; //declaro variables
			int desplazamiento,index; //declaro variables
			
			desplazamiento = log2(this->tamBloques); //bits de desplazamiento
            auxEtiqueta = direccion >> desplazamiento; //aplico el desplazamiento de los bits a la direccion
            index = auxEtiqueta % this->numeroBloques; //operacion para sacar el indice
            
            if((this->cache[index].getValidez()) && (this->cache[index].getEtiqueta() == auxEtiqueta) ){ //si bits de validez verdadero y etiquetas iguales es un acierto
            	result = true; //acierto
			}else{
				if(preEncontrado){ //si prebusqueda es verdadero 
					result = true; //acierto
				}else{
					result = false; //fallo
				}
				this->cache[index].setEtiqueta(auxEtiqueta); //ingreso la etiqueta a la cache
				this->cache[index].setValidez(true); // ingreso el bits de validez
			}
			//this->imprimirCache(); //Mostrar Cache
            return (result); //retorna un boleano 
			
		}
		
		void MemoriaDirecta(unsigned long int direccion,bool preEncontrado){ //metodo principal
			bool bandera = directa(direccion,preEncontrado); //procesa el metodo auxiliar y retorna verdadero o falso
			if(bandera){ //si es verdadero
				this->hit++; // Acierto
			}else{
				this->miss++; //Fallo
			}
		}
		
/*********************************************************************************************************************************************************************/
										//METODO PARA CACHE POR CONJUNTOS
											
		void MemoriaAsociativaConjuntos(unsigned long int direccion,int nConjuntos,bool preEncontrado){ //Metodo Principal
			bool bandera = conjunto(direccion,nConjuntos,preEncontrado); //procesa el metodo auxiliar y retorna verdadero o falso
			if(bandera){ //si es verdadero
				this->hit++; // Acierto
			}else{
				this->miss++; //Fallo
			}
		}
		
		bool conjunto(unsigned long int direccion,int nConjunto,bool preEncontrado){ //Metodo Auxiliar
			unsigned long int auxEtiqueta; //declaro variables
			bool auxValidez,result = false,band = false,bandVacio = true; //declaro variables
			int desplazamiento,index = 0,carriles,auxIndex = 0; //declaro variables
			
			carriles = this->numeroBloques / nConjunto; //operacion para saber el numero de carriles
			desplazamiento = log2(this->tamBloques); //bits de desplazamiento
            auxEtiqueta = direccion >> desplazamiento; //aplico el desplazamiento de los bits a la direccion
            index = auxEtiqueta % nConjunto; //operacion para sacar el indice
			band = buscar(index,carriles,auxEtiqueta); //busca si la etiqueta esta en la cache
	
			if(band){ //si esta la etiqueta en la cache 
            	result = true; //Acierto
			}else{
				if(preEncontrado){ //pre-Busqueda
					result = true; //Acierto 
				}else{
					result = false; //Fallo
				} 
				bandVacio = buscar(index,carriles,-1); //busca si hay una posicion libre
				auxIndex = buscarposicion(index,carriles,-1); //busca la direccion de la posicion
				if(bandVacio){
					this->reciente[index].push_back(auxEtiqueta); //inserta Etiqueta en el vector de lista (en ultima posicion de la lista )
					this->cache[auxIndex].setEtiqueta(auxEtiqueta); //inserta Etiqueta
				}else{
					this->reciente[index].push_front(auxEtiqueta); //inserta en el vector de lista (frente de la lista)
					buscarRemplazo(this->reciente[index].back(),index,carriles,auxEtiqueta);// realiza el remplazo
					this->reciente[index].pop_back(); //elimina la ultima posicion de la lista donde apunta el vector
				}
			}
			//this->imprimirCache(); //Mostrar Cache
            return (result);
			
		}
		
		bool buscar(int index,int carriles,unsigned long int valor){ //Busca dentro de la cache
			bool result = false; //declaro variables
			int i = 0,posicion = index*carriles; //declaro variables
			while((!result) && (i<carriles)){ //mientras no encuentra el resultado y i sea menor al numero de  carriles
				if(this->cache[posicion].getEtiqueta() == valor){ //compara
					result = true; 
				}
				posicion++; //aumenta posicion
				i++; //aumenta i
			}
			return result; //retorna boleano
		}
		
		int buscarposicion(int index,int carriles,unsigned long int valor){ //busca la posicion del valor
			int i = 0,posicion = index*carriles, result = 0; //declaro variables
			bool band = false; //declaro variables
			while((!band) && (i<carriles)){ //mientras no encuentra el resultado y i sea menor al numero de  carriles
				if(this->cache[posicion].getEtiqueta() == valor){ //compara
					result = posicion; //result le asigno la posicion
					band = true;
				}
				posicion++; //aumenta posicion
				i++; //aumenta i
			}
			return result; //retorna posicion
		}
		
		void buscarRemplazo(long int reciente,int index,int carriles,unsigned long int valor){ //Metodo para remplazar Por Conjuntos
			bool band = false; //Declaro Variables
			int i = 0,posicion = index*carriles; //Declaro Variables
			while((!band) && (i<carriles)){ //mientras no encuentra el resultado y i sea menor al numero de  carriles
				if(this->cache[posicion].getEtiqueta() == reciente){ //compara
					band = true;
					this->cache[posicion].setEtiqueta(valor); //sustituyo el valor de la etiqueta
				}
				posicion++; //aumenta posicion
				i++; //aumenta i
			}
		}
		
/*********************************************************************************************************************************************************************/
										//METODO PARA CACHE COMPLETAMENTE ASOCIATIVA	
	
		void MemoriaCompletamenteAsociativa(unsigned long int direccion,bool preEncontrado){ //Metodo Principal
			bool bandera = completaAsociativa(direccion,preEncontrado); //procesa el metodo auxiliar y retorna verdadero o falso
			
			if(bandera){
				this->hit++; //acierto
			}else{
				this->miss++; //Fallo
			}
		}
		
		bool completaAsociativa(unsigned long int direccion,bool preEncontrado){ //Metodo auxiliar
			unsigned long int auxEtiqueta; //Declaro Variables
			bool auxValidez,result = false,band = false,auxBand = false; //Declaro Variables
			int desplazamiento,index =0,auxIndex = 0; //Declaro Variables
			
			desplazamiento = log2(this->tamBloques); //Bits de desplazamiento
            auxEtiqueta = direccion >> desplazamiento; //aplico el desplazamiento de los bits a la direccion
			band = this->buscar(index,this->numeroBloques,auxEtiqueta); //Busca la etiqueta en la cache
			
            if(band){
            	result = true; //Acierto
			}else{
				if(preEncontrado){ //pre-Busqueda
					result = true; //Acierto
				}else{
					result = false; //Fallo
				}
				auxBand = this->buscar(index,this->numeroBloques,-1); //busco Espacio en la Cache Vacia
				if(auxBand){
					index = this->buscarposicion(0,this->numeroBloques,-1); //Busco posicion
					this->cache[index].setEtiqueta(auxEtiqueta); //insertar etiqueta
					this->cache[index].setValidez(true); //insertar bits de validez
				}else{
					auxIndex = rand() % this->numeroBloques; //genera una posicion aleatoria 
					this->cache[auxIndex].setEtiqueta(auxEtiqueta); //insertar etiqueta
					this->cache[auxIndex].setValidez(true); //insertar bits de validez
				}		
			}
			//this->imprimirCache(); //Mostrar Cache
            return (result); //retorna Acierto o Fallo
			
		}


/*********************************************************************************************************************************************************************/
											//OTROS
											
unsigned long int DirHexToDec(string direccionHex) {

    if (direccionHex.substr(0, 2) == "0x") {
        direccionHex = direccionHex.substr(2);
    }

    unsigned long int decimal;
    istringstream(direccionHex) >> hex >> decimal;

    return decimal;
}


void imprimirCache(){ //imprime la memoria Cache
	for(int i = 0; i<this->numeroBloques;i++){
		cout<<"\t"<<this->cache[i].getEtiqueta();
	}
	cout<<endl;
}

bool preBusqueda(unsigned long int direccion){
	unsigned long int auxEtiqueta; //Declaro variables
	int desplazamiento; //Declaro variables
	bool result = false; //Declaro variables
	
	desplazamiento = log2(this->tamBloques); //Bits de desplazamiento
    auxEtiqueta = direccion >> desplazamiento; //aplico el desplazamiento de los bits a la direccion
    
    if(this->buffer == auxEtiqueta ){ //comparo
    	result = true;
	}
	
	this->buffer = auxEtiqueta; //sustituyo el buffer
	
	return result; //retorna un boleano
}
};
#endif 
