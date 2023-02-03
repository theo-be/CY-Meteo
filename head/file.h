#ifndef FILE_H
#define FILE_H

#include "arbre.h"

// definition de la structure Chainon
struct chainon {
    ElementArbre e;
    ElementArbre f;
    float g;
    ElementArbre h;
    char *i;
    ElementArbre j;
    struct chainon *s;
};
typedef struct chainon Chainon;

// manipulation de liste

// insertion

Chainon *creationChainon(ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j);
// Chainon *insertionDebut(Chainon *pliste, PArbre e);
// Chainon *insertionFin(Chainon *pliste, PArbre e);
// Chainon *insertionOrdre(Chainon *pliste, PArbre e, int ordre);
// insertion croissant

// suppression

Chainon *suppressionDebut(Chainon *pliste);
Chainon *suppressionFin(Chainon *pliste);
// Chainon *suppressionElem(Chainon *pliste, PArbre e);
Chainon *nettoyerListe(Chainon *pliste);


// fonctions de tri du projet



Chainon *insertionCroissant(Chainon *pliste, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i);

Chainon *insertionListeAltitude(Chainon *pliste, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i);
Chainon *insertionListeHumidite(Chainon *pliste, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i);
Chainon *insertionListeVent(Chainon *pliste, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j);
Chainon *insertionListeP1(Chainon *pliste, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j);
Chainon *insertionListeP2(Chainon *pliste, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j);
Chainon *insertionListeP3(Chainon *pliste, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j);




























struct filedyn {
    Chainon *tete;
    Chainon *queue;
};
typedef struct filedyn FileDyn;


struct filestat {
    PArbre *tab;
    int taille;
    int tete;
    int queue;
};
typedef struct filestat FileStat;


// file dynamique


FileDyn creerFileDyn();
int verificationFileDyn(FileDyn *f);
int enfilerDyn(FileDyn *f, PArbre e);
int defilerDyn(FileDyn *f, PArbre *e);




// file statique

FileStat creerFileStat(int taille);
int verificationFileStat(FileStat *f);
int enfilerStat(FileStat *f, PArbre e);
int defilerStat(FileStat *f, PArbre *e);



#endif