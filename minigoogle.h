#ifndef MINI_GOOGLE_H
#define MINI_GOOGLE_H

typedef struct sinfo Site;

typedef struct node Node;

typedef struct slist SiteList;

typedef unsigned char boolean;


int Menu();

boolean insertSite();

boolean insertKeyworld();

boolean removeSite();

boolean updateRelevance();

boolean printSiteList();

boolean printSite();

SiteList *initialization();

boolean finalization(SiteList *slist);

#endif