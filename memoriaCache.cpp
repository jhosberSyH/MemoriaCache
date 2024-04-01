#include<iostream>
#include<vector>
#include<string>
using namespace std;
int main(){
	int bloque,direccion,asignacion,*bloques[10][10],i = 0,j = 0,k = -1;
	bool band = true;
	vector<int> memoria,direccionMemoria;
	string acierto[10];
	cout<<"Ingrese el numero de Bloque:";
	cin>>bloque;
	cout<<"Ingrese la dirrecion de memoria:"<<endl;
	for(int i=0;i<bloque+1;i++){
		cin>>direccion;
		direccionMemoria.push_back(direccion); //agrego a la ultima posicion de direccionMemoria
		memoria.push_back(i);	//agrego a la ultima posicion de memoria
	}
	for(int i=0;i<direccionMemoria.size();i++){//inicializo la matriz 
		for(int j=0;j<bloque;j++){
			bloques[i][j] = NULL;	//valor vacio
		}
	}
	cout<<"correspondencia directa"<<endl;
	for(int i=0;i<direccionMemoria.size();i++){//agrego las direcciones de memorias a la matriz
		asignacion = direccionMemoria[i] % 4;
		bloques[i][asignacion] = &memoria[direccionMemoria[i]];	
	}
	for(int i=1;i<direccionMemoria.size();i++){//sigo el seguimiento de la dirrecion anterios en el caso de ser NULL
		for(int j=0;j<bloque;j++){
			if((bloques[i][j] == NULL) && (bloques[i-1][j] != NULL)){
				bloques[i][j] = bloques[i-1][j];
			}
		}	
	}
	acierto[0] = "fallo";
	i=1;
	while( i<direccionMemoria.size()){ //compruba si es acierto o no
		band = true;
		j=0;
		while((j<bloque) && (band == true)){
			if(bloques[i][j] != bloques[i-1][j]){
				band = false;
				acierto[i] = "fallo";
			}else{
				acierto[i] = "acierto";
			}
			j++;
		}
		i++;
	}
	/*for(int i=0;i<direccionMemoria.size();i++){//imprimo matriz
		for(int j=0;j<bloque;j++){
			cout<<bloques[i][j]<<"\t";
		}
		cout<<endl;
	}*/
/*	for(int i=0;i<direccionMemoria.size();i++){//imprimir con dirrecion de memoria
		cout<<direccionMemoria[i]<<"\t"<<acierto[i]<<"\t";
		for(int j=0;j<bloque;j++){
			cout<<bloques[i][j]<<"\t";
		}
		cout<<endl;
	}*/
	for(int i=0;i<direccionMemoria.size();i++){// imprimir ejercicio
		cout<<direccionMemoria[i]<<"\t"<<acierto[i]<<"\t";
		k = direccionMemoria[i];
		for(int j=0;j<bloque;j++){
			if(bloques[i][j] != NULL){
				if(bloques[i][j] == bloques[i-1][j]){
					cout<<"Memoria["<<direccionMemoria[i-1]<<"]\t";
				}else{
					cout<<"Memoria["<<k<<"]\t";	
				}
			}else{
				cout<<"\t";
			}
		}
		cout<<endl;
	}
	cout<<"listo"<<endl;
	return 0;
}
