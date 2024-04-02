#include<iostream>
#include<vector>
#include<string>
//Jhosber Ynojosa 31.116.618
//Miguel Romero 30.155.726
using namespace std;
void inicializarMatriz(int *matriz[][30],int nMemoria,int nBloque);
void esAcierto(int  *matriz[][30],int nMemoria,int nBloque);
void seguimientodDireccion(int *matriz[][30],int nMemoria,int nBloque);
void seguimientodDireccionAsociativaCompleta(int *matriz[][30],int nBloque,int i);
void imprimirDireccionDeMemoria(int *matriz[][30],int nMemoria,int nBloque);
void imprimirDireccionDeMemoriaDosVias(int *matriz[][30],int nMemoria,int nBloque);
void distribuccionMemoriaModulo(int *matriz[][30],int nMemoria,int nBloque);
void distribuccionMemoriaModuloDosVias(int *matriz[][30],int nMemoria,int modulo);
void distribuccionMemoria(int *matriz[][30],int nMemoria,int nBloque);
void correspondenciaDirecta(int *bloques[][30],int bloque);
void correspondenciaAsociativaCompleta(int *bloques[][30],int bloque);
void correspondenciaAsociativaDosVias(int *bloques[][30],int bloque);
//Variables Glogables
string acierto[30];
vector<int> direccionMemoria;
int memoria[] = { 12, 56, 584, 21, 456, 24, 145, 568, 4, 5, 21, 45,14, 58, 74, 11, 22, 66, 55, 77, 89, 66, 44, 55, 22, 8, 4, 2, 3, 1};
int main(){
	int bloque = 0,direccion,asignacion,*bloques[30][30],k = -1,nDireccion;
	bool band = true;
	cout<<"\t\t\tBienvenido"<<endl<<endl;
	do{
		if(bloque > 30){
			cout<<"Por favor, Vuelva a ingresar un numero menor a 31"<<endl;
		}
		cout<<"Ingrese la Cantidad de Bloques:";
		cin>>bloque;	
	}while(bloque > 30);
	cout<<"Ingrese el numero de direccion de memoria:";
	cin>>nDireccion;
	for(int i=0;i<nDireccion;i++){
		cin>>direccion;
		direccionMemoria.push_back(direccion); //agrego a la ultima posicion de direccionMemoria
	}
	correspondenciaDirecta(bloques,bloque);
	correspondenciaAsociativaCompleta(bloques,bloque);
	correspondenciaAsociativaDosVias(bloques,bloque);
	cout<<endl<<endl<<"\t\t\tFeliz Dia"<<endl;
	return 0;
}
void inicializarMatriz(int *matriz[][30],int nMemoria,int nBloque){
	for(int i=0;i<nMemoria;i++){//inicializo la matriz 
		for(int j=0;j<nBloque;j++){
			matriz[i][j] = NULL;	//valor vacio
		}
	}
}

void esAcierto(int  *matriz[][30],int nMemoria,int nBloque){
	int i = 1,j = 0;
	bool band;
	while( i<nMemoria){//Compruba si es acierto o no
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
void seguimientodDireccion(int *matriz[][30],int nMemoria,int nBloque){
	for(int i=1;i<nMemoria;i++){//Seguimiento de la direcion anterios en el caso de ser NULL
		for(int j=0;j<nBloque;j++){
			if((matriz[i][j] == NULL) && (matriz[i-1][j] != NULL)){
				matriz[i][j] = matriz[i-1][j];
			}
		}	
	}
}	
void seguimientodDireccionAsociativaCompleta(int *matriz[][30],int nBloque,int i){
		for(int j=0;j<nBloque;j++){
			if((matriz[i][j] == NULL) && (matriz[i-1][j] != NULL)){
				matriz[i][j] = matriz[i-1][j];
			}
		}	
	
}
void imprimirDireccionDeMemoria(int *matriz[][30],int nMemoria,int nBloque){
	cout<<"Direccion del bloque \t"<<"Acierto\t\t"<<"Contenido de los bloque\t"<<endl;
	cout<<"de memoria accedido\t"<<"o fallo\t\t"<<"de cache despues de cada acceso\t"<<endl<<endl;
	cout<<"\t \t \t \t \t \t";
	for(int t = 0;t<nBloque;t++){
		cout<<"Bloque "<<t<<"\t";
	}
	cout<<endl<<endl;
	for(int i=0;i< nMemoria;i++){//Imprime con dirrecion de memoria
		cout<<"\t"<<direccionMemoria[i]<<"\t\t"<<acierto[i]<<"\t\t\t";
		for(int j=0;j<nBloque;j++){
			if(matriz[i][j] != NULL){
				cout<<matriz[i][j]<<"\t";
			}else{
				cout<<" \t\t";
			}
		}
		cout<<endl;
	}
}
void imprimirDireccionDeMemoriaDosVias(int *matriz[][30],int nMemoria,int nBloque){
	cout<<"Direccion del bloque \t"<<"Acierto\t\t"<<"Contenido de los bloque\t"<<endl;
	cout<<"de memoria accedido\t"<<"o fallo\t\t"<<"de cache despues de cada acceso\t"<<endl<<endl;
	cout<<"\t \t \t \t \t \t";
	for(int t = 0;t<2;t++){
		cout<<"conjunto "<<t<<"\t";
		cout<<"conjunto "<<t<<"\t";
	}
	cout<<endl<<endl;
	for(int i=0;i< nMemoria;i++){//Imprime con dirrecion de memoria
		cout<<"\t"<<direccionMemoria[i]<<"\t\t"<<acierto[i]<<"\t\t\t";
		for(int j=0;j<nBloque;j++){
			if(matriz[i][j] != NULL){
				cout<<matriz[i][j]<<"\t";
			}else{
				cout<<" \t\t";
			}
		}
		cout<<endl;
	}
}
void imprimirNormalxD(int *matriz[][30],int nMemoria,int nBloque){
	int k = -1;
	for(int i=0;i<nMemoria;i++){//Imprime memoria
		cout<<direccionMemoria[i]<<"\t"<<acierto[i]<<"\t";
		k = direccionMemoria[i];
		for(int j=0;j<nBloque;j++){
			if(matriz[i][j] != NULL){
				if(matriz[i][j] == matriz[i-1][j]){
					cout<<"Memoria["<<direccionMemoria[i-1]<<"]\t";
				}else{
					cout<<"Memoria["<<k<<"]\t";	
				}
			}else{
				cout<<" \t";
			}
		}
		cout<<endl;
	}	
}

void distribuccionMemoriaModulo(int *matriz[][30],int nMemoria,int modulo){
	int asignacion;
	for(int i=0;i<nMemoria;i++){//Agrega las direcciones de memorias a la matriz
		asignacion = direccionMemoria[i] % modulo;
		matriz[i][asignacion] = &memoria[direccionMemoria[i]];
	}
}
void distribuccionMemoriaModuloDosVias(int *matriz[][30],int nMemoria,int modulo){ //Falta establecer una pol�tica de reemplazos.
	int asignacion,n0 = 0,n1 = 0,k = 0;
	for(int i=0;i<nMemoria;i++){//Agrega las direcciones de memorias a la matriz
		asignacion = direccionMemoria[i] % modulo;
		switch (asignacion){
			case 0:	
				if((n0 == 1)){
					matriz[i][asignacion+1] = &memoria[direccionMemoria[i]];
					n0--;
				}else{
					matriz[i][asignacion] = &memoria[direccionMemoria[i]];
					n0++;
				}
				break;
			case 1:	
				if(n1 == 1){
					matriz[i][asignacion+2] = &memoria[direccionMemoria[i]];
					n1--;
				}else{
					matriz[i][asignacion+1] = &memoria[direccionMemoria[i]];
					n1++;
				}
				break;
		}
			
	}
}

void correspondenciaDirecta(int *bloques[][30],int bloque){
	int k = -1;
	bool band = true;
	inicializarMatriz(bloques,direccionMemoria.size(),bloque);
	cout<<endl<<"\t\tcorrespondencia directa"<<endl<<endl;
	distribuccionMemoriaModulo(bloques,direccionMemoria.size(),4);
	seguimientodDireccion(bloques,direccionMemoria.size(),bloque);
	acierto[0] = "fallo";
	esAcierto(bloques,direccionMemoria.size(),bloque);
	imprimirDireccionDeMemoria(bloques,direccionMemoria.size(),bloque);
	//imprimirNormalxD(bloques,direccionMemoria.size(),bloque);
	cout<<endl;
}
void distribuccionMemoria(int *matriz[][30],int nMemoria,int nBloque){
	int asignacion;
	int i = 0,j = 0,k = 0,t = 0;
	bool band =true;
	while( i<nMemoria){
		band = true;
		j=0;
		while((j<nBloque) && (band == true)){
			if((i == 0) && (j == 0)){
				matriz[i][j] = &memoria[direccionMemoria[i]];
				band = false;
			}else{
				if(  matriz[i][j] == &memoria[direccionMemoria[i]]){ 
					band = false;
				}else if((matriz[i][j] == NULL) && (matriz[i-1][j] == NULL)){
					matriz[i][j] = &memoria[direccionMemoria[i]];
					band = false;
				}
			}
			j++;
		}
		if(band == true){
			matriz[i][k] = &memoria[direccionMemoria[i]];
			k++;
		}
		i++;
		seguimientodDireccionAsociativaCompleta(matriz,nBloque,i);
	}
}


void correspondenciaAsociativaCompleta(int *bloques[][30],int bloque){
	inicializarMatriz(bloques,direccionMemoria.size(),bloque);
	cout<<endl<<"\t\tcorrespondencia Asociativa Completa"<<endl<<endl;
	distribuccionMemoria(bloques,direccionMemoria.size(),bloque);
	acierto[0] = "fallo";
	esAcierto(bloques,direccionMemoria.size(),bloque);
	imprimirDireccionDeMemoria(bloques,direccionMemoria.size(),bloque);
	//imprimirNormalxD(bloques,direccionMemoria.size(),bloque);
}


void correspondenciaAsociativaDosVias(int *bloques[][30],int bloque){
	inicializarMatriz(bloques,direccionMemoria.size(),bloque);
	cout<<endl<<endl<<"\t\tcorrespondencia Asociativa Dos Vias"<<endl<<endl;
	distribuccionMemoriaModuloDosVias(bloques,direccionMemoria.size(),2);
	seguimientodDireccion(bloques,direccionMemoria.size(),bloque);
	acierto[0] = "fallo";
	esAcierto(bloques,direccionMemoria.size(),bloque);
	imprimirDireccionDeMemoriaDosVias(bloques,direccionMemoria.size(), bloque);
	//imprimirDireccionDeMemoria(bloques,direccionMemoria.size(),bloque);
	//imprimirNormalxD(bloques,direccionMemoria.size(),bloque);
	
}
