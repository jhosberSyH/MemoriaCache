#include "Nodo.h"
template <class elemento>
Nodo<elemento>::Nodo(){
	this->siguiente = NULL;
}
template <class elemento>
Nodo<elemento>::Nodo(elemento inf){
	this->info = inf;
	this->siguiente = NULL;
}
template <class elemento>
Nodo<elemento>::Nodo(const Nodo<elemento> &nodo){
	this->info = nodo.getInfo();
	this->siguiente = nodo.getSiguiente();
}
template <class elemento>
void Nodo<elemento>::setInfo(elemento inf){
	this->info = inf;
}
template <class elemento>
void Nodo<elemento>::setSiguiente(Nodo<elemento> *sig){
	this->siguiente = sig;
}
template <class elemento>
elemento Nodo<elemento>::getInfo(){
	return info;
}
template <class elemento>
Nodo<elemento>* Nodo<elemento>::getSiguiente(){
	return (this->siguiente);
}

