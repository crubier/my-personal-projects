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
//>       ResolveurAttitude.h
//
//$Resume
//       fichier d'en-tête de la classe ResolveurAttitude
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class ResolveurAttitude
//
//$Historique
//       $Log: ResolveurAttitude.h,v $
//       Revision 2.18  2003/10/08 09:40:09  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 2.17  2002/12/02 17:03:41  marmottes
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 2.16  2002/01/17 09:38:03  marmottes
//       correction de spécifications throw (FA 0003)
//
//       Revision 2.15  2001/06/06 07:48:14  luc
//       simplification des signatures à la suite de l'élimination d'un
//       paramètre inutilisé dans Cantor
//
//       Revision 2.14  2000/03/30 17:01:23  luc
//       ajout du copyright CNES
//
//       Revision 2.13  1999/11/02 07:19:22  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 2.12  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines méthodes (correction des oublis
//       après le passage aux exceptions)
//
//       Revision 2.11  1999/08/06 13:32:18  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 2.10  1998/06/25 06:06:13  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 2.9  1998/04/26 18:25:19  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.8  1998/02/19 16:21:51  luc
//       déplacement d'un constructeur inline dans le .cc
//       pour contourner un problème d'optimiseur avec g++ 2.8.0
//
//       Revision 2.7  1998/02/04 08:42:03  luc
//       mise en place d'un en-tête de classe au format AMIGAU
//
//       Revision 2.6  1998/02/04 08:12:33  luc
//       création d'une méthode séparée pour ajouter une solution
//       à l'ensemble géré par l'instance
//
//       Revision 2.5  1997/09/15 09:46:02  luc
//       correction d'un nom de fichier inclus
//
//       Revision 2.4  1997/08/20 09:48:23  luc
//       ajout d'un en-tête de fichier
//       retour d'une erreur lors de la réinitialisation des senseurs
//       retour d'une erreur lors du filtrage des solutions parasites
//       élimination de la méthode premiere (), la méthode selection ()
//       couvrant tous les besoins
//
//       Revision 2.3  1997/04/27 19:33:34  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 2.2  1996/09/11 17:42:17  luc
//       ajout d'une possibilité de n'initialiser que deux consignes
//       (pour Marmottes::deuxConsignes)
//       
//       Revision 2.1  1996/07/31 17:19:08  luc
//       abandon des tools.h++ (Rogue Wave)
//       
//       Revision 1.1  1995/02/02 13:03:24  mercator
//       Initial revision
//
//$Version
//       $Id: ResolveurAttitude.h,v 2.18 2003/10/08 09:40:09 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_ResolveurAttitude_h
#define __marmottes_ResolveurAttitude_h

#include "cantor/DeclDBL.h"

#include "marmottes/Senseur.h"
#include "marmottes/Modele.h"
#include "marmottes/ModeleGeom.h"
#include "marmottes/ModeleCine.h"
#include "marmottes/Etat.h"
#include "marmottes/SpinAtt.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ResolveurAttitude
//
//$Resume
//       résolution numérique d'un modèle d'attitude à un degré de liberté
//
//$Description
//       gestion des modèles de résolution d'attitude selon les types de senseurs
//
//$Usage
//>     construction : 
//          sans argument, par copie
//>     utilisation  : 
//>       ResolveurAttitude& operator = () 
//          affectation
//>       void reinitialise             () 
//          modifie les senseurs qui seront utilisés pour le contrôle
//          de l'attitude lors des résolutions suivantes
//>       void modeliseConsignes        () 
//          initialise les états et consignes pour une résolution
//>       void miseAJourConvergence     () 
//          modifie le critère de convergence de la résolution
//>       void miseAJourDichotomie      () 
//          modifie le nombre de tranches de dichotomie de
//          la séparation des extremums
//>       void deuxConsignes            () 
//          retourne une solution respectant uniquement les deux
//          premières consignes
//>       void trouveTout               () 
//          recherche de toutes les solutions mathématiques respectant
//          les trois consignes d'attitudes courantes
//>       void elimineExcedentaires     () 
//          élimine les artefacts mathématiques et les solutions
//          non contrôlables
//>       const SpinAtt& selection      () 
//          retourne la meilleure solution au sens du plus faible
//          écart par rapport au mouvement précédent
//>       Senseur* s1                   () 
//          retourne un pointeur sur le premier senseur de contrôle
//>       Senseur* s2                   () 
//          retourne un pointeur sur le deuxième senseur de contrôle
//>       Senseur* s3                   () 
//          retourne un pointeur sur le troisième senseur de contrôle
//>       int miseAJourOmegaMax         () 
//           mise à jour du paramètre de vitesse maximale de rotation
//           dans les modèles cinématiques
//>       int nombreSolutions           () 
//           retourne le nombre de solutions mémorisées
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class ResolveurAttitude
{

public :

  // constructeurs
  ResolveurAttitude ();
  ResolveurAttitude (const ResolveurAttitude& r);

  ResolveurAttitude& operator = (const ResolveurAttitude& r);

 ~ResolveurAttitude () { if (tailleTable_) delete [] solutions_; }

  // fonctions d'accès aux éléments internes
  Senseur*       s1       () const { return senseursConsigne_ [0]; }
  Senseur*       s2       () const { return senseursConsigne_ [1]; }
  Senseur*       s3       () const { return senseursConsigne_ [2]; }

  // fonctions de préparation
  void reinitialise         (Senseur* s1, Senseur* s2, Senseur* s3)
    throw (MarmottesErreurs);
  void modeliseConsignes    (const Etat& etatPrecedent,
                             const Etat& etatResolution,
                             double m1, double m2)
    throw (CantorErreurs, MarmottesErreurs);
  void modeliseConsignes    (const Etat& etatPrecedent,
                             const Etat& etatResolution,
                             double m1, double m2, double m3)
    throw (CantorErreurs, MarmottesErreurs);

  void miseAJourOmegaMax    (double omega)
    throw (MarmottesErreurs)
                  { modeleCine_.miseAJourOmegaMax (omega); }
  void miseAJourConvergence (double seuil)
    throw (MarmottesErreurs);
  void miseAJourDichotomie  (int    tranches) 
    throw (MarmottesErreurs);

  // fonctions de résolution
  void    deuxConsignes        (SpinAtt* ptrSpinAtt)
    throw (CantorErreurs, MarmottesErreurs);
  void    trouveTout           ()
    throw (MarmottesErreurs);
  void    elimineExcedentaires ()
    throw (CantorErreurs, MarmottesErreurs);
  int     nombreSolutions      () const { return nbSol_; }
  const SpinAtt& selection     () const;

private :

  Senseur*             senseursConsigne_ [3];
  Senseur*             sA1_;
  Senseur*             sA2_;
  Senseur*             sB_;
  Modele*              modeleCourant_;
  ModeleGeom           modeleGeom_;
  ModeleCine           modeleCine_;
  Etat                 etatPrecedent_;
  Etat                 etatResolution_;
  int                  famille_;
  int                  tailleTable_;
  int                  nbSol_;
  SpinAtt             *solutions_;
  double               seuil_;
  int                  tranches_;

  void  ajouteSolution (double t);

  ValeurDerivee1        f (double t);
  static ValeurDerivee1 f (double t, void* arg);

};

#endif
