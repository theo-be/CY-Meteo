#!/bin/bash






# arguments a verifier avant d'executer :
# si -d date date
# -f fichier

# arguments compatibles :
# types de donnees

# arguments incompatibles :
# lieux

# arguments obligatoires :
#  -f <fichier>
# une des options de donnees -h -p1 -w...
# -t<chiffre> -p<chiffre>

# arguments non obligatoires
# -d
#  --avl, --abr, --tab
# lieux
























# constantes : numero des champs dans le fichier csv

# numeros des colonnes par champ :
# 1 : id station
# 2 : date
# 3 : pression niveau mer
# 4 : direction du vent moyen 10 mn
# 5 : Vitesse du vent moyen 10 mn
# 6 : humidite
# 7 : pression station
# 8 : Variation de pression en 24 heures
# 9 : PrÃ©cipitations dans les 24 derniÃ¨res heures
# 10 : Coordonnees
# 11 : TempÃ©rature (Â°C)
# 12 : TempÃ©rature minimale sur 24 heures (Â°C)
# 13 : TempÃ©rature maximale sur 24 heures (Â°C)
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
# NUM_CHAMP_COORDONEES='10'
NUM_CHAMP_TEMPERATURE='11'
NUM_CHAMP_TEMPERATURE_MIN='12'
NUM_CHAMP_TEMPERATURE_MAX='13'
NUM_CHAMP_ALTITUDE='14'
NUM_CHAMP_COMMUNES='15'



# constantes : regex 


# 1>95 france
# 


# 98411 > 98415 antarctique
# 9841[1-5]

# 973 0-99 guyane

# 97501>97502 saint pierre et miquelon
# 97[3-5]00

# antilles
# guadeloupe 97101 97134
# mar 97201 97234
# saint mar 97801
# st bar 97701
# 97[1-2]00
# 97[7-8]00


# ocean indien
# mayotte 976
# la reunion 974
# 97[4-6]00

regex=""
# commande_grep=""
REGEX_FRANCE="([0-8][0-9]|9[0-5]|2[a,b,A,B])[0-9]{3}$"
REGEX_ANTILLES="97[1-2,7-8][0-9]{2}$"
REGEX_ANTARCTIQUE="9841[0-9]$"
REGEX_OCEAN_INDIEN="97[4,6][0-9]{2}$"
REGEX_GUYANE="973[0-9]{2}$"
REGEX_SAINT_PIERRE="975[0-9]{2}$"



# messages d'erreur

# MESSAGE_ERREUR_PRESSION='erreur pression'

# nom des fichiers d'entree/sortie

fichier_entree=''
fichier_inter='test/temp1.csv'
fichier_sortie='test/filtre.csv'

# presence des arguments

arg_fichier=0
arg_pression=0
# mode_pression=''
arg_temperature=0
# mode_temperature=''
arg_humidite=0
arg_date=0
arg_date1=''
arg_date2=''
arg_lieu=0
arg_vent=0
arg_altitude=0
arg_option=0
arg_lieu=0
lieu=''
# arg_mode_tri=0
mode_tri='avl'












# optlieu $option
optlieu() {
    if (($arg_lieu != 0)) ; then 
        echo "Erreur arg lieu -$1 : l'option de lieu doit etre unique"
        return 1
    fi
    arg_lieu=1
    lieu=$1
    echo "lieu : $lieu"
    return 0
}














# programme principal


# echo "nombre d'arguments : $#"

# recuperation des arguments et options avec getopts

while getopts ":wmhp:t:FGSAOQf:d::-:" option ; do
    # options longues
    if [ "$option" = '-' ] ; then
        case $OPTARG in
            help) echo "menu d'aide"
            exit 0 ;; # sortir immediatement apres
            version) echo "CY-Meteo version 0.1"
            exit 0 ;; # sortir immediatement apres
            avl) echo "opt $OPTARG"
            mode_tri=$OPTARG ;;
            abr) echo "opt $OPTARG"
            mode_tri=$OPTARG ;;
            tab) echo "opt $OPTARG"
            mode_tri=$OPTARG ;;
            *) echo "opt $OPTARG : option invalide";;
        esac
    else
    # options courtes
        case "$option" in
            # options de donnees
            w) echo 'opt w'
            arg_option=1
            arg_vent=1 ;;
            h) echo 'opt h'
            arg_option=1
            arg_altitude=1 ;;
            m) echo 'opt m'
            arg_option=1
            arg_humidite=1 ;;
            p) echo 'opt p'
            if (($OPTARG < 1)) || (($OPTARG > 3)) ; then
                echo "Erreur mode de pression"
                exit 1
            fi
            echo "mode $OPTARG"
            arg_option=1
            arg_pression=$OPTARG ;;
            t) echo 'opt t'
            if (($OPTARG < 1)) || (($OPTARG > 3))  ; then
                echo "Erreur mode de temp"
                exit 1
            fi
            echo "mode $OPTARG"
            arg_option=1
            arg_temperature=$OPTARG ;;

            # options de date
            d) echo 'opt d'
            echo "opt date : $OPTARG"
            arg_date=1
            arg_date1=$OPTARG
            # arg_date2 ??????????????????????????????????????????
            # verif date blabla
            ;;

            # options de fichier
            f) echo 'opt f'
            if (( $arg_fichier != 0 )) ; then
                echo "Erreur : plusieurs fois -f"
                exit 1
            fi
            echo "opt fichier : $OPTARG"
            fichier_entree="$OPTARG"
            if [ ! -f "$fichier_entree" ] ; then
                echo "Erreur : '$fichier_entree' n'existe pas ou n'est pas un fichier"
                exit 1
            fi
            arg_fichier=1
            echo "fichier d'entree : $fichier_entree"
            ;;

            # options de lieu
            # verif l'exclusivite de ces opt
            F) echo 'opt F'
            if ! optlieu $option ; then
                exit 1
            fi 
            regex="$REGEX_FRANCE" ;;
            G) echo 'opt G'
            if ! optlieu $option ; then
                exit 1
            fi 
            regex="$REGEX_GUYANE" ;;
            S) echo 'opt S'
            if ! optlieu $option ; then
                exit 1
            fi 
            regex="$REGEX_SAINT_PIERRE" ;;
            A) echo 'opt A'
            if ! optlieu $option ; then
                exit 1
            fi 
            regex="$REGEX_ANTILLES" ;;
            O) echo 'opt O'
            if ! optlieu $option ; then
                exit 1
            fi 
            regex="$REGEX_OCEAN_INDIEN" ;;
            Q) echo 'opt Q'
            if ! optlieu $option ; then
                exit 1
            fi 
            regex="$REGEX_ANTARCTIQUE" ;;


            # autre
            *) echo "$OPTARG : option invalide"
            echo "$option : option invalide"
            exit 1;;
            --) break;;
        esac
    fi

done







if (( $arg_option != 1 )) ; then
    echo "Erreur : veuillez preciser au moins une option de type de donnee"
    exit 1
elif (( $arg_fichier != 1 )) ; then
    echo "Erreur pas de fichier d'entree"
    exit 1
fi

# exit 0

# commandes de filtrage






# vent : produit en sortie l’orientation moyenne et la vitesse moyenne des
# vents pour chaque station. Quand on parle de moyenne, il s’agira de
# faire la somme pour chaque composante du vecteur, et d’en faire la
# moyenne une fois tous les vecteurs traités. On aura donc une
# moyenne sur l’axe X et une moyenne sur l’axe Y : les 2 résultats
# fournissant le module et l’orientation moyens demandés. Les
# données seront triées par identifiant croissant de la station.

# altitude : Produit en sortie l’altitude pour chaque station. Les altitudes seront triées par ordre décroissant.

# humidite : Produit en sortie l’humidité maximale pour chaque station. Les valeurs d’humidités seront triées par ordre décroissant.



# pression/temperature :
# 1 : produit en sortie les températures (ou pressions)
# minimales, maximales et moyennes par station dans l’ordre
# croissant du numéro de station.
# 2 : produit en sortie les températures (ou pressions)
# moyennes par date/heure, triées dans l’ordre chronologique.
# La moyenne se fait sur toutes les stations.
# 3 : produit en sortie les températures (ou pressions) par
# date/heure par station. Elles seront triées d’abord par ordre
# chronologique, puis par ordre croissant de l’identifiant de la station



# filtrage selon le mode de donnee


code_communes=''
if (($arg_lieu == 1)) ; then
    code_communes="$NUM_CHAMP_COMMUNES,"
fi


# ancienne version









# nouvelle version (meilleure)


if (($arg_altitude > 0)) ; then
    echo 'filtrage alt'
    if (($arg_lieu == 1)) ; then
        echo "filtre lieu"
        grep -E "$regex" "$fichier_entree" | cut -d\; -f"$NUM_CHAMP_ALTITUDE","$NUM_CHAMP_STATION" > test/filtre_altitude.csv
    else 
        cut -d\; -f"$NUM_CHAMP_ALTITUDE","$NUM_CHAMP_STATION" "$fichier_entree" > test/filtre_altitude.csv
    fi
    head -20 test/filtre_altitude.csv
    wc -l test/filtre_altitude.csv
    echo "fini"
fi





if (($arg_humidite > 0)) ; then
    echo "filtrage hum"
    if (($arg_lieu == 1)) ; then
        echo "filtre lieu"
        grep -E "$regex" "$fichier_entree" | cut -d\; -f"$NUM_CHAMP_HUMIDITE","$NUM_CHAMP_STATION" > test/filtre_humidite.csv
    else 
        cut -d\; -f"$NUM_CHAMP_HUMIDITE","$NUM_CHAMP_STATION" "$fichier_entree" > test/filtre_humidite.csv
    fi
    head -20 test/filtre_humidite.csv
    wc -l test/filtre_humidite.csv
    echo "fini"
fi





if (($arg_vent > 0)) ; then
    echo "filtrage vent"
    if (($arg_lieu == 1)) ; then
        echo "filtre lieu"
        grep -E "$regex" "$fichier_entree" | cut -d\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_DIRECTION_VENT","$NUM_CHAMP_VITESSE_VENT" > test/filtre_vent.csv
    else 
        cut -d\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_DIRECTION_VENT","$NUM_CHAMP_VITESSE_VENT" "$fichier_entree" > test/filtre_vent.csv
    fi
    head -20 test/filtre_vent.csv
    wc -l test/filtre_vent.csv
    echo "fini"
fi


if (($arg_pression > 0)) ; then
    echo "filtrage pre"
    # mode 1
    if (($arg_pression == 1)) ; then
        echo "filtrage p1"
        if (($arg_lieu == 1)) ; then
            echo "filtre lieu"
            grep -E "$regex" "$fichier_entree" | cut -d\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_PRESSION_STATION" > test/filtre_p1.csv
        else 
            cut -d\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_PRESSION_STATION" "$fichier_entree" > test/filtre_p1.csv
        fi
        head -20 test/filtre_p1.csv
        wc -l test/filtre_p1.csv
        echo "fini"
    
    
    
    
    elif (($arg_pression == 2)) ; then # mode 2
        echo "filtrage p2"
        
        if (($arg_lieu == 1)) ; then
            echo "filtre lieu"
            grep -E "$regex" "$fichier_entree" | cut -d\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_PRESSION_STATION" > test/filtre_p2.csv
        else 
            cut -d\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_PRESSION_STATION" "$fichier_entree" > test/filtre_p2.csv
        fi
        head -20 test/filtre_p2.csv
        wc -l test/filtre_p2.csv
        echo "fini"
    
    
    
    
    else # mode 3
        echo "filtrage p3"
        if (($arg_lieu == 1)) ; then
            echo "filtre lieu"
            grep -E "$regex" "$fichier_entree" | cut -d\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_STATION","$NUM_CHAMP_PRESSION_STATION" > test/filtre_p3.csv
        else 
            cut -d\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_STATION","$NUM_CHAMP_PRESSION_STATION" "$fichier_entree" > test/filtre_p3.csv
        fi
        head -20 test/filtre_p3.csv
        wc -l test/filtre_p3.csv
        echo "fini"
        
    fi
fi
if (($arg_temperature > 0)) ; then
    echo "filtrage temp"
    # mode 1
    if (($arg_temperature == 1)) ; then
        echo "filtrage t1"
        if (($arg_lieu == 1)) ; then
            echo "filtre lieu"
            grep -E "$regex" "$fichier_entree" | cut -d\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_TEMPERATURE","$NUM_CHAMP_TEMPERATURE_MIN","$NUM_CHAMP_TEMPERATURE_MAX" > test/filtre_t1.csv
        else 
            cut -d\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_TEMPERATURE","$NUM_CHAMP_TEMPERATURE_MIN","$NUM_CHAMP_TEMPERATURE_MAX" "$fichier_entree" > test/filtre_t1.csv
        fi
        head -20 test/filtre_t1.csv
        wc -l test/filtre_t1.csv
        echo "fini"
        
    
    
    
    
    elif (($arg_temperature == 2)) ; then # mode 2
        echo "filtrage t2"
        if (($arg_lieu == 1)) ; then
            echo "filtre lieu"
            grep -E "$regex" "$fichier_entree" | cut -d\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_TEMPERATURE" > test/filtre_t2.csv
        else 
            cut -d\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_TEMPERATURE" "$fichier_entree" > test/filtre_t2.csv
        fi
        head -20 test/filtre_t2.csv
        wc -l test/filtre_t2.csv
        echo "fini"
        
    
    
    
    
    else # mode 3
        echo "filtrage t3"
        if (($arg_lieu == 1)) ; then
            echo "filtre lieu"
            grep -E "$regex" "$fichier_entree" | cut -d\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_STATION","$NUM_CHAMP_TEMPERATURE" > test/filtre_t3.csv
        else 
            cut -d\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_STATION","$NUM_CHAMP_TEMPERATURE" "$fichier_entree" > test/filtre_t3.csv
        fi
        head -20 test/filtre_t3.csv
        wc -l test/filtre_t3.csv
        echo "fini"
        
    fi
fi




# cut -f

# Each range is one of:

#   N     N'th byte, character or field, counted from 1
#   N-    from N'th byte, character or field, to end of line
#   N-M   from N'th to M'th (included) byte, character or field
#   -M    from first to M'th (included) byte, character or field





















# verification de l'existence du fichier de tri

if [ ! -x 'bin/tri' ] ; then
    echo "Compilation du fichier exec de tri"
    make all
    echo "Retour makefile : $?"
    if (($? != 0)) ; then
        echo "Erreur makefile"
        exit 1
    fi
fi
# a mettre dans une fonction


echo "./bin/tri $mode_tri"
./bin/tri "$mode_tri"



make mrproper
echo "Fin normale du programme"
exit 0



# parcourir les arg d'options de donnees
# pour chaque option de donnees :
# voir si les autres opt sont presentes
# filtrer, trier, gnuplot



# pour le C : option -R pour trier en decroissant



# $? : code de retour de la derniere commande utilisee

# for (( i=0 ; i<=$# ; i++ )) ; do
#     echo $i
# done





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



