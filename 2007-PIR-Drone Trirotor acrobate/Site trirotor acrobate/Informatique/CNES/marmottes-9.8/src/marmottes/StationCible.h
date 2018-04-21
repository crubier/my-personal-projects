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
//>       StationCible.h
//
//$Resume
//       fichier d'en-tête de la classe StationCible
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class StationCible
//
//$Historique
//       $Log: StationCible.h,v $
//       Revision 1.7  2002/12/02 17:08:06  marmottes
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.6  2000/03/30 17:01:25  luc
//       ajout du copyright CNES
//
//       Revision 1.5  1999/11/02 07:19:23  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.4  1998/06/25 06:16:05  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.3  1998/06/08 15:55:08  luc
//       élimination des méthodes et attributs inutilisés
//
//       Revision 1.2  1998/04/26 18:25:44  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.1  1997/12/01 13:48:22  luc
//       Initial revision
//
//$Version
//       $Id: StationCible.h,v 1.7 2002/12/02 17:08:06 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_StationCible_h
#define __marmottes_StationCible_h

#include "cantor/Util.h"
#include "cantor/DeclDBL.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class StationCible
//
//$Resume
//       modélise une station sol de localisation
//
//$Description
//       Cette classe concrète donne accès à la position (angulaire ou
//       cartésienne), et aux mesures réalisées par la station, et aux
//       changement de repère topo vers Terre ou l'inverse
//
//$Usage
//>     construction : 
//          à partir des coordonnées (radians et mètres), et des données
//          météo, sans argument, par copie
//>     utilisation  : 
//>       StationCible& operator =    () 
//          affectation
//>       void correctionTropo        () 
//          calcule la correction troposphérique en site et
//          en distance, en fonction du site mesuré
//>       void correctionTropoInverse () 
//          calcule la correction troposphérique en site et
//          en distance, en fonction du site théorique
//>       double siteObservePt        () 
//          retourne le site d'observation d'un point
//>       double azimutPt             () 
//          retourne l'azimut d'observation d'un point
//>       double masque               () 
//          retourne le masque d'antennepour un azimut donné
//>       VecDBL position             () 
//          retourne le vecteur position en repère terrestre (km)
//>       double siteTheoriquePt      () 
//          retourne le site théorique (sans effet tropo) d'observation
//          d'un point
//>       int visiblePt               () 
//          indique si un point est visible (au dessus du masque d'antenne)
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class StationCible
{

public:

  // constructeurs
  StationCible ()
    : pression_ (1025.0), temperature_ (10.0), hygrometrie_ (10.0),
      nbPtsMasque_ (0), masqueAz_ (0), masqueSi_ (0)
  { initCoord (0, 0, 0); initMasque (0, 0, 0); }

  StationCible (double pression, double temperature, double hygrometrie,
                double longitude, double latitude, double altitude,
                int nbPtsMasque,
                const double masqueAz [], const double masqueSi [])
    : pression_ (pression), temperature_ (temperature),
      hygrometrie_ (hygrometrie),
      nbPtsMasque_ (0), masqueAz_ (0), masqueSi_ (0)
  { initCoord  (longitude, latitude, altitude);
    initMasque (nbPtsMasque, masqueAz, masqueSi);
  }

  // copie constructeur et affectation
  StationCible (const StationCible& s)
    : pression_ (s.pression_), temperature_ (s.temperature_),
      hygrometrie_ (s.hygrometrie_), altitude_ (s.altitude_),
      position_ (s.position_), nordEstNadir_ (s.nordEstNadir_),
      nbPtsMasque_ (0), masqueAz_ (0), masqueSi_ (0)
  { initMasque (s.nbPtsMasque_ - 2, s.masqueAz_ + 1, s.masqueSi_ + 1); }

  StationCible& operator = (const StationCible& s);

  ~StationCible () { if (nbPtsMasque_) delete [] masqueAz_; }

  // accès aux éléments internes
  VecDBL position  () const { return position_;  }

  // correction troposphérique (delta = mesuré - théorique)
  void   correctionTropo        (double siteMesure,
                                 double* dSite, double* dDist) const;
  void   correctionTropoInverse (double siteTheorique,
                                 double* dSite, double* dDist) const;

  // observation d'un point exprimé en repère terrestre
  double siteObservePt       (const VecDBL& p) const;
  double siteTheoriquePt     (const VecDBL& p) const
         { return (nordEstNadir_ (position_ - p)).delta (); }
  double azimutPt            (const VecDBL& p) const;

  // visibilité par rapport au masque antenne
  double masque     (double azimut) const;

  int    visiblePt  (const VecDBL& p) const
         { return siteObservePt  (p) >= masque (azimutPt  (p)); }

private :

  double       pression_;
  double       temperature_;
  double       hygrometrie_;
  double       altitude_;
  VecDBL       position_;
  RotDBL       nordEstNadir_;

  int          nbPtsMasque_;
  double      *masqueAz_;
  double      *masqueSi_;

  void          initCoord  (double longitude, double latitude,
                            double altitude);

  void          initMasque (int          nbPtsMasque,
                            const double masqueAz [],
                            const double masqueSi []);

};

#endif
