#ifndef Simulador_h
#define Simulador_h
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
		vector<Cache> cache;
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
		}
/*********************************************************************************************************************************************************************/
		//getters
		int getNumeroBloques(){
			return (this->numeroBloques);
		}
		int getTamBloques(){
			return (this->tamBloques);
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
            if((this->cache[index].getValidez()) && (this->cache[index].getEtiqueta() == auxEtiqueta) ){
            	result = true;
			}else{
				this->cache[index].setEtiqueta(auxEtiqueta);
				this->cache[index].setValidez(true);
				result = false;
			}
            return (result);
			
		}
		void MemoriaDrirecta(long int direccion){
			cout<<"paso";
			bool bandera = directa(direccion);
			if(bandera){
				this->hit++;
			}else{
				this->miss++;
			}
		}
/*********************************************************************************************************************************************************************/
	/*	long int direccioToBinario(int direccion){
			long int result;
			bitset<32> resu



			return (result);
		}*/
};
#endif 
