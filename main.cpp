#include <iostream>
#include <string>
#include <bitset>
#include "Simulador.h"
using namespace std;

int main() {
    Simulador memoriaCache(4,8);
    long int valor = 0;
    cout<<"bienvenido"<<endl;
    for(int i = 0;i<5;i++){
    	cin>>valor;
    	memoriaCache.MemoriaDrirecta(valor);
	}
	cout<<"miss:"<<memoriaCache.getMiss()<<endl;
	cout<<"hit:"<<memoriaCache.getHit()<<endl;
	//cout<<"etiqueta"<<memoriaCache.getEtiqueta()<<endl;
    return 0;
}




