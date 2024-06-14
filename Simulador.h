#ifndef Simulador_h
#define Simulador_h
#include<iostream>
#include "Cache.h"
#include "Pila.cpp"
#include "Pila.h"
#include "Nodo.cpp"
#include "Nodo.h"
#include <vector>
#include <string>
#include<cmath>
#include <bitset>
#include <sstream>
using namespace std;
class Simulador{
	private:
		//atributos
		int numeroBloques;
		int tamBloques;
		int hit;
		int miss;
		Cache cache[30];
	public:
/**********-***********************************************************************************************************************************************************/
	//Constructores
		Simulador(){
			this->numeroBloques = 0;
			this->tamBloques = 0;
			this->hit = 0;
			this->miss = 0;
		}
		Simulador(int nBloques,int tBloques){
			this->numeroBloques = nBloques;
			this->tamBloques = tBloques;
			this->hit = 0;
			this->miss = 0;
			for(int i = 0;i<nBloques;i++){
				this->cache[i].setEtiqueta(-1);
				this->cache[i].setValidez(false);
			}
		}
/*********************************************************************************************************************************************************************/
		//getters
		int getNumeroBloques(){
			return (this->numeroBloques);
		}
		int getTamBloques(){
			return (this->tamBloques);
		}
		int getHit(){
			return (this->hit);
		}
		int getMiss(){
			return (this->miss);
		}
/*********************************************************************************************************************************************************************/
		//Setters
		void setNumeroBloques(int nBloques){
			this->numeroBloques = nBloques;
		}
		void setTamBloques(int tBloques){
			this->tamBloques = tBloques;
		}
		void setHit(int cambio){
			this->hit = cambio;
		}
		void setMiss(int cambio){
			this->miss = cambio;
		}
		void reiniciar(){
			for(int i = 0;i<this->numeroBloques;i++){
				this->cache[i].setEtiqueta(-1);
				this->cache[i].setValidez(false);
			}
		}
/*********************************************************************************************************************************************************************/
		bool directa(long int direccion){
			long int auxEtiqueta;
			bool auxValidez,result = false;
			int desplazamiento,index;
			desplazamiento = log2(this->tamBloques);
            auxEtiqueta = direccion >> desplazamiento;
            index = auxEtiqueta % this->numeroBloques;
            //std::cout<<"Desplazamiento: "<<desplazamiento<<endl;
           // std::cout<<"indice:"<<index<<endl;
            if((this->cache[index].getValidez()) && (this->cache[index].getEtiqueta() == auxEtiqueta) ){
            	result = true;
			}else{
				this->cache[index].setEtiqueta(auxEtiqueta);
				this->cache[index].setValidez(true);
				result = false;
			}
			//cout<<"Etiqueta:"<<this->cache[index].getEtiqueta()<<endl;
            return (result);
			
		}
		void MemoriaDirecta(long int direccion){
			bool bandera = directa(direccion);
			if(bandera){
				this->hit++;
				cout<<"\tDireccion: "<<direccion<<" Acierto en el BLoque"<<endl;
			}else{
				this->miss++;
				cout<<"\tDireccion: "<<direccion<<" Fallo en el BLoque"<<endl;
			}
		}
/*********************************************************************************************************************************************************************/
		void MemoriaAsociativaConjuntos(long int direccion,int nConjuntos){
			bool bandera = conjunto(direccion,nConjuntos);
			if(bandera){
				this->hit++;
				cout<<"\tDireccion: "<<direccion<<" Acierto en el BLoque"<<endl;
			}else{
				cout<<"\tDireccion: "<<direccion<<" Fallo en el BLoque"<<endl;
				this->miss++;
			}
			//cout<<"miss:"<<this->getMiss()<<endl;
			//cout<<"hit:"<<this->getHit()<<endl;
		}
		
		bool conjunto(long int direccion,int nConjunto){
			long int auxEtiqueta;
			bool auxValidez,result = false,band = false,bandVacio = true;
			int desplazamiento,index = 0,carriles,auxIndex = 0;
			Pila<long int> reciente;
			carriles = this->numeroBloques / nConjunto;
			desplazamiento = log2(this->tamBloques);
            auxEtiqueta = direccion >> desplazamiento;
            index = auxEtiqueta % carriles;
			//cout<<"posicion: "<<index<<endl;
			band = buscar(index,carriles,auxEtiqueta);
            if(band){
            	result = true;
			}else{
				bandVacio = buscar(index,carriles,-1);
				auxIndex = buscarposicion(index,carriles,-1);
				if(bandVacio){
					reciente.apilar(auxEtiqueta);
					//cout<<"posicion: "<<auxIndex<<endl;
					this->cache[auxIndex].setEtiqueta(auxEtiqueta);
				}else{
					reciente.apilar(auxEtiqueta);
					buscarRemplazo(reciente,index,carriles,auxEtiqueta);//falla posible error
					reciente.desapilar();
				}
			}
            return (result);
			
		}
		bool buscar(int index,int carriles,long int valor){
			bool result = false;
			int i = index;
			while((!result) && (i<carriles)){
				if(this->cache[i].getEtiqueta() == valor){
					result = true;
				}
				i++;
			}
			return result;
		}
		int buscarposicion(int index,int carriles,long int valor){
			int i = index, result = 0;
			while((!result) && (i<carriles)){
				if(this->cache[i].getEtiqueta() == valor){
					result = i;
				}
				i++;
			}
			return result;
		}
		void buscarRemplazo(Pila<long int> reciente,int index,int carriles,long int valor){
			bool band = false;
			int i = index;
			while((!band) && (i<carriles)){
				if(this->cache[i].getEtiqueta() == reciente.tope()){
					this->cache[i].setEtiqueta(valor);
				}
				i++;
			}
		}
/*********************************************************************************************************************************************************************/
	void MemoriaCompletamenteAsociativa(long int direccion){
			bool bandera = completaAsociativa(direccion);
			if(bandera){
				this->hit++;
				cout<<"\tDireccion: "<<direccion<<" Acierto en el BLoque"<<endl;
			}else{
				this->miss++;
				cout<<"\tDireccion: "<<direccion<<" Fallo en el BLoque"<<endl;
			}
		}
		
		bool completaAsociativa(long int direccion){
			long int auxEtiqueta;
			bool auxValidez,result = false,band = false;
			int desplazamiento,index =0;
			desplazamiento = log2(this->tamBloques);
            auxEtiqueta = direccion >> desplazamiento;
			band = buscar(index,this->numeroBloques,auxEtiqueta);
            index = this->buscarposicion(0,this->numeroBloques,-1);
            //std::cout<<"Desplazamiento: "<<desplazamiento<<endl;
           // std::cout<<"indice:"<<index<<endl;
            if(band){
            	result = true;
			}else{
				this->cache[index].setEtiqueta(auxEtiqueta);
				this->cache[index].setValidez(true);
				result = false;
			}
			//cout<<"Etiqueta:"<<this->cache[index].getEtiqueta()<<endl;
            return (result);
			
		}


/*********************************************************************************************************************************************************************/

long int DirHexToDec(string direccionHex) {

    // Elimina el prefijo "0x" si está presente
    if (direccionHex.substr(0, 2) == "0x") {
        direccionHex = direccionHex.substr(2);
    }

    // Convierte el número hexadecimal a decimal
    long int decimal;
    istringstream(direccionHex) >> hex >> decimal;

    return decimal;
}



};
#endif 
