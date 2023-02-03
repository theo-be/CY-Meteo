
#include <stdio.h>
#include <string.h>

#include "../head/ABR.h"


int recherche(PArbre a, ElementArbre e) {
    if (!a) return 0;
    if (a->e == e) {
        // printf("%d existe\n", e);
        return 1;
    }
    else {
        if (e < a->e) return recherche(a->fg, e);
        else return recherche(a->fd, e);
    }
    return 0;
}



PArbre insertABR(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, float j) {
    if (!a) return creerArbre(e, f, g, h, i, j);
    // if (recherche(a, e)) return a;

    if (e < a->e) a->fg = insertABR(a->fg, e, f, g, h, i, j);
    else if (e > a->e) a->fd = insertABR(a->fd, e, f, g, h, i, j);
    else a->fm = insertABR(a->fm, e, f, g, h, i, j);
    return a;
}



// Tri par altitude
PArbre insertionABRAltitude(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i) {
    if (!a) {
        return creerArbre(e, f, g, h, i, 0.0);
    }
    else if (e < a->e) {
        a->fg = insertionABRAltitude(a->fg, e, f, g, h, i);
    }
    else if (e > a->e) {
        a->fd = insertionABRAltitude(a->fd, e, f, g, h, i);
    }
    else {
        if (f == a->f) return a;
        else a->fm = insertionABRAltitude(a->fm, e, f, g, h, i);
    }   
    return a;
}

// Tri par station
PArbre insertionABRHumidite(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i) {
    if (!a) {
        return creerArbre(e, f, g, h, i, .0);
    }
    else if (f < a->f) {
        a->fg = insertionABRHumidite(a->fg, e, f, g, h, i);
    }
    else if (f > a->f) {
        a->fd = insertionABRHumidite(a->fd, e, f, g, h, i);
    }
    else {
        if (e > a->e) a->e = e;
    }       
    return a;
}

// Tri par station
PArbre insertionABRVent(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j) {
    if (!a) {
        return creerArbre(e, f, g, h, i, j);
    }
    else if (e < a->e) {
        a->fg = insertionABRVent(a->fg, e, f, g, h, i, j);
    }
    else if (e > a->e) {
        a->fd = insertionABRVent(a->fd, e, f, g, h, i, j);
    }
    else {

        // ajout des valeurs
        a->f += f;
        a->g += g;

        // iterations
        a->h++;
        a->j++;


    }        
 
    return a;
}

// Tri par station
PArbre insertionABRP1(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j) {
    if (!a) {
        // printf("creation arbre\n");
        return creerArbre(e, f, g, f, i, f);
    }
    else if (e < a->e) {
        a->fg = insertionABRP1(a->fg, e, f, g, h, i, j);
    }
    else if (e > a->e) {
        a->fd = insertionABRP1(a->fd, e, f, g, h, i, j);
    }
    else {
        a->f += f;
        a->g++;
        if (f < a->h) a->h = f;
        if (f > a->j) a->j = f;
    }        

  
    return a;
}

// Tri par date
PArbre insertionABRP2(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j) {
    if (!a) {
        // printf("creation arbre\n");
        return creerArbre(e, f, g, h, i, j);
    }
    else if (strcmp(i, a->i) < 0) {
        a->fg = insertionABRP2(a->fg, e, f, g, h, i, j);
    }
    else if (strcmp(i, a->i) > 0) {
        a->fd = insertionABRP2(a->fd, e, f, g, h, i, j);
    }
    else if (strcmp(i, a->i) == 0) {
        a->f += f;
        a->g++;
    }        
    else {
        return a;
    }

    return a;
}

// Tri par station
PArbre insertionABRP3(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j) {
    if (!a) {
        return creerArbre(e, f, g, h, i, j);
    }
    else if (strcmp(i, a->i) < 0) {
        a->fg = insertionABRP3(a->fg, e, f, g, h, i, j);
    }
    else if (strcmp(i, a->i) > 0) {
        a->fd = insertionABRP3(a->fd, e, f, g, h, i, j);
    }
    else {
        a->fm = insertionABRP3(a->fm, e, f, g, h, i, j);
    }        
    return a;
}
