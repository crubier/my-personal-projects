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
//>       SenseurGyroInteg.h
//
//$Resume
//       fichier d'en-tête de la classe SenseurGyroInteg
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class SenseurGyroInteg
//
//$Historique
//       $Log: SenseurGyroInteg.h,v $
//       Revision 1.10  2003/10/08 09:40:09  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 1.9  2002/12/11 17:18:58  marmottes
//       DM-ID 12 Ajout d'un constructeur par défaut (protégé) pour prévenir celui construit par le compilateur.
//
//       Revision 1.8  2002/01/17 09:39:05  marmottes
//       correction de spécifications throw (FA 0003)
//
//       Revision 1.7  2000/10/02 12:22:17  luc
//       remplacement d'attributs entiers en booléens
//
//       Revision 1.6  2000/09/13 10:41:08  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.5  2000/03/30 17:01:24  luc
//       ajout du copyright CNES
//
//       Revision 1.4  1999/11/02 07:19:23  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.3  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines méthodes (correction des oublis
//       après le passage aux exceptions)
//
//       Revision 1.2  1999/08/06 13:32:20  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.1  1998/07/15 12:33:48  luc
//       support pour les gyros integrateurs
//
//$Version
//       $Id: SenseurGyroInteg.h,v 1.10 2003/10/08 09:40:09 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurGyroInteg_h
#define __marmottes_SenseurGyroInteg_h

#include "cantor/DeclDBLVD1.h"

#include "marmottes/Etat.h"
#include "marmottes/SenseurCinematique.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurGyroInteg
//
//$Resume
//       modélisation d'un gyroscope intégrateur
//
//$Description
//       modélisation d'un senseur cinématique
//
//$Usage
//>     construction : 
//          à partir du nom, du repère satellite, de l'axe de calage
//          et de la précision, par copie
//          La classe étant abstraite, les constructeurs sont appelés
//          par les constructeurs des classes dérivées.
//>     utilisation  : 
//>       SenseurGyroInteg& operator =     () 
//          affectation
//>       virtual int modeliseConsigne     () 
//          permet de stocker un modèle de la consigne que doit
//          respecter un senseur contrôlant l'attitude du satellite
//          dans l'état courant ATTENTION: dans cet état, l'attitude
//          ne doit pas être utilisée, elle ne sera initialisée
//          correctement qu'à la fin de la résolution ayant utilisé ce
//          modèle!
//>       virtual double mesure            () 
//          retourne la mesure que donnerait le senseur dans l'état donné
//>       virtual ValeurDerivee1 foncEcart () 
//          calcule la fonction d'écart du senseur par rapport à sa
//          consigne à la date donnée et dans l'attitude donnée en
//          tenant compte de l'état précédent.
//>       virtual int initialiseGyro       () 
//          initialise l'angle d'un gyro intégrateur
//>       virtual int prendEtatEnCompte    () 
//          prise en compte d'un état de résolution
//          (pour les gyros intégrateurs)
//>       virtual Senseur* copie           () 
//          retourne une copie du senseur allouée en mémoire
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurGyroInteg : public SenseurCinematique
{
public :

  // constructeurs
  SenseurGyroInteg (const string& nom, const RotDBL& repere,
                    const VecDBL& axeCalage, double precision,
                    const VecDBL& axeSensible)
    : SenseurCinematique (nom, repere, axeCalage, precision, axeSensible),
      t0_ (0.0), alpha0_ (0.0), initialise_ (false)
  {}
  SenseurGyroInteg (const SenseurGyroInteg& s)
    : SenseurCinematique (s),
      t0_ (s.t0_), alpha0_ (s.alpha0_), initialise_ (s.initialise_)
  {}

  SenseurGyroInteg& operator = (const SenseurGyroInteg& s);

  // destructeur
  virtual ~SenseurGyroInteg () {}

  virtual Senseur* copie () const { return new SenseurGyroInteg (*this); }

  // fonctions de resolution de l'attitude
  virtual void           modeliseConsigne (const Etat& etat, double valeur)
    throw (CantorErreurs, MarmottesErreurs);

  virtual double         mesure           (const Etat& etat)
    throw (MarmottesErreurs);

  virtual ValeurDerivee1 foncEcart        (const Etat& etatPrecedent,
                                           const Etat& etatResolution,
                                           const RotVD1& attitude,
                                           const VecVD1& spin);

  // initialisation d'un gyro intégrateur
  virtual void initialiseGyro (double date, double angle)
    throw (MarmottesErreurs);

  // prise en compte des états après résolution d'attitude
  virtual void prendEtatEnCompte (const Etat& etat);

protected :

  // constructeur par defaut : ne doit JAMAIS être utilisé
  SenseurGyroInteg () {}

private :

  double t0_;
  double alpha0_;
  bool   initialise_;

};

#endif
