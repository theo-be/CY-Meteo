#ifndef ABR_H
#define ABR_H

#include "arbre.h"


int recherche(PArbre a, ElementArbre e);

PArbre insertABR(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, float j);



PArbre insertionABRAltitude(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i);
PArbre insertionABRHumidite(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i);
PArbre insertionABRVent(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j);
PArbre insertionABRP1(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j);
PArbre insertionABRP2(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j);
PArbre insertionABRP3(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j);

#endif