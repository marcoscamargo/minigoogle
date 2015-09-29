#include "minigoogle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char *argv[]){
	SiteList* slist = NULL;
	int opr = 1;
	int code, relevance;
	char *keyword = (char *)malloc(sizeof(char)*MAX_STR_SIZE);

	FILE* csv = fopen("googlebot.csv","r");
	slist = buildSList();
	readCSVFile(slist,csv);
	fclose(csv);
	
	printf("Bem vindo ao Mini Google!\n\n");

	do {
		opr = opSelection();

		switch(opr) {
			case 1:
					insertSite(slist,readSite(slist));
					break;
			case 2:
					printf("Digite o código do site e a palavra-chave a ser inserida : ");
					scanf("%d %s", &code, keyword);
					getchar();
					insertKeyword(slist, code, keyword);
					break;
			case 3:
					printf("Digite o código do site a ser removido : ");
					scanf("%d", &code);
					getchar();
					removeSite(slist, code);
					break;
			case 4:
					printf("Digite o código do site e a nova relevância : ");
					scanf("%d %d", &code, &relevance);
					getchar();
					updateRelevance(slist, code, relevance);
					break;
			case 5:
					printSiteList(slist, 'f');
					break;
			case 6:
					getchar();
					GoogleSearch(slist);
					break;
			default:
					opr = 0;
					clearSList(slist);
					break;
		}
	} while (opr);
	

	free(keyword);
	return 0;
}