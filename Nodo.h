#ifndef Nodo_h
#define Nodo_h
#include <iostream>
using namespace std;
template <class elemento>
class Nodo{
	private:
		elemento info;
		Nodo<elemento> *siguiente;
	public:
		Nodo();
		Nodo(elemento inf);
		Nodo(const Nodo<elemento> &nodo);
		void setInfo(elemento inf);
		void setSiguiente(Nodo<elemento> *sig);
		elemento getInfo();
		Nodo<elemento>* getSiguiente();
};
#endif
