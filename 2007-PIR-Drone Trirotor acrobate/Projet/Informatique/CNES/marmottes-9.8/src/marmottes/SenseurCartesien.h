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
//>       SenseurCartesien.h
//
//$Resume
//       fichier d'en-tête de la classe SenseurCartesien
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class SenseurCartesien
//
//$Historique
//       $Log: SenseurCartesien.h,v $
//       Revision 1.14  2003/02/27 16:16:04  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.13  2002/12/11 17:12:57  marmottes
//       DM-ID 12 Ajout d'un constructeur par défaut (protégé) pour prévenir celui construit par le compilateur.
//
//       Revision 1.12  2002/01/17 09:38:03  marmottes
//       correction de spécifications throw (FA 0003)
//
//       Revision 1.11  2001/07/17 15:30:32  luc
//       ajout du vecteur observé pour la cible vitesse-sol-apparente
//       lancement d'une exception par le constructeur
//
//       Revision 1.10  2001/03/26 11:12:26  luc
//        mise à jour résultant de la modélisation des inhibitions dans la
//       classe SenseurOptique
//
//       Revision 1.9  2000/09/13 10:09:02  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.8  2000/03/30 17:01:23  luc
//       ajout du copyright CNES
//
//       Revision 1.7  1999/11/02 07:19:22  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.6  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines méthodes (correction des oublis
//       après le passage aux exceptions)
//
//       Revision 1.5  1999/08/06 13:32:19  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.4  1998/06/25 06:14:10  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.3  1997/11/27 07:07:50  luc
//       remplacement de la notion d'astre par la notion de cible
//       ajout du paramétrage des cibles de type stations sol
//
//       Revision 1.2  1997/09/23 09:25:57  luc
//       ajout d'une gestion des unités de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/09/15 13:48:39  luc
//       Initial revision
//
//$Version
//       $Id: SenseurCartesien.h,v 1.14 2003/02/27 16:16:04 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurCartesien_h
#define __marmottes_SenseurCartesien_h

#include "marmottes/SenseurVecteur.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurCartesien
//
//$Resume
//       modélisation d'un senseur mesurant une coordonnée cartésienne
//
//$Description
//       Cette classe concrète modélise un senseur mesurant la projection
//       de la cible sur un axe de référence.
//
//$Usage
//>     construction : 
//          à partir du nom, du repère satellite, de l'axe de calage
//          et de la précision, par copie
//          La classe étant abstraite, les constructeurs sont appelés
//          par les constructeurs des classes dérivées.
//>     utilisation  : 
//>       SenseurCartesien& operator =  () 
//          affectation
//>       virtual void respecterMesures () 
//          force le senseur à respecter les unités de mesures dans
//          ses sorties
//>       virtual void convertirMesures () 
//          force le senseur à convertir les unités de mesures dans
//          ses sortie
//>       virtual int modeliseConsigne  () 
//          permet de stocker un modèle de la consigne que doit
//          respecter un senseur contrôlant l'attitude du satellite
//          dans l'état courant ATTENTION: dans cet état, l'attitude
//          ne doit pas être utilisée, elle ne sera initialisée
//          correctement qu'à la fin de la résolution ayant utilisé ce
//          modèle!
//>       virtual double mesure         () 
//          retourne la mesure que donnerait le senseur dans l'état donné
//>       virtual Senseur* copie        () 
//          retourne une copie du senseur allouée en mémoire
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


class SenseurCartesien : public SenseurVecteur
{ public :

  // constructeurs
  SenseurCartesien (const string& nom, const RotDBL& repere,
                    const VecDBL& axeCalage, double precision,
                    codeCible code, const StationCible *ptrStation,
                    const VecDBL& observe,
                    Parcelle* ptrChampDeVue,
                    Parcelle *ptrChampInhibitionSoleil,
                    Parcelle *ptrChampInhibitionLune,
                    Parcelle *ptrChampInhibitionCentral,
                    double margeEclipseSoleil, double margeEclipseLune,
                    double seuilPhaseLune, const VecDBL& reference)
    throw (MarmottesErreurs)
    : SenseurVecteur (nom, repere, axeCalage,
                      degres (precision), // <-- pour compenser la conversion
                                          // inverse de la classe de base :-(
                      code, ptrStation, observe, ptrChampDeVue,
                      ptrChampInhibitionSoleil, ptrChampInhibitionLune,
                      ptrChampInhibitionCentral,
                      margeEclipseSoleil, margeEclipseLune, seuilPhaseLune,
                      reference)
  {}
  SenseurCartesien (const SenseurCartesien& s)
    : SenseurVecteur (s)
  {}

  SenseurCartesien& operator = (const SenseurCartesien& s);

  // destructeur
  virtual ~SenseurCartesien () {}

  virtual void respecterMesures ();
  virtual void convertirMesures ();

  virtual Senseur* copie () const { return new SenseurCartesien (*this); }

  // fonctions de résolution de l'attitude
  virtual void    modeliseConsigne (const Etat& etat, double valeur)
    throw (CantorErreurs, MarmottesErreurs);
  virtual double  mesure           (const Etat& etat)
    throw (MarmottesErreurs);

protected :

  // constructeur par defaut : ne doit JAMAIS être utilisé
  SenseurCartesien () {}

};

#endif
