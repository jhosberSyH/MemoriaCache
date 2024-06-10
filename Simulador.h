#ifndef Simulador_h
#define Simulador_h
#include<iostream>
#include "Cache.h"
#include <vector>
#include <string>
#include<cmath>
#include <bitset>
using namespace std;
class Simulador{
	private:
		int numeroBloques;
		int tamBloques;
		int hit;
		int miss;
		Cache cache[10];
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
				this->cache[i].setEtiqueta(0);
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
/*********************************************************************************************************************************************************************/
		bool directa(long int direccion){
			long int auxEtiqueta;
			bool auxValidez,result = false;
			int desplazamiento,index;
			desplazamiento = log2(this->tamBloques);
            auxEtiqueta = direccion >> desplazamiento;
            index = auxEtiqueta % this->numeroBloques;
            std::cout<<"Desplazamiento: "<<desplazamiento<<endl;
            std::cout<<"indice:"<<index<<endl;
            if((this->cache[index].getValidez()) && (this->cache[index].getEtiqueta() == auxEtiqueta) ){
            	//std::cout<<"paso3";
            	result = true;
			}else{
				//std::cout<<"paso 4";
				this->cache[index].setEtiqueta(auxEtiqueta);
				this->cache[index].setValidez(true);
				result = false;
			}
			cout<<"Etiqueta:"<<this->cache[index].getEtiqueta()<<endl;
            return (result);
			
		}
		void MemoriaDrirecta(long int direccion){
			bool bandera = directa(direccion);
			if(bandera){
				this->hit++;
			}else{
				this->miss++;
			}
		}
/*********************************************************************************************************************************************************************/
};
#endif 
