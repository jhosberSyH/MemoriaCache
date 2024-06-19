#ifndef Cache_h
#define Cache_h
class Cache{
	private:
		unsigned long int etiqueta; //bits de Etiqueta
		bool validez; //bits de validez
	public:
/*********************************************************************************************************************************************************************/
	//Constructores
		Cache(){ //Inicializar cache
			this->validez = false;
			this->etiqueta = -1;
		}
		
		Cache(unsigned long int etq,bool val){ //inicializar cache con su valores
			this->validez = val;
			this->etiqueta = etq;
		}
/*********************************************************************************************************************************************************************/
		//getters
		unsigned long int getEtiqueta(){ //Obtener Etiqueta
			return (this->etiqueta); 
		}
		
		bool getValidez(){ //Obtener Validez
			return (this->validez);
		}

/*********************************************************************************************************************************************************************/
		//Setters
		void setEtiqueta(unsigned long int etq){ //insertar etiqueta
			this->etiqueta = etq;
		}
		
		void setValidez(bool val){ //Insertar bits de validez
			this->validez = val;
		}
/*********************************************************************************************************************************************************************/
};
#endif 
