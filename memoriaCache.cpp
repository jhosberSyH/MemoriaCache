#include<iostream>
#include<vector>
#include<string>
using namespace std;
void inicializarMatriz(int *matriz[][10],int nMemoria,int nBloque);
void esAcierto(int  *matriz[][10],int nMemoria,int nBloque);
void seguimientodDireccion(int *matriz[][10],int nMemoria,int nBloque);
void imprimirDireccionDeMemoria(int *matriz[][10],int nMemoria,int nBloque);
void distribuccionMemoria(int *matriz[][10],int nMemoria,int nBloque);
//Variables Glogables
string acierto[10];
vector<int> memoria,direccionMemoria;
int main(){
	int bloque,direccion,asignacion,*bloques[10][10],k = -1;
	bool band = true;
	cout<<"Ingrese el numero de Bloque:";
	cin>>bloque;
	cout<<"Ingrese la dirrecion de memoria:"<<endl;
	for(int i=0;i<bloque+1;i++){
		cin>>direccion;
		direccionMemoria.push_back(direccion); //agrego a la ultima posicion de direccionMemoria
		memoria.push_back(i);	//agrego a la ultima posicion de memoria
	}
	inicializarMatriz(bloques,direccionMemoria.size(),bloque);
	cout<<"correspondencia directa"<<endl;
	distribuccionMemoria(bloques,direccionMemoria.size(),4);
	seguimientodDireccion(bloques,direccionMemoria.size(),bloque);
	acierto[0] = "fallo";
	esAcierto(bloques,direccionMemoria.size(),bloque);
	//imprimirDireccionDeMemoria(bloques,direccionMemoria.size(),bloque);
	for(int i=0;i<direccionMemoria.size();i++){// imprimir memoria
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
void inicializarMatriz(int *matriz[][10],int nMemoria,int nBloque){
	for(int i=0;i<nMemoria;i++){//inicializo la matriz 
		for(int j=0;j<nBloque;j++){
			matriz[i][j] = NULL;	//valor vacio
		}
	}
}

void esAcierto(int  *matriz[][10],int nMemoria,int nBloque){
	int i = 1,j = 0;
	bool band;
	while( i<nMemoria){//compruba si es acierto o no
		band = true;
		j=0;
		while((j<nBloque) && (band == true)){
			if(matriz[i][j] != matriz[i-1][j]){
				band = false;
				acierto[i] = "fallo";
			}else{
				acierto[i] = "acierto";
			}
			j++;
		}
		i++;
	}
}	
void seguimientodDireccion(int *matriz[][10],int nMemoria,int nBloque){
	for(int i=1;i<nMemoria;i++){//sigo el seguimiento de la dirrecion anterios en el caso de ser NULL
		for(int j=0;j<nBloque;j++){
			if((matriz[i][j] == NULL) && (matriz[i-1][j] != NULL)){
				matriz[i][j] = matriz[i-1][j];
			}
		}	
	}
}	
void imprimirDireccionDeMemoria(int *matriz[][10],int nMemoria,int nBloque){
	for(int i=0;i< nMemoria;i++){//imprimir con dirrecion de memoria
		cout<<direccionMemoria[i]<<"\t"<<acierto[i]<<"\t";
		for(int j=0;j<nBloque;j++){
			cout<<matriz[i][j]<<"\t";
		}
		cout<<endl;
	}
}
void distribuccionMemoria(int *matriz[][10],int nMemoria,int modulo){
	int asignacion;
	for(int i=0;i<nMemoria;i++){//agrego las direcciones de memorias a la matriz
		asignacion = direccionMemoria[i] % modulo;
		matriz[i][asignacion] = &memoria[direccionMemoria[i]];	
	}
}
