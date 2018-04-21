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
//>       Etat.cpp
//$Resume
//       fichier d'implantation de la classe Etat
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class Etat               
//>         Etat()                 
//>         operator =()           
//>         ~Etat()                
//>         desinitialise()        
//>         attitudeExtrapolee()   
//>         spinExtrapole()        
//>         spinExtrapole()        
//>         miseAJourTempsSideral()
//>         enregistreCorps()      
//$Historique
//       $Log: Etat.cpp,v $
//       Revision 4.21  2003/02/27 16:39:46  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 4.20  2003/02/04 16:22:24  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 4.19  2002/09/13 08:51:33  marmottes
//       extension du copyright à 2002 suite à la DM 0007
//
//       Revision 4.18  2002/09/09 13:37:02  marmottes
//       ajout de la méthode enregistreCorps, modification des attributs et
//       utilisation de la classe BodyEphem, avec suppression des calculs:
//       temps sidéral et positions du Soleil et de la Lune (DM 0007)
//
//       Revision 4.17  2001/07/19 07:23:22  luc
//       correction de la formule du temps sidéral
//
//       Revision 4.16  2001/07/17 15:25:10  luc
//       ajout d'une méthode vitesseRotation
//
//       Revision 4.15  2001/06/06 08:22:29  luc
//       remontée des exceptions Cantor
//
//       Revision 4.14  2001/04/04 12:30:13  luc
//       ajout des distances lune et soleil
//       report du corps du constructeur par copie depuis Etat.h
//
//       Revision 4.13  2001/03/26 11:15:21  luc
//       ajout des caractéristiques du corps central
//       (et correction du calcul du rayon angulaire fait de façon erronée dans
//       l'ancienne classe SenseurTerre)
//
//       Revision 4.12  2000/09/13 08:46:06  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 4.11  2000/03/30 17:01:18  luc
//       ajout du copyright CNES
//
//       Revision 4.10  1999/08/06 13:32:12  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 4.9  1999/04/26 11:36:17  luc
//       remplacement de abs par fabs
//
//       Revision 4.8  1998/10/05 13:51:17  luc
//       élimination d'une valeur par défaut inutile
//       (c'est la déclaration qui la spécifie, pas la définition)
//
//       Revision 4.7  1998/06/24 19:54:12  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 4.6  1998/05/14 12:08:12  luc
//       déplacement d'un constructeur depuis le .h
//       initialisation correcte des astres dans le constructeur par défaut
//       normalisation de la direction terre-soleil
//
//       Revision 4.5  1998/04/29 16:20:54  luc
//       correction d'une erreur sur la direction du soleil
//
//       Revision 4.4  1998/04/26 18:24:56  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 4.3  1998/04/26 18:18:18  luc
//       ajout d'une gestion d'unités de position et de vitesse variables
//
//       Revision 4.2  1998/02/04 09:22:40  luc
//       élimination d'une variable inutilisée
//
//       Revision 4.1  1997/11/27 07:03:30  luc
//       ajout du temps sidéral
//
//       Revision 3.6  1997/09/15 10:48:26  luc
//       restriction de la partie scalaire du quaternion à des valeurs positives
//
//       Revision 3.5  1997/09/03 09:28:04  luc
//       renommage de Etat::soleil () en Etat::satSoleil ()
//       renommage de Etat::lune   () en Etat::satLune   ()
//       ajout de Etat::terreSoleil ()
//
//       Revision 3.4  1997/08/20 07:58:23  luc
//       ajout d'un en-tête de fichier
//
//       Revision 3.3  1997/04/27 19:34:33  luc
//       ajout des directions lune et soleil
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 3.2  1997/03/21 18:58:58  luc
//       déplacement de la protection sur les dates trop proches
//       l'extrapolation de spin est appelée également depuis
//       des classes externes, la protection doit être intrinsèque
//       à la méthode d'extrapolation, pas gérée par l'appelant
//       
//       Revision 3.1  1997/01/28 12:35:53  luc
//       ajout de la vitesse du satellite
//       initialisation de spin dès le début
//       (il n'y a donc plus besoin de compter les réinitialisations)
//       
//       Revision 2.2  1996/10/18 07:49:49  luc
//       ajout d'une protection sur les dates identiques
//       dans l'extrapolation de spin
//       
//       Revision 2.1  1996/07/31 15:51:10  luc
//       abandon des tools.h++ (Rogue Wave)
//       
//       Revision 1.5  1996/02/19 15:59:15  luc
//       correction d'une erreur de signe dans l'extrapolation de l'attitude a l'aide du spin
//       
//       Revision 1.4  1995/07/12 12:16:53  mercator
//       ajout d'une methode de desinitialisation de l'etat
//       
//       Revision 1.3  1995/02/10 16:16:05  mercator
//       ajout d'un test de spin nul pour eviter une division par zero en cas d'immobilite
//       
//       Revision 1.2  1995/02/06 08:07:51  mercator
//       prise en compte du spin precedent pour estimer le spin courant
//       incorporation de l'extrapolation de spin dans la classe Etat
//       
//       Revision 1.1  1994/12/23 11:00:01  luc
//       Initial revision
//
//$Version
//       $Id: Etat.cpp,v 4.21 2003/02/27 16:39:46 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2002 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Util.h"
#include "marmottes/Etat.h"
#include "marmottes/BodyEphemC.h"
#include "marmottes/BodyEphemF.h"


Etat::Etat ()
  throw (CantorErreurs)
  : date_ (0),
    position_ (VecDBL (7000.0, 0.0, 0.0)),
    vitesse_  (VecDBL (7.5, 0.0, 0.0)),
    attitude_ (VecDBL (1.0, 0.0, 0.0), 0.0),
    attitudeVD1_ (RotDBLVD1 (attitude_)), spin_ (0.0, 0.0, 0.0),
    coeffPosition_ (1.0), coeffVitesse_ (1.0), normesLitigieuses_ (0)
{ // constructeur par défaut
  ptrBodyEphem_ = new BodyEphemC();

  miseAJourTempsSideral ();
  miseAJourAstres       ();
}

Etat::Etat (double date, const VecDBL& position, const VecDBL& vitesse,
            const RotDBL& attitude, const VecDBL& spin,
            double coeffPosition, double coeffVitesse)
  throw (CantorErreurs)
  : date_ (date),
    position_ (position * coeffPosition), vitesse_ (vitesse * coeffVitesse),
    spin_ (spin),
    coeffPosition_ (coeffPosition), coeffVitesse_ (coeffVitesse),
    normesLitigieuses_ (0)
{ // constructeur
  ptrBodyEphem_ = new BodyEphemC();

  // on s'arrange pour que la partie scalaire du quaternion soit positive
  if (attitude.q0 () >= 0.0)
    attitude_  = attitude;
  else
    attitude_  = RotDBL (-(attitude.q0 ()),
                         -(attitude.q1 ()),
                         -(attitude.q2 ()),
                         -(attitude.q3 ()));

  attitudeVD1_ = RotDBLVD1 (attitude_);
  
  miseAJourTempsSideral ();
  miseAJourAstres       ();

}

Etat::Etat (double date, const VecDBL& position, const VecDBL& vitesse,
            const RotDBL& attitude,
            double coeffPosition, double coeffVitesse)
  throw (CantorErreurs)
  : date_ (date),
    position_ (position * coeffPosition), vitesse_ (vitesse * coeffVitesse),
    spin_ (0.0, 0.0, 0.0),
    coeffPosition_ (coeffPosition), coeffVitesse_ (coeffVitesse),
    normesLitigieuses_ (0)
{  // constructeur
  ptrBodyEphem_ = new BodyEphemC();

  // on s'arrange pour que la partie scalaire du quaternion soit positive
  if (attitude.q0 () >= 0.0)
    attitude_  = attitude;
  else
    attitude_  = RotDBL (-(attitude.q0 ()),
                         -(attitude.q1 ()),
                         -(attitude.q2 ()),
                         -(attitude.q3 ()));

  attitudeVD1_ = RotDBLVD1 (attitude_);
  
  miseAJourTempsSideral ();
  miseAJourAstres       ();

}

Etat::Etat (const Etat& e)
  : date_ (e.date_), tempsSideral_ (e.tempsSideral_),
    position_ (e.position_), vitesse_ (e.vitesse_),
    attitude_ (e.attitude_), attitudeVD1_ (e.attitudeVD1_), spin_ (e.spin_),
    rayonCorpsCentral_ (e.rayonCorpsCentral_),
    satLune_ (e.satLune_), distLune_ (e.distLune_),
    rayonLune_ (e.rayonLune_),
    satSoleil_ (e.satSoleil_), distSoleil_ ( e.distSoleil_),
    terreSoleil_ (e.terreSoleil_), rayonSoleil_ (e.rayonSoleil_),
    ptrBodyEphem_ (e.ptrBodyEphem_->clone()),
    coeffPosition_ (e.coeffPosition_), coeffVitesse_ (e.coeffVitesse_),
    normesLitigieuses_ (e.normesLitigieuses_)
{}

Etat& Etat::operator = (const Etat& e)
{ if (this != &e)       // protection contre x = x
  { date_              = e.date_;
    tempsSideral_      = e.tempsSideral_;
    position_          = e.position_;
    vitesse_           = e.vitesse_;
    attitude_          = e.attitude_;
    attitudeVD1_       = e.attitudeVD1_;
    rayonCorpsCentral_ = e.rayonCorpsCentral_;
    spin_              = e.spin_;
    satLune_           = e.satLune_;
    distLune_          = e.distLune_;
    rayonLune_         = e.rayonLune_;
    satSoleil_         = e.satSoleil_;
    distSoleil_        = e.distSoleil_;
    terreSoleil_       = e.terreSoleil_;
    rayonSoleil_       = e.rayonSoleil_;

    if (ptrBodyEphem_ != 0)
    {
      delete ptrBodyEphem_;
    }
    ptrBodyEphem_      = e.ptrBodyEphem_->clone();

    coeffPosition_     = e.coeffPosition_;
    coeffVitesse_      = e.coeffVitesse_;
    normesLitigieuses_ = e.normesLitigieuses_;
  }

  return *this;

}

Etat::~Etat()
{
  if (ptrBodyEphem_ != 0)
  {
    delete ptrBodyEphem_;
  }
}

void Etat::desinitialise ()
{ date_         = 0;
  attitude_     = RotDBL (VecDBL (1.0, 0.0, 0.0), 0.0);
  attitudeVD1_  = RotDBLVD1 (attitude_);;
  spin_         = VecDBL (0.0, 0.0, 0.0);
}

void Etat::reinitialise (double date,
                         const VecDBL& position, const VecDBL& vitesse,
                         const RotDBL& attitude)
  throw (CantorErreurs)
{ // réinitialisation des attributs
  spin_              = spinExtrapole (date, attitude);
  date_              = date;
  position_          = position * coeffPosition_;
  vitesse_           = vitesse  * coeffVitesse_;
  normesLitigieuses_ = 0;

  if (attitude.q0 () >= 0.0)
    attitude_  = attitude;
  else
    attitude_  = RotDBL (-(attitude.q0 ()),
                         -(attitude.q1 ()),
                         -(attitude.q2 ()),
                         -(attitude.q3 ()));

  attitudeVD1_ = RotDBLVD1 (attitude_);

  miseAJourTempsSideral ();
  miseAJourAstres       ();

}

void Etat::unitesPositionVitesse (const string& unitePos,
                                  const string& uniteVit)
  throw (MarmottesErreurs)
{ // mémorisation des unités de travail de l'appelant de Marmottes
  if (unitePos == "km")
    coeffPosition_ = 1.0;
  else
    if (unitePos == "m")
      coeffPosition_ = 0.001;
    else
      throw MarmottesErreurs (MarmottesErreurs::unite_position,
                              unitePos.c_str (), "km", "m");

  if (uniteVit == "km/s")
    coeffVitesse_ = 1.0;
  else
    if (uniteVit == "m/s")
      coeffVitesse_ = 0.001;
    else
      throw MarmottesErreurs (MarmottesErreurs::unite_vitesse,
                              unitePos.c_str (), "km/s", "m/s");

  // à partir de maintenant, les unités d'entrée seront converties,
  // mais on ignore si l'état courant avait déjà les bonnes unités ou
  // non ; les normes de le position et de la vitesse sont donc
  // sujettes à caution et on le mémorise
  normesLitigieuses_ = 1;

}

RotDBL Etat::attitudeExtrapolee (double date) const
{ // calcul de l'évolution de l'état courant à la date demandée
  double omega = spin_.norme ();
  if (omega < 1.0e-8)
    return attitude_;
  double angle = omega * 86400.0 * (date_ - date);
  RotDBL evolution (spin_, angle, omega);

  RotDBL attExp (evolution (attitude_));

  // on s'arrange pour que la partie scalaire du quaternion soit positive
  return (attExp.q0 () >= 0.0) ? attExp : RotDBL (-(attExp.q0 ()),
                                                  -(attExp.q1 ()),
                                                  -(attExp.q2 ()),
                                                  -(attExp.q3 ()));

}

VecDBL Etat::spinExtrapole (double date, const RotDBL& attitude) const
{ // calcul du spin par différence finie entre attitudes précédente et courante

  if (fabs (date - date_) < 1.0e-8)
  { // on ne sait pas extrapoler sur un intervalle aussi court
    // on considère que le spin n'a pas eu le temps de changer
    return spin_;
  }

  // évolution de l'attitude
  RotDBL evolution              =   attitude (-attitude_);
  VecDBL directionSpin          =   evolution.axe   ();
  double angleRotationSatellite = -(evolution.angle ());

  // la même attitude peut être obtenue en tournant de 2kPI + angle, k entier
  // d'où un modèle linéaire de l'écart de spin: A + k B
  double dt = 86400.0 * (date - date_);
  VecDBL A = directionSpin * angleRotationSatellite / dt - spin_;
  VecDBL B = directionSpin * (M_PI + M_PI)  / dt;

  // recherche du k donnant l'écart de spin minimum
  // (c'est à dire le maximum de cohérence avec le spin précédent)
  double kInf   = floor (- (A | B) / (B | B));
  VecDBL ecart1 = A + kInf * B;
  VecDBL ecart2 = A + (kInf + 1.0) * B;
  double kMin   = (ecart1.norme () <= ecart2.norme ()) ? kInf : (kInf + 1.0);

  return directionSpin * (angleRotationSatellite + kMin * (M_PI + M_PI)) / dt;

}

VecVD1 Etat::spinExtrapole (double date, const RotVD1& attitude) const
{ // calcul du spin par différence finie entre attitudes précédente et courante

  if (fabs (date - date_) < 1.0e-8)
  { // on ne sait pas extrapoler sur un intervalle aussi court
    // on considère que le spin n'a pas eu le temps de changer
    return VecDBLVD1 (spin_);
  }

  // évolution de l'attitude
  RotVD1 evolution                      =   attitude (-attitudeVD1_);
  VecVD1 directionSpin                  =   evolution.axe   ();
  ValeurDerivee1 angleRotationSatellite = -(evolution.angle ());

  // la même attitude peut être obtenue en tournant de 2kPI + angle, k entier
  // d'où un modèle linéaire de l'écart de spin: A + k B
  double dt     = 86400.0 * (date - date_);
  VecDBL axeDBL = VecVD1DBL (directionSpin);
  VecDBL A      = axeDBL * angleRotationSatellite.f0 () / dt - spin_;
  VecDBL B      = axeDBL * (M_PI + M_PI)  / dt;

  // recherche du k donnant l'écart de spin minimum
  // (c'est à dire le maximum de cohérence avec le spin précédent)
  double kInf   = floor (- (A | B) / (B | B));
  VecDBL ecart1 = A + kInf * B;
  VecDBL ecart2 = A + (kInf + 1.0) * B;
  double kMin   = (ecart1.norme () <= ecart2.norme ()) ? kInf : (kInf + 1.0);

  return directionSpin * (angleRotationSatellite + kMin * (M_PI + M_PI)) / dt;

}

void Etat::miseAJourTempsSideral (double decalage)
{ // mise à jour du temps sidéral selon la date

  tempsSideral_ = ptrBodyEphem_->siderealTime (date_ , decalage); 
  
}

void Etat::miseAJourAstres ()
  throw (CantorErreurs)
{
  // Update of the Moon and Sun positions according to the current date


  // update of the Earth apparent radius
  // -----------------------------------

  rayonCorpsCentral_ = asin (ptrBodyEphem_ -> getEquatorialRadius()/ position_.norme ());

  // update of the Moon postion wrt satellite
  // --------------------------------------------

  // Moon postion wrt central body

  VecDBL CentralBodyMoon = ptrBodyEphem_->moonPosition(date_); // units : km


  // computation of the Moon position wrt the satellite
  // with position_ = satellite positon wrt central body (units: km)

  satLune_    = CentralBodyMoon - position_; // units: km
  distLune_   = satLune_.norme ();           // unit: km 
  rayonLune_  = asin (ptrBodyEphem_->getMoonRadius() / distLune_); // unit: rad
  satLune_   /= distLune_;                   // units: none



  // update of the Sun postion wrt satellite
  // ---------------------------------------

  // Sun postion wrt central body

  VecDBL CentralBodySun = ptrBodyEphem_->sunPosition(date_); // units : km

  // computation of the Sun position wrt satellite
  // with position_ = satellite positon wrt central body (units: km)

  satSoleil_   = CentralBodySun - position_; // units: km
  distSoleil_  = satSoleil_.norme ();        // unit: km 
  rayonSoleil_ = asin (ptrBodyEphem_->getSunRadius() / distSoleil_); // unit: rad
  satSoleil_  /= distSoleil_;                // units: none

  terreSoleil_ = CentralBodySun;  // units: km
  terreSoleil_.normalise ();      // units: none

}

void Etat::normesLitigieuses () const
  throw (MarmottesErreurs)
{ // vérifie si l'on peut faire confiance aux normes de la position et
  // de la vitesse, et génère une erreur dans le cas contraire
  if (normesLitigieuses_)
    throw MarmottesErreurs (MarmottesErreurs::normes_litigieuses);
}

void Etat::enregistreCorps (double equatorialRadius, 
                            double oblateness, double rotationVelocity,
                            double moonRadius, double sunRadius,
                            BodyEphemC::TypeFuncTsid *tsidFunc, 
                            BodyEphemC::TypeFuncPos *sunFunc, BodyEphemC::TypeFuncPos *moonFunc, 
                            BodyEphemC::TypeFuncPos *earthFunc)
{
    if (ptrBodyEphem_ != 0)
    {
      delete ptrBodyEphem_;
    }
    ptrBodyEphem_ = new BodyEphemC(equatorialRadius, oblateness, rotationVelocity,
                                   moonRadius, sunRadius,
                                   tsidFunc, sunFunc, moonFunc, earthFunc);
}

void Etat::enregistreCorps (double equatorialRadius, 
                            double oblateness, double rotationVelocity, 
                            double moonRadius, double sunRadius,
                            BodyEphemF::TypeFuncTsid *tsidFunc, 
                            BodyEphemF::TypeFuncPos *sunFunc, BodyEphemF::TypeFuncPos *moonFunc, 
                            BodyEphemF::TypeFuncPos *earthFunc)
{
    if (ptrBodyEphem_ != 0)
    {
      delete ptrBodyEphem_;
    }
    ptrBodyEphem_ = new BodyEphemF(equatorialRadius, oblateness, rotationVelocity, 
                                   moonRadius, sunRadius,
                                   tsidFunc, sunFunc, moonFunc, earthFunc);
}
