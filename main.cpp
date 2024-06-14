#include <iostream>
#include <string>
#include <bitset>
#include "Simulador.h"
using namespace std;

int main() {
    Simulador memoriaCache(4,0);//numerode bloques && tam de bloques
    long int valor = 0,totales = 0;
	float porcentaje = 0;
    cout<<endl<<"bienvenido"<<endl;
	cin>>totales;
	cout<<"\t\tCache Directa"<<endl;
	for(int i = 0;i<totales;i++){
    	cin>>valor;
    	memoriaCache.MemoriaDirecta(valor);
	}
	cout<<"\tFallos:"<<memoriaCache.getMiss()<<endl;
	cout<<"\tAcierto:"<<memoriaCache.getHit()<<endl;
	porcentaje = ((float)memoriaCache.getHit()/totales)*100;
	cout<<"\tPorcentaje De Acierto: "<<porcentaje<<"%"<<endl;
	memoriaCache.setHit(0);
	memoriaCache.setMiss(0);
	memoriaCache.reiniciar();
	cout<<endl<<"\t\tCache Asociativa Por Cojunto"<<endl;
	for(int i = 0;i<totales;i++){
    	cin>>valor;
    	memoriaCache.MemoriaAsociativaConjuntos(valor,2);
	}
	cout<<"\tFallos:"<<memoriaCache.getMiss()<<endl;
	cout<<"\tAcierto:"<<memoriaCache.getHit()<<endl;
	porcentaje = ((float)memoriaCache.getHit()/totales)*100;
	cout<<"\tPorcentaje De Acierto: "<<porcentaje<<"%"<<endl;
	memoriaCache.setHit(0);
	memoriaCache.setMiss(0);
	memoriaCache.reiniciar();
	cout<<endl<<"\t\tCache Completamente Asociativa"<<endl;
	for(int i = 0;i<totales;i++){
    	cin>>valor;
    	memoriaCache.MemoriaCompletamenteAsociativa(valor);
	}
	cout<<"\tFallos:"<<memoriaCache.getMiss()<<endl;
	cout<<"\tAcierto:"<<memoriaCache.getHit()<<endl;
	porcentaje = ((float)memoriaCache.getHit()/totales)*100;
	cout<<"\tPorcentaje De Acierto: "<<porcentaje<<"%"<<endl;	
    return 0;
}




