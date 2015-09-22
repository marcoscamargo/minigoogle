#ifndef MINI_GOOGLE_H
#define MINI_GOOGLE_H

typedef struct sinfo Site;

typedef struct node Node;

typedef struct slist SiteList;

typedef unsigned char boolean;
const boolean true 	= 1;
const boolean false = 0;

int Menu();

boolean insertSite();

boolean insertKeyworld();

boolean removeSite();

boolean updateRelevance();

boolean printSiteList();

boolean printSite();

boolean initialization();

boolean finalization();

#endif