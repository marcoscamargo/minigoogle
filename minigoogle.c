#include "minigoogle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sinfo {
	int code;
	char name[51];
	int relevance;
	char link[101];
	char *keyword[51];
};

struct no {
	Site *key;
	struct no *next;
	struct no *previous;
};

struct slist {
	No *header;
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

	scanf("%d", &opr);

	return opr;
}

boolean insertSite(SiteList *list, Site *site){
	No *p = list->header->next;
	No *n = (No *) malloc (sizeof(No));

	if(n != NULL && site != NULL){
		n->key = site;

		while (p != list->header && p->site->relevance <	n->site->relevance){
			p = p->next;
		}

		n->next = p->next;
		n->previous = p;
		p->next->previous = n; 
		p->next = n;

		return true;
	} else {
		return false;
	}

}

boolean printSiteList(SiteList *list) {
	No *p = list->header->next;
	if (p != NULL) {
		while (p != list->header){
			printSite(p->key);
		}

		return true;
	} else {
		return false;
	}

}