///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//       Chope
//
//$Application
//       Club
//
//$Nom
//>       CallTrace.h
//$Resume
//       header file for class CallTrace
//
//$Description
//       declaration module for the class
//
//$Contenu
//>       class CallTrace
//$Historique
//       $Log: CallTrace.h,v $
//       Revision 1.2  2002/12/09 15:52:50  club
//       DM-ID 12 Mise en conformité des constructeurs/destructeurs avec la norme qualité
//
//       Revision 1.1  2001/06/05 15:00:24  club
//       initial version
//
//$Version
//       $Id: CallTrace.h,v 1.2 2002/12/09 15:52:50 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_CallTrace_h
#define __club_CallTrace_h

#include <fstream>
#include <map>
#include <string>

#include "club/ClubErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class CallTrace
//$Resume
//       this class handles debugging call trace for libraries
//
//$Description
//       This class handles debugging trace for the public interface
//       of libraries (high level functions). It allows to toggle on
//       and off the tracing status and write all calls to the public
//       interface in a log file when this status is on. It also
//       handles reading these files and performing playback.
//
//       The write part is mainly used by end users when they
//       encounter problems and want to submit bug reports while the
//       reading part is mainly used by developpers while analyzing
//       such bug reports or for non-regression tests.
//
//$Usage
//>     construction : 
//          this is a singleton design pattern, it should not been built
//          except by itself
//>     utilisation  : 
//>       void activate         () 
//          activate the tracing mechanism
//>       void deactivate       () 
//          deactivate the tracing mechanism
//>       void putToSleep       () 
//          temporarily stop the tracinf mechanisms
//>       void wakeUp           () 
//          reset the normal tracing status
//>       void registerObject   () 
//          register an object reference to reckognize calls involving it
//>       void unregisterObject () 
//          remove an object reference
//>       bool isRegistered     () 
//          check if an object is registered
//>       bool isActive         () 
//          check if the tracing mechanisms is activated
//>       void startCall        () 
//          start logging a call
//>       void endCall          () 
//          stop loggin a call
//>       void startResult      () 
//          start logging the result of a call
//>       void endResult        () 
//          stop logging the result of a call
//>       void logBool          () 
//          log a boolean argument
//>       void logInt           () 
//          log an integer argument
//>       void logDouble        () 
//          log a double argument
//>       void logString        () 
//          log a string argument
//>       void logPointer       () 
//          log a pointer argument
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////
class CallTrace
{

public :

  static CallTrace *getInstance ()
    throw (ClubErreurs);

  // tracing status handling
  void activate (string fileName)
    throw (ClubErreurs);

  void deactivate ();

  bool isActive () { return logFile_.is_open (); }

  // temporary status changes
  void putToSleep ();

  void wakeUp ();

  // objects references storage
  void registerObject (const void *p);

  void unregisterObject (const void *p);

  bool isRegistered (const void *p) const;

  // call traces
  void startCall (string functionName, const void *object)
    throw (ClubErreurs);

  void logBool (bool b)
    throw (ClubErreurs);

  void logInt (int i)
    throw (ClubErreurs);

  void logDouble (double d)
    throw (ClubErreurs);

  void logString (string s)
    throw (ClubErreurs);

  void logPointer (void *p)
    throw (ClubErreurs);

  void endCall ()
    throw (ClubErreurs);

  void startResult ()
    throw (ClubErreurs);

  void endResult ()
    throw (ClubErreurs);

private :

  // the only allowed instance (singleton)
  static CallTrace *instance_;

  ofstream                        logFile_;
  map<const void *, const void *> registeredObjects_;
  bool                            inCall_;
  bool                            awaken_;

  // the tracing instance is a singleton (in the design patterns
  // terminology), so all its constructors are private to prevent
  // inadvertent instanciations
  CallTrace ();
  CallTrace (const CallTrace& c) {}
  CallTrace& operator = (const CallTrace& c) { return *this; }

  // destructor
  ~CallTrace () {};

};

#endif
