#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "../head/tri.h"
#include "../head/AVL.h"




// 12/01 debut du c


int main(int argc, char *argv[]) {
    // printf("executable C CY-Meteo\n");

    int option;

    int opt_entree = 0;
    int opt_sortie = 0;
    int opt_r = 0;
    int opt_d = 0;

    char *fichier_entree = malloc(sizeof(char) * 128);
    int mode_tri = -1;
    if (!fichier_entree) {
        printf("Erreur malloc\n");
        exit(4);
    }
    char *fichier_sortie = malloc(sizeof(char) * 128);
    if (!fichier_sortie) {
        printf("Erreur malloc\n");
        exit(4);
    }
    char *option_d = malloc(sizeof(char) * 3);
    if (!option_d) {
        printf("Erreur malloc\n");
        exit(4);
    }
    
    
    while ((option = getopt(argc, argv, ":f:o:rk:t:")) != -1) {
        switch (option)  {
            case 'f':
                opt_entree = 1;
                sprintf(fichier_entree, "%s", optarg);
                // printf("fichier\n");
                
                break;
            case 'o':
                opt_sortie = 1;
                sprintf(fichier_sortie, "%s", optarg);
                // printf("fichier\n");
                
                break;
            case 'r':
                opt_r = 1;
                break;
            case 'k':
                // option de donnee
                sprintf(option_d, "%s", optarg);
                opt_d = 1;
                // printf("clef\n");
                break;
            case 't':
                // option de mode de tri
                if (!strcmp("avl", optarg)) mode_tri = 0;
                else if (!strcmp("abr", optarg)) mode_tri = 1;
                else if (!strcmp("tab", optarg)) mode_tri = 2;
                else {
                    printf("Erreur %s : argument inconnu\n");
                    exit(1);
                }
                // printf("option de mode de tri\n");
            case '?':
                // printf("Erreur : option -%c requiert un argument\n", option);
                /*
                switch (optopt) {
                    case 'c':
                        printf("Erreur : option -%c requiert un argument\n", optopt);
                        break;
                    
                }



                if (optopt == 'c') {
                    printf("Erreur : option -%c requiert un argument\n", optopt);
                }*/
                break;
            default:
                // option inconnue
                printf("option inconnue %c\n", optopt);
                exit(1);
                break;
        }
    }

    // Verification de la presence des options obligatoires

    if (!opt_entree) {
        printf("Erreur : veuillez préciser le fichier d\'entrée\n");
        exit(1);
    }
    if (!opt_sortie) {
        printf("Erreur : veuillez préciser le fichier de sortie\n");
        exit(1);
    }
    if (!opt_d) {
        printf("Erreur : veuillez préciser le type de tri\n");
        exit(1);
    }




    // for (int index = optind; index < argc; index++) {
    //    printf("argument restant : %s\n", argv[index]);
    // }

    if (!strcmp(option_d, "h")) {
        // altitude
        lectureFichierAltitude(fichier_entree, fichier_sortie, mode_tri);
    }
    else if (!strcmp(option_d, "w")) {
        // vent
        lectureFichierVent(fichier_entree, fichier_sortie, mode_tri);
    }
    else if (!strcmp(option_d, "m")) {
        // hum
        lectureFichierHumidite(fichier_entree, fichier_sortie, mode_tri);
    }
    else if (!strcmp(option_d, "p1")) {
        // p1
        lectureFichierP1(fichier_entree, fichier_sortie, mode_tri);
    }
    else if (!strcmp(option_d, "p2")) {
        // p2
        lectureFichierP2(fichier_entree, fichier_sortie, mode_tri);
    }
    else if (!strcmp(option_d, "p3")) {
        // p3
        lectureFichierP3(fichier_entree, fichier_sortie, mode_tri);
    }
    else if (!strcmp(option_d, "t1")) {
        // t1
        lectureFichierT1(fichier_entree, fichier_sortie, mode_tri);
    }
    else if (!strcmp(option_d, "t2")) {
        // t2
        lectureFichierT2(fichier_entree, fichier_sortie, mode_tri);
    }
    else if (!strcmp(option_d, "t3")) {
        // t3
        lectureFichierT3(fichier_entree, fichier_sortie, mode_tri);
    }
    else {
        printf("%s : argument inconnu\n");
        exit(1);
    }

    return 0;
}



void lectureFichierAltitude(char *nom_fichier, char *nom_fichier_sortie, int mode) {
    // printf("tri altitude\n");
    FILE *fichier = NULL;
    fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Erreur ouverture fichier %s\n", nom_fichier);
        exit(2);
    }
    // printf("fichier %s ouvert\n", nom_fichier);

    char *buffer = NULL;
    char *ligne = malloc(sizeof(char) * 1024);
    if (!ligne) {
        printf("ERREUR MALLOC\n");
        exit(4);
    }

    long valeur1 = 0;
    long valeur2 = 0;
    char *coordonees = NULL;

    long i = 0;
    int h = 0;

    PArbre arbre = NULL;
    Chainon *liste = NULL;
    while (!feof(fichier)) {
        // i++;

        // printf("Ligne %ld :\r", i);
        fgets(ligne, 1023, fichier);

        // valeur 1 : num station
        buffer = strtok(ligne, ";");
        if (!buffer) continue;
        valeur1 = strtol(buffer, NULL, 10);

        // valeur 2 : coordonees
        buffer = strtok(NULL, ";");
        if (!buffer) continue;
        coordonees = buffer;

        // valeur 3 : altitude
        buffer = strtok(NULL, ";");
        if (!buffer) continue;
        valeur2 = strtol(buffer, NULL, 10);

        if (mode == 0) {
            arbre = insertionAVLAltitude(arbre, valeur2, valeur1, 0, 0, coordonees, &h);
        }
        else if (mode == 1) {
            arbre = insertionABRAltitude(arbre, valeur2, valeur1, 0, 0, coordonees);
        }
        else{
            liste = insertionListeAltitude(liste, valeur2, valeur1, 0, 0, coordonees);
        }
    }

    fclose(fichier);

    // printf("\nlecture terminee, %ld lignes\n", i);

    ecritureFichierAltitude(nom_fichier_sortie, arbre, liste);
}

void lectureFichierHumidite(char *nom_fichier, char *nom_fichier_sortie, int mode) {
    // printf("tri humidite\n");
    FILE *fichier = NULL;
    fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Erreur ouverture fichier %s\n", nom_fichier);
        exit(2);
    }
    // printf("fichier %s ouvert\n", nom_fichier);

    char *buffer = NULL;
    char *ligne = malloc(sizeof(char) * 1024);
    if (!ligne) {
        printf("ERREUR MALLOC\n");
        exit(4);
    }

    long valeur1 = 0;
    long valeur2 = 0;
    char *coordonees = NULL;

    int h = 0;
    long i = 0;

    PArbre arbre = NULL;
    Chainon *liste = NULL;

    while (!feof(fichier)) {
        // i++;

        // printf("Ligne %ld :\r", i);
        fgets(ligne, 1023, fichier);

        // valeur 1 : num station
        buffer = strtok(ligne, ";");
        if (!buffer) continue;
        valeur1 = strtol(buffer, NULL, 10);
        // valeur 2 : humidite
        buffer = strtok(NULL, ";");
        if (!buffer) continue;
        valeur2 = strtol(buffer, NULL, 10);    
        // valeur 3 : coordonees
        buffer = strtok(NULL, ";");
        if (!buffer) continue;
        coordonees = buffer;
        coordonees[strlen(coordonees) - 1] = '\0';
        
        // valeur clef : humidite
        if (mode == 0){
            arbre = insertionAVLHumidite(arbre, valeur2, valeur1, 0, 0, coordonees, &h);
        }
        else if (mode == 1){
            arbre = insertionABRHumidite(arbre, valeur2, valeur1, 0, 0, coordonees);
        }
        else{
            //chainon
            liste = insertionListeHumidite(liste, valeur2, valeur1, 0, 0, coordonees);
        }


    }

    fclose(fichier);

    // printf("\nlecture terminee, %ld lignes\n", i);


    PArbre arbre_trie = NULL;
    Chainon *liste_triee = NULL;
    arbre_trie = parcoursHumidite(arbre, arbre_trie);
    liste_triee = parcoursListeHumidite(liste_triee);

    supprimerFilsGauche(arbre);
    supprimerFilsDroit(arbre);
    free(arbre);

    liste = nettoyerListe(liste);

    ecritureFichierHumidite(nom_fichier_sortie, arbre_trie, liste_triee);


}

PArbre parcoursHumidite(PArbre a, PArbre b) {
    if (!a) return b;
    b = parcoursHumidite(a->fg, b);
    // printf("insertion");
    int h = 0;
    b = insertionAVL(b, a->e, a->f, a->g, a->h, a->i, &h);
    // printf("insere");
    b = parcoursHumidite(a->fm, b);
    b = parcoursHumidite(a->fd, b);

    // printf("fin\n");
    
    return b;
}

PArbre parcoursHumiditeABR(PArbre a, PArbre b) {
    if (!a) return b;
    b = parcoursHumiditeABR(a->fg, b);
    // printf("insertion");
    int h = 0;
    b = insertABR(b, a->e, a->f, a->g, a->h, a->i, a->j);
    // printf("insere");
    b = parcoursHumiditeABR(a->fm, b);
    b = parcoursHumiditeABR(a->fd, b);

    // printf("fin\n");
    
    return b;
}

Chainon *parcoursListeHumidite(Chainon *a) {
    if (!a) return NULL;
    Chainon *b = NULL;
    Chainon *i = a;
    while (!i) {
        b = insertionCroissant(b, a->e, a->f, a->g, a->h, a->i);
    }
    return b;
}



void lectureFichierVent(char *nom_fichier, char *nom_fichier_sortie, int mode) {
    // printf("tri vent\n");

    FILE *fichier = NULL;
    fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Erreur ouverture fichier %s\n", nom_fichier);
        exit(2);
    }
    // printf("fichier %s ouvert\n", nom_fichier);

    char *buffer = NULL;
    char *ligne = malloc(sizeof(char) * 1024);
    if (!ligne) {
        printf("ERREUR MALLOC\n");
        exit(4);
    }

    long valeur1 = 0;
    long valeur2 = 0;
    float valeur3 = .0;
    char *coordonees = NULL;

    float vx = .0, vy = .0;
    long dirX = 0, dirY = 0;


    long i = 0;
    int h = 0;


    PArbre arbre = NULL;
    Chainon *liste = NULL;

    while (!feof(fichier)) {
        // i++;

        // printf("Ligne %ld :\r", i);
        fgets(ligne, 1023, fichier);

        // valeur 1 : num station
        buffer = strtok(ligne, ";");
        if (!buffer) continue;
        valeur1 = strtol(buffer, NULL, 10);

        // valeur 2 : vitesse vent
        buffer = strtok(NULL, ";");
        if (!buffer) continue;
        valeur2 = strtol(buffer, NULL, 10);

        // valeur 3 : direction vent
        buffer = strtok(NULL, ";");
        if (!buffer) continue;
        valeur3 = strtof(buffer, NULL);

        // valeur 4 : coordonees
        buffer = strtok(NULL, ";");
        if (!buffer) continue;
        coordonees = buffer;
        coordonees[strlen(coordonees) - 1] = '\0';

        if (mode == 0){
            arbre = insertionAVLVent(arbre, valeur1, valeur2, valeur3, 0, coordonees, 0, &h);
        }
        else if (mode == 1){
            arbre = insertionABRVent(arbre, valeur1, valeur2, valeur3, 0, coordonees, 0);
        }
        else{
            //chainon
            liste = insertionListeVent(liste, valeur1, valeur2, valeur3, 0, coordonees, 0);
        }

    }

    fclose(fichier);
    
    // printf("\nlecture terminee, %ld lignes\n", i);
    parcoursMoyenneVent(arbre);

    ecritureFichierVent(nom_fichier_sortie, arbre, liste);
}

void parcoursMoyenneVent(PArbre a) {
    if (!a) return;
    ElementArbre moy_dir = a->f / a->h;
    float moy_dent = a->g / (float)a->j;
    a->f = moy_dir;
    a->g = moy_dent;
    parcoursMoyenneVent(a->fg);
    parcoursMoyenneVent(a->fd);
}

void parcoursListeMoyenneVent(Chainon *l) {
    while (l) {
        ElementArbre moy_dir = l->f / l->h;
        float moy_vent = l->g / (float)l->j;
        l->f = moy_dir;
        l->g = moy_vent;
        l = l->s;
    }
    
}


void lectureFichierP1(char *nom_fichier, char *nom_fichier_sortie, int mode) {
    // printf("tri p1\n");

    FILE *fichier = NULL;
    fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Erreur ouverture fichier %s\n", nom_fichier);
        exit(2);
    }
    // printf("fichier %s ouvert\n", nom_fichier);

    char *buffer = NULL;
    char *ligne = malloc(sizeof(char) * 1024);
    if (!ligne) {
        printf("ERREUR MALLOC\n");
        exit(4);
    }

    long valeur1 = 0;
    long valeur2 = 0;

    int h = 0;
    long i = 0;

    PArbre arbre = NULL;
    Chainon *liste = NULL;

    while (!feof(fichier)) {
        // i++;

        // printf("Ligne %ld\r", i);
        fgets(ligne, 1023, fichier);

        // valeur 1 : num station
        buffer = strtok(ligne, ";");
        if (!buffer) continue;
        valeur1 = strtol(buffer, NULL, 10);

        // valeur 2 : pression
        buffer = strtok(NULL, ";");
        if (!buffer) continue;
        if (buffer[0] == '\n') continue;
        valeur2 = strtol(buffer, NULL, 10);
        
        // valeur clef : num stat

        if (mode == 0){
            arbre = insertionAVLP1(arbre, valeur1, valeur2, 1, 0, NULL, 0, &h);
        }
        else if (mode == 1){
            arbre = insertionABRP1(arbre, valeur1, valeur2, 1, 0, NULL, 0);
        }
        else{
            //chainon
            liste = insertionListeP1(liste, valeur1, valeur2, 1, 0, NULL, 0);
        }

        // valeur1 = -1;
        // valeur2 = -1;
    }

    parcoursMoyenneP1(arbre);
    parcoursMoyenneListeP1(liste);

    fclose(fichier);

    // printf("\nlecture terminee, %ld lignes\n", i);

    ecritureFichierP1(nom_fichier_sortie, arbre, liste);

}


void lectureFichierT1(char *nom_fichier, char *nom_fichier_sortie, int mode) {
    // printf("tri t1\n");
    FILE *fichier = NULL;
    fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Erreur ouverture fichier %s\n", nom_fichier);
        exit(2);
    }
    // printf("fichier %s ouvert\n", nom_fichier);

    char *buffer = NULL;
    char *ligne = malloc(sizeof(char) * 1024);
    if (!ligne) {
        printf("ERREUR MALLOC\n");
        exit(4);
    }

    long valeur1 = 0;
    long valeur2 = 0;

    int h = 0;
    long i = 0;

    PArbre arbre = NULL;
    Chainon *liste = NULL;

    while (!feof(fichier)) {
        // i++;

        // printf("Ligne %ld\r", i);
        fgets(ligne, 1023, fichier);

        // valeur 1 : num station
        buffer = strtok(ligne, ";");
        if (!buffer) continue;
        valeur1 = strtol(buffer, NULL, 10);

        // valeur 2 : pression
        buffer = strtok(NULL, ";");
        if (!buffer) continue;
        if (buffer[0] == '\n') continue;
        valeur2 = strtol(buffer, NULL, 10);
        
        // valeur clef : num stat

        if (mode == 0){
            arbre = insertionAVLP1(arbre, valeur1, valeur2, 1, 0, NULL, 0, &h); //on appelle insertionAVLP1 car c'est le même que T1
        }
        else if (mode == 1){
            arbre = insertionABRP1(arbre, valeur1, valeur2, 1, 0, NULL, 0);
        }
        else{
            //chainon
            liste = insertionListeP1(liste, valeur1, valeur2, 1, 0, NULL, 0);
        }

        // valeur1 = -1;
        // valeur2 = -1;
    }

    fclose(fichier);

    parcoursMoyenneP1(arbre);
    parcoursMoyenneListeP1(liste);


    // printf("\nlecture terminee, %ld lignes\n", i);

    ecritureFichierT1(nom_fichier_sortie, arbre, liste);

}


void parcoursMoyenneP1(PArbre a) {
    if (!a) return;
    ElementArbre moy = a->f / a->g;
    a->f = moy;
    parcoursMoyenneP1(a->fg);
    parcoursMoyenneP1(a->fd);
}

void parcoursMoyenneListeP1(Chainon *liste) {
    while (liste) {
        ElementArbre moy = liste->f / liste->g;
        liste->f = moy;
        liste = liste->s;
    }
    
}


void lectureFichierP2(char *nom_fichier, char *nom_fichier_sortie, int mode) {
    // printf("tri p2\n");
    FILE *fichier = NULL;
    fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Erreur ouverture fichier %s\n", nom_fichier);
        exit(2);
    }
    // printf("fichier %s ouvert\n", nom_fichier);

    char *buffer = NULL;
    char *ligne = malloc(sizeof(char) * 1024);
    if (!ligne) {
        printf("ERREUR MALLOC\n");
        exit(4);
    }

    long valeur1 = 0;
    long valeur2 = 0;
    char *coordonees = NULL;

    int h = 0;
    long i = 0;

    PArbre arbre = NULL;
    Chainon *liste = NULL;

    while (!feof(fichier)) {
        // i++;
        // h = 0;

        // printf("Ligne %ld\r", i);
        fgets(ligne, 1023, fichier);

        // valeur 1 : date
        buffer = strtok(ligne, ";");
        if (!buffer) continue;
        coordonees = buffer;

        // valeur 2 : pression
        buffer = strtok(NULL, ";");
        if (!buffer) continue;
        if (buffer[0] == '\n') continue;
        valeur2 = strtol(buffer, NULL, 10);
        
        // valeur clef : date

        if (mode == 0){
            arbre = insertionAVLP2(arbre, 0, valeur2, 1, 0, coordonees, 0, &h);
        }
        else if (mode == 1){
            arbre = insertionABRP2(arbre, 0, valeur2, 1, 0, coordonees, 0);
        }
        else{
            //chainon
            liste = insertionListeP2(liste, 0, valeur2, 1, 0, coordonees, 0);
        }

    }

    // printf("parcours arbre\n");
    parcoursMoyenneP1(arbre);

    // printf("parcours liste\n");
    parcoursMoyenneListeP1(liste);

    fclose(fichier);

    // printf("\nlecture terminee, %ld lignes\n", i);

    ecritureFichierP2(nom_fichier_sortie, arbre, liste);

}


void lectureFichierT2(char *nom_fichier, char *nom_fichier_sortie, int mode) {
    // printf("tri t2\n");
    FILE *fichier = NULL;
    fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Erreur ouverture fichier %s\n", nom_fichier);
        exit(2);
    }
    // printf("fichier %s ouvert\n", nom_fichier);

    char *buffer = NULL;
    char *ligne = malloc(sizeof(char) * 1024);
    if (!ligne) {
        printf("ERREUR MALLOC\n");
        exit(4);
    }

    long valeur1 = 0;
    long valeur2 = 0;
    char *coordonees = NULL;

    int h = 0;
    long i = 0;

    PArbre arbre = NULL;
    Chainon *liste = NULL;

    while (!feof(fichier)) {
        // i++;

        // printf("Ligne %ld\r", i);
        fgets(ligne, 1023, fichier);

        // valeur 1 : date
        buffer = strtok(ligne, ";");
        if (!buffer) continue;
        coordonees = buffer;

        // valeur 2 : temperature
        buffer = strtok(NULL, ";");
        if (!buffer) continue;
        if (buffer[0] == '\n') continue;
        valeur2 = strtol(buffer, NULL, 10);
        
        // valeur clef : date


        if (mode == 0){
            arbre = insertionAVLP2(arbre, 0, valeur2, 1, 0, coordonees, 0, &h); //La même pour T2 et P2
        }
        else if (mode == 1){
            arbre = insertionABRP2(arbre, 0, valeur2, 1, 0, coordonees, 0); //La même pour T2 et P2
        }
        else{
            //chainon
            liste = insertionListeP2(liste, 0, valeur2, 1, 0, coordonees, 0);
        }

        // valeur1 = -1;
        // valeur2 = -1;
    }

    parcoursMoyenneP1(arbre);
    parcoursMoyenneListeP1(liste);

    fclose(fichier);

    // printf("\nlecture terminee, %ld lignes\n", i);

    ecritureFichierT2(nom_fichier_sortie, arbre, liste);

}



void lectureFichierP3(char *nom_fichier, char *nom_fichier_sortie, int mode) {
    // printf("tri p3\n");
    FILE *fichier = NULL;
    fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Erreur ouverture fichier %s\n", nom_fichier);
        exit(2);
    }
    // printf("fichier %s ouvert\n", nom_fichier);

    char *buffer = NULL;
    char *ligne = malloc(sizeof(char) * 1024);
    if (!ligne) {
        printf("ERREUR MALLOC\n");
        exit(4);
    }

    long valeur1 = 0;
    long valeur2 = 0;
    char *date = NULL;

    int h = 0;
    long i = 0;

    PArbre arbre = NULL;
    Chainon *liste = NULL;

    while (!feof(fichier)) {
        // i++;

        // printf("Ligne %ld\r", i);
        fgets(ligne, 1023, fichier);

        // valeur 1 : num stat
        buffer = strtok(ligne, ";");
        if (!buffer) continue;
        valeur1 = strtol(buffer, NULL, 10);

        // valeur 2 : date
        buffer = strtok(NULL, ";");
        if (!buffer) continue;
        date = buffer;

        // valeur 3 : pression
        buffer = strtok(NULL, ";");
        if (!buffer) continue;
        if (buffer[0] == '\n') continue;
        valeur2 = strtol(buffer, NULL, 10);

        // AVL par date
        if (mode == 0){
            arbre = insertionAVLP3(arbre, valeur1, valeur2, 0, 0, date, 0, &h);
        }
        else if (mode == 1){
            arbre = insertionABRP3(arbre, valeur1, valeur2, 0, 0, date, 0);
        }
        else{
            //chainon
            liste = insertionListeP3(liste, valeur1, valeur2, 0, 0, date, 0);
        }

        

        /*
        double avl : un par date, un par station
        parcours du premier par date -> insertion dans le 2e par date
        num station dans e
        mettre la pression dans f
        date dans i
        */

        // valeur1 = -1;
        // valeur2 = -1;
    }

    fclose(fichier);

    // printf("\nlecture terminee, %ld lignes\n", i);

    PArbre arbre_trie = NULL;
    Chainon *liste_triee = NULL;

    // creation de l'AVL par station avec les dates triees

    if (mode == 0)
        arbre_trie = parcoursHumidite(arbre, arbre_trie);
    else if (mode == 1)
        arbre_trie = parcoursHumiditeABR(arbre, arbre_trie);
    else
        liste_triee = parcoursListeHumidite(liste);

    // printf("fin du tri par station\n");

    supprimerFilsGauche(arbre);
    supprimerFilsDroit(arbre);
    free(arbre);
    liste = nettoyerListe(liste);

    ecritureFichierP3(nom_fichier_sortie, arbre_trie, liste_triee);
    
    
}


void lectureFichierT3(char *nom_fichier, char *nom_fichier_sortie, int mode) {
    // printf("tri t3\n");
    // char *nom_fichier = "test/filtre_t3.csv";
    FILE *fichier = NULL;
    fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Erreur ouverture fichier %s\n", nom_fichier);
        exit(2);
    }
    // printf("fichier %s ouvert\n", nom_fichier);

    char *buffer = NULL;
    char *ligne = malloc(sizeof(char) * 1024);
    if (!ligne) {
        printf("ERREUR MALLOC\n");
        exit(4);
    }

    long valeur1 = 0;
    long valeur2 = 0;
    char *date = NULL;

    int h = 0;
    long i = 0;

    PArbre arbre = NULL;
    Chainon *liste = NULL;

    while (!feof(fichier)) {
        // i++;

        // num stat, date, pression

        // printf("Ligne %ld\r", i);
        fgets(ligne, 1023, fichier);

        // valeur 1 : num stat
        buffer = strtok(ligne, ";");
        if (!buffer) continue;
        valeur1 = strtol(buffer, NULL, 10);
        // printf("v1 : %ld ", valeur1);

        // valeur 2 : date
        buffer = strtok(NULL, ";");
        if (!buffer) continue;
        date = buffer;
        // coordonees[strlen(coordonees) - 1] = '\0';

        // printf("v2 : %s ", date);


        // valeur 3 : pression
        buffer = strtok(NULL, ";");
        if (!buffer) continue;
        if (buffer[0] == '\n') continue;
        valeur2 = strtol(buffer, NULL, 10);

        // printf("v3 : %ld\n", valeur2);
        
        // valeur clef : date
        // valeur clef 2 : num stat


        // AVL par date
        if (mode == 0){
            arbre = insertionAVLP3(arbre, valeur1, valeur2, 0, 0, date, 0, &h);; //La même chose pour T3 et P3
        }
        else if (mode == 1){
            arbre = insertionABRP3(arbre, valeur1, valeur2, 0, 0, date, 0);; //La même chose pour T3 et P3
        }
        else{
            //chainon
            liste = insertionListeP3(liste, valeur1, valeur2, 0, 0, date, 0);
        }

        

        /*
        double avl : un par date, un par station
        parcours du premier par date -> insertion dans le 2e par date
        num station dans e
        mettre la pression dans f
        date dans i
        */

        valeur1 = -1;
        valeur2 = -1;
    }

    fclose(fichier);

    // printf("\nlecture terminee, %ld lignes\n", i);

    
    PArbre arbre_trie = NULL;

    // printf("tri par station\n");

    // creation de l'AVL par station avec les dates triees

    arbre_trie = parcoursHumidite(arbre, arbre_trie);
    Chainon *liste_triee = parcoursListeHumidite(liste);

    // printf("fin du tri par station\n");

    supprimerFilsGauche(arbre);
    supprimerFilsDroit(arbre);
    free(arbre);
    liste = nettoyerListe(liste);

    ecritureFichierT3(nom_fichier_sortie, arbre_trie, liste_triee);
    
}





void parcoursInfixeEcritureCroissant(PArbre a, FILE *f) {
    if (!a) return;
    parcoursInfixeEcritureCroissant(a->fg, f);
    fprintf(f, "%ld,%f,%s\n", a->f, a->g, a->i);
    // parcoursInfixeEcritureCroissant(a->fm, f);
    parcoursInfixeEcritureCroissant(a->fd, f);
}

void parcoursInfixeEcritureCroissantP1(PArbre a, FILE *f) {
    if (!a) return;
    parcoursInfixeEcritureCroissantP1(a->fg, f);
    fprintf(f, "%ld,%ld,%ld,%ld\n", a->e, a->f, a->h, a->j);
    parcoursInfixeEcritureCroissantP1(a->fd, f);
}

void parcoursInfixeEcritureCroissantP2(PArbre a, FILE *f) {
    if (!a) return;
    parcoursInfixeEcritureCroissantP2(a->fg, f);
    fprintf(f, "%s,%ld\n", a->i, a->f);
    parcoursInfixeEcritureCroissantP2(a->fm, f);
    parcoursInfixeEcritureCroissantP2(a->fd, f);
}

void parcoursInfixeEcritureDecroissant(PArbre a, FILE *f) {
    if (!a) return;
    parcoursInfixeEcritureDecroissant(a->fd, f);
    // fprintf(f, "%d;%d\n", a->e);
    fprintf(f, "%ld,%ld,%s\n", a->e, a->f, a->i);
    parcoursInfixeEcritureDecroissant(a->fm, f);
    parcoursInfixeEcritureDecroissant(a->fg, f);
}

void parcoursInfixeEcritureDecroissantAltitude(PArbre a, FILE *f) {
    if (!a) return;
    parcoursInfixeEcritureDecroissantAltitude(a->fd, f);
    fprintf(f, "%ld,%s\n", a->e, a->i);
    parcoursInfixeEcritureDecroissantAltitude(a->fm, f);
    parcoursInfixeEcritureDecroissantAltitude(a->fg, f);
}

void parcoursInfixeEcritureCroissantP3(PArbre a, FILE *f) {
    if (!a) return;
    parcoursInfixeEcritureCroissantP3(a->fg, f);
    fprintf(f, "%ld,%s,%ld\n", a->e, a->i, a->f);
    parcoursInfixeEcritureCroissantP3(a->fm, f);
    parcoursInfixeEcritureCroissantP3(a->fd, f);
}


void parcoursListeEcritureCroissant(Chainon *l, FILE *f) {
    while (l) {
        fprintf(f, "%ld,%f,%s\n", l->f, l->g, l->i);
        l = l->s;
    }
}

void parcoursListeEcritureCroissantP1(Chainon *l, FILE *f) {
    while (l) {
        fprintf(f, "%ld,%ld,%ld,%ld\n", l->e, l->f, l->h, l->j);
        l = l->s;
    }
}

void parcoursListeEcritureCroissantP2(Chainon *l, FILE *f) {
    while (l) {
        fprintf(f, "%s,%ld\n", l->i, l->f);
        l = l->s;
    }
}

void parcoursListeEcritureDecroissant(Chainon *l, FILE *f) {
    while (l) {
        fprintf(f, "%ld,%ld,%s\n", l->e, l->f, l->i);
        l = l->s;
    }
}

void parcoursListeEcritureDecroissantAltitude(Chainon *l, FILE *f) {
    while (l) {
        fprintf(f, "%ld,%s\n", l->e, l->i);
        l = l->s;
    }
}

void parcoursListeEcritureCroissantP3(Chainon *l, FILE *f) {
    while (l) {
        fprintf(f, "%ld,%s,%ld\n", l->e, l->i, l->f);
        l = l->s;
    }
}



void ecritureFichierAltitude(char *nom_fichier, PArbre a, Chainon *liste) {
    // char *nom_fichier = "test/tri_altitude.csv";
    FILE *sortie = fopen(nom_fichier, "w+");
    if (!sortie) {
        printf("Erreur ouverture de %s\n", nom_fichier);
        exit(3);
    }

    // printf("debut de l\'ecriture %s\n", nom_fichier);

    if (a)
        parcoursInfixeEcritureDecroissantAltitude(a, sortie);
    else 
        parcoursListeEcritureDecroissantAltitude(liste, sortie);



    // printf("fin de l\'ecriture %s\n", nom_fichier);
    fclose(sortie);
    free(a);
    free(liste);
}

void ecritureFichierHumidite(char *nom_fichier, PArbre a, Chainon *liste) {
    // char *nom_fichier = "test/tri_humidite.csv";
    FILE *sortie = fopen(nom_fichier, "w+");
    if (!sortie) {
        printf("Erreur ouverture de %s\n", nom_fichier);
        exit(3);
    }

    // printf("debut de l\'ecriture %s\n", nom_fichier);

    if (a)
        parcoursInfixeEcritureDecroissant(a, sortie);
    else
        parcoursListeEcritureDecroissant(liste, sortie);

    // printf("fin de l\'ecriture %s\n", nom_fichier);
    fclose(sortie);
    free(a);
    free(liste);
}

void ecritureFichierVent(char *nom_fichier, PArbre a, Chainon *liste) {
    // char *nom_fichier = "test/tri_vent.csv";
    FILE *sortie = fopen(nom_fichier, "w+");
    if (!sortie) {
        printf("Erreur ouverture de %s\n", nom_fichier);
        exit(3);
    }

    // printf("debut de l\'ecriture %s\n", nom_fichier);

    if (a)
        parcoursInfixeEcritureCroissant(a, sortie);
    else
        parcoursListeEcritureCroissant(liste, sortie);

    // printf("fin de l\'ecriture %s\n", nom_fichier);
    fclose(sortie);
    free(a);
    free(liste);
}

void ecritureFichierP1(char *nom_fichier, PArbre a, Chainon *liste) {
    // char *nom_fichier = "test/tri_p1.csv";
    FILE *sortie = fopen(nom_fichier, "w+");
    if (!sortie) {
        printf("Erreur ouverture de %s\n", nom_fichier);
        exit(3);
    }

    // printf("debut de l\'ecriture %s\n", nom_fichier);

    if (a)
        parcoursInfixeEcritureCroissantP1(a, sortie);
    else
        parcoursListeEcritureCroissantP1(liste, sortie);

    // printf("fin de l\'ecriture %s\n", nom_fichier);
    fclose(sortie);
    free(a);
    free(liste);
}


void ecritureFichierP2(char *nom_fichier, PArbre a, Chainon *liste) {
    // char *nom_fichier = "test/tri_p2.csv";
    FILE *sortie = fopen(nom_fichier, "w+");
    if (!sortie) {
        printf("Erreur ouverture de %s\n", nom_fichier);
        exit(3);
    }

    // printf("debut de l\'ecriture %s\n", nom_fichier);

    if (a)
        parcoursInfixeEcritureCroissantP2(a, sortie);
    else
        parcoursListeEcritureCroissantP2(liste, sortie);

    // printf("fin de l\'ecriture %s\n", nom_fichier);
    fclose(sortie);
    free(a);
    free(liste);
}

void ecritureFichierT1(char *nom_fichier, PArbre a, Chainon *liste) {
    // char *nom_fichier = "test/tri_t1.csv";
    FILE *sortie = fopen(nom_fichier, "w+");
    if (!sortie) {
        printf("Erreur ouverture de %s\n", nom_fichier);
        exit(3);
    }

    // printf("debut de l\'ecriture %s\n", nom_fichier);

    if (a)
        parcoursInfixeEcritureCroissantP1(a, sortie);
    else
        parcoursListeEcritureCroissantP1(liste, sortie);

    // printf("fin de l\'ecriture %s\n", nom_fichier);
    fclose(sortie);
    free(a);
    free(liste);
}

void ecritureFichierT2(char *nom_fichier, PArbre a, Chainon *liste) {
    // char *nom_fichier = "test/tri_t2.csv";
    FILE *sortie = fopen(nom_fichier, "w+");
    if (!sortie) {
        printf("Erreur ouverture de %s\n", nom_fichier);
        exit(3);
    }

    // printf("debut de l\'ecriture %s\n", nom_fichier);

    if (a)
        parcoursInfixeEcritureCroissantP2(a, sortie);
    else
        parcoursListeEcritureCroissantP2(liste, sortie);

    // printf("fin de l\'ecriture %s\n", nom_fichier);
    fclose(sortie);
    free(a);
    free(liste);
}

void ecritureFichierP3(char *nom_fichier, PArbre a, Chainon *liste) {
    // char *nom_fichier = "test/tri_p3.csv";
    FILE *sortie = fopen(nom_fichier, "w+");
    if (!sortie) {
        printf("Erreur ouverture de %s\n", nom_fichier);
        exit(3);
    }

    // printf("debut de l\'ecriture %s\n", nom_fichier);

    if (a)
        parcoursInfixeEcritureCroissantP3(a, sortie);
    else
        parcoursListeEcritureCroissantP3(liste, sortie);

    // printf("fin de l\'ecriture %s\n", nom_fichier);
    fclose(sortie);
    free(a);
    free(liste);
}

void ecritureFichierT3(char *nom_fichier, PArbre a, Chainon *liste) {
    // char *nom_fichier = "test/tri_t3.csv";
    FILE *sortie = fopen(nom_fichier, "w+");
    if (!sortie) {
        printf("Erreur ouverture de %s\n", nom_fichier);
        exit(3);
    }

    // printf("debut de l\'ecriture %s\n", nom_fichier);

    if (a)
        parcoursInfixeEcritureCroissantP3(a, sortie);
    else
        parcoursListeEcritureCroissantP3(liste, sortie);

    // printf("fin de l\'ecriture %s\n", nom_fichier);
    fclose(sortie);
    free(a);
    free(liste);
}







/*

nettoyer le gnuplot

commentaires C

github : push et envoyer le lien sur teams

LA DATE

revoir mode 3 : insertion des fils des doublons dans l'ordre

faire les tris par liste


readme
rapport : mettre les droits au shell, manque de donnees avec le filtrage geo/, 
exemples d'execution/, gestion des doublons, structure arbre/chainon, options C, 
methodes pour chaque type de donnee, pk c code en dur
les pbs de pt2/, pt3 non fait/, valeurs de pression moyenne p1 negatives/
separateur d'entree ; separateur de sortie , car on peut melanger avec lat et long
nombres a virgule tronques/, fichiers temp crees puis supprimes/,
option -r inutile/, compilation propre, LA DATE


PLANNING derniere semaine
lundi : tri alt, hum, vent, debut p1
mardi : tri p1 t1 p2 t2 p3 t3
mercredi : getopt, association du shell et du c, gestion des fichiers temporaires, gnuplot vent, p1, p2
jeudi : gnuplot alt, hum  pt1, pt2, tri abr, debut liste, commentaires, ajustement du shell
vendredi paufiner gnuplot, finalisation du rapport et du readme







filtrer par coordonees
faire des casts pour les flottants
optimiser le code pour strtol et strtok




voir pour le multi-thread pour un tri plus efficace/rapide

*/
