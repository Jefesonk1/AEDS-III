#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
struct registro{
	char nome[20];
	char numero[10];

}typedef Registro;

int main(int argc, char const *argv[])
{
	if(argc!=3)
		return -1;
	int bytes=atoi(argv[1]);
	char const* filename=argv[2];
	FILE* myFile;

	myFile=fopen(filename,"r");
	if(myFile==NULL)
		return -33;

	Registro reg;
	while(!feof(myFile)){
		fscanf(myFile,"%[^:]:%[^\n]\n",reg.nome,reg.numero);
		printf("%s %s\n",reg.nome,reg.numero);
	}
	return 0;
}
