Partir du contenu de ce répertoire pour réaliser le BE.
Son contenu est dans le fichier archive BE_info.tar.gz.

S'assurer rapidement du bon comportement du graphique
avec le programme de test (main.c) qui est proposé.

Pour le développer, utiliser les fichiers Makefile.linux
et Makefile.solaris qui ont été testés dans les trois
salles de SUPAERO.
Pour un PC sous Windows, utiliser les informations données
dans l'énoncé. Il est rappelé que les oraux se dérouleront
avec les machines du centre informatique de SUPAERO.

Pour chaque changement de machine, ne pas oublier de
tout redévelopper, et donc commencer par :
make -f Makefile.linux clean

Avant l'exécution du programme produit, il faut que le
système puisse retrouver les bibliothèques à charger 
dynamiquement. 
Dans une salle PC, il faut :
export JRE_PATH=/usr/java/jdk/jre/lib/i386
dans une salle Sun :
export JRE_PATH=/usr/java/jdk/jre/lib/sparc
puis dans les deux cas :
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$JRE_PATH:$JRE_PATH/client

Pour vérifier le bon positionnement des variables d'environnement,
la commande :
ldd supanoid
ne doit pas renvoyer d'erreur.


