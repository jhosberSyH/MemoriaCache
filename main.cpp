#include <iostream>
#include <string>
#include <bitset>
#include "Simulador.h"
using namespace std;

int main() {
    Simulador memoriaCache(4,8);//numerode bloques && tam de bloques
    long int valor = 0;
    cout<<"bienvenido"<<endl;
	for(int i = 0;i<5;i++){
    	cin>>valor;
    	//memoriaCache.MemoriaDirecta(valor);
    	//memoriaCache.MemoriaAsociativaConjuntos(valor,2); // el 2 es el conjunto
    	memoriaCache.MemoriaCompletamenteAsociativa(valor);
	}
	cout<<"miss:"<<memoriaCache.getMiss()<<endl;
	cout<<"hit:"<<memoriaCache.getHit()<<endl;	
    return 0;
}




