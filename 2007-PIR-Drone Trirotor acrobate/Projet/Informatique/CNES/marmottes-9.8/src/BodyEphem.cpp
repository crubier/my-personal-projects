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
//>       BodyEphem.cpp
//$Resume
//       implantation file of the BodyEphem class
//
//$Description
//       Definition module of the class
//
//$Contenu
//>       class BodyEphem          
//>         BodyEphem()            
//>         operator =()           
//>         defaultCsiderealTime() 
//>         defaultCsunPosition()  
//>         defaultCmoonPosition() 
//>         defaultCearthPosition()
//>         defaultFsiderealTime() 
//>         defaultFsunPosition()  
//>         defaultFmoonPosition() 
//>         defaultFearthPosition()
//$Historique
//       $Log: BodyEphem.cpp,v $
//       Revision 1.3  2003/02/27 16:38:39  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.2  2003/02/04 16:20:10  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.1  2002/09/09 13:44:25  marmottes
//       Initial version (DM 0007)
//
//$Version
//       $Id: BodyEphem.cpp,v 1.3 2003/02/27 16:38:39 marmottes Exp $
//
//$Auteur
//       G. Prat and L. Maisonobe CS SI
//       Copyright (C) 2002 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/BodyEphem.h"

#include "cantor/DeclDBL.h"
#include "cantor/Util.h"

// constant initializations
const double BodyEphem::defaultEquatorialRadius  = 6378.14;                // unit: km
const double BodyEphem::defaultOblateness        = 1.0 / 298.257;
const double BodyEphem::defaultRotationVelocity  = 7.29211514670519379e-5; // unit: rad.s-1 

const double BodyEphem::defaultMoonRadius        = 1737.4;                 // unit: km
const double BodyEphem::defaultSunRadius         = 695500;                 // unit: km


// default constructor
BodyEphem::BodyEphem ()
{
  // for use of default values if none are given by the user
  equatorialRadius_  = defaultEquatorialRadius ;
  oblateness_        = defaultOblateness ;
  rotationVelocity_  = defaultRotationVelocity ;
  moonRadius_        = defaultMoonRadius ;
  sunRadius_         = defaultSunRadius ;
}


// in case the user gives equatorial radius, oblateness and rotation velocity of the central body
BodyEphem::BodyEphem (double equatorialRadius, double oblateness, double rotationVelocity,
                      double moonRadius, double sunRadius)
{
  if (equatorialRadius <= 0) // incorrect value : use of the default value
    equatorialRadius_ = defaultEquatorialRadius;
  else
    equatorialRadius_ = equatorialRadius;

  if (oblateness <= 0) // incorrect value : use of the default value
    oblateness_ = defaultOblateness;
  else
    oblateness_ = oblateness;

  if (rotationVelocity <= 0) // incorrect value : use of the default value
    rotationVelocity_ = defaultRotationVelocity;
  else
    rotationVelocity_ = rotationVelocity;

  if (moonRadius <= 0) // incorrect value : use of the default value
    moonRadius_ = defaultMoonRadius;
  else
    moonRadius_ = moonRadius;

  if (sunRadius <= 0) // incorrect value : use of the default value
    sunRadius_ = defaultSunRadius;
  else
    sunRadius_ = sunRadius;

}

// copy constructor
BodyEphem::BodyEphem (const BodyEphem& b)
{
  equatorialRadius_  = b.equatorialRadius_  ;
  oblateness_        = b.oblateness_ ;
  rotationVelocity_  = b.rotationVelocity_  ;
  moonRadius_        = b.moonRadius_ ;
  sunRadius_         = b.sunRadius_ ;
}

// affectation
const BodyEphem& BodyEphem::operator = (const BodyEphem& b)
{
  if (this != &b)  // protection against x = x
  {
    equatorialRadius_  = b.equatorialRadius_  ;
    oblateness_        = b.oblateness_ ;
    rotationVelocity_  = b.rotationVelocity_  ; 
    moonRadius_        = b.moonRadius_ ;
    sunRadius_         = b.sunRadius_ ;
  }
  return *this;
}


double BodyEphem::defaultCsiderealTime (double t, double offset)
{
  // sidereal time upgraded wrt the CNES julian date t (seconds are expressed in fraction of day)
  const double a1  = 0.1746647708617871e1;
  const double a3  = 0.7292115146705e-04;
  const double eps = 1.7202179573714597e-02;

  double r = t - floor (t);
  r = a1 + eps * t + a3 * offset + (M_PI + M_PI) * r;

  return recaleAngle (r, M_PI);

}


void BodyEphem::defaultCsunPosition (double t, double BodySun[3])
{
  // computation of the Sun position wrt the central body (units: km)
  // ================================================================

  // In this case : central body = Earth

  double date   = t - 10000.0;
  double f   = radians (225.768 + 13.2293505 * date);
  double d   = radians (11.786 + 12.190749 * date);
  double xlp = radians (134.003 + 0.9856 * date);
  double g   = radians (282.551 + 0.000047 * date);
  double e   = radians (23.44223 - 3.5626e-07 * date);
  double ce  = cos (e);
  double se  = sin (e);
  double rot = 0.6119022e-06 * t;
  double cr  = cos (rot);
  double sr  = sin (rot);


  // Newcomb's theory

  double cl   = 99972.0 * cos (xlp + g) + 1671.0 * cos (xlp + xlp + g) - 1678.0 * cos (g);
  cl   = cl + 32.0 * cos (3.0 * xlp + g) + cos (4.0 * xlp + g) + 2.0 * cos (xlp + d + g);
  cl   = cl - 4.0 * cos (g - xlp) - 2.0 * cos (xlp - d + g) + 4.0 * cos (f - d);
  cl   = cl - 4.0 * cos (xlp + xlp - f + d + g + g);
  cl   = cl * 1.e-05;

  double sl   = 99972.0 * sin (xlp + g) + 1671.0 * sin (xlp + xlp + g) - 1678.0 * sin (g);
  sl   = sl + 32.0 * sin (3.0 * xlp + g) + sin (4.0 * xlp + g) + 2.0 * sin (xlp + d + g);
  sl   = sl - 4.0 * sin (g - xlp) - 2.0 * sin (xlp - d + g) + 4.0 * sin (f - d);
  sl   = sl - 4.0 * sin (xlp + xlp - f + d + g + g);
  sl   = sl * 1.e-05;

  double q    = sqrt (cl * cl + sl * sl);
  double sx   = cl / q;
  double sy   = sl * ce / q;

  double  EarthSun[3];
  EarthSun[0] = sx * cr + sy * sr;
  EarthSun[1] = sy * cr - sx * sr;
  EarthSun[2] = sl * se / q;

  double dasr = 1672.2 * cos (xlp) + 28.0 * cos (xlp + xlp) - 0.35 * cos (d);

  // units: km
  BodySun[0] = EarthSun[0] * 149597870.0 / (1.0 + 1.e-05 * dasr);
  BodySun[1] = EarthSun[1] * 149597870.0 / (1.0 + 1.e-05 * dasr);
  BodySun[2] = EarthSun[2] * 149597870.0 / (1.0 + 1.e-05 * dasr);

}


void BodyEphem::defaultCmoonPosition (double t, double BodyMoon[3])
{
  // computation of the Moon position wrt the central body (units: km)
  // =================================================================

  // In this case : central body = Earth

  double date   = t - 10000.0;
  double f   = radians (225.768 + 13.2293505 * date);
  double xl  = radians (185.454 + 13.064992 * date);
  double d   = radians (11.786 + 12.190749 * date);
  double xlp = radians (134.003 + 0.9856 * date);
  double e   = radians (23.44223 - 3.5626e-07 * date);
  double ce  = cos (e);
  double se  = sin (e);
  double rot = 0.6119022e-06 * t;
  double cr  = cos (rot);
  double sr  = sin (rot);

  // Brown's theory

  double dl = 10976.0 * sin (xl) - 2224.0 * sin (xl - d - d) + 1149.0 * sin (d + d);
  dl   = dl + 373.0 * sin (xl + xl) - 324.0 * sin (xlp) - 200.0 * sin (f + f);
  dl   = dl - 103.0 * sin (xl + xl - d - d) - 100.0 * sin (xl + xlp - d - d);
  dl   = dl + 93.0 * sin (xl + d + d);
  dl   = dl - 80.0 * sin (xlp - d - d) + 72.0 * sin (xl - xlp) - 61.0 * sin (d);
  dl   = dl - 53.0 * sin (xl + xlp);
  dl   = dl + 14.0 * sin (xl - xlp - d - d) + 19.0 * sin (xl - f - f);
  dl   = dl - 19.0 * sin (xl - 4.0 * d);
  dl   = dl + 17.0 * sin (3.0 * xl) - 27.0 * sin (f + f - d - d);
  dl   = dl - 12.0 * sin (xlp + d + d);
  dl   = dl - 22.0 * sin (xl + f + f) - 15.0 * sin (xl + xl - 4.0 * d);
  dl   = dl + 7.0 * sin (xl + xl + d + d) + 9.0 * sin (xl - d);
  dl   = dl - 6.0 * sin (3.0 * xl - d - d);
  dl   = dl + 7.0 * sin (4.0 * d) + 9.0 * sin (xlp + d) + 7.0 * sin (xl - xlp + d + d);
  dl   = dl + 5.0 * sin (xl + xl - xlp);
  dl   = dl * 1.e-05;

  double b = 8950.0 * sin (f) + 490.0 * sin (xl + f) + 485.0 * sin (xl - f);
  b    = b - 302.0 * sin (f - d - d);
  b    = b - 97.0 * sin (xl - f - d - d) - 81.0 * sin (xl + f - d - d);
  b    = b + 57.0 * sin (f + d + d);
  b    = b - 14.0 * sin (xlp + f - d - d) + 16.0 * sin (xl - f + d + d);
  b    = b + 15.0 * sin (xl + xl - f) + 30.0 * sin (xl + xl + f);
  b    = b - 6.0 * sin (xlp - f + d + d) - 7.0 * sin (xl + xl + f - d - d);
  b    = b + 7.0 * sin (xl + f + d + d);
  b    = b * 1.e-05;

  double u  = radians (68.341 + 13.176397 * date) + dl;
  double cu = cos (u);
  double su = sin (u);
  double cb = cos (b);
  double sb = sin (b);
  double rx = cu * cb;
  double ry = su * cb * ce - sb * se;

  double EarthMoon[3];
  EarthMoon[0] =  rx * cr + ry * sr;
  EarthMoon[1] =  ry * cr - rx * sr;
  EarthMoon[2] =  sb * ce + su * cb * se;

  double dasr = 5450.0 * cos (xl) + 1002.0 * cos (xl - d - d) + 825.0 * cos (d + d);
  dasr = dasr + 297.0 * cos (xl + xl) + 90.0 * cos (xl + d + d);
  dasr = dasr + 56.0 * cos (xlp - d - d);
  dasr = dasr + 42.0 * cos (xl + xlp - d - d) + 34.0 * cos (xl - xlp);
  dasr = dasr - 12.0 * cos (xlp) - 29.0 * cos (d) - 21.0 * cos (xl - f - f);
  dasr = dasr + 18.0 * cos (xl - 4.0 * d) - 28.0 * cos (xl + xlp);
  dasr = dasr + 11.0 * cos (xl + xl - 4.0 * d) + 18.0 * cos (3.0 * xl);
  dasr = dasr - 9.0 * cos (xlp + d + d) - 7.0 * cos (xl - xlp - d - d);
  dasr = dasr + 7.0 * cos (xl - xlp + d+d);
  dasr = dasr - 9.0 * cos (xl + xl - d - d) + 8.0 * cos (xl + xl + d + d);
  dasr = dasr + 8.0 * cos (4.0 * d);

  // units: km
  BodyMoon[0] = EarthMoon[0] * 384389.3 / (1.0 + 1.0e-5 * dasr);
  BodyMoon[1] = EarthMoon[1] * 384389.3 / (1.0 + 1.0e-5 * dasr);
  BodyMoon[2] = EarthMoon[2] * 384389.3 / (1.0 + 1.0e-5 * dasr);

}


void BodyEphem::defaultCearthPosition (double t, double BodyEarth[3])
{
  // computation of the Earth position wrt the central body (units: km)
  // =================================================================

  // In this case : central body = Earth

  BodyEarth[0] = 0. ;
  BodyEarth[1] = 0. ; 
  BodyEarth[2] = 0. ;

}


double BodyEphem::defaultFsiderealTime (double* t, double* offset)
{

  return defaultCsiderealTime(* t, * offset);

}

void BodyEphem::defaultFsunPosition (double* t, double BodySun[3])
{
  defaultCsunPosition (* t, BodySun);
}


void BodyEphem::defaultFmoonPosition (double* t, double BodyMoon[3])
{
  defaultCmoonPosition (* t, BodyMoon);
}


void BodyEphem::defaultFearthPosition (double* t, double BodyEarth[3])
{
  defaultCearthPosition (* t, BodyEarth);
}

