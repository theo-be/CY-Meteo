#!/bin/bash


# cut -d\; -f1 data/meteo_filtered_data_v1.csv > test/test.csv

# arguments a verifier avant d'executer :
# si -d date date
# -f fichier

# arguments compatibles :
# types de donnees

# arguments incompatibles :
# --avl --abr --tab
# lieux

# arguments obligatoires :
#  -f <fichier>
# une des options de donnees -h -p1 -w...
# -t<chiffre> -p<chiffre>

# arguments non obligatoires
# -d
#  --avl, --abr, --tab
# lieux


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





# verifier chaque option au lieu de verif le nombre d'args



# messages d'erreur

MESSAGE_ERREUR_PRESSION='erreur pression'

# nom des fichiers d'entree/sortie

fichier_entree=''
fichier_sortie='test/filtre.csv'

# presence des arguments

arg_fichier=0
arg_pression=0
mode_pression=''
arg_temperature=0
mode_temperature=''
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
arg_mode_tri=0
mode_tri='--avl'


# numero des champs dans le fichier

NUM_CHAMP_STATION='1'
NUM_CHAMP_DATE='2'
NUM_CHAMP_DIRECTION_VENT='4'
NUM_CHAMP_VITESSE_VENT='5'
NUM_CHAMP_HUMIDITE='6'
NUM_CHAMP_PRESSION='7'
NUM_CHAMP_VARIATION_PRESSION='8'
NUM_CHAMP_PRECIPITATIONS='9'
NUM_CHAMP_COORDONEES='10'
NUM_CHAMP_TEMPERATURE='11'
NUM_CHAMP_TEMPERATURE_MIN='12'
NUM_CHAMP_TEMPERATURE_MAX='13'
NUM_CHAMP_ALTITUDE='14'
NUM_CHAMP_COMMUNES='15'



# chaine='-p2'
# c1='-p'
# c2='-p1'
# c3='-p2'
# c4='-p3'

# if [ "$chaine" = "$c1" ] ; then
#     echo "c1="
# fi
# if [ "$chaine" \> "$c1" ] ; then
#     echo "c1>"
# fi
# if [ "$chaine" \< "$c1" ] ; then
#     echo "c1<"
# fi




# echo "nombre d'arguments : $#"

oldIFS=$IFS
IFS=' '
############################################################

# while getops <format> option ; do
# while getops <format> option ; do
#     case "$option" in




#         *) ;;
#     esac


# done







##############################################







# premiere boucle pour verifier les parametres importants ou obligatoires

for arg in "$@" ; do

    if (( $arg_fichier == -1 )) ; then
        if [ ! -f $arg ] ; then
            echo "Erreur : '$arg' n'existe pas ou n'est pas un fichier"
            exit 1
        fi
        fichier_entree=$arg
        arg_fichier=1
        echo "fichier d'entree : $fichier_entree"
        continue
    fi





    case $arg in
    '--help') 
        echo "menu d'aide utilisateur"
        exit 0 ;;
    '--version') 
        echo "CY-Meteo version 0"
        echo "Voir --help pour le menu d'aide"
        exit 0 ;;
    '-f') 
        if (( $arg_fichier == 1 )) ; then
            echo "Erreur : plusieurs fois -f"
            exit 1
        fi
        arg_fichier=-1 ;;


    esac
done




# verifier les param obligatoires manquants

if (($arg_fichier != 1)) ; then
    echo "Erreur : fichier d'entree specifie"
    # exit 1
fi




# boucle de recuperation des autres arguments

for arg in "$@" ; do
    # echo $arg

    # verification des dates

    if (($arg_date < 0)) ; then
        # echo "arg date : $arg_date"
        if (($arg_date == -1)) ; then
            arg_date1=$arg
            arg_date=-2
            # echo "date 1 : $arg_date1"
            continue
        elif (($arg_date == -2)) ; then
            arg_date2=$arg
            arg_date=1
            # echo "date 2 : $arg_date2"
            continue
        fi
    fi





    case $arg in

        # options de donnees

        '-m') # humidite
            echo "humidite"
            if (( $arg_humidite > 0 )) ; then
                echo "pb humidite"
                # affichage du menu d'aide
                # ./CY-Meteo.bash --help
                exit 1
            fi
            arg_humidite=1
            arg_option=1 ;;
        
        '-h') # altitude
            echo "altitude"
            if (( $arg_altitude > 0 )) ; then
                echo "pb humidite"
                exit 1
            fi
            arg_altitude=1
            arg_option=1 ;;
        '-w') # vent
            echo "vent"
            if (( $arg_vent > 0 )) ; then
                echo "pb vent"
                exit 1
            fi
            arg_vent=1
            arg_option=1 ;;



        # options de lieu
        '-F') # France
            if (( $arg_lieu != 0 )) ; then
                echo "Erreur : un seul lieu en meme temps"
                exit 1
            fi
            arg_lieu=1
            lieu="$arg" ;;
        '-G') # Guyane
            if (( $arg_lieu != 0 )) ; then
                echo "Erreur : un seul lieu en meme temps"
                exit 1
            fi
            arg_lieu=1
            lieu="$arg" ;;
        '-S') # Saint Pierre et Miquelon
            if (( $arg_lieu != 0 )) ; then
                echo "Erreur : un seul lieu en meme temps"
                exit 1
            fi
            arg_lieu=1
            lieu="$arg" ;;
        '-A') # Antilles
            if (( $arg_lieu != 0 )) ; then
                echo "Erreur : un seul lieu en meme temps"
                exit 1
            fi
            arg_lieu=1
            lieu="$arg" ;;
        '-O') # Ocean Indien
            if (( $arg_lieu != 0 )) ; then
                echo "Erreur : un seul lieu en meme temps"
                exit 1
            fi
            arg_lieu=1
            lieu="$arg" ;;
        '-Q') # Antarctique
            if (( $arg_lieu != 0 )) ; then
                echo "Erreur : un seul lieu en meme temps"
                exit 1
            fi
            arg_lieu=1
            lieu="$arg" ;;


        # dates

        '-d') 
            if (( $arg_date != 0)) ; then
                echo "Erreur date"
            fi
            arg_date=-1 ;;




        # modes de tri

        '--avl')
            if (( $arg_mode_tri != 0 )) ; then
                echo "Erreur mode de tri"
                # exit 1
            fi
            arg_mode_tri=1 ;;

        '--abr')
            if (( $arg_mode_tri != 0 )) ; then
                echo "Erreur mode de tri"
                # exit 1
            fi
            arg_mode_tri=2
            mode_tri=$arg ;;

        '--tab')
            if (( $arg_mode_tri != 0 )) ; then
                echo "Erreur mode de tri"
                # exit 1
            fi
            arg_mode_tri=3
            mode_tri=$arg ;;



        
        *) 
            # modes de pression et temperature
            if [ "$arg" \> '-p' ] && [ "$arg" \< '-p4' ] ; then
                echo "mode de pression"
                arg_pression=1
                mode_pression=$arg
                arg_option=1
            elif [ "$arg" \> '-t' ] && [ "$arg" \< '-t4' ] ; then
                echo "mode de temp"
                arg_temperature=1
                mode_temperature=$arg
                arg_option=1
            else # argument inconnu
                echo "Erreur : $arg : argument invalide"
                # exit 1
            fi ;;
    esac
done

IFS=$oldIFS

if (( $arg_option != 1 )) ; then
    echo "Erreur : veuillez preciser au moins une option de type de donnee"
    IFS=$oldIFS
    exit 1
fi

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




if (($arg_pression > 0)) ; then
    echo "filtre pre"
    # mode 1
    if [ "$mode_pression" = '-p1' ] ; then
        echo "filtre p1"
        echo "cut -d\; -f$NUM_CHAMP_STATION,$NUM_CHAMP_PRESSION_MER,$NUM_CHAMP_PRESSION_STATION $fichier_entree > $fichier_sortie"
        cut -d\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_PRESSION_MER","$NUM_CHAMP_PRESSION_STATION" "$fichier_entree" > "$fichier_sortie"
    elif [ "$mode_pression" = '-p2' ] ; then # mode 2
        echo "filtre p2"
        echo "cut -d\; -f$NUM_CHAMP_DATE,$NUM_CHAMP_PRESSION_STATION $fichier_entree > $fichier_sortie"
        cut -d\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_PRESSION_STATION" "$fichier_entree" > "$fichier_sortie"
    else # mode 3
        echo "filtre p3"
        echo "cut -d\; -f$NUM_CHAMP_DATE,$NUM_CHAMP_STATION,$NUM_CHAMP_PRESSION_STATION $fichier_entree > $fichier_sortie"
        cut -d\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_STATION","$NUM_CHAMP_PRESSION_STATION" "$fichier_entree" > "$fichier_sortie"
    fi
fi
if (($arg_temperature > 0)) ; then
    echo "filtre temp"
    # mode 1
    if [ "$mode_temperature" = '-t1' ] ; then
        echo "filtre t1"
        echo "cut -d\; -f$NUM_CHAMP_STATION,$NUM_CHAMP_TEMPERATURE,$NUM_CHAMP_TEMPERATURE_MIN,$NUM_CHAMP_TEMPERATURE_MAX $fichier_entree > $fichier_sortie"
        cut -d\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_TEMPERATURE","$NUM_CHAMP_TEMPERATURE_MIN","$NUM_CHAMP_TEMPERATURE_MAX" "$fichier_entree" > "$fichier_sortie"
    elif [ "$mode_temperature" = '-t2' ] ; then # mode 2
        echo "filtre t2"
        echo "cut -d\; -f$NUM_CHAMP_DATE,$NUM_CHAMP_TEMPERATURE $fichier_entree > $fichier_sortie"
        cut -d\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_TEMPERATURE" "$fichier_entree" > "$fichier_sortie"
    else # mode 3
        echo "filtre t3"
        echo "cut -d\; -f$NUM_CHAMP_DATE,$NUM_CHAMP_STATION,$NUM_CHAMP_TEMPERATURE $fichier_entree > $fichier_sortie"
        cut -d\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_STATION","$NUM_CHAMP_TEMPERATURE" "$fichier_entree" > "$fichier_sortie"
    fi
fi


if (($arg_altitude > 0)) ; then
    echo "filtre alt"
    # verifier les autres options
    echo "cut -d\; -f$NUM_CHAMP_ALTITUDE,$NUM_CHAMP_STATION $fichier_entree > $fichier_sortie"
    cut -d\; -f"$NUM_CHAMP_ALTITUDE","$NUM_CHAMP_STATION" "$fichier_entree" > "$fichier_sortie"
fi
if (($arg_humidite > 0)) ; then
    echo "filtre hum"
    # verifier les autres options
    echo "cut -d\; -f$NUM_CHAMP_HUMIDITE,$NUM_CHAMP_STATION $fichier_entree > $fichier_sortie"
    cut -d\; -f"$NUM_CHAMP_HUMIDITE","$NUM_CHAMP_STATION" "$fichier_entree" > "$fichier_sortie"
fi
if (($arg_vent > 0)) ; then
    echo "filtre vent"
    echo "cut -d\; -f$NUM_CHAMP_STATION,$NUM_CHAMP_DIRECTION_VENT,$NUM_CHAMP_VITESSE_VENT $fichier_entree > $fichier_sortie"
    cut -d\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_DIRECTION_VENT","$NUM_CHAMP_VITESSE_VENT" "$fichier_entree" > "$fichier_sortie"
    
fi




# NUM_CHAMP_STATION='1'
# NUM_CHAMP_DATE='2'
# NUM_CHAMP_PRESSION_MER='3'
# NUM_CHAMP_DIRECTION_VENT='4'
# NUM_CHAMP_VITESSE_VENT='5'
# NUM_CHAMP_HUMIDITE='6'
# NUM_CHAMP_PRESSION_STATION='7'
# NUM_CHAMP_VARIATION_PRESSION='8'
# NUM_CHAMP_PRECIPITATIONS='9'
# NUM_CHAMP_COORDONEES='10'
# NUM_CHAMP_TEMPERATURE='11'
# NUM_CHAMP_TEMPERATURE_MIN='12'
# NUM_CHAMP_TEMPERATURE_MAX='13'
# NUM_CHAMP_ALTITUDE='14'
# NUM_CHAMP_COMMUNES='15'






# verification de l'existence du fichier de tri

if [ ! -x 'bin/tri' ] ; then
    echo "pas de fichier de tri"
    make all
    echo "retour makefile : $?"
    if (($? != 0)) ; then
        echo "erreur makefile"
        IFS=$oldIFS
        exit 1
    fi
fi
# a mettre dans une fonction


echo "./bin/tri $mode_tri"
./bin/tri "$mode_tri"




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

# aller chercher le fichier et filtrer
# si plusieurs modes : les faire a la suite dans plusieurs fichiers de sortie

# verifier l'existence du C
# le compiler sinon
# afficher en echo les commandes avant de les exec




# continuer la verif des arguments
# fusionner les boucles
# faire des fonctions partout
# faire une fonction chaine de caracteres pour --arg
# penser a IFS avant de faire un exit
# mettre des codes exit dans des variables
# faire des var commande option comme pour les makefiles
# gerer si plusieurs modes de pre/temp en meme temps
# voir pour les donnees manquantes du csv

# verifier le format des dates ?


