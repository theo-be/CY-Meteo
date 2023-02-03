#!/bin/bash

# Constantes contenant le numero des champs dans le fichier csv de reference

# Numeros des colonnes par champ :
# 1 : id station
# 2 : date
# 3 : pression niveau mer
# 4 : direction du vent moyen 10 mn
# 5 : Vitesse du vent moyen 10 mn
# 6 : humidite
# 7 : pression station
# 8 : Variation de pression en 24 heures
# 9 : Precipitations dans les 24 derniÃ¨res heures
# 10 : Coordonnees
# 11 : Temperature ( °C)
# 12 : Temperature minimale sur 24 heures ( °C)
# 13 : Temperature maximale sur 24 heures ( °C)
# 14 : Altitude
# 15 : communes (code)

NUM_CHAMP_STATION='1'
NUM_CHAMP_DATE='2'
# NUM_CHAMP_PRESSION_MER='3'
NUM_CHAMP_DIRECTION_VENT='4'
NUM_CHAMP_VITESSE_VENT='5'
NUM_CHAMP_HUMIDITE='6'
NUM_CHAMP_PRESSION_STATION='7'
# NUM_CHAMP_VARIATION_PRESSION='8'
# NUM_CHAMP_PRECIPITATIONS='9'
NUM_CHAMP_COORDONEES='10'
NUM_CHAMP_TEMPERATURE='11'
# NUM_CHAMP_TEMPERATURE_MIN='12'
# NUM_CHAMP_TEMPERATURE_MAX='13'
NUM_CHAMP_ALTITUDE='14'
# NUM_CHAMP_COMMUNES='15'




# Utilisation des regex pour le filtrage geographique

regex=""
REGEX_FRANCE="([0-8][0-9]|9[0-5]|2[a,b,A,B])[0-9]{3}$"
REGEX_GUYANE="973[0-9]{2}$"
REGEX_SAINT_PIERRE="975[0-9]{2}$"
REGEX_ANTILLES="97[1-2,7-8][0-9]{2}$"
REGEX_OCEAN_INDIEN="97[4,6][0-9]{2}$"
REGEX_ANTARCTIQUE="98414$"



fichier_entree=''

# Constantes contenant le nom des fichiers d'entree/sortie

FICHIER_F_ALTITUDE='data/filtre_altitude.csv'
FICHIER_F_HUMIDITE='data/filtre_humidite.csv'
FICHIER_F_VENT='data/filtre_vent.csv'
FICHIER_F_p1='data/filtre_p1.csv'
FICHIER_F_p2='data/filtre_p2.csv'
FICHIER_F_p3='data/filtre_p3.csv'
FICHIER_F_t1='data/filtre_t1.csv'
FICHIER_F_t2='data/filtre_t2.csv'
FICHIER_F_t3='data/filtre_t3.csv'

FICHIER_T_altitude='data/tri_altitude.csv'
FICHIER_T_humidite='data/tri_humidite.csv'
FICHIER_T_vent='data/tri_vent.csv'
FICHIER_T_p1='data/tri_p1.csv'
FICHIER_T_p2='data/tri_p2.csv'
FICHIER_T_p3='data/tri_p3.csv'
FICHIER_T_t1='data/tri_t1.csv'
FICHIER_T_t2='data/tri_t2.csv'
FICHIER_T_t3='data/tri_t3.csv'


# Variables contenant la presence des arguments

arg_fichier=0
arg_pression=0
arg_temperature=0
arg_humidite=0
arg_date=0
arg_lieu=0
arg_vent=0
arg_altitude=0
arg_option=0
arg_lieu=0
mode_tri='avl'



# Fonction optlieu qui gere les options geographiques

# optlieu $option
optlieu() {
    # si on a deja une option de lieu, on quitte
    if (($arg_lieu != 0)) ; then 
        echo "Erreur option -$1 : l'option de lieu doit etre unique"
        return 1
    fi
    arg_lieu=1
    # lieu=$1
    return 0
}





# Programme principal



# Recuperation des arguments et options avec getopts

while getopts ":wmhp:t:FGSAOQf:d::-:" option ; do
    # Options longues
    if [ "$option" = '-' ] ; then
        case $OPTARG in
            help) echo "menu d'aide"
            echo "Utilisation : ./CY-Meteo.bash  [OPTIONS]  -f [FICHIER]

Les options courtes :

La première option est obligatoire :
-f<nom fichier> : fichier d’entrée

Il faut mettre au minimum une option de données

Les options de données :
-w : vent
-m : humidité
-h : altitude
-t<mode> : température
-p<mode> : pression atmosphérique

Les options -t et -p doivent être accompagner d’un mode entre 1 et 3 :
Mode 1 : produit en sortie les températures (ou pressions) minimales, maximales et moyennes par station dans l’ordre croissant du numéro de station
Mode 2 : produit en sortie les températures (ou pressions) moyennes par date/heure, triées dans l’ordre chronologique. La moyenne se fait sur toutes les stations
Mode 3 : produit en sortie les températures (ou pressions) par date/heure par station. Elles seront triées d’abord par ordre chronologique, puis par ordre croissant de l’identifiant de la station.


Options de lieux (attention ces options sont exclusives entre elles) :
-F : France : France métropolitaine + Corse
-G : Guyane française
-S : Saint-Pierre et Miquelon : ile située à l’Est du Canada
-A : Antilles
-O : Océan indien
-Q : Antarctique

Option de dates, les données de sortie sont dans l’intervalle de dates [<min>...<max>]
-d<min,max> : dates
L’option -d ne prends qu’un seul argument contenant les deux dates (au format AAAA-MM-DD) séparé par une virgule.

Les options longues :

Options de tris :
--tab : tri par listes chainées 
--abr : tri par ABR
--avl : tri par AVL"
            exit 0 ;; # Sortir immediatement apres
            version) 
            echo "CY-Meteo version 1.0"
            echo "Voir ./CY-Meteo --help pour afficher le menu d'aide"
            exit 0 ;; # Sortir immediatement apres
            avl) 
            mode_tri=$OPTARG ;;
            abr) 
            mode_tri=$OPTARG ;;
            tab) 
            mode_tri=$OPTARG ;;
            *) echo "Erreur : --$OPTARG : option invalide"
            exit 1;;
        esac
    else
    # Options courtes
        case "$option" in
            # Options de donnees
            w) 
            arg_option=1
            arg_vent=1 ;;
            h) 
            arg_option=1
            arg_altitude=1 ;;
            m) 
            arg_option=1
            arg_humidite=1 ;;
            p) 
            if (($OPTARG < 1)) || (($OPTARG > 3)) ; then
                echo "Erreur : le mode de pression est compris entre 1 et 3"
                exit 1
            fi
            arg_option=1
            arg_pression=$OPTARG ;;
            t) 
            if (($OPTARG < 1)) || (($OPTARG > 3))  ; then
                echo "Erreur : le mode de temperature est compris entre 1 et 3"
                exit 1
            fi
            arg_option=1
            arg_temperature=$OPTARG ;;


            # Options de date
            d) 
            if (($arg_date != 0)) ; then
                echo "Erreur : l'option de date doit etre unique"
                exit 1
            fi
            date=$OPTARG 
            # echo "Dates : $OPTARG"
            arg_date=1
            ;;

            # Options de fichier
            f) 
            if (( $arg_fichier != 0 )) ; then
                echo "Erreur : l'option -f doit etre unique"
                exit 1
            fi
            fichier_entree="$OPTARG"
            if [ ! -f "$fichier_entree" ] ; then
                echo "Erreur : '$fichier_entree' n'existe pas ou n'est pas un fichier"
                exit 1
            fi
            arg_fichier=1
            ;;

            # Options de lieu
            F) 
            if ! optlieu "$option" ; then
                exit 1
            fi 
            regex="$REGEX_FRANCE" ;;
            G) 
            if ! optlieu "$option" ; then
                exit 1
            fi 
            regex="$REGEX_GUYANE" ;;
            S) 
            if ! optlieu "$option" ; then
                exit 1
            fi 
            regex="$REGEX_SAINT_PIERRE" ;;
            A) 
            if ! optlieu "$option" ; then
                exit 1
            fi 
            regex="$REGEX_ANTILLES" ;;
            O) 
            if ! optlieu "$option" ; then
                exit 1
            fi 
            regex="$REGEX_OCEAN_INDIEN" ;;
            Q) 
            if ! optlieu "$option" ; then
                exit 1
            fi 
            regex="$REGEX_ANTARCTIQUE" ;;


            # Autre
            --) 
            break;;
            *) 
            echo "$OPTARG : option invalide"
            echo "$option : argument invalide"            
            exit 1
            break;;
        esac
    fi

done


# Verification de la presence des options obligatoires

if (( $arg_option != 1 )) ; then
    echo "Erreur : veuillez preciser au moins une option de type de donnee"
    exit 1
elif (( $arg_fichier != 1 )) ; then
    echo "Erreur : pas de fichier d'entree, utilisez l'option -f <fichier> pour inclure un fichier d'entree"
    exit 1
fi


# Commandes de filtrage

echo "Filtrage du fichier d'entrée"


# Filtrage selon le type de donnee

# Altitude 
if (($arg_altitude > 0)) ; then
    # filtrage avec restriction geographique
    if (($arg_lieu == 1)) ; then
        
        grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_ALTITUDE","$NUM_CHAMP_STATION","$NUM_CHAMP_COORDONEES" > "$FICHIER_F_ALTITUDE"
    # filtrage sans restiction geographique
    else 
        cut -sd\; -f"$NUM_CHAMP_ALTITUDE","$NUM_CHAMP_STATION","$NUM_CHAMP_COORDONEES" "$fichier_entree" | tail -n+2 > "$FICHIER_F_ALTITUDE"
    fi
fi



# Humidite

if (($arg_humidite > 0)) ; then

    if (($arg_lieu == 1)) ; then

        grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_HUMIDITE","$NUM_CHAMP_STATION","$NUM_CHAMP_COORDONEES" > "$FICHIER_F_HUMIDITE"
    else
        cut -sd\; -f"$NUM_CHAMP_HUMIDITE","$NUM_CHAMP_STATION","$NUM_CHAMP_COORDONEES" "$fichier_entree" | tail -n+2 > "$FICHIER_F_HUMIDITE"
    fi
fi



# Vent

if (($arg_vent > 0)) ; then

    if (($arg_lieu == 1)) ; then

        grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_DIRECTION_VENT","$NUM_CHAMP_VITESSE_VENT","$NUM_CHAMP_COORDONEES" > "$FICHIER_F_VENT"
    else 
        cut -sd\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_DIRECTION_VENT","$NUM_CHAMP_VITESSE_VENT","$NUM_CHAMP_COORDONEES" "$fichier_entree" | tail -n+2 > "$FICHIER_F_VENT"
    fi
fi

# Pression

if (($arg_pression > 0)) ; then

    # Mode 1
    if (($arg_pression == 1)) ; then

        if (($arg_lieu == 1)) ; then

            grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_PRESSION_STATION" > "$FICHIER_F_p1"
        else 
            cut -sd\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_PRESSION_STATION" "$fichier_entree" | tail -n+2 > "$FICHIER_F_p1"
        fi    
    # Mode 2
    elif (($arg_pression == 2)) ; then 
        
        if (($arg_lieu == 1)) ; then

            grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_PRESSION_STATION" > "$FICHIER_F_p2"
        else 
            cut -sd\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_PRESSION_STATION" "$fichier_entree" | tail -n+2 > "$FICHIER_F_p2"
        fi    
    
    # Mode 3
    else 

        if (($arg_lieu == 1)) ; then

            grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_STATION","$NUM_CHAMP_PRESSION_STATION" > "$FICHIER_F_p3"
        else 
            cut -sd\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_DATE","$NUM_CHAMP_PRESSION_STATION" | tail -n+2 "$fichier_entree" > "$FICHIER_F_p3"
        fi
        
    fi
fi

# Temperature

if (($arg_temperature > 0)) ; then

    # Mode 1
    if (($arg_temperature == 1)) ; then

        if (($arg_lieu == 1)) ; then
            grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_TEMPERATURE" > "$FICHIER_F_t1"
        else 
            cut -sd\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_TEMPERATURE" "$fichier_entree" | tail -n+2 > "$FICHIER_F_t1"
        fi

    # Mode 2
    elif (($arg_temperature == 2)) ; then 

        if (($arg_lieu == 1)) ; then

            grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_TEMPERATURE" > "$FICHIER_F_t2"
        else 
            cut -sd\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_TEMPERATURE" "$fichier_entree" | tail -n+2 > "$FICHIER_F_t2"
        fi

    # Mode 3
    else 

        if (($arg_lieu == 1)) ; then

            grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_STATION","$NUM_CHAMP_TEMPERATURE" > "$FICHIER_F_t3"
        else 
            cut -sd\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_STATION","$NUM_CHAMP_TEMPERATURE" "$fichier_entree" | tail -n+2 > "$FICHIER_F_t3"
        fi
        
    fi
fi


if (($arg_date > 0)) ; then
    # echo "separation des dates"
    #echo "$date"
    date1=${date%%,*} # Je recupère la première date
    #echo "première date : $date1"
    date2=${date##*,} # Je recupère la seconde date
    #echo "seconde date : $date2"
    echo "$date1">data/date1
    echo "$date2">data/date2
    verif=$(grep -E "$REGEX_DATE" data/date1)
    #echo "la verification vaut : $verif"
    if [ "$verif" != "$date1" ] ; then
        echo "La première date n'est pas au bon format (format : AAAA-MM-JJ)"
        exit 1
    fi
    verif=$(grep -E "$REGEX_DATE" data/date2)
    if [ "$verif" != "$date2" ] ; then
        echo "La seconde date n'est pas au bon format (format : AAAA-MM-JJ)"
        exit 1
    fi
    rm data/date1 data/date2
fi

echo "Filtrage des fichiers terminé"
echo "Tri des fichiers filtrés en cours"


# Verification de l'existence du fichier executable de tri

if [ ! -x 'bin/tri' ] ; then
    echo "Compilation du fichier executable de tri"
    make all
    retour_makefile="$?"
    if (($retour_makefile != 0)) ; then
        echo "Erreur makefile : code $retour_makefile"
        make mrproper
        exit 1
    fi
    make clean
fi



# Tri des fichiers filtres et construction des graphiques de sortie

# Altitude

if (($arg_altitude == 1)) ; then
    # Execution du programme
    ./bin/tri -rf "$FICHIER_F_ALTITUDE" -o "$FICHIER_T_altitude" -t "$mode_tri" -k h

    # Verification du code de retour du programme de tri
    retour_C="$?"
    if (($retour_C != 0)) ; then
        echo "Erreur d'exécution de bin/tri, code $retour_C"
        exit 1
    fi

    # Creation du graphique final
    cd 'gnuplot'
    gnuplot "altitude.plt"
    cd '..'

    # Suppression des fichiers temporaires
    rm "$FICHIER_F_ALTITUDE" "$FICHIER_T_altitude"
fi

# Humidite

if (($arg_humidite == 1)) ; then
    ./bin/tri -f "$FICHIER_F_HUMIDITE" -o "$FICHIER_T_humidite" -t "$mode_tri" -k m 
    retour_C="$?"
    if (($retour_C != 0)) ; then
        echo "Erreur d'exécution de bin/tri, code $retour_C"
        exit 1
    fi
    cd 'gnuplot'
    gnuplot "humidite.plt"
    cd '..'
    rm "$FICHIER_F_HUMIDITE" "$FICHIER_T_humidite"
fi

# Vent

if (($arg_vent == 1)) ; then
    ./bin/tri -f "$FICHIER_F_VENT" -o "$FICHIER_T_vent" -t "$mode_tri" -k w
    retour_C="$?"
    if (($retour_C != 0)) ; then
        echo "Erreur d'exécution de bin/tri, code $retour_C"
        exit 1
    fi
    cd 'gnuplot'
    gnuplot "vent.plt"
    cd '..'
    rm "$FICHIER_F_VENT" "$FICHIER_T_vent"
fi

# Pression

if (($arg_pression > 0)) ; then
    # Mode 1
    if (($arg_pression == 1)) ; then

        ./bin/tri -t "$mode_tri" -f "$FICHIER_F_p1" -o "$FICHIER_T_p1" -k p1
        retour_C="$?"
        if (($retour_C != 0)) ; then
            echo "Erreur d'exécution de bin/tri, code $retour_C"
            exit 1
        fi
        cd 'gnuplot'
        gnuplot 'p1.plt'
        cd '..'
        rm "$FICHIER_F_p1" "$FICHIER_T_p1"
    # Mode 2
    elif (($arg_pression == 2)) ; then

        ./bin/tri -f "$FICHIER_F_p2" -o "$FICHIER_T_p2" -t "$mode_tri" -k p2
        retour_C="$?"
        if (($retour_C != 0)) ; then
            echo "Erreur d'exécution de bin/tri, code $retour_C"
            exit 1
        fi
        cd 'gnuplot'
        gnuplot 'p2.plt'
        cd '..'
        rm "$FICHIER_F_p2" "$FICHIER_T_p2"
    # Mode 3
    else

        ./bin/tri -f "$FICHIER_F_p3" -o "$FICHIER_T_p3" -t "$mode_tri" -k p3
        retour_C="$?"
        if (($retour_C != 0)) ; then
            echo "Erreur d'exécution de bin/tri, code $retour_C"
            exit 1
        fi
        cd 'gnuplot'
        gnuplot 'p3.plt'
        cd '..'
        rm "$FICHIER_F_p3" "$FICHIER_T_p3"
    fi
fi

# Temperature

if (($arg_temperature > 0)) ; then
    # Mode 1
    if (($arg_temperature == 1)) ; then

        ./bin/tri -f "$FICHIER_F_t1" -o "$FICHIER_T_t1" -t "$mode_tri" -k t1
        retour_C="$?"
        if (($retour_C != 0)) ; then
            echo "Erreur d'exécution de bin/tri, code $retour_C"
            exit 1
        fi
        cd 'gnuplot'
        gnuplot 't1.plt'
        cd '..'
        rm "$FICHIER_F_t1" "$FICHIER_T_t1"
    # Mode 2
    elif (($arg_temperature == 2)) ; then

        ./bin/tri -f "$FICHIER_F_t2" -o "$FICHIER_T_t2" -t "$mode_tri" -k t2
        retour_C="$?"
        if (($retour_C != 0)) ; then
            echo "Erreur d'exécution de bin/tri, code $retour_C"
            exit 1
        fi
        cd 'gnuplot'
        gnuplot 't2.plt'
        cd '..'
        rm "$FICHIER_F_t2" "$FICHIER_T_t2"
    # Mode 3
    else

        ./bin/tri -f "$FICHIER_F_t3" -o "$FICHIER_T_t3" -t "$mode_tri" -k t3
        retour_C="$?"
        if (($retour_C != 0)) ; then
            echo "Erreur d'exécution de bin/tri, code $retour_C"
            exit 1
        fi
        cd 'gnuplot'
        gnuplot 't3.plt'
        cd '..'
        rm "$FICHIER_F_t3" "$FICHIER_T_t3"
    fi
fi

echo "Tris terminés"
echo "Graphiques générés dans le répertoire data"

exit 0








# parcourir les arg d'options de donnees
# pour chaque option de donnees :
# voir si les autres opt sont presentes
# filtrer, trier, gnuplot



# pour le C : option -r pour trier en decroissant

# verifier les params d'entree :
# verifier la compatibilite des params /
# verifier lexistence du fichier /
# revoir les cut/grep
# LA DATE

# aller chercher le fichier et filtrer
# si plusieurs modes : les faire a la suite dans plusieurs fichiers de sortie
# verifier le format des dates
# voir le fichier de sortie shell

# verifier l'existence du C /
# le compiler sinon /
# afficher en echo les commandes avant de les exec




# continuer la verif des arguments /
# faire des fonctions partout
# penser a IFS avant de faire un exit
# mettre des codes exit dans des variables
# faire des var commande option comme pour les makefiles
# voir pour les donnees manquantes du csv


# tester le format csv
