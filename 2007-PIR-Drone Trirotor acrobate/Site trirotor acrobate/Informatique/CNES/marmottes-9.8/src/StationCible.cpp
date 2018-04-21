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
//>       StationCible.cpp
//
//$Resume
//       fichier d'implantation de la classe StationCible
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class StationCible        
//>         operator =()            
//>         initCoord()             
//>         initMasque()            
//>         masque()                
//>         correctionTropo()       
//>         correctionTropoInverse()
//>         siteObservePt()         
//>         azimutPt()              
//
//$Historique
//       $Log: StationCible.cpp,v $
//       Revision 1.10  2004/06/21 14:52:28  marmottes
//       correction d'une erreur d'interpolation dans les masques d'antenne (FA-ID 34)
//
//       Revision 1.9  2003/02/04 16:42:27  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.8  2000/03/30 17:01:21  luc
//       ajout du copyright CNES
//
//       Revision 1.7  1999/10/05 11:58:04  luc
//       correction d'un bug lors de la copie de stations non initialisées
//       (masque comportant 0 point), le patch a été suggéré par Annie Gauzens.
//
//       Revision 1.6  1999/04/26 11:39:54  luc
//       remplacement de abs par fabs
//
//       Revision 1.5  1998/07/31 08:36:02  luc
//       remplacement de math.h par cantor/MathPi.h
//
//       Revision 1.4  1998/06/24 20:06:59  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 1.3  1998/06/08 15:54:58  luc
//       élimination des méthodes et attributs inutilisés
//
//       Revision 1.2  1998/04/26 18:25:45  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.1  1997/12/01 13:47:17  luc
//       Initial revision
//
//$Version
//       $Id: StationCible.cpp,v 1.10 2004/06/21 14:52:28 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/MathPi.h"
#include "cantor/Util.h"

#include "marmottes/StationCible.h"

StationCible& StationCible::operator = (const StationCible& s)
{ if (this != &s)      // protection contre x = x
  { pression_     = s.pression_;
    temperature_  = s.temperature_;
    hygrometrie_  = s.hygrometrie_;
    altitude_     = s.altitude_;
    position_     = s.position_;
    nordEstNadir_ = s.nordEstNadir_;

    initMasque (s.nbPtsMasque_ - 2, s.masqueAz_ + 1, s.masqueSi_ + 1);

  }

  return *this;

}

void StationCible::initCoord (double longitude, double latitude,
                              double altitude)
{ double sinLat = sin (latitude);
  double cosLat = cos (latitude);
  double sinLon = sin (longitude);
  double cosLon = cos (longitude);

  altitude_ = altitude;

  // prise en compte de l'aplatissement terrestre
  const double aplatissement = 1.0 / 298.257;
  const double rayonTerre    = 6378.137;
  double ef2                 = (2.0 - aplatissement) * aplatissement;
  double coeff               = rayonTerre / sqrt (1.0 - ef2 * sinLat * sinLat);

  // initialisation des coordonnées cartésiennes
  double x  = (coeff             + altitude * 1.0e-3) * cosLat * cosLon;
  double y  = (coeff             + altitude * 1.0e-3) * cosLat * sinLon;
  double z  = (coeff * (1 - ef2) + altitude * 1.0e-3) * sinLat;
  position_ = VecDBL (x, y, z);

  // initialisation du repère (Nord, Est, Nadir)
  RotDBL rotLongi (VecDBL (0.0, 0.0, 1.0), -longitude,        1.0);
  RotDBL rotLati  (VecDBL (0.0, 1.0, 0.0), M_PI_2 + latitude, 1.0);
  nordEstNadir_ = rotLati (rotLongi);

}

void StationCible::initMasque (int          nbPtsMasque,
                               const double masqueAz [],
                               const double masqueSi [])
{ // initialisation des masques d'antenne sol
  int i, j;

  if (nbPtsMasque_)
  { // un masque existe déjà, il faut le supprimer
    nbPtsMasque_ = 0;
    delete [] masqueAz_; // le tableau en site est détruit dans la foulée
    masqueAz_ = 0;
    masqueSi_ = 0;
  }

  if (nbPtsMasque <= 0)
    return;

  // allocation des tables (en un seul appel)
  nbPtsMasque_ = nbPtsMasque + 2;
  masqueAz_    = new double [2 * nbPtsMasque_];
  masqueSi_    = masqueAz_ + nbPtsMasque_;

  for (i = 0; i < nbPtsMasque_ - 2; i++)
  { // copie des tableaux (en recalant les angles entre 0 et 2PI)
    masqueAz_ [i + 1] = recaleAngle (masqueAz [i], M_PI);
    masqueSi_ [i + 1] = masqueSi [i];
  }

  // mise en ordre du masque (tri par insertion)
  double sauveAz, sauveSi;
  for (j = 2; j < nbPtsMasque_ - 1; j++)
    if (masqueAz_ [j] < masqueAz_ [j - 1])
    { // il faut insérer masqueAz_ [j] plus près du début
      sauveAz = masqueAz_ [j];
      sauveSi = masqueSi_ [j];
      i     = j - 1;
      while ((i >= 1) && (sauveAz < masqueAz_ [i]))
      { masqueAz_ [i + 1] = masqueAz_ [i];
        masqueSi_ [i + 1] = masqueSi_ [i];
        i--;
      }
      masqueAz_ [i + 1] = sauveAz;
      masqueSi_ [i + 1] = sauveSi;
    }

  // ajout de deux points autour de l'intervalle [0 ; 2PI] pour l'interpolation
  masqueAz_ [0]                = masqueAz_ [nbPtsMasque_ - 2] - M_PI - M_PI;
  masqueSi_ [0]                = masqueSi_ [nbPtsMasque_ - 2];
  masqueAz_ [nbPtsMasque_ - 1] = masqueAz_ [1] + M_PI + M_PI;
  masqueSi_ [nbPtsMasque_ - 1] = masqueSi_ [1];

}

double StationCible::masque (double azimut) const
{ // interpolation du masque d'antenne sol
  if (nbPtsMasque_ == 0)
    return 0.0;

  // recherche de l'intervalle encadrant l'azimut désiré
  azimut = recaleAngle (azimut, M_PI);
  int i = 0;
  while ((i < nbPtsMasque_ - 2) && (masqueAz_ [i + 1] < azimut))
    i++;

  // interpolation
  return (masqueSi_ [i]   * (masqueAz_ [i+1] - azimut)
        + masqueSi_ [i+1] * (azimut - masqueAz_ [i])
         ) / (masqueAz_ [i+1] - masqueAz_ [i]);

}


void StationCible::correctionTropo (double siteMesure,
                                    double *dSite, double *dDist) const
{ // calcul de l'effet troposphérique
  if (siteMesure < 0.0)
  { // pas d'effet troposphérique sous l'horizon
    *dSite = 0.0;
    *dDist = 0.0;
    return;
  }

  const double tk  = 273.16;
  const double eps = 0.0017;

  double tAbs = temperature_ + tk;

  // calcul de la pression de vapeur saturante ew 
  // (formule approchée de Goff et Gratch)
  double xlew = 10.57974   * (1.0 - tk / tAbs)
              - 5.028      * log10 (tAbs / tk)
              + 1.50475e-4 * (1.0 - pow (10.0, -8.2969 * (tAbs / tk - 1.0)))
              + 0.42873e-3 * (pow (10.0, 4.76955 * (1.0 - tk / tAbs)) - 1.0)
              + 0.78614;
  double ew = pow (10.0, xlew);

  // pression partielle de vapeur d'eau
  double pve = ew * hygrometrie_ / 100.0;

  // coindice à l'altitude du point de mesure
  double h0   = altitude_ * 0.001;
  double xnh0 = 77.6 * (pression_ + 4810.0 * pve / tAbs) / tAbs;

  // erreur de distance à la verticale
  double fnh0 = 3.0 * xnh0 + 1437.0;
  if (xnh0 >= 370.0)
    fnh0 += (xnh0 - 370.0) * (xnh0 - 370.0) / 10.0;
  double dlv  = fnh0 - h0 * xnh0 / 2.0;

  // correction en site et en distance
  double sinSite = sin (siteMesure);
  double cosSite = cos (siteMesure);
  double denom  = sqrt (sinSite * sinSite + eps * cosSite * cosSite);

  *dDist = dlv  * 1.0e-6 / denom;
  *dSite = xnh0 * 1.0e-6 * (1.0 - eps / 2.0) * cos (siteMesure) / denom;

}


void StationCible::correctionTropoInverse (double siteTheorique,
                                           double* dSite, double* dDdist) const
{ // calcul du site corrigé de l'effet troposphérique si le site 
  // théorique est supérieur à -0.43 degrés (-0.0075 rad)
  if (siteTheorique <= -0.0075)
  { // pas d'effet troposphérique sous l'horizon
    *dSite  = 0.0;
    *dDdist = 0.0;
  }
  else
  { // calcul de l'inverse de l'effet troposphérique
    double siteMesure = siteTheorique;
    double dismes     = 0.0;

    while (1)
    { // calcul itératif (converge en une ou deux itérations)
      correctionTropo (siteMesure, dSite, dDdist);

      // test de convergence (à 0.0057 degrés et 1 mètre près)
      double newsit = siteTheorique + *dSite;
      if ((fabs (newsit - siteMesure) < 1.0e-4)
          &&
          (fabs (*dDdist - dismes) < 1.0e-3))
        return;

      siteMesure = newsit;
      dismes     = *dDdist;

    }

  }

}

double StationCible::siteObservePt (const VecDBL& p) const
{ double siteTheorique = siteTheoriquePt (p);

  double dSite;
  double dDist;
  correctionTropoInverse (siteTheorique, &dSite, &dDist);

  return siteTheorique + dSite;

}

double StationCible::azimutPt (const VecDBL& p) const
{ // conversion du point observé en repère (Nord, Est, Nadir)
  VecDBL observe = nordEstNadir_ (p - position_);

  // calcul de l'azimut
  double az = observe.alpha ();
  return (az < 0.0) ? M_PI + M_PI + az : az;

}
