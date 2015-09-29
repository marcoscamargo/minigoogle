#ifndef MINI_GOOGLE_H
#define MINI_GOOGLE_H

#define MAX_STR_SIZE 51

#include <stdio.h>

typedef struct sinfo Site;

typedef struct node Node;

typedef struct slist SiteList;

typedef unsigned char boolean;


int opSelection();

boolean insertSite(SiteList *list, Site *site);

boolean insertKeyword(SiteList *slist, int code, char *keyword);

boolean removeSite(SiteList *slist, int code);

boolean updateRelevance(SiteList *slist, int code, int relevance);

boolean printSiteList(SiteList *slist, char flag);

void printSite(Site *site, char flag);

SiteList* buildSList();

boolean clearSList(SiteList *slist);

Site* readCSVLine(FILE* csv);

boolean readCSVFile(SiteList* slist, FILE* csv);

void freeSite(Site* reg);

Site* readSite();

SiteList* searchList(SiteList* copy, SiteList* resultList, char* keyword);

boolean clearAuxList(SiteList *slist);

void GoogleSearch(SiteList* slist);

#endif