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

		// insete na posicao correta
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
	printf("%4d, %s, %d, %s", site->code, site->name, site->relevance, site->link);
	int i;
	// imprimindo as palavras-chave conforme a quantidade
	for(i = 0; i < site->nkeywords; i++){
		printf(", %s", site->keyword[i]);
	}
}


boolean printSiteList(SiteList *list) {
	Node *p = list->header->next;
	// se a lista de sites informadas for invalida, retornara null
	if (p != NULL) {
		// percorre todos os valores da lista, e imprime
		while (p != list->header){
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