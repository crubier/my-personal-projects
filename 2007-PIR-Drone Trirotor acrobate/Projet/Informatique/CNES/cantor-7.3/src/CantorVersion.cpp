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
//       Cantor
//
//$Nom
//>       CantorVersion.cpp
//
//$Resume
//       fichier d'implantation de la fonction CantorVersion
//
//$Description
//       Module de définition de la fonction
//
//$Contenu
//>       const char *cantorVersion()
//
//$Historique
//       $Log: CantorVersion.cpp,v $
//       Revision 4.7  2003/07/09 08:59:00  cantor
//       remplacement de VERSION par PACKAGE_VERSION pour compatibilité avec autoconf 2.57 (DM 24)
//
//       Revision 4.6  2003/02/04 09:26:28  cantor
//       DM-ID 17 Mise à jour du nom du fichier dans le bandeau suite à la modification des extensions.
//
//       Revision 4.5  2000/10/24 16:25:23  cantor
//       modification des includes pour permettre la compilation avec le
//       compilateur Sun Workshop 5.0
//
//       Revision 4.4  2000/08/09 14:36:41  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 4.3.4.1  2000/03/30 15:36:05  cantor
//       ajout du copyright CNES
//
//       Revision 4.3  1998/07/29 11:25:26  cantor
//       utilisation de la macro mise en place par configure
//
//       Revision 4.2  1998/06/24 16:39:37  luc
//       correction d'erreurs de déclarations d'arguments par défaut
//       correction d'une inclusion de fichier système
//       modification du format des en-têtes
//       éliminations des variables statiques RCS
//
//       Revision 4.1  1998/05/20 06:57:08  luc
//       inversion de la convention de nommage des attributs
//       contournements d'un bug du compilateur SUN 4.0
//       correction d'un const inutile dans une signature de CantorErreurs
//       ajout de la classe StatistiqueEchantillon
//       ajout de la fonction SectionDoree
//       déplacement de Champ et Secteurs vers la bibliothèque Marmottes
//
//       Revision 3.13  1998/04/20 19:22:35  luc
//       amélioration de messages d'erreurs divers
//       ajout de l'opérateur *= entre Créneaux
//       (même s'il n'apporte rien par rapport à l'opérateur *)
//       suppression de la méthode estValide dans toutes les classes
//
//       Revision 3.12  1998/02/19 17:28:15  luc
//       élimination du const rajouté dans une signature de Rotation<T>
//       à la version précédente
//
//       Revision 3.11  1998/01/22 10:57:00  luc
//       inversion des macro-définitions sur les exceptions (active par défaut)
//       correction de valeurs de retour dans les opérateurs =, +=, -=, ...
//       de la classe Polynome<T>
//       ajout d'un const dans une signature (classe rotation<T>)
//       amélioration des en-têtes de classes
//
//       Revision 3.10  1997/11/06 20:03:49  luc
//       correction d'un test d'alignement incohérent avec la précision machine
//       (class Rotation<T>)
//
//       Revision 3.9  1997/09/15 05:50:36  luc
//       reconnaissance correcte des zéros en fin d'intervalle
//       (classes Resolution1Iterateur et Resolution2Iterateur)
//       factorisation des règles communes de compilation
//       dans un Makefile de base unique
//
//       Revision 3.8  1997/07/24 17:11:29  luc
//       ajout d'un heuristique de détection des arcs parasites
//       basée sur le découpage des arcs "diagonaux" (classe Champ)
//
//       Revision 3.7  1997/07/11 09:18:59  luc
//       ajout d'en-têtes de fichiers dans toute la bibliothèque
//       refonte des calculs d'arcs parasites dans les intersections de champs
//       correction des signatures de fonctions de l'interface fortran
//       correction de tests de sécurité sur la norme de l'axe d'une rotation
//       ajout de méthodes d'accès aux éléments constitutifs d'un secteur
//       remplacement des size_t par des int
//       ajout des fichiers ArcIterateur.h et ArcIterateur.cc
//       ajout d'une méthode de test des recouvrements d'arcs
//       ajout d'une protection sur les dérivées des racines carrées
//
//       Revision 3.6  1997/05/20 08:21:13  luc
//       correction de fonctions amies des classes ValeurDerivee1 et ValeurDerivee2
//       
//       Revision 3.5  1997/04/26 21:07:30  luc
//       ajout de la fonction en ligne recaleAngle dans Util.h
//       correction de certains numéros de version de fichiers
//       
//       Revision 3.4  1997/04/17 06:22:53  luc
//       introduction des classes Secteurs et Champ
//       en provenance de la bibliothèque marmottes
//       déplacement de corrigOrthog (pour les rotations) dans l'interface publique
//       de la bibliothèque
//       
//       Revision 3.3  1997/04/03 19:37:00  luc
//       inversion des codes de retour, 0 signifie désormais : pas d'erreur
//       
//       Revision 3.2  1997/03/26 06:49:43  luc
//       passage de la bibliothèque en version 3.2
//       à la suite d'un changement général de conventions de nommage
//       et d'un changement de signature dans CantorErreurs
//       
//       Revision 3.1  1997/03/24 10:46:19  luc
//       passage en version 3.1 suite aux modifications :
//       passage de SCCS à RCS
//       extraction de /SOFT_SDM
//       ajout des fichiers math_pi.h et util.h
//       séparation de FonctionApprochee en deux classes
//       (d'où apparition de la classe MoindreCarreLineaire)
//       prise en compte du renommage de util_c++ en club
//       
//       Revision 2.3  1996/10/07 15:14:55  luc
//       prise en compte de la correction d'une erreur dans FonctionApprochee
//       
//       Revision 2.2  1996/08/06 17:17:34  luc
//       prise en compte de l'évolution de Arc (arc.h et arc.cc)
//       
//       Revision 2.1  1996/07/16 12:15:58  luc
//       archivage de l'état des fichiers composant la version 2.1 de libcantor.a
//       
//       Revision 1.1  1996/07/16 09:32:02  luc
//       Initial revision
//
//$Version
//       $Id: CantorVersion.cpp,v 4.7 2003/07/09 08:59:00 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <CantorConfigNoInstall.h>
#include "cantor/CantorVersion.h"

const char *cantorVersion ()
{ return PACKAGE_VERSION; }
