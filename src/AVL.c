#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../head/AVL.h"



PArbre RotationGauche(PArbre a) {
    int eqa = 0, eqp = 0;
    PArbre p = a->fd;
    a->fd = p->fg;
    p->fg = a;
    eqa = a->equilibre;
    eqp = p->equilibre;
    a->equilibre = eqa - Max(eqp, 0) - 1;
    p->equilibre = Min(Min(eqa - 2, eqa + eqp - 2), eqp - 1);
    a = p;
    return a;
}

PArbre RotationDroite(PArbre a) {
    int eqa = 0, eqp = 0;
    PArbre p = a->fg;
    p->fd = a;
    a->fg = p->fd;
    eqa = a->equilibre;
    eqp = p->equilibre;
    a->equilibre = eqa - Min(eqp, 0) + 1;
    p->equilibre = Max(Max(eqa + 2, eqa + eqp + 2), eqp + 1);
    a = p;
    return a;
}


PArbre DoubleRotationGauche(PArbre a) {
    a->fd = RotationDroite(a->fd);
    return RotationGauche(a);
}

PArbre DoubleRotationDroit(PArbre a) {
    a->fg = RotationGauche(a->fg);
    return RotationDroite(a);
}


PArbre equilibrerAVL(PArbre a) {
    if (a->equilibre > 1) {
        if (a->fd->equilibre >= 0) return RotationGauche(a);
        else return DoubleRotationGauche(a);
    }
    else if (a->equilibre < -1) {
        if (a->fg->equilibre <= 0) return RotationDroite(a);
        else return DoubleRotationDroit(a);
    }
    return a;
}


// fonctions necessaires au projet

PArbre insertionAVL(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, int *_h) {
    if (!a) {
        *_h = 1;
        // printf("creation arbre\n");
        return creerArbre(e, f, g, h, i, 0.0);
    }
    else if (e < a->e) {
        a->fg = insertionAVL(a->fg, e, f, g, h, i, _h);
        *_h = -(*_h);
    }
    else if (e > a->e) {
        a->fd = insertionAVL(a->fd, e, f, g, h, i, _h);
    }
    else if (e == a->e) {
        a->fm = insertionAVL(a->fm, e, f, g, h, i, _h);
    }
    else {
        *_h = 0;
        return a;
    }
    if (*_h) {
        a->equilibre += *_h;
        if (!(a->equilibre)) *_h = 0;
        else *_h = 1;
    }
    return a;
}






// Tri par altitude
PArbre insertionAVLAltitude(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, int *_h) {
    if (!a) {
        *_h = 1;
        return creerArbre(e, f, g, h, i, .0);
    }
    else if (e < a->e) {
        a->fg = insertionAVLAltitude(a->fg, e, f, g, h, i, _h);
        *_h = -(*_h);
    }
    else if (e > a->e) {
        a->fd = insertionAVLAltitude(a->fd, e, f, g, h, i, _h);
    }
    else if (e == a->e) {
        // Si doublon de station, on ne la stocke pas
        if (f == a->f) return a;
        else a->fm = insertionAVLAltitude(a->fm, e, f, g, h, i, _h);
    }        
    else {
        *_h = 0;
        return a;
    }
    if (*_h) {
        a->equilibre += *_h;
        if (!(a->equilibre)) *_h = 0;
        else *_h = 1;
    }
    return a;
}

// Tri par station
PArbre insertionAVLHumidite(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, int *_h) {
    if (!a) {
        *_h = 1;
        return creerArbre(e, f, g, h, i, .0);
    }
    else if (f < a->f) {
        a->fg = insertionAVLHumidite(a->fg, e, f, g, h, i, _h);
        *_h = -(*_h);
    }
    else if (f > a->f) {
        a->fd = insertionAVLHumidite(a->fd, e, f, g, h, i, _h);
    }
    else if (f == a->f) {
        // Si l'humidite est plus grande que le max, c'est le nouveau max
        if (e > a->e) a->e = e;
    }        
    else {
        *_h = 0;
        return a;
    }
    if (*_h) {
        a->equilibre += *_h;
        if (!(a->equilibre)) *_h = 0;
        else *_h = 1;
    }
    return a;
}

// Tri par station
PArbre insertionAVLVent(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j, int *_h) {
    if (!a) {
        *_h = 1;
        return creerArbre(e, f, g, h, i, j);
    }
    else if (e < a->e) {
        a->fg = insertionAVLVent(a->fg, e, f, g, h, i, j, _h);
        *_h = -(*_h);
    }
    else if (e > a->e) {
        a->fd = insertionAVLVent(a->fd, e, f, g, h, i, j, _h);
    }
    else if (e == a->e) {
        // Ajout des valeurs
        a->f += f;
        a->g += g;

        // Iterations
        a->h++;
        a->j++;
    }        
    else {
        *_h = 0;
        return a;
    }
    if (*_h) {
        a->equilibre += *_h;
        if (!(a->equilibre)) *_h = 0;
        else *_h = 1;
    }
    return a;
}

// Tri par station
PArbre insertionAVLP1(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j, int *_h) {
    if (!a) {
        *_h = 1;
        return creerArbre(e, f, g, f, i, f);
    }
    else if (e < a->e) {
        a->fg = insertionAVLP1(a->fg, e, f, g, h, i, j, _h);
        *_h = -(*_h);
    }
    else if (e > a->e) {
        a->fd = insertionAVLP1(a->fd, e, f, g, h, i, j, _h);
    }
    else if (e == a->e) {
        // Moyenne
        a->f += f;
        a->g++;
        // Min et max
        if (f < a->h) a->h = f;
        if (f > a->j) a->j = f;
    }        
    else {
        *_h = 0;
        return a;
    }
    if (*_h) {
        a->equilibre += *_h;
        if (!(a->equilibre)) *_h = 0;
        else *_h = 1;
    }
    return a;
}

// Tri par date
PArbre insertionAVLP2(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j, int *_h) {
    if (!a) {
        *_h = 1;
        return creerArbre(e, f, g, h, i, j);
    }
    else if (strcmp(i, a->i) < 0) {
        a->fg = insertionAVLP2(a->fg, e, f, g, h, i, j, _h);
        *_h = -(*_h);
    }
    else if (strcmp(i, a->i) > 0) {
        a->fd = insertionAVLP2(a->fd, e, f, g, h, i, j, _h);
    }
    else if (strcmp(i, a->i) == 0) {
        // Moyenne
        a->f += f;
        a->g++;
    }        
    else {
        *_h = 0;
        return a;
    }
    if (*_h) {
        a->equilibre += *_h;
        if (!(a->equilibre)) *_h = 0;
        else *_h = 1;
    }
    return a;
}

// Tri par station
PArbre insertionAVLP3(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j, int *_h) {
    if (!a) {
        *_h = 1;
        return creerArbre(e, f, g, h, i, j);
    }
    else if (strcmp(i, a->i) < 0) {
        a->fg = insertionAVLP3(a->fg, e, f, g, h, i, j, _h);
        *_h = -(*_h);
    }
    else if (strcmp(i, a->i) > 0) {
        a->fd = insertionAVLP3(a->fd, e, f, g, h, i, j, _h);
    }
    else if (strcmp(i, a->i) == 0) {
        a->fm = insertionAVLP3(a->fm, e, f, g, h, i, j, _h);
    }        
    else {
        *_h = 0;
        return a;
    }
    if (*_h) {
        a->equilibre += *_h;
        if (!(a->equilibre)) *_h = 0;
        else *_h = 1;
    }
    return a;
}

