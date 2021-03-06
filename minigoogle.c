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
	char **keyword;
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

int opSelection(){
	int opr;
	printf("1. Inserir um novo site na lista\n");
	printf("2. Inserir palavra-chave em um site\n");
	printf("3. Remover um site da lista\n");
	printf("4. Atualizar relevância de um site\n");
	printf("5. Exibir a lista\n");
	printf("6. Busca por palavra-chave\n");
	printf("7. Sair\n\n");
	printf("Digite o numero de sua operação : ");

	// le e retorna a opcao escolhida
	scanf("%d", &opr);

	return opr;
}


boolean insertSite(SiteList *list, Site *site){
	Node *p = list->header->next;
	Node *n = (Node*)malloc(sizeof(Node));
	// verifica se o no e o site informados são validos
	if(n != NULL && site != NULL){
		n->key = site;

		// procura a posicao para inserir o novo registro
		while (p != list->header && p->key->relevance > n->key->relevance){
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
		list->tam++;
		return true;
	} else {
		// caso os ponteiros sejam invalidos retorna false
		return false;
	}

}

void printSite(Site *site, char flag){
	int i;
	//imprimindo codigo, nome, relevancia, e link
	switch(flag){
		case 'f':
			printf("%04d, %s, %d, %s", site->code, site->name, site->relevance, site->link);
			// imprimindo as palavras-chave conforme a quantidade
			for(i = 0; i < site->nkeywords; i++){
				printf(", %s", site->keyword[i]);
			}
			printf("\n");
			break;
		default:
			printf("Nome: %s\n",site->name);
			printf("Url: %s\n",site->link);
	}
}

boolean printSiteList(SiteList *slist, char flag) {
	Node *p = slist->header->next;
	// se a lista de sites informadas for invalida, retornara null
	if (p != NULL) {
		// percorre todos os valores da lista, e imprime
		while (p != slist->header){
			printSite(p->key,flag);
			p = p->next;
		}
		return true;
	} else {
		return false;
	}
}

SiteList *buildSList(){
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

boolean clearSList(SiteList *slist){
	// verifica se eh uma lista de sites valida
	if(slist != NULL){
	Node *p = slist->header->next;
		// percorre todos vetores, e libera o anterior
		do{
			p = p->next;
			freeSite(p->previous->key);
			free(p->previous);

		}while (p != slist->header);
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
			freeSite(p->key);
			free(p);
			slist->tam--;
			// retorna true seja removido com sucesso
			return true;
		}
		return false;
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

Site* readSite(SiteList* list){
	Site *reg = (Site*)malloc(sizeof(Site));
	char *lineRead = NULL;
	char* temp = NULL;
	size_t strsize = 0;
	reg->code = list->tam + 1;

	reg->keyword = NULL;
	reg->nkeywords = 0;
	printf("Digite as informações do site a serem inseridas\n");
	printf("Formato de entrada:\n");
	printf("\"NOME,RELEVANCIA,URL,<PALAVRAS-CHAVE>\"\n");
	printf("Cada palavra deve ser inserida entre vírgulas, exceto pela ultima.\n");
	getchar();
	//lendo uma linha
	getline(&lineRead, &strsize, stdin);
	//removendo o '\n' final da linha, caso haja
	if(lineRead[strlen(lineRead)-1] == '\n') lineRead[strlen(lineRead)-1] = '\0';

	//recebendo o número do site

	//recebendo nome
	temp = strtok(lineRead,",");
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
	for(i = 0; i < reg->nkeywords; i++){
		free(reg->keyword[i]);
	}
	free(reg->keyword);
	free(reg);
}

int getEndPos(FILE* fp){
	if(fp == NULL) return -1;
	int end = 0;
	fseek(fp,0,SEEK_END);
	end = ftell(fp);
	fseek(fp,0,SEEK_SET);
	return end;
}

boolean readCSVFile(SiteList* slist, FILE* csv){
	Site* temp = NULL;
	long int endpos;

	if(slist == NULL){
		printf("Invalid List\n");
		return false;
	}

	endpos = getEndPos(csv);
	while(ftell(csv) < endpos){
		temp = readCSVLine(csv);
		insertSite(slist, temp);
	}
	return true;
}


boolean updateRelevance(SiteList *slist, int code, int relevance){
	Node *p = slist->header->next;
	// verifica se o ponteiro é valido
	if(p != NULL){
		// procura a posicao do registro para atualizar a relevancia
		while (p != slist->header && p->key->code != code){
			p = p->next;
		}
		// atualiza a relevancia
		if(p != slist->header){
			p->key->relevance = relevance;
			return true;
		} else {
			printf("valor nao encontrado !\n");
			return false;
		}
	} else {
		// caso os ponteiros sejam invalidos retorna false
		return false;
	}

}


boolean insertKeyword(SiteList *slist, int code, char *keyword){
	Node *p = slist->header->next;
	// verifica se o ponteiro é valido
	if(p != NULL){
		// procura a posicao do registro para inserir a palavra-chave
		while (p != slist->header && p->key->code != code){
			p = p->next;
		}
		// atualiza a relevancia
		if(p != slist->header){
			p->key->nkeywords++;
			p->key->keyword = (char **) realloc (p->key->keyword, sizeof(char *)*p->key->nkeywords);
			p->key->keyword[p->key->nkeywords - 1] = (char *) malloc (sizeof(char)*MAX_STR_SIZE);	
			strcpy(p->key->keyword[p->key->nkeywords - 1], keyword);
			return true;
		} else {
			printf("código nao encontrado !\n");
			return false;
		}
	} else {
		// caso os ponteiros sejam invalidos retorna false
		return false;
	}

}


//libera uma lista sem liberar suas chaves
boolean clearAuxList(SiteList *slist){
	// verifica se eh uma lista de sites valida
	if(slist != NULL){
	Node *p = slist->header->next;
		// percorre todos vetores, e libera o anterior
		do{
			p = p->next;
			if(p->previous != slist->header)free(p->previous);

		}while (p != slist->header);
		free(slist->header);
		// libera 	list
		free(slist);
		return true;
	} else {
		return false;
	}
}


boolean HaveKeyword(Site* site, char* word){
	int i;
	// verifica se o site contem a palavra word
	for(i = 0; i < site->nkeywords; i++){
		if(!strcmp(site->keyword[i],word)) return true;
	}
	return false;
}

boolean removeNode(SiteList *slist, int code){
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
			free(p);
			slist->tam--;
			// retorna true seja removido com sucesso
			return true;
		}
		return false;
	} else {
		// caso os ponteiros sejam invalidos retorna false
		return false;
	}

}

//busca valores com um keyword em específico em uma lista
void searchList(SiteList* copy, SiteList* resultList, char* keyword){
	int i;
	Node* aux = NULL;
	Node* auxBackup = NULL;
	aux = copy->header->next;
	//buscando resultados e inserindo-os na lista de resultados
	while(aux != copy->header){
		auxBackup = aux->next;

		if( HaveKeyword(aux->key,keyword) ) {
			//insiro aux na lista de resultados
			insertSite(resultList, aux->key);
			// removo aux da lista cópia;
			removeNode(copy, aux->key->code);
		}
	
		aux = auxBackup;
	}
}


SiteList *copyList(SiteList *original){
	if(original == NULL) return NULL;

	SiteList *copy = buildSList();
	Node *p = original->header->next;

	while(original->header != p){
		insertSite(copy, p->key);	
		p = p->next;
	}

	return copy;
}

char **getKeywordsList(SiteList *slist, int *tam){
	// inicializando vetor de strings para 1 palara que vem da stdin
	//tam inicializado em 1.

	char **keywords = (char **)malloc(sizeof(char *) * (*tam) );
	keywords[0] = NULL;
	size_t keywordSize = 0;
	// lendo primeira palavra da stdin
	getline(&keywords[0], &keywordSize, stdin);
	keywords[0][strlen(keywords[0])-1] = '\0';


	int i;
	Node *aux = slist->header->next;

	while(slist->header != aux){
		// verifica se exista a palavra buscada no site
		if( HaveKeyword(aux->key, keywords[0]) ){
			// se existir percorre todas palavras chaves do site
			for(i = 0; i < aux->key->nkeywords; i++){
				// se for diferente da palavra buscada (strcmp retorna 0 == false quando é igual)
				//	copia para a lista
				if( strcmp(aux->key->keyword[i], keywords[0]) ){
					
					keywords = (char **) realloc (keywords, sizeof(char *) * (*tam + 1) );
					keywords[*tam] = (char *) malloc (sizeof(char) * MAX_STR_SIZE);
					strcpy(keywords[*tam], aux->key->keyword[i]);
					(*tam)++;
				
				}

			}

		}
		aux = aux->next;
	}


	return keywords;
}

//busca e imprime resultados e relacionados
void GoogleSearch(SiteList* slist){
	int i, j, nkeywords = 1;
	SiteList* resultList = NULL;
	SiteList *copy = copyList(slist);
	resultList = buildSList();

	// obtem a lista de palavras
	char **keywords = getKeywordsList(slist, &nkeywords);

	// busca a primeira palavra - palavra digitada
	searchList(copy, resultList, keywords[0]);

	//verificando se a lista de resultados está vazia
	if(resultList->header->next != resultList->header){
		printf("Resultados encontrados: %d\n",resultList->tam);
		printSiteList(resultList,'d');
	} else {
		printf("Resultados encontrados: 0\n");
	}
	printf("\n");
	// apagando valores ja imprimidos
	clearAuxList(resultList);
	// gerando nova lista
	resultList = buildSList();

	//buscando por palavras relacionadas
	for(i = 1; i < nkeywords; i++){
		searchList(copy, resultList, keywords[i]);
	}

	//imprimindo sites relacionados
	if(resultList->header->next != resultList->header){
		printf("Resultados relacionados: %d\n",resultList->tam);
		printSiteList(resultList,'d');
	}

	//liverando a copia e a lista de palavras relacionadas
	clearAuxList(copy);
	clearAuxList(resultList);

	// liberando lista de palavras
	for(i = 0; i < nkeywords; i++){
		free(keywords[i]);
	}
	free(keywords);

}