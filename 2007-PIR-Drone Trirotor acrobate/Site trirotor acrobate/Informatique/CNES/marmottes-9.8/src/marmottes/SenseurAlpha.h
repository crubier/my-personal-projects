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
//>       SenseurAlpha.h
//
//$Resume
//       fichier d'en-tête de la classe SenseurAlpha
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class SenseurAlpha
//
//$Historique
//       $Log: SenseurAlpha.h,v $
//       Revision 1.16  2003/10/08 09:40:09  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 1.15  2002/12/11 17:11:50  marmottes
//       DM-ID 12 Ajout d'un constructeur par défaut (protégé) pour prévenir celui construit par le compilateur.
//
//       Revision 1.14  2002/12/02 17:03:58  marmottes
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.13  2002/01/17 09:38:03  marmottes
//       correction de spécifications throw (FA 0003)
//
//       Revision 1.12  2000/09/13 10:04:11  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.11  2000/03/30 17:01:23  luc
//       ajout du copyright CNES
//
//       Revision 1.10  1999/11/02 07:19:22  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.9  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines méthodes (correction des oublis
//       après le passage aux exceptions)
//
//       Revision 1.8  1999/08/06 13:32:18  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.7  1998/09/14 11:53:36  luc
//       élimination de caractères de contrôle parasites
//       devant certains accents de l'en-tête
//
//       Revision 1.6  1998/06/25 06:13:06  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.5  1998/04/26 18:25:27  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.4  1998/02/06 17:33:32  luc
//       ajout d'une spécialisation de foncEcart de sorte que
//       la valeur produite soit bien un écart entre mesure et consigne
//       (dans le cas contraire, des problèmes se posent pour des
//       pseudo-senseurs utilisant une cible très proche de l'axe sensible)
//
//       Revision 1.3  1998/02/04 08:42:38  luc
//       mise en place d'un en-tête de classe au format AMIGAU
//
//       Revision 1.2  1997/09/23 09:25:40  luc
//       ajout d'une gestion des unités de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/08/20 09:50:16  luc
//       Initial revision
//
//$Version
//       $Id: SenseurAlpha.h,v 1.16 2003/10/08 09:40:09 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurAlpha_h
#define __marmottes_SenseurAlpha_h

#include "marmottes/SenseurGeometrique.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurAlpha
//
//$Resume
//       modélisation d'un pseudo-senseur d'ascension droite
//
//$Description
//       modélisation d'un pseudo-senseur d'ascension droite
//
//$Usage
//>     construction : 
//          à partir du nom, du repère satellite, de l'axe de calage
//          et de la précision, par copie
//          La classe étant abstraite, les constructeurs sont appelés
//          par les constructeurs des classes dérivées.
//>     utilisation  : 
//>       SenseurAlpha& operator =         () 
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
//>       virtual ValeurDerivee1 foncEcart () 
//          calcule la fonction d'écart du senseur par rapport à sa
//          consigne à la date donnée et dans l'attitude donnée en
//          tenant compte de l'état précédent.
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

class SenseurAlpha : public SenseurGeometrique
{ 

public :

  // constructeurs
  SenseurAlpha (const string& nom,
                const RotDBL& repere, const VecDBL& axeCalage,
                double precision, const VecDBL& observe);
  SenseurAlpha (const SenseurAlpha& s)
    : SenseurGeometrique (s),
      observe_ (s.observe_), alphaConsigne_ (s.alphaConsigne_)
  {}

  SenseurAlpha& operator = (const SenseurAlpha& s);

  // destructeur
  virtual ~SenseurAlpha () {}

  virtual void respecterMesures ();
  virtual void convertirMesures ();

  virtual int      controlable     (const Etat& etat)
    throw (MarmottesErreurs)
                                   { return 1; }

  virtual Senseur* copie           () const
                                   { return new SenseurAlpha (*this); }

  virtual typeGeom typeGeometrique () const { return pseudoSenseur; }

  // réorientation du senseur
  virtual void  nouveauRepere (const RotDBL& nouveau);

  // fonctions de résolution de l'attitude
  virtual void    modeliseConsigne (const Etat& etat, double valeur)
    throw (CantorErreurs, MarmottesErreurs);
  virtual double  mesure           (const Etat& etat)
    throw (MarmottesErreurs);
  virtual ValeurDerivee1 foncEcart (const Etat& etatPrecedent,
                                    const Etat& etatResolution,
                                    const RotVD1& attitude,
                                    const VecVD1& spin
                                   );

protected :

  // constructeur par defaut : ne doit JAMAIS être utilisé
  SenseurAlpha () {}

private :

  VecDBL observe_;
  double alphaConsigne_;

  void    initialiseCible (double alpha);

};

#endif
