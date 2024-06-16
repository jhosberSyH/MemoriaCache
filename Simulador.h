#ifndef Simulador_h
#define Simulador_h
#include<iostream>
#include "Cache.h"
#include <vector>
#include <string>
#include <list>
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
		Cache cache[300];
		list<unsigned long int> reciente[300];
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
		bool directa(unsigned long int direccion){
			unsigned long int auxEtiqueta;
			bool auxValidez,result = false;
			int desplazamiento,index;
			desplazamiento = log2(this->tamBloques);
            auxEtiqueta = direccion >> desplazamiento;
            index = auxEtiqueta % this->numeroBloques;
            //std::cout<<"Desplazamiento: "<<desplazamiento<<endl;
            //std::cout<<"indice:"<<index<<endl;
            if((this->cache[index].getValidez()) && (this->cache[index].getEtiqueta() == auxEtiqueta) ){
            	result = true;
			}else{
				this->cache[index].setEtiqueta(auxEtiqueta);
				this->cache[index].setValidez(true);
				result = false;
			}
			//this->imprimirCache(); //Mostrar Cache
            return (result);
			
		}
		void MemoriaDirecta(unsigned long int direccion){
			bool bandera = directa(direccion);
			if(bandera){
				this->hit++;
			//	cout<<"\tDireccion: "<<direccion<<" Acierto en el BLoque"<<endl;
			}else{
				this->miss++;
				//cout<<"\tDireccion: "<<direccion<<" Fallo en el BLoque"<<endl;
			}
		}
/*********************************************************************************************************************************************************************/
		void MemoriaAsociativaConjuntos(unsigned long int direccion,int nConjuntos){
			bool bandera = conjunto(direccion,nConjuntos);
			if(bandera){
				this->hit++;
				//cout<<"\tDireccion: "<<direccion<<" Acierto en el BLoque"<<endl;
			}else{
				//cout<<"\tDireccion: "<<direccion<<" Fallo en el BLoque"<<endl;
				this->miss++;
			}
			//cout<<"miss:"<<this->getMiss()<<endl;
			//cout<<"hit:"<<this->getHit()<<endl;
		}
		
		bool conjunto(unsigned long int direccion,int nConjunto){
			unsigned long int auxEtiqueta;
			bool auxValidez,result = false,band = false,bandVacio = true;
			int desplazamiento,index = 0,carriles,auxIndex = 0;
			carriles = this->numeroBloques / nConjunto;
			desplazamiento = log2(this->tamBloques);
            auxEtiqueta = direccion >> desplazamiento;
            index = auxEtiqueta % nConjunto;
			//cout<<"posicion: "<<index<<endl;
			band = buscar(index,carriles,auxEtiqueta);
			//cout<<index<<endl<<endl;
            //cout<<"index: "<<index<<endl;
			if(band){
            	result = true;
			}else{
				bandVacio = buscar(index,carriles,-1);
				auxIndex = buscarposicion(index,carriles,-1);
				if(bandVacio){
					this->reciente[index].push_back(auxEtiqueta);
					this->cache[auxIndex].setEtiqueta(auxEtiqueta);
				}else{
					//cout<<"posicion: "<<index<<endl;
					this->reciente[index].push_front(auxEtiqueta);
					buscarRemplazo(this->reciente[index].back(),index,carriles,auxEtiqueta);//falla posible error
					this->reciente[index].pop_back();
				}
			}
			//this->imprimirCache(); //Mostrar Cache
            return (result);
			
		}
		bool buscar(int index,int carriles,unsigned long int valor){
			bool result = false;
			int i = 0,posicion = index*carriles;
			//cout<<index<<endl<<endl;
			while((!result) && (i<carriles)){
				if(this->cache[posicion].getEtiqueta() == valor){
					result = true;
				}
				posicion++;
				i++;
			}
			return result;
		}
		int buscarposicion(int index,int carriles,unsigned long int valor){
			int i = 0,posicion = index*carriles, result = 0;
			bool band = false;
			//cout<<valor<<endl;
			while((!band) && (i<carriles)){
				if(this->cache[posicion].getEtiqueta() == valor){
					result = posicion;
					band = true;
				}
				posicion++;
				i++;
			}
			return result;
		}
		void buscarRemplazo(long int reciente,int index,int carriles,unsigned long int valor){
			bool band = false;
			int i = 0,posicion = index*carriles;
			//cout<<"reciente : "<<reciente<<endl<<endl;
			while((!band) && (i<carriles)){
				if(this->cache[posicion].getEtiqueta() == reciente){
					band = true;
					this->cache[posicion].setEtiqueta(valor);
				}
				posicion++;
				i++;
			}
		}
/*********************************************************************************************************************************************************************/
	void MemoriaCompletamenteAsociativa(unsigned long int direccion){
			bool bandera = completaAsociativa(direccion);
			if(bandera){
				this->hit++;
				//cout<<"\tDireccion: "<<direccion<<" Acierto en el BLoque"<<endl;
			}else{
				this->miss++;
				//cout<<"\tDireccion: "<<direccion<<" Fallo en el BLoque"<<endl;
			}
		}
		
		bool completaAsociativa(unsigned long int direccion){
			unsigned long int auxEtiqueta;
			bool auxValidez,result = false,band = false,auxBand = false;
			int desplazamiento,index =0,auxIndex = 0;
			desplazamiento = log2(this->tamBloques);
            auxEtiqueta = direccion >> desplazamiento;
			band = this->buscar(index,this->numeroBloques,auxEtiqueta);
            //std::cout<<"Desplazamiento: "<<desplazamiento<<endl;
           // std::cout<<"indice:"<<index<<endl;
            if(band){
            	result = true;
			}else{
				auxBand = this->buscar(index,this->numeroBloques,-1);
				if(auxBand){
					index = this->buscarposicion(0,this->numeroBloques,-1);
					this->cache[index].setEtiqueta(auxEtiqueta);
					this->cache[index].setValidez(true);
				}else{
					auxIndex = rand() % this->numeroBloques;
					this->cache[auxIndex].setEtiqueta(auxEtiqueta);
					this->cache[auxIndex].setValidez(true);
				}
				result = false;
			}
			//this->imprimirCache(); //Mostrar Cache
            return (result);
			
		}


/*********************************************************************************************************************************************************************/

unsigned long int DirHexToDec(string direccionHex) {

    if (direccionHex.substr(0, 2) == "0x") {
        direccionHex = direccionHex.substr(2);
    }

    unsigned long int decimal;
    istringstream(direccionHex) >> hex >> decimal;

    return decimal;
}


void imprimirCache(){
	for(int i = 0; i<this->numeroBloques;i++){
		cout<<"\t"<<this->cache[i].getEtiqueta();
	}
	cout<<endl;
}


};
#endif 
