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
//>       ModeleCine.cpp
//
//$Resume
//       fichier d'implantation de la classe ModeleCine
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class ModeleCine          
//>         ModeleCine()            
//>         operator =()            
//>         prendConsignesEnCompte()
//>         miseAJourOmegaMax()     
//>         attitude()              
//
//$Historique
//       $Log: ModeleCine.cpp,v $
//       Revision 1.20  2003/02/04 16:30:30  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.19  2002/01/17 09:22:41  marmottes
//       (prendConsignesEnCompte): génération de l'erreur consignes_gyro_elevees (FA 0001)
//
//       Revision 1.18  2001/01/25 16:29:20  luc
//       modification de la valeur par défaut de la vitesse maximale de
//       rotation de 2 radians par seconde à 0.4 radian par seconde
//
//       Revision 1.17  2000/06/07 16:43:40  filaire
//       correction d'une erreur de signe
//
//       Revision 1.16  2000/06/07 14:08:04  luc
//       correction d'une erreur de valeur absolue
//
//       Revision 1.15  2000/03/30 17:01:19  luc
//       ajout du copyright CNES
//
//       Revision 1.14  2000/03/14 17:16:50  luc
//       correction d'une discontinuité du modèle pour les spins faibles mais
//       non nuls (introduction d'un développement limité du sinus cardinal)
//
//       Revision 1.13  1999/08/06 13:32:13  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.12  1999/07/29 12:15:17  filaire
//       Modification de la signature de la fonction prendConsignesEnCompte
//
//       Revision 1.12  1999/07/02 07:23:07  geraldine
//       modification de la signature de prendConsignesEnCompte
//       utilisation des exceptions
//
//       Revision 1.11  1998/10/05 15:24:56  luc
//       élimination de DBL_EPSILON pour éviter des problèmes de portabilité
//       contournement d'un bug du compilateur Sun
//
//       Revision 1.10  1998/08/04 06:59:10  luc
//       réduction de l'intervalle de validité de la variable libre
//       de [-1 ; +1] à [0 ; 1]
//
//       Revision 1.9  1998/06/24 19:58:40  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 1.8  1998/04/26 18:25:08  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.7  1998/02/19 16:19:02  luc
//       déplacement d'un constructeur inline dans le .cc
//       pour contourner un problème d'optimiseur avec g++ 2.8.0
//
//       Revision 1.6  1997/09/23 09:28:10  luc
//       utilisation de la consigne indépendante des unités de sortie
//       pour la modélisation interne
//
//       Revision 1.5  1997/08/20 08:27:17  luc
//       ajout d'un en-tête de fichier
//       utilisation du valeurConsigne () commun à tous les senseurs à la place
//       du omega () spécifique aux senseurs cinématiques qui disparaît
//
//       Revision 1.4  1997/04/27 19:35:50  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 1.3  1996/10/03 14:39:58  luc
//       correction du modèle des consignes en spin
//       
//       Revision 1.2  1995/01/27 16:59:56  mercator
//       propagation du spin dans tous les calculs depuis la modelisation
//       jusqu'a la sauvegarde de la solution finale dans l'etat
//       
//       Revision 1.1  1995/01/27 10:48:27  mercator
//       Initial revision
//
//$Version
//       $Id: ModeleCine.cpp,v 1.20 2003/02/04 16:30:30 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/ModeleCine.h"

#include "marmottes/SenseurCinematique.h"

ModeleCine::ModeleCine ()
 : omegaMax_ (0.4)
{}


ModeleCine& ModeleCine::operator = (const ModeleCine& m)
{ if (&m != this)    // protection contre x = x
  { u_        = m.u_;
    v_        = m.v_;
    thetaMax_ = m.thetaMax_;
    omegaMax_ = m.omegaMax_;
  }

  return *this;

}

void ModeleCine::prendConsignesEnCompte () throw (MarmottesErreurs)
{ SenseurCinematique* s1 = (SenseurCinematique *) senseur1 ();
  SenseurCinematique* s2 = (SenseurCinematique *) senseur2 ();

  double scal = s1->sensible () | s2->sensible ();
  double denominateur = 1.0 - scal * scal;
  if ((denominateur >= -1.0e-12) && (denominateur <= 1.0e-12))
    throw MarmottesErreurs (MarmottesErreurs::gyros_coaxiaux);

  u_ = VecDBLVD1 ((s1->sensible () * (s1->omega () - s2->omega () * scal)
                 + s2->sensible () * (s2->omega () - s1->omega () * scal)
                  ) / denominateur);
  v_ = VecDBLVD1 (s1->sensible () ^ s2->sensible ());

  double theta2V2 = omegaMax_ * omegaMax_ - (u_ | u_).f0 ();
  if (theta2V2 <= 0.0)
    throw MarmottesErreurs (MarmottesErreurs::consignes_gyro_elevees,
                            s1->nom ().c_str (), s2->nom ().c_str (),
                            degres (omegaMax_));
  thetaMax_ = sqrt (theta2V2 / (v_ | v_).f0 ());

}

void ModeleCine::miseAJourOmegaMax (double omega)
  throw (MarmottesErreurs)
{ 
  if (omega <= 0.0)
    throw MarmottesErreurs (MarmottesErreurs::omega_neg,
                            omega);

  omegaMax_ = omega;

}


void ModeleCine::attitude (const Etat& etatPrecedent, double date,
                           const ValeurDerivee1& t, int famille,
                           RotVD1* ptrAtt, VecVD1* ptrSpin) const
{ // modélisation de la rotation autour des gyros 1 et 2
  double dtSur2 = 43200.0 * (date - etatPrecedent.date ());

  ValeurDerivee1 theta   ((t * 2.0 - 1.0) * thetaMax_);
  *ptrSpin = u_ + v_ * theta;
  ValeurDerivee1 vitesse (ptrSpin->norme ());
  ValeurDerivee1 demiAngle = vitesse * dtSur2;

  ValeurDerivee1 sinCardinal;
  if (fabs (demiAngle.f0 ()) < 4.0e-4)
  { // si l'angle est trop petit, on utilise un développement limité
    // pour calculer sin (alpha) / alpha. En se limitant à l'ordre 4,
    // on obtient les erreurs relatives suivantes : 8.1e-25 sur
    // la valeur, 9.1e-17 pour la dérivée (pour des demi-angles
    // inférieurs à 4e-4)
    ValeurDerivee1 alpha2 = demiAngle * demiAngle;
    sinCardinal = (120.0 - alpha2 * (20.0 - alpha2)) / 120.0;
  }
  else
    sinCardinal = sin (demiAngle) / demiAngle;

  // rotation autour de l'axe de spin depuis la date de l'attitude précédente
  ValeurDerivee1 q0 = cos (demiAngle);
  VecVD1         q  = *ptrSpin * (sinCardinal * dtSur2);
  RotVD1         evolution (q0, q.x (), q.y (), q.z ());

  // calcul de l'attitude après évolution
  *ptrAtt = evolution (etatPrecedent.attitudeVD1 ());

}
