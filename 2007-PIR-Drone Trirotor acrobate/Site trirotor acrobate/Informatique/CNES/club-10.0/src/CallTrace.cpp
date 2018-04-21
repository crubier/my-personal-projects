////////////////////////////////////////////////////////////////////////////////
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
//
//$Resume
//       implementation file for class CallTrace
//
//$Description
//       definition module for the class
//
//$Contenu
//
//$Historique
//       $Log: CallTrace.cpp,v $
//       Revision 1.6  2005/02/04 10:14:09  chope
//       remplace;ent d'un code d'erreur
//
//       Revision 1.5  2003/02/27 09:41:41  club
//       FA-ID 21 Modification du commentaire du code après vérification de la dernière norme
//
//       Revision 1.4  2003/02/26 14:54:35  club
//       FA-ID 21 Contournement d'un bogue lors de l'écriture de l'adresse NULL avec le compilateur GCC 3.2.1
//
//       Revision 1.3  2002/12/10 08:50:16  club
//       Modification portant sur l'initialisation des pointeurs dans le fichier CC (DM 12 - mise en conformité avec les normes qualités projet ATV).
//
//       Revision 1.2  2001/06/22 05:42:38  club
//       corrected a variable type (from long to ios::fmtflags)
//
//       Revision 1.1  2001/06/05 15:02:59  club
//       initial version
//
//$Version
//       $Id: CallTrace.cpp,v 1.6 2005/02/04 10:14:09 chope Exp $
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "ClubConfigNoInstall.h"

#if HAVE_CTIME
# include <ctime>
#endif

#include <iomanip>

#include "club/CallTrace.h"
#include "club/ClubErreurs.h"

// implementation of the only instance
CallTrace *CallTrace::instance_ = 0;

// simple constructor
CallTrace::CallTrace ()
  : inCall_ (false), awaken_ (false)
{}

// get the singleton
CallTrace *CallTrace::getInstance ()
  throw (ClubErreurs)
{
  if (instance_ == 0)
  {
    instance_ = new CallTrace ();
    if (instance_ == 0)
      throw ClubErreurs (ClubErreurs::allocation_memoire);
  }
  return instance_;
}

// activate the tracing status
void CallTrace::activate (string fileName)
  throw (ClubErreurs)
{
  time_t t;
  struct tm *gmt = NULL;

  // reset existing trace status
  deactivate ();

  // open a new log file
  logFile_.open (fileName.c_str (), ios::out);
  if (! logFile_.good ())
  {
    logFile_.close ();
    throw ClubErreurs (ClubErreurs::ouverture_fichier, fileName.c_str ());
  }
  logFile_.setf (ios::scientific, ios::floatfield);
  logFile_.precision (17);

  // write a header
  time (&t);
  gmt = gmtime (&t);
  logFile_ << "# Marmottes trace" << endl;
  logFile_ << setfill ('0')
           << "# date : " << (gmt->tm_year + 1900)
           << '-' << setw (2) << (gmt->tm_mon + 1)
           << '-' << setw (2) << gmt->tm_mday
           << 'T' << setw (2) << gmt->tm_hour
           << ':' << setw (2) << gmt->tm_min
           << ':' << setw (2) << gmt->tm_sec
           << endl;
  logFile_ << endl;

  inCall_ = false;
  awaken_ = true;

}

// deactivate the tracing status
void CallTrace::deactivate ()
{
  if (logFile_.is_open ())
    logFile_.close ();
  registeredObjects_.clear ();
  inCall_ = false;
  awaken_ = false;
}

// temporary shut call traces
void CallTrace::putToSleep ()
{
  awaken_ = false;
}

// recover normal status
void CallTrace::wakeUp ()
{
  awaken_ = true;
}

// register some objects to ensure they can be used later on
void CallTrace::registerObject (const void *p)
{
  if (awaken_)
    registeredObjects_ [p] = p;
}

void CallTrace::unregisterObject (const void *p)
{
  if (awaken_)
    registeredObjects_.erase (p);
}

bool CallTrace::isRegistered (const void *p) const
{
  return registeredObjects_.find (p) != registeredObjects_.end ();
}

// write the calls
void CallTrace::startCall (string functionName, const void *object)
  throw (ClubErreurs)
{
  if (!awaken_)
    return;

  if (! logFile_.is_open ())
    throw ClubErreurs (ClubErreurs::calltrace_not_activated);

  if (inCall_)
    throw ClubErreurs (ClubErreurs::internal_error, __LINE__, __FILE__);

  ios::fmtflags oldBase = logFile_.setf (ios::hex, ios::basefield);
  logFile_.setf (ios::showbase);
  logFile_ << functionName << ' ' << (unsigned long) object;
  logFile_.setf (oldBase, ios::basefield);
  logFile_.unsetf (ios::showbase);

  inCall_ = true;

}

void CallTrace::endCall ()
  throw (ClubErreurs)
{
  if (!awaken_)
    return;

  if (! logFile_.is_open ())
    throw ClubErreurs (ClubErreurs::calltrace_not_activated);

  if (! inCall_)
    throw ClubErreurs (ClubErreurs::internal_error, __LINE__, __FILE__);

  logFile_ << endl;

  inCall_ = false;

}

void CallTrace::startResult ()
  throw (ClubErreurs)
{
  if (!awaken_)
    return;

  if (! logFile_.is_open ())
    throw ClubErreurs (ClubErreurs::calltrace_not_activated);

  if (inCall_)
    throw ClubErreurs (ClubErreurs::internal_error, __LINE__, __FILE__);

  logFile_ << "  -> ";

  inCall_ = true;

}

void CallTrace::endResult ()
  throw (ClubErreurs)
{
  if (!awaken_)
    return;

  if (! logFile_.is_open ())
    throw ClubErreurs (ClubErreurs::calltrace_not_activated);

  if (! inCall_)
    throw ClubErreurs (ClubErreurs::internal_error, __LINE__, __FILE__);

  logFile_ << endl;

  inCall_ = false;

}

void CallTrace::logBool (bool b)
  throw (ClubErreurs)
{
  if (!awaken_)
    return;

  if (! logFile_.is_open ())
    throw ClubErreurs (ClubErreurs::calltrace_not_activated);

  if (! inCall_)
    throw ClubErreurs (ClubErreurs::internal_error, __LINE__, __FILE__);

  logFile_ << ' ' << b;

}

void CallTrace::logInt (int i)
  throw (ClubErreurs)
{
  if (!awaken_)
    return;

  if (! logFile_.is_open ())
    throw ClubErreurs (ClubErreurs::calltrace_not_activated);

  if (! inCall_)
    throw ClubErreurs (ClubErreurs::internal_error, __LINE__, __FILE__);

  logFile_ << ' ' << i;

}

void CallTrace::logDouble (double d)
  throw (ClubErreurs)
{
  if (!awaken_)
    return;

  if (! logFile_.is_open ())
    throw ClubErreurs (ClubErreurs::calltrace_not_activated);

  if (! inCall_)
    throw ClubErreurs (ClubErreurs::internal_error, __LINE__, __FILE__);

  logFile_ << ' ' << d;

}

void CallTrace::logString (string s)
  throw (ClubErreurs)
{
  if (!awaken_)
    return;

  if (! logFile_.is_open ())
    throw ClubErreurs (ClubErreurs::calltrace_not_activated);

  if (! inCall_)
    throw ClubErreurs (ClubErreurs::internal_error, __LINE__, __FILE__);

  logFile_ << ' ' << s;

}

void CallTrace::logPointer (void *p)
  throw (ClubErreurs)
{
  if (!awaken_)
    return;

  if (! logFile_.is_open ())
    throw ClubErreurs (ClubErreurs::calltrace_not_activated);

  if (! inCall_)
    throw ClubErreurs (ClubErreurs::internal_error, __LINE__, __FILE__);

  // Old compilers (e.g. g++ prior to version 3.2.1) use 0x
  // as a prefix for all values. It seems this is an error
  // and new version of g++ use this prefix only if the value
  // is non null (i.e. 0 IS a special case and should always
  // be displayed as 0, even if showbase is true and if base
  // is hex or oct).
  // We prefer here to have an hint showing the value is a
  // pointer and so explicitly put 0x0 for null pointers,
  // just in case this code is compiled by a recent compiler.
  if (p == 0)
  {
    logFile_ << " 0x0";
  }
  else
  {
    ios::fmtflags  oldBase = logFile_.setf (ios::hex, ios::basefield);
    logFile_.setf (ios::showbase);
    logFile_ << ' ' << (unsigned long) p;
    logFile_.setf (oldBase, ios::basefield);
    logFile_.unsetf (ios::showbase);
  }

}
