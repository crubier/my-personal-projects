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
//>       ParcelleElementaire.h
//
//$Resume
//       fichier d'en-tête de la classe ParcelleElementaire
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class ParcelleElementaire
//
//$Historique
//       $Log: ParcelleElementaire.h,v $
//       Revision 1.13  2002/12/11 17:08:23  marmottes
//       DM-ID 12 Ajout d'un constructeur par défaut (protégé) pour prévenir celui construit par le compilateur.
//
//       Revision 1.12  2002/04/17 16:14:59  marmottes
//       Corrections de throw
//
//       Revision 1.11  2002/01/17 09:38:03  marmottes
//       correction de spécifications throw (FA 0003)
//
//       Revision 1.10  2001/06/22 07:06:36  luc
//       utilisation du type bool pour les prédicats
//       utilisation d'un axe et d'un angle pour spécifier l'intégration le
//       long d'une rotation
//
//       Revision 1.9  2001/04/04 12:19:58  luc
//       ajout de la méthode ecartFrontiere
//
//       Revision 1.8  2000/11/13 09:02:05  luc
//       remplacement de la classe Champ par la classe Field
//
//       Revision 1.7.2.1  2000/07/07 11:26:46  luc
//       remplacement de TypeFoncConstChamp par Champ::TypeFoncConstChamp
//       dans les signatures des différentes méthodes applique
//
//       Revision 1.7  2000/03/30 17:01:23  luc
//       ajout du copyright CNES
//
//       Revision 1.6  1999/11/02 07:19:21  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.5  1998/06/25 06:05:40  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.4  1998/06/09 20:15:40  luc
//       suppression d'une directive de dérivation virtual inutile
//
//       Revision 1.3  1998/04/26 18:25:16  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.2  1998/02/04 08:37:53  luc
//       mise en place d'un en-tête de classe au format AMIGAU
//
//       Revision 1.1  1997/08/20 09:37:47  luc
//       Initial revision
//
//$Version
//       $Id: ParcelleElementaire.h,v 1.13 2002/12/11 17:08:23 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_ParcelleElementaire_h
#define __marmottes_ParcelleElementaire_h

#include "marmottes/Parcelle.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ParcelleElementaire
//
//$Resume
//       modélisation de parcelles simples sur la sphère unité
//
//$Description
//       modélisation de la parcelle la plus simple sur la sphère
//       unité : un champ sans comportement particulier au
//       regard des visibilités d'horizon
//
//$Usage
//>     construction : 
//          à partir d'un champ de la sphère unité
//>     utilisation  : 
//>       virtual Parcelle* copie       () 
//          retourne une copie de la parcelle allouée en mémoire
//>       virtual bool inclus           () 
//          teste si un vecteur est dans la parcelle
//>       virtual double ecartFrontiere () 
//          calcule la distance d'un point à la frontière
//>       virtual bool visible          () 
//          teste si un cône est visible à travers la parcelle
//>       virtual Secteurs visible      () 
//          filtre les parties visibles de secteurs à traver la parcelle
//>       virtual void appliqueRotation () 
//          remplace l'instance par son image à travers une rotation
//>       virtual void integreRotation  () 
//          remplace l'instance par la trainée qu'elle laisse lorsqu'on
//          la déplace par rotation
//>       virtual void appliqueMarge    () 
//          déforme l'instance par ajout d'une marge
//          (soustraction si m < 0)
//>       virtual void applique         () 
//          applique la fonction f à tous les champs de la parcelle, en
//          lui passant le pointeur anonyme d
//>       virtual void rechercheChamp   () 
//          recherche dans la structure récursive un champ différent de
//          celui dont l'adresse est fournie
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class ParcelleElementaire : public Parcelle
{

public:

  // constructeurs
  ParcelleElementaire  (const Field& f) : f_ (f) {}
  virtual Parcelle* copie        ()                                 const;

  // destructeur
 ~ParcelleElementaire  () {}

  // fonctions de test
  virtual bool     inclus         (const VecDBL& u)   const;
  virtual double   ecartFrontiere (const VecDBL& u)   const;
  virtual bool     visible        (const Cone& c)     const
    throw (CantorErreurs);
  virtual Secteurs visible        (const Secteurs& s) const
    throw (CantorErreurs);

  // fonctions de modification de l'instance
  virtual void appliqueRotation  (const RotDBL& r);
  virtual void integreRotation   (const VecDBL& axe, double angle)
    throw (CantorErreurs, MarmottesErreurs);
  virtual void appliqueMarge     (double m)
    throw (CantorErreurs, MarmottesErreurs);
  virtual void applique          (Field::TypeFuncConstField *f, void *d) const;
  virtual void applique          (Field::TypeFuncField      *f, void *d);

  // fonctions de parcours de la frontière d'un champ
  virtual void rechercheChamp (Field **adressePtr);

private:

  // constructeur par défaut : il ne doit JAMAIS être appellé
  // car il n'y a pas de sens a construire une parcelle
  // sans arguments
  ParcelleElementaire () {}
  
  // la copie n'est autorisée que par pointeur et allocation (méthode copie ())
  // le constructeur par copie et l'affectation sont donc privés
  ParcelleElementaire (const ParcelleElementaire& p) {}
  ParcelleElementaire& operator = (const ParcelleElementaire& p)
  { return *this; }

  Field f_;

};

#endif
