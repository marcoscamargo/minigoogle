#include "minigoogle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const boolean true 	= 1;
const boolean false = 0;

struct sinfo {
	int code;
	char name[51];
	int relevance;
	char link[101];
	char *keyword[51];
	int nkeywords;
};

struct node {
	Site *key;
	struct node *next;
	struct node *previous;
};

struct slist {
	Node *header;
	int tam;
};

int Menu(){
	int opr;
	printf("Bem vindo ao Mini Google!\n");
	printf("1. Inserir um novo site na lista\n");
	printf("2. Inserir palavra-chave em um site\n");
	printf("3. Remover um site da lista\n");
	printf("4. Atualizar relevância de um site");
	printf("5. Exibir a lista\n");
	printf("6. Busca por palavra-chave\n");
	printf("7. Sair\n");
	printf("Digite o numero de sua operação : ");

	// le e retorna a opcao escolhida
	scanf("%d", &opr);

	return opr;
}


boolean insertSite(SiteList *list, Site *site){
	Node *p = list->header->next;
	Node *n = (Node *) malloc (sizeof(Node));
	// verifica se o no e o site informados são valos (diferentes de null)
	if(n != NULL && site != NULL){
		n->key = site;

		// procura a posicao para inserir o novo registro
		while (p != list->header && p->key->relevance < n->key->relevance){
			p = p->next;
		}
		// volta para a posicao anterior para inserir a direita
		p = p->previous;

		// insere na posicao correta
		n->next = p->next;
		n->previous = p;
		p->next->previous = n; 
		p->next = n;
		// retorna true caso tenha inserido corretamente
		return true;
	} else {
		// caso os ponteiros sejam invalidos retorna false
		return false;
	}

}

boolean printSite(Site *site){
	//imprimindo codigo, nome, relevancia, e link
	printf("%4d, %s, %d, %s\n", site->code, site->name, site->relevance, site->link);
	int i;
	// imprimindo as palavras-chave conforme a quantidade
	for(i = 0; i < site->nkeywords; i++){
		printf(", %s", site->keyword[i]);
	}
}


boolean printSiteList(SiteList *slist) {
	Node *p = slist->header->next;
	// se a lista de sites informadas for invalida, retornara null
	if (p != NULL) {
		// percorre todos os valores da lista, e imprime
		while (p != slist->header){
			printSite(p->key);
		}
		return true;
	} else {
		return false;
	}

}

SiteList *initialization(){
	//alocando memoria para uma nova lista de sites
	SiteList *slist = (SiteList *) malloc (sizeof(SiteList));
	// verifica se a memoria alocada eh valida
	if(slist == NULL){
		return NULL;	
	} else {
		// inicializa o tamanho
		slist->tam = 0;
		//aloca memoria para o no cabecalho
		slist->header = (Node *) malloc (sizeof(Node));
		// aponta os valores do cabecalho para ele mesmo -- lista sem valores
		slist->header->next = slist->header;
		slist->header->previous = slist->header;

		return slist;
	}
}

boolean finalization(SiteList *slist){
	Node *p = slist->header->next;
	// verifica se eh uma lista de sites valida
	if(slist != NULL){
		// percorre todos vetores, e libera o anterior
		while (p != slist->header){
			p = p->next;
			free(p->previous->key->keyword);
			free(p->key);
			free(p->previous);
		}
		free(slist->header);
		// libera 	list
		free(slist);
		return true;
	} else {
		return false;
	}
}

boolean removeSite(SiteList *slist, int code){
	Node *p = slist->header->next;
	// verifica se o ponteiro é valido (diferente de null)
	if(p != NULL) {
		// procura a posicao da chave a ser removida
		while (p != slist->header && p->key->code != code){
			p = p->next;
		}

		if(p != slist->header){
			// "removendo" site da slist
			p->previous->next = p->next;
			p->next->previous = p->previous;
			// liberando a memoria do valor utilizado
			free(p->key->keyword);
			free(p->key);
			free(p);
			// retorna true seja removido com sucesso
			return true;
		}
	} else {
		// caso os ponteiros sejam invalidos retorna false
		return false;
	}

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