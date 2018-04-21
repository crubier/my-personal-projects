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
//>       BodyEphemF.h
//$Resume
//       fichier d'en-tête de la classe BodyEphemF
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class BodyEphemF
//$Historique
//       $Log: BodyEphemF.h,v $
//       Revision 1.2  2003/02/27 16:18:28  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.1  2002/09/09 13:28:54  marmottes
//       Initial version (DM 0007)
//
//
//$Version
//       $Id: BodyEphemF.h,v 1.2 2003/02/27 16:18:28 marmottes Exp $
//
//$Auteur
//       G. Prat and L. Maisonobe CS SI
//       Copyright (C) 2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


#ifndef __marmottes_BodyEphemF_h
#define __marmottes_BodyEphemF_h

#include "marmottes/BodyEphem.h"


///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class BodyEphemF
//$Resume
//       concrete class for ephemeride computations with fortran functions
//
//$Description
//       ephemeride computations for the Sun, the Moon and the Earth, 
//       with respect to the central body;
//       and sidereal time evaluation for the central body
//
//$Usage
//>     construction : 
//          without arguments, 
//          with given equatorial radius/oblateness/rotation velocity
//          of the central body and radii of moon and sun (negative value
//          means: must use the default value)
//          and functions for computation of Sun/Moon/Earth position
//          (null pointer means: must use the default function),
//          by copy
//>     utilisation  : 
//>       typedef double TypeFuncTsid  () 
//          defines signature of the sidereal time function
//>       typedef void TypeFuncPos     () 
//          defines signature of the ephemeride computation functions
//>       const BodyEphemF& operator = () 
//          affectation
//>       virtual BodyEphem *clone     () 
//          can perform a copy without knowing the actual concrete class
//>       virtual double siderealTime  () 
//          computes sidereal time
//>       virtual VecDBL sunPosition   () 
//          computes Sun position wrt central body
//>       virtual VecDBL moonPosition  () 
//          computes Moon position wrt central body
//>       virtual VecDBL earthPosition () 
//          computes Earth position  wrt central body
//$Auteur
//       G. Prat and L. Maisonobe CS SI
//       Copyright (C) 2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class BodyEphemF : public BodyEphem
{  
  public:

  // types of global functions that can by defined by the user
  typedef double TypeFuncTsid (double *, double *);    // for sidereal time computation
  typedef void   TypeFuncPos (double *, double [3]);   // for position computation

  // default constructor
  BodyEphemF (); 

  // copy constructor
  BodyEphemF (const BodyEphemF& b); 

 // in case the user gives his own values and functions
  BodyEphemF (double equatorialRadius, double oblateness, double rotationVelocity,
              double moonRadius, double sunRadius,
              TypeFuncTsid *tsidFunc, 
              TypeFuncPos *sunFunc, TypeFuncPos *moonFunc, TypeFuncPos *earthFunc); 

  // affectation operator
  const BodyEphemF& operator = (const BodyEphemF& b); 

  // destructor
  virtual ~BodyEphemF() {}


  // cloning method
  virtual BodyEphem *clone() const;

  // sidereal time computation for central body (unit: rad)
  virtual double siderealTime (double t, double offset);

  // Sun position wrt central body (units: km)
  virtual VecDBL sunPosition (double t);   

  // Moon position wrt central body (units: km)
  virtual VecDBL moonPosition (double t);  

  // Earth position wrt central body (units: km)
  virtual VecDBL earthPosition (double t); 

  private:

  TypeFuncTsid *tsidFuncPtr_;
  TypeFuncPos  *sunFuncPtr_;
  TypeFuncPos  *moonFuncPtr_;
  TypeFuncPos  *earthFuncPtr_;


};

#endif
