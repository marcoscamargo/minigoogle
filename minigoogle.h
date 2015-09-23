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

boolean insertKeyword();

boolean removeSite(SiteList *slist, int code);

boolean updateRelevance();

boolean printSiteList(SiteList *slist) ;

void printSite(Site *site);

SiteList* buildSList();

boolean clearSList(SiteList *slist);

Site* readCSVLine(FILE* csv);

boolean readCSVFile(SiteList* slist, FILE* csv);

void freeSite(Site* reg);

Site* readSite();

#endif