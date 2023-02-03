
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../head/file.h"

// Liste chainee

// Manipulation de la liste

// Insertion


Chainon *creationChainon(ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j) {
    Chainon *n = malloc(sizeof(Chainon));
    if (!n) {
        printf("***ERREUR ALLOCATION MALLOC***\n");
        exit(4);
    }
    n->e = e;
    n->f = f;
    n->g = g;
    n->h = h;
    if (i) {
        n->i = malloc(sizeof(char) * 128);
        if (!n->i) {
            printf("ERREUR ALLOCATION MALLOC\n");
            exit(4);
        }
        sprintf(n->i, "%s", i);
    }
    n->j = j;
    n->s = NULL;
    return n;
}
/*
Chainon *insertionDebut(Chainon *pliste, PArbre e) {
    Chainon *n = creationChainon(e);

    if (!pliste) return n;

    n->s = pliste;
    return n;
}

Chainon *insertionFin(Chainon *pliste, PArbre e) {
    Chainon *n = creationChainon(e);
    Chainon *i = pliste;
    if (!pliste) return n;

    while (i->s) i = i->s;

    i->s = n;
    return pliste;
}
*/

// Suppression

Chainon *suppressionDebut(Chainon *pliste) {
    if (!pliste) return NULL;
    Chainon *i = pliste->s;
    free(pliste);
    return i;
}

Chainon *suppressionFin(Chainon *pliste) {
    if (!pliste) return NULL;
    Chainon *i = pliste;
    Chainon *p = pliste;

    if (!(pliste->s)) return suppressionDebut(pliste);

    while (i->s) {
        p = i;
        i = i->s;
    }

    free(i);
    p->s = NULL;
    return pliste;
}

/*
Chainon *suppressionElem(Chainon *pliste, PArbre e) {
    if (!pliste) return NULL;
    if (pliste->e == e) return suppressionDebut(pliste);
    

    Chainon *i = pliste;
    Chainon *pre = pliste;
    while (i) {

        if (i->e == e) {
            pre->s = i->s;
            free(i);
            return pliste;
        }

        pre = i;
        i = i->s;
    }
    return pliste;
}
*/

Chainon *nettoyerListe(Chainon *pliste) {
    while (pliste) {
        pliste = suppressionDebut(pliste);
    }
    return pliste;
}




// Fonctions necessaires au projet
// Ne fonctionnent pas correctement


Chainon *insertionCroissant(Chainon *pliste, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i) {
    if (!pliste) return creationChainon(e, f, g, h, i, .0);
    Chainon *t = pliste;
    Chainon *n = NULL;
    Chainon *p = t;

    while (e > t->e) {
        if (t->s) {
            p = t;
            t = t->s;
        }
        else break;
    }

    n = creationChainon(e, f, g, h, i, .0);
    n->s = t;
    p->s = n;

    return pliste;
}


Chainon *insertionListeAltitude(Chainon *pliste, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i) {
    if (!pliste) return creationChainon(e, f, g, h, i, .0);
    Chainon *t = pliste;
    Chainon *n = NULL;
    Chainon *p = t;

    while (e < t->e) {
        if (t->s) {
            p = t;
            t = t->s;
        }
        else break;
    }

    if (f == p->f) return pliste;
    else {
        n = creationChainon(e, f, g, h, i, .0);
        n->s = t;
        p->s = n;
    }
    return pliste;
}


Chainon *insertionListeHumidite(Chainon *pliste, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i) {
    if (!pliste) return creationChainon(e, f, g, h, i, .0);
    Chainon *t = pliste;
    Chainon *n = NULL;
    Chainon *p = t;

    while (f < t->f) {
        if (t->s) {
            p = t;
            t = t->s;
        }
        else break;
    }

    if (f == p->f) {
        if (e > p->e) p->e = e;
    }
    else {
        n = creationChainon(e, f, g, h, i, 0);
        n->s = p->s;
        p->s = n;
    }
    return pliste;
}


Chainon *insertionListeVent(Chainon *pliste, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j) {
    if (!pliste) return creationChainon(e, f, g, h, i, j);
    Chainon *t = pliste;
    // Chainon *n = NULL;

    while (e > t->e) {
        if (t->s) t = t->s;
        else break;
    }

    if (e == t->e) {
        pliste->f += f;
        pliste->g += g;

        pliste->h++;
        pliste->j++;
    }
    return pliste;
}


Chainon *insertionListeP1(Chainon *pliste, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j) {
    if (!pliste) return creationChainon(e, f, g, f, i, f);
    Chainon *t = pliste;
    // Chainon *n = NULL;

    while (e > t->e) {
        if (t->s) t = t->s;
        else break;
    }

    if (e == t->e) {
        pliste->f += f;
        pliste->g++;
        if (f < pliste->h) pliste->h = f;
        if (f > pliste->j) pliste->j = f;
    }
    return pliste;
}


Chainon *insertionListeP2(Chainon *pliste, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j) {
    if (!pliste) return creationChainon(e, f, g, h, i, j);
    Chainon *t = pliste;
    // Chainon *n = NULL;

    while (strcmp(i, pliste->i) > 0) {
        if (t->s) t = t->s;
        else break;
    }

    if (!strcmp(i, pliste->i)) {
        pliste->f += f;
        pliste->g++;
    }
    return pliste;
}


Chainon *insertionListeP3(Chainon *pliste, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j) {
    if (!pliste) return creationChainon(e, f, g, h, i, j);
    Chainon *t = pliste;
    Chainon *n = NULL;

    // tri par station
    // pas opti
    while (strcmp(i, pliste->i) > 0 || e > pliste->e) {
        if (t->s) t = t->s;
        else break;
    }
    
    // tri par date
    if (!strcmp(i, pliste->i)) return pliste;

    n = creationChainon(e, f, g, h, i, j);
    n->s = t->s;
    t->s = n;
    return pliste;
}












/*

//file dynamique


FileDyn creerFileDyn() {
    FileDyn f = {NULL, NULL};
    return f;
}

int verificationFileDyn(FileDyn *f) {
    int res = 0;
    if (!f) res = -1;
    else if ((f->tete == NULL) != (f->queue == NULL)) res = -2;
    else if (f->queue != NULL && f->queue->s != NULL) res = -3;
    return res;
}

int enfilerDyn(FileDyn *f, PArbre e) {
    Chainon *n = NULL;
    int res = verificationFileDyn(f);
    if (res > -2) {
        n = creationChainon(e);
        if (f->tete == NULL) {
            f->tete = n;
            f->queue = n;
        }
        else {
            f->queue->s = n;
            f->queue = n;
        }
    }
    return res;
}

int defilerDyn(FileDyn *f, PArbre *e) {
    int res = verificationFileDyn(f);
    Chainon *i = NULL;
    if (res > -2) {
        if (!(f->tete)) res = 1;
        else {
            // s'il n'y a qu'un element dans la liste
            if (f->tete == f->queue) {
                *e = f->tete->e;
                free(f->tete);
                f->tete = NULL;
                f->queue = NULL;
            } else {
                *e = f->tete->e;
                i = f->tete;
                f->tete = f->tete->s;
                free(i);
            }
        }
    }
    return res;
}




// file statique

FileStat creerFileStat(int taille) {
    FileStat f;
    f.tab = malloc(sizeof(PArbre) * taille);
    if (!(f.tab)) {
        printf("ERREUR MALLOC\n");
        exit(4);
    }
    f.taille = taille;
    f.tete = -1;
    f.queue = -1;
    return f;
}

int verificationFileStat(FileStat *f) {
    int res = 0;
    if (!f) res = -1;
    else if (f->tete > f->queue) res = -2;
    return res;
}


int enfilerStat(FileStat *f, PArbre e) {
    int res = verificationFileStat(f);
    if (res > -2) {
        // file pleine
        if ((f->tete % f->taille) + 1 == f->queue % f->taille) res = 1;
        else {
            f->tab[f->queue % f->taille] = e;
            (f->queue)++;
        }
    }
    return res;
}

int defilerStat(FileStat *f, PArbre *e) {
    int res = verificationFileStat(f);;
    if (res > -2) {
        // file vide
        if (f->tete % f->taille == f->queue % f->taille) res = 1;
        else {
            *e = f->tab[f->tete % f->taille];
            (f->tete)++;
        }
    }
    return res;
}

*/
