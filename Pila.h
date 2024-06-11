#ifndef Pila_h
#define Pila_h
#include "Nodo.h"
template <class elemento>
class Pila{
	private:
		Nodo<elemento> *ultimo;
		int longitud;
	public:
		Pila();
		Pila(const Pila<elemento> &pila);
		void copiar(const Pila<elemento> &pila);
		void desapilar();
		void apilar(elemento e);
		elemento tope();
		bool esVacia();
		//void vaciar();
};
#endif 

