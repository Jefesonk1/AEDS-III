#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct registro{
	char nome[20];
	char numero[10];

}typedef Registro;


struct chunk{
	Registro* registro;
	int begin;
}typedef Chunk;


void swap(Registro* bloco,int a,int b){
	Registro temp;
	temp=bloco[a];
	bloco[a]=bloco[b];
	bloco[b]=temp;
}

void bubbleLex(Registro* bloco,int tam){
	for(int i=0;i<tam;i++){
		for(int j=0;j<tam-1;j++){

			char *a=bloco[j].nome;
			char *b=bloco[j+1].nome;
			int r=strcmp(a,b);
			if(r>0){

				swap(bloco,j,j+1);
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	if(argc!=3)
		return -1;
	int bytes=atoi(argv[1]);
	char const* filename=argv[2];
	FILE* myFile, *tempFile;

	myFile=fopen(filename,"r");
	tempFile=fopen("entrada.ordenado","w");
	if(myFile==NULL){
		printf("Erro ao abrir arquivo.\n");
		return -1;
	}


	Registro* bloco;
	int qtd=bytes/sizeof(Registro);


	printf("cabe %d registros de tamanho %d cada\n",qtd,sizeof(Registro));

	bloco=(Registro*)malloc(sizeof(Registro)*qtd);


	int i=0;
	int registros_qtd=0;
	int qtd_blocos=0;

	while(!feof(myFile)){

		int contador=0;
		i=0;
		while(!feof(myFile) && contador<qtd && fscanf(myFile,"%[^:]:%[^\n]\n",bloco[i].nome,bloco[i].numero))
		{
			contador++;
			i++;
			registros_qtd++;
		}
		for(i=0;i<contador-1;i++){
			bubbleLex(bloco,contador);
			fprintf(tempFile,"%s:%s\n",bloco[i].nome,bloco[i].numero);
			}
		
		if(feof(myFile)){
			fprintf(tempFile,"%s:%s",bloco[contador-1].nome,bloco[contador-1].numero);
		}
		else
			fprintf(tempFile,"%s:%s\n",bloco[contador-1].nome,bloco[contador-1].numero);
		qtd_blocos++;
	}
	fclose(tempFile);

	FILE* rolinha;
	rolinha=fopen("entrada.ordenado","r");
	printf("qtd registros = %d\n",registros_qtd );
	printf("qtd_blocos = %d \n",qtd_blocos );

	Chunk* ch=(Chunk*)malloc(sizeof(Chunk)*(qtd_blocos+1));
	int elem=bytes/(qtd_blocos+1)/sizeof(Registro);
	printf("elem %d\n",elem);
	for(i=0;i<(qtd_blocos+1);i++){                             
		ch[0].registro=(Registro*)malloc(sizeof(Registro)*elem);
	}
	return 0;
}
