////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//        Bibam
//$Application
//        Club
//$Nom
//
//$Resume
//       fichier de test de la classe XMLUnits
//
//$Description
//       Module de test de la classe
//
//$Contenu
//
//$Historique
//       $Log: prgm_XMLUnits.cpp,v $
//       Revision 1.1  2005/02/21 13:01:09  chope
//       version initiale
//
//
//$Version
//       $Id: prgm_XMLUnits.cpp,v 1.1 2005/02/21 13:01:09 chope Exp $
//$Auteur
//        L. Maisonobe CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#include <cstdlib>

#ifdef HAVE_IOSTREAM
#include <iostream>
#endif

#include "club/ClubErreurs.h"
#include "club/XMLUnits.h"

int main (int argc, char **argv)
{
  try {

    // check the command line
    if (argc != 5)
    {
      cerr << "prgm_XMLUnits units-file value unit1 unit2" << endl;
      return 1;
    }

    XMLUnits units (argv[1]);
    double converted = units.convert (atof (argv[2]),
                                      XMLString::transcode (argv[3]),
                                      XMLString::transcode (argv[4]));
    cout << argv [2] << ' ' << argv [3] << " -> "
         << converted << ' ' << argv [4] << endl;

    return 0;

  }
  catch (ClubErreurs ce)
  {
    cout << argv [2] << ' ' << argv [3] << " -> "
         << "??? " << argv [4]
         << ' ' << ce.why () << endl; 
    ce.correction ();
    return 1;
  }
}
