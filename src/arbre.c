
#include <stdio.h>
#include <stdlib.h>

#include "../head/arbre.h"

int Max(int a, int b) {
    return (a > b) ? a : b;
}

int Min(int a, int b) {
    return (a < b) ? a : b;
}

PArbre creerArbre(ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j) {
    PArbre nouveau = malloc(sizeof(Arbre));
    if (nouveau == NULL) {
        printf("***ERREUR ALLOCATION MALLOC***\n");
        exit(4);
    }
    nouveau->e = e;
    nouveau->f = f;
    nouveau->g = g;
    nouveau->h = h;
    if (i) {
        nouveau->i = malloc(sizeof(char) * 128);
        if (!nouveau->i) {
            printf("ERREUR ALLOCATION MALLOC\n");
            exit(4);
        }
        sprintf(nouveau->i, "%s", i);
    }
    nouveau->j = j;
    nouveau->fg = NULL;
    nouveau->fm = NULL;
    nouveau->fd = NULL;
    nouveau->equilibre = 0;
    nouveau->hauteur = 0;
    return nouveau;
}

int estVide(PArbre a) {
    return (a == NULL);
}

int estFeuille(PArbre a) {
    return (a && !(a->fg) && !(a->fd)) ? 1 : 0;
}

// ElementArbre elementArbre(PArbre a) {
//     return (a ? a->e : ELEMENTNUL);
// }

int existeFilsGauche(PArbre a) {
    return (a && a->fg);
}

int existeFilsDroit(PArbre a) {
    return (a && a->fd);
}

// PArbre ajouterFilsGauche(PArbre a, ElementArbre e) {
//     if (estVide(a)) return creerArbre(e);
//     if (!existeFilsGauche(a)) {
//         a->fg = creerArbre(e);
//     }
//     return a;
// }

// PArbre ajouterFilsDroit(PArbre a, ElementArbre e) {
//     if (estVide(a)) return creerArbre(e);
//     if (!existeFilsDroit(a)) {
//         a->fd = creerArbre(e);
//     }
//     return a;
// }

void traiter(PArbre a) {
    if (a) printf("%ld ", a->e);
}

void parcoursPrefixe(PArbre a) {
    if (!a) return;
    traiter(a);
    parcoursPrefixe(a->fg);
    parcoursPrefixe(a->fd);
}

void parcoursInfixe(PArbre a) {
    if (!a) return;
    parcoursInfixe(a->fg);
    traiter(a);
    parcoursInfixe(a->fd);
}

void parcoursPostfixe(PArbre a) {
    if (!a) return;
    parcoursPostfixe(a->fg);
    parcoursPostfixe(a->fd);
    traiter(a);
}
/*
void parcoursLargeur(PArbre a) {
    if (a == NULL) return;
    printf("Parcours en largeur : ");
    PArbre noeud = NULL;
    FileDyn file = {NULL, NULL};
    enfilerDyn(&file, a);
    while (file.tete != NULL) {
        defilerDyn(&file, &noeud);
        // printf("\ndefile : %d\n", estVide(noeud));
        if (noeud) {
            traiter(noeud);
            enfilerDyn(&file, noeud->fg);
            // printf("\nenfile : %d\n", estVide(noeud));
            enfilerDyn(&file, noeud->fd);
            // printf("\nenfile : %d\n", estVide(noeud));
        }
    }
    printf("\n");
}
*/
PArbre modifierRacine(PArbre a, ElementArbre e) {
    if (a!= NULL) {
        a->e = e;
    }
    return a;
}

void supprimerFilsGauche(PArbre a) {
    if (!a) return;
    if (a->fg) {
        if (a->fg->fg) supprimerFilsGauche(a->fg);
        if (a->fg->fd) supprimerFilsDroit(a->fg);
        free(a->fg);
        a->fg = NULL;
        // printf("supprime\n");
    }
}

void supprimerFilsDroit(PArbre a) {
    if (!a) return;
    if (a->fd) {
        if (a->fd->fg) supprimerFilsGauche(a->fd);
        if (a->fd->fd) supprimerFilsDroit(a->fd);
        free(a->fd);
        a->fd = NULL;
        // printf("supprime\n");
    }
}

int nbFeuilles(PArbre a) {
    if (a == NULL) return 0;
    int feuilles = 0;
    feuilles += nbFeuilles(a->fg);
    feuilles += nbFeuilles(a->fd);
    if (a->fg == NULL && a->fd == NULL) return 1;

    return feuilles;
}

int tailleArbre(PArbre a) {
    if (a == NULL) return 0;
    int taille = 0;

    taille += tailleArbre(a->fg);
    taille += tailleArbre(a->fd);

    if (((a->fg != NULL) + (a->fd != NULL)) > 0) taille++;

    return taille;
}

int hauteurArbre(PArbre a) {
    int hauteur = 1;
    if (!a) return 0;
    hauteur += Max(hauteurArbre(a->fg), hauteurArbre(a->fd));

    return hauteur;
}

