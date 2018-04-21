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
//>       BodyEphemC.cpp
//$Resume
//       implantation file of the BodyEphemC class
//
//$Description
//       Definition module of the class
//
//$Contenu
//>       class BodyEphemC 
//>         BodyEphemC()   
//>         operator =()   
//>         clone()        
//>         siderealTime() 
//>         sunPosition()  
//>         moonPosition() 
//>         earthPosition()
//$Historique
//       $Log: BodyEphemC.cpp,v $
//       Revision 1.5  2003/02/27 16:39:05  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.4  2003/02/04 16:20:53  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.3  2002/12/18 16:10:15  marmottes
//       FA-ID 20 Ajout d'appel aux fonctionnalitées de trace des appels des fonctions enregitrées par un utilisateur
//
//       Revision 1.2  2002/09/13 08:54:54  marmottes
//       homogénéisation de l'appel à la fonction utilisateur (rendu identique
//       à celui fait dans sunPosition)
//
//       Revision 1.1  2002/09/09 13:44:36  marmottes
//       Initial version (DM 0007)
//
//$Version
//       $Id: BodyEphemC.cpp,v 1.5 2003/02/27 16:39:05 marmottes Exp $
//
//$Auteur
//       G. Prat and L. Maisonobe CS SI
//       Copyright (C) 2002 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/BodyEphemC.h"
#include "club/CallTrace.h"


// default constructor
BodyEphemC::BodyEphemC ()
{
  // for use of default functions if none are given by the user
  tsidFuncPtr_  = defaultCsiderealTime;
  sunFuncPtr_   = defaultCsunPosition;
  moonFuncPtr_  = defaultCmoonPosition;
  earthFuncPtr_ = defaultCearthPosition;
}

// copy constructor
BodyEphemC::BodyEphemC (const BodyEphemC& b)
  : BodyEphem (b)
{
  tsidFuncPtr_  = b.tsidFuncPtr_;
  sunFuncPtr_   = b.sunFuncPtr_;
  moonFuncPtr_  = b.moonFuncPtr_;
  earthFuncPtr_ = b.earthFuncPtr_;
}

// affectation
const BodyEphemC& BodyEphemC::operator = (const BodyEphemC& b)
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
BodyEphemC::BodyEphemC (double equatorialRadius, double oblateness, double rotationVelocity,
                        double moonRadius, double sunRadius,
                        TypeFuncTsid *tsidFunc,
                        TypeFuncPos *sunFunc, TypeFuncPos *moonFunc, TypeFuncPos *earthFunc)
  : BodyEphem (equatorialRadius, oblateness, rotationVelocity, moonRadius, sunRadius)
{
  if (tsidFunc == 0) // null pointer : use of the default function
    tsidFuncPtr_ = defaultCsiderealTime ;
  else
    tsidFuncPtr_ = tsidFunc;


  if (sunFunc == 0) // null pointer : use of the default function
    sunFuncPtr_ = defaultCsunPosition ;
  else
    sunFuncPtr_ = sunFunc;


  if (moonFunc == 0) // null pointer : use of the default function
    moonFuncPtr_ = defaultCmoonPosition ;
  else
    moonFuncPtr_ = moonFunc;


  if (earthFunc == 0) // null pointer : use of the default function
    earthFuncPtr_ = defaultCearthPosition ;
  else
    earthFuncPtr_ = earthFunc;

}


BodyEphem * BodyEphemC::clone () const
{
  return new BodyEphemC (*this);
}

double BodyEphemC::siderealTime (double t, double offset)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive() && (tsidFuncPtr_ != defaultCsiderealTime))
  {
    trace->startCall (string ("BodyEphemC::siderealTime"), (void *) 0);
    trace->logDouble (t);
    trace->logDouble (offset);
    trace->endCall ();
  }
  
  double result = (*tsidFuncPtr_) (t, offset);

  if (trace->isActive() && (tsidFuncPtr_ != defaultCsiderealTime))
  {
    trace->startResult ();
    trace->logDouble (result);
    trace->endResult ();
  }

  return result;
}

VecDBL BodyEphemC::sunPosition (double t)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive() && (sunFuncPtr_ != defaultCsunPosition))
  {
    trace->startCall (string ("BodyEphemC::sunPosition"), (void *) 0);
    trace->logDouble (t);
    trace->endCall ();
  }

  double pos[3];
  (*sunFuncPtr_) (t, pos);

  if (trace->isActive() && (sunFuncPtr_ != defaultCsunPosition))
  {
    trace->startResult ();
    trace->logDouble (pos[0]);
    trace->logDouble (pos[1]);
    trace->logDouble (pos[2]);
    trace->endResult ();
  }

  return VecDBL (pos[0], pos[1], pos[2]);
}

VecDBL BodyEphemC::moonPosition (double t)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive() && (moonFuncPtr_ != defaultCmoonPosition))
  {
    trace->startCall (string ("BodyEphemC::moonPosition"), (void *) 0);
    trace->logDouble (t);
    trace->endCall ();
  }

  double pos[3];
  (*moonFuncPtr_) (t, pos);

  if (trace->isActive() && (moonFuncPtr_ != defaultCmoonPosition))
  {
    trace->startResult ();
    trace->logDouble (pos[0]);
    trace->logDouble (pos[1]);
    trace->logDouble (pos[2]);
    trace->endResult ();
  }

  return VecDBL (pos[0], pos[1], pos[2]);
}

VecDBL BodyEphemC::earthPosition (double t)
{
  CallTrace *trace = CallTrace::getInstance ();
  if (trace->isActive() && (earthFuncPtr_ != defaultCearthPosition))
  {
    trace->startCall (string ("BodyEphemC::earthPosition"), (void *) 0);
    trace->logDouble (t);
    trace->endCall ();
  }

  double pos[3];
  (*earthFuncPtr_) (t, pos);

  if (trace->isActive() && (earthFuncPtr_ != defaultCearthPosition))
  {
    trace->startResult ();
    trace->logDouble (pos[0]);
    trace->logDouble (pos[1]);
    trace->logDouble (pos[2]);
    trace->endResult ();
  }

  return VecDBL (pos[0], pos[1], pos[2]);
}

