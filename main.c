#include "minigoogle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char *argv[]){
	SiteList* slist = NULL;
	int opr = 1;
	int code;

	FILE* csv = fopen("googlebot.csv","r");
	slist = buildSList();
	readCSVFile(slist,csv);
	fclose(csv);
	printf("Bem vindo ao Mini Google!\n");
	do {
		opr = opSelection();

		switch(opr) {
			case 1:
					insertSite(slist,readSite(slist));
					break;
			case 2:
					break;
			case 3:
					scanf("%d", &code);
					removeSite(slist, code);
					break;
			case 4:
					break;
			case 5:
					printSiteList(slist);
					break;
			case 6:
					break;
			case 7:
					opr = 0;
					clearSList(slist);
					break;
		}
	} while (opr);
	


	return 0;
}