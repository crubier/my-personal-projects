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
//>       BodyEphemF.cpp
//$Resume
//       implantation file of the BodyEphemF class
//
//$Description
//       Definition module of the class
//
//$Contenu
//>       class BodyEphemF 
//>         BodyEphemF()   
//>         operator =()   
//>         clone()        
//>         siderealTime() 
//>         sunPosition()  
//>         moonPosition() 
//>         earthPosition()
//$Historique
//       $Log: BodyEphemF.cpp,v $
//       Revision 1.6  2003/07/02 15:22:10  marmottes
//       Mise en conf pour sauvegarde des modifs suite a la FA sur la mise a disposition des fonctions de calcul par defaut du temps sideral, de la position de la Lune de la Terre et du Soleil pour linterface Fortran
//
//       Revision 1.5  2003/07/02 07:24:19  marmottes
//       Mise en conf pour sauvegarde des modifs suite a la DM sur la mise a disposition des fonctions de calcul par defaut du temps sideral, de la position de la Lune de la Terre et du Soleil pour linterface Fortran
//
//       Revision 1.4  2003/02/27 16:39:22  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.3  2003/02/04 16:21:35  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.2  2002/12/18 16:10:32  marmottes
//       FA-ID 20 Ajout d'appel aux fonctionnalitées de trace des appels des fonctions enregitrées par un utilisateur
//
//       Revision 1.1  2002/09/09 13:44:51  marmottes
//       Initial version (DM 0007)
//
//$Version
//       $Id: BodyEphemF.cpp,v 1.6 2003/07/02 15:22:10 marmottes Exp $
//
//$Auteur
//       G. Prat and L. Maisonobe CS SI
//       Copyright (C) 2002 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/BodyEphemF.h"
#include "club/CallTrace.h"


// default constructor
BodyEphemF::BodyEphemF ()
{
  // for use of default functions if none are given by the user
  tsidFuncPtr_  = defaultFsiderealTime;
  sunFuncPtr_   = defaultFsunPosition;
  moonFuncPtr_  = defaultFmoonPosition;
  earthFuncPtr_ = defaultFearthPosition;
}

// copy constructor
BodyEphemF::BodyEphemF (const BodyEphemF& b)
  : BodyEphem (b)
{
  tsidFuncPtr_  = b.tsidFuncPtr_;
  sunFuncPtr_   = b.sunFuncPtr_;
  moonFuncPtr_  = b.moonFuncPtr_;
  earthFuncPtr_ = b.earthFuncPtr_;
}

// affectation
const BodyEphemF& BodyEphemF::operator = (const BodyEphemF& b)
{
  if (this != &b)  // protection against x = x
  {
    BodyEphem::operator = (b);
    tsidFuncPtr_  = b.tsidFuncPtr_;
    sunFuncPtr_   = b.sunFuncPtr_;
    moonFuncPtr_  = b.moonFuncPtr_;
    earthFuncPtr_ = b.earthFuncPtr_;
  }
  return *this;
}

// in case the user gives equatorial radius, oblateness, rotation 
// velocity of the central body and
// functions for computation of sidereal time, and Sun, Moon and Earth positions
BodyEphemF::BodyEphemF (double equatorialRadius, double oblateness, double rotationVelocity, 
                        double moonRadius, double sunRadius,
                        TypeFuncTsid *tsidFunc,
                        TypeFuncPos *sunFunc, TypeFuncPos *moonFunc, TypeFuncPos *earthFunc)
  : BodyEphem (equatorialRadius, oblateness, rotationVelocity, moonRadius, sunRadius)
{

    if (tsidFunc == 0) // null pointer : use of the default function
        tsidFuncPtr_ = defaultFsiderealTime ;
    else
        tsidFuncPtr_ = tsidFunc;

    if (sunFunc == 0) // null pointer : use of the default function
        sunFuncPtr_ = defaultFsunPosition ;
    else
        sunFuncPtr_ = sunFunc;


    if (moonFunc == 0) // null pointer : use of the default function
        moonFuncPtr_ = defaultFmoonPosition ;
    else
        moonFuncPtr_ = moonFunc;

    if (earthFunc == 0) // null pointer : use of the default function
        earthFuncPtr_ = defaultFearthPosition ;
    else
        earthFuncPtr_ = earthFunc;
}


BodyEphem * BodyEphemF::clone () const
{
  return new BodyEphemF (*this);
}

double BodyEphemF::siderealTime (double t, double offset)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive() && (tsidFuncPtr_ != defaultFsiderealTime))
  {
    trace->startCall (string ("BodyEphemF::siderealTime"), (void *) 0);
    trace->logDouble (t);
    trace->logDouble (offset);
    trace->endCall ();
  }
  
  double result = tsidFuncPtr_ (&t, &offset);
  if (trace->isActive() && (tsidFuncPtr_ != defaultFsiderealTime))
  {
    trace->startResult ();
    trace->logDouble (result);
    trace->endResult ();
  }

  return result;
}

VecDBL BodyEphemF::sunPosition (double t)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive() && (sunFuncPtr_ != defaultFsunPosition))
  {
    trace->startCall (string ("BodyEphemF::sunPosition"), (void *) 0);
    trace->logDouble (t);
    trace->endCall ();
  }

  double pos[3];
  sunFuncPtr_ (&t, pos);

  if (trace->isActive() && (sunFuncPtr_ != defaultFsunPosition))
  {
    trace->startResult ();
    trace->logDouble (pos[0]);
    trace->logDouble (pos[1]);
    trace->logDouble (pos[2]);
    trace->endResult ();
  }

  return VecDBL (pos[0], pos[1], pos[2]);
}

VecDBL BodyEphemF::moonPosition (double t)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive() && (moonFuncPtr_ != defaultFmoonPosition))
  {
    trace->startCall (string ("BodyEphemF::moonPosition"), (void *) 0);
    trace->logDouble (t);
    trace->endCall ();
  }

  double pos[3];
  moonFuncPtr_ (&t, pos);

  if (trace->isActive() && (moonFuncPtr_ != defaultFmoonPosition))
  {
    trace->startResult ();
    trace->logDouble (pos[0]);
    trace->logDouble (pos[1]);
    trace->logDouble (pos[2]);
    trace->endResult ();
  }

  return VecDBL (pos[0], pos[1], pos[2]);
}

VecDBL BodyEphemF::earthPosition (double t)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive() && (earthFuncPtr_ != defaultFearthPosition))
  {
    trace->startCall (string ("BodyEphemF::earthPosition"), (void *) 0);
    trace->logDouble (t);
    trace->endCall ();
  }

  double pos[3];
  earthFuncPtr_ (&t, pos);

  if (trace->isActive() && (earthFuncPtr_ != defaultFearthPosition))
  {
    trace->startResult ();
    trace->logDouble (pos[0]);
    trace->logDouble (pos[1]);
    trace->logDouble (pos[2]);
    trace->endResult ();
  }

  return VecDBL (pos[0], pos[1], pos[2]);
}

