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
//>       ArcIterateur.h
//
//$Resume
//       fichier d'en-tête de la classe ArcIterateur
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class ArcIterateur
//
//$Historique
//       $Log: ArcIterateur.h,v $
//       Revision 1.8  2002/12/10 14:52:05  cantor
//       DM-ID 12 Ajout d'un destructeur et d'un constructeur pour prévenir ceux crées par le compilateur
//
//       Revision 1.7  2002/12/02 13:32:19  cantor
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.6  2000/08/09 14:36:43  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.5.4.1  2000/03/30 15:36:08  cantor
//       ajout du copyright CNES
//
//       Revision 1.5  1998/06/24 16:43:54  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.4  1998/04/26 15:23:41  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.3  1998/04/18 19:08:08  luc
//       élimination de la méthode estValide
//
//       Revision 1.2  1998/01/22 10:38:23  luc
//       amélioration de l'en-tête de classe
//
//       Revision 1.1  1997/07/08 10:14:34  luc
//       Initial revision
//
//
//$Version
//       $Id: ArcIterateur.h,v 1.8 2002/12/10 14:52:05 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_ArcIterateur_h
#define __cantor_ArcIterateur_h

#include "cantor/Arc.h"


///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ArcIterateur
//$Resume
//       itérateur sur la classe Arc
//
//$Description
//       itérateur sur un arc de cercle tracé sur la sphère
//       (parcours de l'arc point à point)
//
//$Usage
//>     construction : 
//          à partir d'une référence à un arc et d'une tolérance ou
//          par copie (l'etat est indéfini juste après la
//          construction, il faut appeler l'opérateur ())
//>     utilisation  : 
//>       ArcIterateur& operator = () 
//          affectation
//>       VecDBL point             () 
//          retourne une copie du point courant (si on n'a pas encore
//          appelé (), le point de début est renvoyé, et sera
//          EGALEMENT renvoyé après le premier appel, si on a fini le
//          parcours, le point de fin est renvoyé, alors qu'il a DEJA
//          été envoyé par les appels précédents).
//>       int nbSegments           () 
//          retourne le nombre de segments que l'itérateur décrit.
//>       int nbPoints             () 
//          retourne le nombre de points que l'itérateur décrit.
//>       void reinitialise        () 
//          remet l'itérateur en début d'arc.
//>       int suivant              () 
//          déplace le pointeur courant et retourne un indicateur de
//          validité.
//>       int operator()           () 
//          déplace le pointeur courant et retourne un indicateur de
//          validité.
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class ArcIterateur
{ 
  public :

  // constructeurs
  ArcIterateur (const Arc& a, double tolerance = 1.0e-4);
  ArcIterateur (const ArcIterateur& i)
    : arc_ (i.arc_), pas_ (i.pas_), indice_ (i.indice_),
      segments_ (i.segments_)
  {}

  ArcIterateur& operator = (const ArcIterateur& i);

  // destructeur
  ~ArcIterateur () {}

  // fonctions d'accès
  int    nbSegments   () const { return segments_;     }
  int    nbPoints     () const { return segments_ + 1; }

  // fonctions d'itération (on peut itérer segments_+1 fois)
  void   reinitialise () { indice_ = 0;                   }
  int    suivant      () { return indice_++ <= segments_; }
  int    operator ()  () { return suivant ();             }

  // calcul du point courant
  VecDBL point        () const;

  protected :

  // constructeur par défaut
  ArcIterateur () {}

  private :

  const Arc*        arc_;
  double            pas_;
  int               indice_;
  int               segments_;

};

#endif
