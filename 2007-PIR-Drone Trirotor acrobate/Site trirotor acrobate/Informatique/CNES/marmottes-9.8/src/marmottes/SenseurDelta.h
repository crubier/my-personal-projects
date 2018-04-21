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
//>       SenseurDelta.h
//
//$Resume
//       fichier d'en-tête de la classe SenseurDelta
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class SenseurDelta
//
//$Historique
//       $Log: SenseurDelta.h,v $
//       Revision 1.13  2002/12/11 17:13:59  marmottes
//       DM-ID 12 Ajout d'un constructeur par défaut (protégé) pour prévenir celui construit par le compilateur.
//
//       Revision 1.12  2002/12/02 17:05:00  marmottes
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.11  2002/01/17 09:39:05  marmottes
//       correction de spécifications throw (FA 0003)
//
//       Revision 1.10  2000/09/13 10:19:55  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.9  2000/03/30 17:01:23  luc
//       ajout du copyright CNES
//
//       Revision 1.8  1999/11/02 07:19:22  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.7  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines méthodes (correction des oublis
//       après le passage aux exceptions)
//
//       Revision 1.6  1999/08/06 13:32:19  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.5  1998/06/25 06:14:48  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.4  1998/04/26 18:25:32  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.3  1998/02/04 08:45:47  luc
//       mise en place d'un en-tête de classe au format AMIGAU
//
//       Revision 1.2  1997/09/23 09:26:27  luc
//       ajout d'une gestion des unités de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/08/20 09:51:21  luc
//       Initial revision
//
//$Version
//       $Id: SenseurDelta.h,v 1.13 2002/12/11 17:13:59 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurDelta_h
#define __marmottes_SenseurDelta_h

#include "marmottes/SenseurGeometrique.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurDelta
//
//$Resume
//       modélisation d'un pseudo-senseur de déclinaison
//
//$Description
//       modélisation d'un pseudo-senseur de déclinaison
//
//$Usage
//>     construction : 
//          à partir du nom, du repère satellite, de l'axe de calage
//          et de la précision, par copie
//          La classe étant abstraite, les constructeurs sont appelés
//          par les constructeurs des classes dérivées.
//>     utilisation  : 
//>       SenseurDelta& operator =         () 
//          affectation
//>       virtual void respecterMesures    () 
//          force le senseur à respecter les unités de mesures dans
//          ses sorties
//>       virtual void convertirMesures    () 
//          force le senseur à convertir les unités de mesures dans
//          ses sortie
//>       virtual void nouveauRepere       () 
//          tourne le senseur pour l'aligner sur le repère donné
//>       virtual int modeliseConsigne     () 
//          permet de stocker un modèle de la consigne que doit
//          respecter un senseur contrôlant l'attitude du satellite
//          dans l'état courant ATTENTION: dans cet état, l'attitude
//          ne doit pas être utilisée, elle ne sera initialisée
//          correctement qu'à la fin de la résolution ayant utilisé ce
//          modèle!
//>       virtual double mesure            () 
//          retourne la mesure que donnerait le senseur dans l'état donné
//>       virtual int controlable          () 
//          indique si le senseur serait capable de contrôler
//          l'attitude de l'état donné
//>       virtual Senseur* copie           () 
//          retourne une copie du senseur allouée en mémoire
//>       virtual typeGeom typeGeometrique () 
//          retourne le type de senseur géométrique (pseudoSenseur)
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurDelta : public SenseurGeometrique
{

public :

  // constructeurs
  SenseurDelta (const string& nom,
                const RotDBL& repere, const VecDBL& axeCalage,
                double precision, const VecDBL& observe)
   : SenseurGeometrique (nom, repere, axeCalage, radians (precision))
  { observe_ = (-repere) (observe); }
  SenseurDelta (const SenseurDelta& s)
    : SenseurGeometrique (s), observe_ (s.observe_)
  {}

  SenseurDelta& operator = (const SenseurDelta& s);

  // destructeur
  virtual ~SenseurDelta () {}

  virtual void respecterMesures ();
  virtual void convertirMesures ();

  virtual int      controlable     (const Etat& etat)
    throw (CantorErreurs, MarmottesErreurs)
                                   { return 1; }

  virtual Senseur* copie           () const
                                   { return new SenseurDelta (*this); }

  virtual typeGeom typeGeometrique () const { return pseudoSenseur; }

  // réorientation du senseur
  virtual void  nouveauRepere (const RotDBL& nouveau);

  // fonctions de résolution de l'attitude
  virtual void    modeliseConsigne (const Etat& etat, double valeur)
    throw (CantorErreurs, MarmottesErreurs);
  virtual double  mesure           (const Etat& etat)
    throw (MarmottesErreurs);

protected :

  // constructeur par defaut : ne doit JAMAIS être utilisé
  SenseurDelta () {}

private :

  VecDBL observe_;

};

#endif
