#ifndef ARBRE_H
#define ARBRE_H

#define ELEMENTNUL 0
#define ARBRENULL NULL



typedef long ElementArbre;

// Structure d'arbre
struct arbre {
    ElementArbre e;
    ElementArbre f;
    float g;
    ElementArbre h;
    char *i;
    ElementArbre j;
    struct arbre *fg;
    struct arbre *fd;
    struct arbre *fm;
    int equilibre;
    int hauteur;
};
typedef struct arbre Arbre;
typedef Arbre* PArbre;

// typedef PArbre ElementListe;


#include "file.h"




int Max(int a, int b);
int Min(int a, int b);

PArbre creerArbre(ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j);
int estVide(PArbre a);
int estFeuille(PArbre a);
ElementArbre elementArbre(PArbre a);
int existeFilsGauche(PArbre a);
int existeFilsDroit(PArbre a);
// PArbre ajouterFilsGauche(PArbre a, ElementArbre e);
// PArbre ajouterFilsDroit(PArbre a, ElementArbre e);

void traiter(PArbre a);
void parcoursPrefixe(PArbre a);
void parcoursInfixe(PArbre a);
void parcoursPostfixe(PArbre a);


void parcoursLargeur(PArbre a);

void supprimerFilsGauche(PArbre a);
void supprimerFilsDroit(PArbre a);

int nbFeuilles(PArbre a);
int tailleArbre(PArbre a);
int hauteurArbre(PArbre a);


#endif