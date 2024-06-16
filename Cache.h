#ifndef Cache_h
#define Cache_h
#include<vector>
class Cache{
	private:
		unsigned long int etiqueta;
		bool validez;
	public:
/*********************************************************************************************************************************************************************/
	//Constructores
		Cache(){
			this->validez = false;
			this->etiqueta = -1;
		}
		Cache(unsigned long int etq,bool val){
			this->validez = val;
			this->etiqueta = etq;
		}
/*********************************************************************************************************************************************************************/
		//getters
		unsigned long int getEtiqueta(){
			return (this->etiqueta);
		}
		bool getValidez(){
			return (this->validez);
		}

/*********************************************************************************************************************************************************************/
		//Setters
		void setEtiqueta(unsigned long int etq){
			this->etiqueta = etq;
		}
		void setValidez(bool val){
			this->validez = val;
		}
/*********************************************************************************************************************************************************************/
};
#endif 
