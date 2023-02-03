# CY-Meteo

Ce projet a pour objectif de créer un application qui va traiter un fichier de données météorologiques pour ensuite afficher des graphiques. 

# Pour commencer

Pour utiliser ce projet il faut d'abord attribuer les droits de lecture et d'exécution à CY-Meteo.bash. Il faut ensuite lancer le script en faisant ./CY-Meteo.bash.

# Utilisation

Pour utiliser l'application, il faut faire ./CY-Meteo.bash. Il faut ensuite ajouter ensuite les différentes options de données souhaitées, puis il faut obligatoirement mettre l'option -f accompagné du nom du fichier csv à étudier. Pour vous aider vous pouvez utiliser l'option --help qui vous montrera toute les options possibles et comment les utiliser.
Il est possible de faire un filtrage géographique sur une zone partuculière. Cette option doit être unique

Ensuite pour compiler les fichiers sources, il suffit simplement d'exécuter make avec la cible all. Néanmoins le script Shell se charge de faire cette compilation lorsque nécessaire.

# Utilisation du programme C indépendamment du script Shell

Vous pouvez, si vous le souhaitez, utiliser le programme de tri en C indépendamment du script Shell. 
Pour cela, il faut appeller le fichier avec les options :
-f fichier_entree
-o fichier_sortie
-t mode_tri
-k option_de_donnee

Ces options sont toutes obligatoires et doivent être unique.

# Erreurs d'exécution

En cas d'erreur lors de l'exécution du script Shell ou du programme C, un message d'erreur sera affiché, expliquant la raison de l'erreur. Un code de retour sera retourné.

# Auteurs

Théo Belliere

Maëlys Picault
