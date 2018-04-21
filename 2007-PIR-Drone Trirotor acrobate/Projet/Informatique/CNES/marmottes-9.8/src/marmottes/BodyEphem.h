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
//>       BodyEphem.h
//$Resume
//       fichier d'en-tête de la classe BodyEphem
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class BodyEphem
//$Historique
//       $Log: BodyEphem.h,v $
//       Revision 1.6  2003/07/09 12:33:49  marmottes
//       Formattage des paragraphes de commentaires
//
//       Revision 1.5  2003/07/02 15:41:06  marmottes
//       FA-ID 0023 Ajout des interfaces des fonctions par defaut pour marmottesenregistrecorps
//
//       Revision 1.4  2003/07/02 07:25:40  marmottes
//       Mise en conf pour sauvegarde des modifs suite a la DM sur la mise a disposition des 
//       fonctions de calcul par defaut du temps sideral, de la position de la Lune de la Terre 
//       et du Soleil pour linterface Fortran
//
//       Revision 1.3  2003/02/27 16:18:51  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.2  2002/12/02 17:02:05  marmottes
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.1  2002/09/09 13:26:23  marmottes
//       Initial version (DM 0007)
//
//$Version
//       $Id: BodyEphem.h,v 1.6 2003/07/09 12:33:49 marmottes Exp $
//
//$Auteur
//       G. Prat and L. Maisonobe CS SI
//       Copyright (C) 2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


#ifndef __marmottes_BodyEphem_h
#define __marmottes_BodyEphem_h

#include "cantor/DeclDBL.h"


///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class BodyEphem
//$Resume
//       abstract class for ephemeride computations
//
//$Description
//       ephemeride computations for the Sun, the Moon and the Earth, 
//       with respect of the central body
//       and sidereal time evaluation
//
//$Usage
//>     construction : 
//          without arguments, 
//          with given equatorial radius/oblateness/rotation velocity
//          of the central body and radii of moon and sun (negative value
//          means: must use the default value),
//          by copy
//>     utilisation  : 
//>       virtual BodyEphem *clone           () 
//          can perform a copy without knowing the actual concrete class
//>       virtual double siderealTime        () 
//          computes sidereal time
//>       virtual VecDBL sunPosition         () 
//          computes Sun position wrt central body
//>       virtual VecDBL moonPosition        () 
//          computes Moon position wrt central body
//>       virtual VecDBL earthPosition       () 
//          computes Earth position  wrt central body
//>       static double defaultCsiderealTime () protegee - 
//          computes default sidereal time (for C call)
//>       static double defaultFsiderealTime () protegee - 
//          computes default sidereal time (for fortran call)  
//>       static void defaultCsunPosition    () protegee - 
//          computes default Sun position (for C call)    
//>       static void defaultFsunPosition    () protegee - 
//          computes default Sun position (for fortran call)    
//>       static void defaultCmoonPosition   () protegee - 
//          computes default Moon position (for C call)        
//>       static void defaultFmoonPosition   () protegee - 
//          computes default Moon position (for fortrann call)        
//>       static void defaultCearthPosition  () protegee - 
//          computes default Earth position (for C call)
//>       static void defaultFearthPosition  () protegee - 
//          computes default Earth position (for fortran call)
//>       const BodyEphem& operator =        () protegee - 
//          affectation
//>       double getEquatorialRadius         () 
//          gives equatorial radius of the central body
//>       double getOblateness               () 
//          gives oblateness of the central body 
//>       double getRotationVelocity         () 
//          gives rotation velocity of the central body 
//>       double getMoonRadius               () 
//          gives radius of the moon
//>       double getSunRadius                () 
//          gives radius of the sun
//$Auteur
//       G. Prat and L. Maisonobe CS SI
//       Copyright (C) 2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////
class BodyEphem
{  

  public:

  // destructor
  virtual ~BodyEphem() {}

  // cloning method
  virtual BodyEphem *clone() const = 0;

  // sidereal time computation for central body (unit: rad)
  virtual double siderealTime (double t, double offset) = 0; 

  // Sun position wrt central body (units: km)
  virtual VecDBL sunPosition (double t) = 0;   

  // Moon position wrt central body (units: km)
  virtual VecDBL moonPosition (double t) = 0;  

  // Earth position wrt central body (units: km)
  virtual VecDBL earthPosition (double t) = 0; 

  // access to physical values
  double getEquatorialRadius  () const { return equatorialRadius_ ;}
  double getOblateness        () const { return oblateness_ ;}
  double getRotationVelocity  () const { return rotationVelocity_ ;}
  double getMoonRadius        () const { return moonRadius_ ;}
  double getSunRadius         () const { return sunRadius_ ;}

  // FAB_MODIF

  // fortran signature for default function
  static double defaultFsiderealTime (double *ptrT, double *ptrOffset); 
  static void defaultFsunPosition (double *ptrT, double BodySun[3]);
  static void defaultFmoonPosition (double *ptrT, double BodyMoon[3]);
  static void defaultFearthPosition (double *ptrT, double BodyEarth[3]);

  // FAB_MODIF


  protected:

  // class variables:
  // values for the central body = Earth
  static const double defaultEquatorialRadius;    // unit: km
  static const double defaultOblateness;          // unit: none
  static const double defaultRotationVelocity;    // unit: rad.s-1 

  static const double defaultMoonRadius;          // unit: km
  static const double defaultSunRadius;           // unit: km

  // C signature for default function
  static double defaultCsiderealTime (double t, double offset);
  static void defaultCsunPosition (double t, double BodySun[3]);
  static void defaultCmoonPosition (double t, double BodyMoon[3]);
  static void defaultCearthPosition (double t, double BodyEarth[3]);

  // default constructor
  BodyEphem ();

 // in case the user gives his own values
  BodyEphem (double equatorialRadius, double oblateness, double rotationVelocity,
             double moonRadius, double sunRadius);

  // copy constructor
  BodyEphem (const BodyEphem& b);

  // affectation operator
  const BodyEphem& operator = (const BodyEphem& b);

  // attributes

  double equatorialRadius_;
  double oblateness_;
  double rotationVelocity_;
  double moonRadius_;
  double sunRadius_;

};

#endif
