#ifndef AVL_H
#define AVL_H


#include "ABR.h"


PArbre RotationGauche(PArbre a);
PArbre RotationDroite(PArbre a);

PArbre DoubleRotationDroit(PArbre a);
PArbre DoubleRotationGauche(PArbre a);

PArbre equilibrerAVL(PArbre a);

PArbre insertionAVL(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, int *_h);



PArbre insertionAVLAltitude(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, int *_h);
PArbre insertionAVLHumidite(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, int *_h);
PArbre insertionAVLVent(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j, int *_h);
PArbre insertionAVLP1(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j, int *_h);
PArbre insertionAVLP2(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j, int *_h);
PArbre insertionAVLP3(PArbre a, ElementArbre e, ElementArbre f, float g, ElementArbre h, char *i, ElementArbre j, int *_h);



#endif