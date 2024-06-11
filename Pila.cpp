#include "Pila.h"

template <class elemento>
Pila<elemento>::Pila(){
	this->ultimo = NULL;
	this->longitud = 0;
}


template <class elemento>
Pila<elemento>::Pila(const Pila<elemento> &pila){
	this->ultimo = pila.ultimo;
	this->longitud = pila.longitud;
}

template <class elemento>
void Pila<elemento>::copiar(const Pila<elemento> &pila){
	 Nodo<elemento> *temp,*aux,*info;
    if (pila.longitud != 0) {
        temp = pila.ultimo;
        // Copiar el primer nodo
        info = new Nodo<elemento>(temp->getInfo());
        this->ultimo = info;
        aux = this->ultimo;
        temp = temp->getSiguiente();

        // Copiar los nodos restantes
        while (temp != NULL) {
			info = new Nodo<elemento>(temp->getInfo());
            aux->setSiguiente(info);
            aux = aux->getSiguiente();
            temp = temp->getSiguiente();
        }
        this->longitud = pila.longitud;
    }	
}


template <class elemento>
void Pila<elemento>::apilar(elemento e) {
    Nodo<elemento>* nuevoNodo = new Nodo<elemento>(e);
    if (this->ultimo == NULL) {
        this->ultimo = nuevoNodo;
    } else {
        nuevoNodo->setSiguiente(this->ultimo);
        this->ultimo = nuevoNodo;
    }
    this->longitud++;
}

template <class elemento>
void Pila<elemento>::desapilar() {
    Nodo<elemento>* temp = this->ultimo;
    if (this->longitud == 1) {
        this->ultimo = NULL;
    }else{
		this->ultimo = this->ultimo->getSiguiente();
		
	}
    delete temp;
    this->longitud--;
}


template <class elemento>
elemento Pila<elemento>::tope(){
	return (this->ultimo->getInfo());
}


template <class elemento>
bool Pila<elemento>::esVacia(){
	bool res = false;
	if(this->longitud < 1){
		res = true;
	}
	return res;
}
