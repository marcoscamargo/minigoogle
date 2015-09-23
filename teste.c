#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sinfo {
	int code;
	char name[51];
	int relevance;
	char link[101];
	char **keyword;
	int nkeywords;
}Site;

#define MAX_STR_SIZE 51

void printSite(Site *site){
	//imprimindo codigo, nome, relevancia, e link
	printf("%04d, %s, %d, %s", site->code, site->name, site->relevance, site->link);
	int i;
	// imprimindo as palavras-chave conforme a quantidade
	for(i = 0; i < site->nkeywords; i++){
		printf(", %s", site->keyword[i]);
	}
	printf("\n");
}

Site* readCSVLine(FILE* csv){
	Site *reg = (Site*)malloc(sizeof(Site));
	char *lineRead = NULL;
	char* temp = NULL;
	size_t strsize = 0;

	reg->keyword = NULL;
	reg->nkeywords = 0;

	//lendo uma linha
	getline(&lineRead, &strsize, csv);
	//removendo o '\n' final da linha, caso haja
	if(lineRead[strlen(lineRead)-1] == '\n') lineRead[strlen(lineRead)-1] = '\0';

	//recebendo o número do site
	temp = strtok(lineRead,",");
	reg->code = atoi(temp);

	//recebendo nome
	temp = strtok(NULL,",");
	strcpy(reg->name,temp);

	//recebendo relevancia
	temp = strtok(NULL,",");
	reg->relevance = atoi(temp);

	//recebendo link
	temp = strtok(NULL,",");
	strcpy(reg->link,temp);

	//recebendo palavras chave:
	temp = strtok(NULL,","); //recebe a primeira palavra chave
	while(temp != NULL){
		reg->nkeywords++;
		//alocando memoria necessaria
		reg->keyword = (char**)realloc(reg->keyword,sizeof(char*)*(reg->nkeywords));
		reg->keyword[(reg->nkeywords)-1] = (char*)malloc(sizeof(char)*MAX_STR_SIZE);
		// copiando a string para o destino
		strcpy(reg->keyword[(reg->nkeywords)-1],temp);
		//lê a palavra chave antes da verificacao inicial da proxima iteração
		temp = strtok(NULL,",");
	}
	//liberando a memoria utilizada
	free(temp);
	free(lineRead);
	return reg;
}

void freeSite(Site* reg)
{
	int i;
	for(i = 0; i < reg->nkeywords; i++)
	{
		free(reg->keyword[i]);
	}
	free(reg->keyword);
	free(reg);
}



int main(void)
{
	Site* site = NULL;
	FILE* csv = fopen("googlebot.csv","r");
	site = readCSVLine(csv);

	printSite(site);

	freeSite(site);

	fclose(csv);
	
	return 0;
}