///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//       Marmottes
//
//$Application
//       Marmottes
//
//$Nom
//>       MarmottesVersion.cpp
//
//$Resume
//       fichier d'implantation de la fonction MarmottesVersion
//
//$Description
//       Module de définition de la fonction
//
//$Contenu
//>       const char *marmottesVersion()
//
//$Historique
//       $Log: MarmottesVersion.cpp,v $
//       Revision 6.8  2003/07/09 12:52:15  marmottes
//       remplacement de VERSION par PACKAGE_VERSION pour compatibilité avec autoconf 2.57 (DM 24)
//
//       Revision 6.7  2003/02/04 16:30:12  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 6.6  2000/11/13 10:04:16  luc
//       changement du nom du fichier d'inclusion
//
//       Revision 6.5  2000/03/30 17:01:19  luc
//       ajout du copyright CNES
//
//       Revision 6.4  1998/07/31 08:42:21  luc
//       utilisation de la macro définie par configure
//
//       Revision 6.3  1998/06/25 06:30:53  luc
//       modification du format des en-têtes
//       élimination des variables statiques RCS
//
//       Revision 6.2  1998/06/02 15:39:57  hotbird
//       correction d'un bug de compilation
//       (instanciation explicite)
//
//       Revision 6.1  1998/05/17 18:41:58  luc
//       inversion de la convention de nommage des attributs
//       élimination des classes ListeSenseurs, SenseurDiedreTan
//       séparation des interfaces C et fortran dans leurs fichiers
//       partage de la même table de simulateurs entre C et fortran
//       ajout des longueurs de messages dans l'interface C
//       ajout d'une possibilité de changer les unités position/vitesse
//       élimination des messages d'erreur inutilisés
//
//       Revision 5.8  1998/04/26 18:28:32  luc
//       ajout d'une gestion d'unités de position et de vitesse variables
//       reformatage de cerains messages d'erreur
//
//       Revision 5.7  1998/03/24 18:43:47  luc
//       correction de signatures de fonctions extern "C" dans Marmottes.h
//
//       Revision 5.6  1998/02/19 17:45:14  luc
//       contournement d'un bug d'optimiseur en ne déclarant
//       plus inline quelques constructeurs complexes
//
//       Revision 5.5  1998/02/06 17:47:22  luc
//       correction d'un bug de tri des solutions mathématiques et physiques
//       dans le cas des senseurs dièdres et des senseurs d'ascension droite
//       élargissement d'un critère de rejet de solutions
//
//       Revision 5.4  1998/02/04 09:50:21  luc
//       correction d'un bug de zéros non trouvés dans la résolution numérique
//       correction d'un bug dans les mesures de senseurs d'élévation
//       mise au format AMIGAU des en-têtes de classes
//       correction d'avertissements mineurs détectés par l'option -Wall
//
//       Revision 5.3  1997/12/01 14:02:06  luc
//       suppression des inhibitions de senseurs terre par la lune
//       et le soleil lors des éclipses
//       remplacement de la notion d'astre par la notion de cible
//       ajout d'une cible de type station sol
//       ajout de fichiers d'exemple pour les senseurs
//
//       Revision 5.2  1997/09/23 09:36:24  luc
//       refonte des senseurs de Cardan, désormais tous dérivés
//       de SenseurGeometrique et utilisables en contrôle
//       ajout d'une cible pour la direction le long de la trace
//       (SenseurOptique et dérivés)
//       ajout de la possibilité de gérer les unité
//       dans chaque instance de senseur
//
//       Revision 5.1  1997/09/17 15:32:12  luc
//       éclatement des fichiers (une classe par fichier)
//       ajout de fonctions inhibant la résolution rapide par extrapolation
//       ajout de fonctions de réinitialisation de simulateur déjà créé
//       refonte de la méthode de filtrage des solutions parasites
//       correction d'une erreur d'initialisation de ModeleGeom (_nombreDomaines)
//       limitation de la copie au seul modèle actif (ResolveurAttitude)
//       correction du message cible_inconnue (une partie n'était pas traduite)
//       réorganisation des Makefiles
//       remplacement de ModeleGeomMono et ModeleGeomAlig par ModeleGeomV1Fixe
//       forçage de la composante scalaire du quaternion à des valeurs positives
//       ajout des senseurs roulis, tangage, lacet
//       ajout du senseur de tangente d'angle dièdre
//       ajout du senseur cartésien
//       ajout d'une cible terre-soleil (soleil sans parallaxe)
//       préparation de l'utilisation de secteurs pour les consignes
//       (en prévision d'une résolution plus sélective dans une version future)
//
//       Revision 4.2  1997/04/30 08:27:32  luc
//       correction d'une mauvaise utilisation de la référence interne
//       retournée par TraduitVersexterne
//       
//       Revision 4.1  1997/04/27 19:42:56  luc
//       ajout des directions lune et soleil dans l'état
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       extraction de /SOFT_SDM
//       
//       Revision 3.7  1997/04/15 16:08:11  luc
//       correction d'une inversion dans le calcul du moment de l'orbite
//       remontée possible des champs d'inhibition des senseurs terre
//       
//       Revision 3.6  1997/03/21 18:51:25  luc
//       passage en version 3.6 à la suite de la correction d'un bug
//       fichier affecté : etat.cc (3.1 -> 3.2)
//       
//       Revision 3.5  1997/02/13 12:30:04  luc
//       prise en compte des évolutions de lecture.cc,
//       senseur_geom.h, senseur_geom.cc, et marmottes.cc
//       suite à l'introduction de la cible "moment"
//       et à la suppression des vérifications sur les dates trop proches
//       dans Marmottes::deuxConsignes
//       
//       Revision 3.4  1997/02/12 11:00:04  luc
//       prise en compte des évolutions de lecture.cc,
//       senseur_geom.h et senseur_geom.cc
//       à la suite de l'introduction de la cible "pseudo-soleil"
//       et de la prise en compte des éclipses par la lune
//       
//       Revision 3.3  1997/02/11 08:38:46  luc
//       prise en compte de l'évolution de marmottes.cc
//       (suppression d'une limitation sur les dates trop proches)
//       
//       Revision 3.2  1997/02/10 11:23:50  luc
//       prise en compte des évolutions de lecture.cc,
//       senseurs_geom.h et senseur_geom.cc,
//       à la suite de l'introduction de la vitesse en tant que cible observable
//       et de la gestion des éclipses de la lune et du soleil
//       
//       Revision 3.1  1997/01/28 12:50:20  luc
//       Evolution majeure :
//       gestion de la vitesse du satellite
//       initialisation du spin dès le début
//       prise en compte des évolutions de etat.h, etat.cc, marmottes.h, marmottes.cc,
//       marmottes_f.h marmottes_f.cc, resolveur_attitude.cc, senseur.h,
//       et senseur_cine.h
//       
//       Revision 2.6  1996/10/18 07:54:16  luc
//       prise en compte de l'évolution de mosaique.cc (correction d'un bug)
//       et des évolutions des etat.cc et modele_geom.cc (ajout de protections)
//       
//       Revision 2.5  1996/10/07 15:46:02  luc
//       prise en compte de l'évolution de mosaique.cc
//       (correction d'une erreur d'index de boucle)
//       et de resolveur_attitude.cc
//       (ajout de conversions explicites pour éviter des avertissements)
//       
//       Revision 2.4  1996/10/03 14:37:06  luc
//       prise en compte de la modification de :
//       continuite.cc, continuite.h, modele_geom.cc
//       pour la correction du prolongement par continuité,
//       de modele_cine.cc pour la correction des consignes en spin
//       et de lecture.cc pour la correction d'un message d'erreur
//       
//       Revision 2.3  1996/09/11 17:48:52  luc
//       prise en compte de l'ajout du nom dans Senseur (et classes dérivées)
//       prise en compte de la correction d'une erreur de références multiples
//       en raison de copies inconsidérées de pointeurs
//       ajout des interfaces C et fortran MarmottesCopie
//       ajout des interfaces C et fortran MarmottesDeuxConsignes
//       ajout de la méthode Marmottes:deuxConsignes
//       
//       Revision 2.2  1996/08/06 17:30:47  luc
//       prise en compte de l'utilisation du balayage dans la recherche
//       des visibilités d'horizon (mosaique.cc, secteurs.h, secteurs.cc)
//       
//       Revision 2.1  1996/07/31 18:13:07  luc
//       prise en compte des évolutions de fichiers dues au passage en version 2.1
//       (presque tous les fichiers ont été touchés)
//       
//       Revision 1.1  1996/07/31 17:59:19  luc
//       Initial revision
//
//$Version
//       $Id: MarmottesVersion.cpp,v 6.8 2003/07/09 12:52:15 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "MarmottesConfigNoInstall.h"

#include "marmottes/MarmottesVersion.h"

const char *marmottesVersion ()
{ return PACKAGE_VERSION; }
