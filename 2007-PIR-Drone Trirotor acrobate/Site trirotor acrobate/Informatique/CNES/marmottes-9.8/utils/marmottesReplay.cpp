////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//       Marmottes
//
//$Application
//       marmottesReplay
//
//$Nom
//       marmottesReplay.cc
//$Resume
//       fichier d'exploitation des LOG utilisateurs.
//
//$Description
//       Ce programme permet le rejoue d'un fichier de LOG fourni par
//       l'utilisateur et permettant aux programmeurs de rejouer un
//       contexte litigieux et de deboguer si besoin.
//
//$Contenu
//
//$Historique
//       $Log: marmottesReplay.cpp,v $
//       Revision 1.6  2003/10/22 13:09:12  marmottes
//       DM 0027, 0028
//
//       Revision 1.5  2003/10/08 09:43:13  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 1.4  2003/02/27 16:50:05  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.3  2002/12/18 15:37:48  marmottes
//       DM-ID 13 Ajout de la fonctionnalité de traitement des fonctions enregistrées par l'utilisateur
//
//$Version
//       $Id: marmottesReplay.cpp,v 1.6 2003/10/22 13:09:12 marmottes Exp $
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2002 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <cstring>
#include <cstdlib>

#include <string>
#include <iostream>
#include <map>

#include "club/TamponTexte.h"
#include "club/OptionsAppli.h"
#include "cantor/Util.h"
#include "cantor/DeclDBL.h"
#include "club/CallTrace.h"

#include "marmottes/Marmottes.h"
#include "marmottes/MarmottesErreurs.h"

// global variables
int l;
TamponTexte file;

static void argumentsAnalyze (int argc, char** argv,
                              string *ptrInput, string *ptrOutput,
                              string *ptrDirectory, bool *ptrVerbose)
  throw (ClubErreurs)
{ // command line arguments analyze
  OptionsAppli analyzer (argv [0]);

  // input file name
  // unnamed option: one occurrence, no default value
  analyzer.ajouterOption (OptionChaine ("", 1, 1, sansValeurDefaut, "", 1000));

  // output file name
  // option o: zero or one occurrence, no default value
  analyzer.ajouterOption (OptionChaine ("o", 0, 1, sansValeurDefaut, "", 1000));

  // directory
  // option d: zero or one occurrence, default value : "."
  analyzer.ajouterOption (OptionChaine ("d", 0, 1, avecValeurDefaut, ".", 1000));

  // verbose mode
  // option v: zero or one occurrence
  analyzer.ajouterOption (OptionSansValeur ("v", 0, 1));

  // analyze
  analyzer.initialiser (argc, argv);
  analyzer.garantirComplet ();

  // data extraction
  analyzer.lireValeur ("",  ptrInput);
  if (analyzer.occurrencesPassees ("o") > 0)
    analyzer.lireValeur ("o",  ptrOutput);
  else
    *ptrOutput = string ("");
  analyzer.lireValeur ("d",  ptrDirectory);
  *ptrVerbose = (analyzer.occurrencesPassees ("v") > 0);

}

void checkLine (const TamponTexte& file, int line, int args)
  throw (ClubErreurs)
{
  if (file.nombreChampsLigne (line) != (args + 2))
    throw ClubErreurs (ClubErreurs::message_simple, file.ligne (line));
}

bool resultLine (const TamponTexte& file, int line, int args)
{
  if (file.nombreChampsLigne (line) != (args + 1))
    return false;
  else
    return true;
}

Marmottes *getSimulator (const char *key,
                         const map<string, Marmottes *>& simulator,
                         bool failIfNotFound)
  throw (ClubErreurs)
{
  string skey (key);
  map<string, Marmottes *>::const_iterator found = simulator.find (skey);
  if (found == simulator.end ())
  {
    if (failIfNotFound)
      throw ClubErreurs (ClubErreurs::message_simple, skey.c_str ());
    else
      return 0;
  }
  else
    return found->second;
}

string basename (const string& directory, const char *field)
{
  string path (field);
  string::size_type last  = path.rfind  ('/', path.size ());
  return directory + path.substr (last + 1, path.size ());
}

double userSiderealTime (double t, double offset)
{
  int lbeg  = l + 1;
  int lend  = lbeg;

  double siderealTime = 0.;

  bool occurrenceFound = false;

  // search for the upper line boundary assuming that all lines
  // between two consecutive marmottes calls is filled with
  // BodyEphemC or BodyEphemF calls
  do {
    lend++;
  } while ((strstr(file.champLigne(1, lend),"Marmottes::") == NULL)
           && (lend < file.nombreLignes()));

  // scan lines between lower (lbeg) and upper (lend) line boundary
  int lcurr = lbeg;
  do
  {
    // scan lines until we found the first sidereal time call
    if (((strcmp(file.champLigne(1, lcurr), "BodyEphemC::siderealTime") == 0) ||
        (strcmp(file.champLigne(1, lcurr), "BodyEphemF::siderealTime") == 0)) &&
        ((strcmp(file.champLigne(2, lcurr), "0x0") == 0)
         || (strcmp(file.champLigne(2, lcurr), "0") == 0)))
    {
      // we found a line calling the user sidereal time function
      if (abs(atof(file.champLigne(3, lcurr)) - t) <= 1.e-10)
      {
        int lres = lcurr + 1;
        if ((strcmp (file.champLigne(1, lres), "->") == 0) && (resultLine(file, lres, 1)))
        {
          // result like line - get the result from line
          siderealTime = atof(file.champLigne (2, lres));
          occurrenceFound= true;
        }
        else
        {
          // not a result like line - send a error message
          cout << "Truncated line: " << lcurr << endl;
        }
      }
    }
    lcurr++;
  } while ((lcurr < lend) && (! occurrenceFound));

  if (! occurrenceFound) 
  {
    cout << "Cannot retrieve sidereal time value from file at time: " << t << endl;
  }
  return  siderealTime;
}

void userSunPosition (double t, double pos[3])
{
  int lbeg  = l + 1;
  int lend  = lbeg;

  bool occurrenceFound = false;

  pos[0] = 1.0;
  pos[1] = 0.0;
  pos[2] = 0.0;

  // search for the upper line boundary assuming that all lines
  // between two consecutive marmottes calls is filled with
  // BodyEphemC or BodyEphemF calls
  do {
    lend++;
  } while ((strstr(file.champLigne(1, lend),"Marmottes::") == NULL)
           && (lend < file.nombreLignes()));

  // scan lines between lower (lbeg) and upper (lend) line boundary
  int lcurr = lbeg;
  do
  {
    // scan lines until we found the first sun position call
    if ((strcmp(file.champLigne(1, lcurr), "BodyEphemC::sunPosition") == 0) ||
        (strcmp(file.champLigne(1, lcurr), "BodyEphemF::sunPosition") == 0))
    {
      // user's sun position function call found
      if (abs(atof(file.champLigne(3, lcurr)) - t) <= 1.e-10)
      {
        int lres = lcurr + 1;
        if ((strcmp (file.champLigne(1, lres), "->") == 0) && (resultLine(file, lres, 3)))
        {
          // result like line - get the result from line
          pos[0] = atof(file.champLigne (2, lres));
          pos[1] = atof(file.champLigne (3, lres));
          pos[2] = atof(file.champLigne (4, lres));
          occurrenceFound = true;
        }
        else
        {
          // not a result like line - send a error message
          cout << "Truncated line: " << lcurr << endl;
        }
      }
    }
    lcurr++;
  } while ((lcurr < lend) && (! occurrenceFound));
  if (! occurrenceFound) 
  {
    cout << "Cannot retrieve Sun position value from file at time: " << t << endl;
  }
}

void userMoonPosition (double t, double pos[3])
{
  int lbeg  = l + 1;
  int lend  = lbeg;

  bool occurrenceFound = false;

  pos[0] = 1.0;
  pos[1] = 0.0;
  pos[2] = 0.0;

  // search for the upper line boundary assuming that all lines
  // between two consecutive marmottes calls is filled with
  // BodyEphemC or BodyEphemF calls
  do {
    lend++;
  } while ((strstr(file.champLigne(1, lend),"Marmottes::") == NULL)
           && (lend < file.nombreLignes()));

  // scan lines between lower (lbeg) and upper (lend) line boundary
  int lcurr = lbeg;
  do
  {
    // scan lines until we found the first sidereal time call
    if ((strcmp(file.champLigne(1, lcurr), "BodyEphemC::moonPosition") == 0) ||
        (strcmp(file.champLigne(1, lcurr), "BodyEphemF::moonPosition") == 0))
    {
      // user's moon position function call found
      if (abs(atof(file.champLigne(3, lcurr)) - t) <= 1.e-10)
      {
        int lres = lcurr + 1;
        if ((strcmp (file.champLigne(1, lres), "->") == 0) && (resultLine(file, lres, 3)))
        {
          // result like line - get the result from line
          pos[0] = atof(file.champLigne (2, lres));
          pos[1] = atof(file.champLigne (3, lres));
          pos[2] = atof(file.champLigne (4, lres));
          occurrenceFound = true;
        }
        else
        {
          // not a result like line - send a error message
          cout << "Truncated line: " << lcurr << endl;
        }
      }
    }
    lcurr++;
  } while ((lcurr < lend) && (! occurrenceFound));
  if (! occurrenceFound) 
  {
    cout << "Cannot retrieve Moon position value from file at time: " << t << endl;
  }
}

void userEarthPosition (double t, double pos[3])
{
  int lbeg  = l + 1;
  int lend  = lbeg;

  bool occurrenceFound = false;

  pos[0] = 1.0;
  pos[1] = 0.0;
  pos[2] = 0.0;

  // search for the upper line boundary assuming that all lines
  // between two consecutive marmottes calls is filled with
  // BodyEphemC or BodyEphemF calls
  do {
    lend++;
  } while ((strstr(file.champLigne(1, lend),"Marmottes::") == NULL)
           && (lend < file.nombreLignes()));

  // scan lines between lower (lbeg) and upper (lend) line boundary
  int lcurr = lbeg;
  do
  {
    // scan lines until we found the first earth position call
    if ((strcmp(file.champLigne(1, lcurr), "BodyEphemC::earthPosition") == 0) ||
        (strcmp(file.champLigne(1, lcurr), "BodyEphemF::earthPosition") == 0))
    {
      // user's earth position function call found
      if (abs(atof(file.champLigne(3, lcurr)) - t) <= 1.e-10)
      {
        int lres = lcurr + 1;
        if ((strcmp (file.champLigne(1, lres), "->") == 0) && (resultLine(file, lres, 3)))
        {
          // result like line - get the result from line
          pos[0] = atof(file.champLigne (2, lres));
          pos[1] = atof(file.champLigne (3, lres));
          pos[2] = atof(file.champLigne (4, lres));
          occurrenceFound = true;
        }
        else
        {
          // not a result like line - send a error message
          cout << "Truncated line: " << lcurr << endl;
        }
      }
    }
    lcurr++;
  } while ((lcurr < lend) && (! occurrenceFound));  
  if (! occurrenceFound) 
  {
    cout << "Cannot retrieve Earth position value from file at time: " << t << endl;
  }
}

int main (int argc, char** argv)
{ // replay program for marmottes

  try
  {
    ClubAllocHandler h; // used only for its constructor/destructor

    // call trace file handling
    string input, output, directory;
    bool   verbose;
    argumentsAnalyze (argc, argv, &input, &output, &directory, &verbose);
    if (directory [directory.size () - 1] != '/')
      directory.append (1, '/');
    file = TamponTexte(input.c_str ());
    file.elimineCommentaires ();
    file.elimineBlancs ();
    if (output.length () > 0)
      CallTrace::getInstance ()->activate (output);

    // simulators map
    map<string, Marmottes *> simulator;

    // main loop
    for (l = 1; l <= file.nombreLignes (); ++l)
    {
      if (file.nombreChampsLigne (l) < 2)
        throw ClubErreurs (ClubErreurs::message_simple, file.ligne (l));
      else
      {
        if (strcmp (file.champLigne (1, l), "->") == 0)
          continue;

        if (verbose)
          cout << "calling: " << file.champLigne (1, l) << endl;

        try
        {

          if (strcmp (file.champLigne (1, l), "Marmottes::copyConstructor") == 0)
          {
            checkLine (file, l, 1);
            Marmottes *arg = getSimulator (file.champLigne (3, l), simulator,
                                           true);
            simulator [file.champLigne (2, l)] = new Marmottes (*arg);
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::operator=") == 0)
          {
            checkLine (file, l, 1);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               false);
            if (thisOne == 0)
            {
              thisOne = new Marmottes ();
              simulator [file.champLigne (2, l)] = thisOne;
            }
            Marmottes *arg = getSimulator (file.champLigne (3, l), simulator,
                                           true);

            *thisOne = *arg;
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::reinitialise") == 0)
          {
            checkLine (file, l, 18);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               false);
            if (thisOne == 0)
            {
              thisOne = new Marmottes ();
              simulator [file.champLigne (2, l)] = thisOne;
            }
            thisOne->reinitialise (atof (file.champLigne (3, l)),
                                   VecDBL (atof (file.champLigne  (4, l)),
                                           atof (file.champLigne  (5, l)),
                                           atof (file.champLigne  (6, l))),
                                   VecDBL (atof (file.champLigne  (7, l)),
                                           atof (file.champLigne  (8, l)),
                                           atof (file.champLigne  (9, l))),
                                   RotDBL (atof (file.champLigne (10, l)),
                                           atof (file.champLigne (11, l)),
                                           atof (file.champLigne (12, l)),
                                           atof (file.champLigne (13, l))),
                                   VecDBL (atof (file.champLigne (14, l)),
                                           atof (file.champLigne (15, l)),
                                           atof (file.champLigne (16, l))),
                                   basename (directory, file.champLigne (17, l)),
                                   string (file.champLigne (18, l)),
                                   string (file.champLigne (19, l)),
                                   string (file.champLigne (20, l)));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::senseurs") == 0)
          {
            checkLine (file, l, 4);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->senseurs (basename (directory, file.champLigne (3, l)),
                               string (file.champLigne (4, l)),
                               string (file.champLigne (5, l)),
                               string (file.champLigne (6, l)));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::nouveauRepere") == 0)
          {
            checkLine (file, l, 6);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->nouveauRepere (basename (directory, file.champLigne (3, l)),
                                    string (file.champLigne (4, l)),
                                    RotDBL (atof (file.champLigne (5, l)),
                                            atof (file.champLigne (6, l)),
                                            atof (file.champLigne (7, l)),
                                            atof (file.champLigne (8, l))));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::calage") == 0)
          {
            checkLine (file, l, 3);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->calage (basename (directory, file.champLigne (3, l)),
                             string (file.champLigne (4, l)),
                             atof   (file.champLigne (5, l)));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::modifieCible") == 0)
          {
            checkLine (file, l, 5);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->modifieCible (basename (directory, file.champLigne (3, l)),
                                   string (file.champLigne (4, l)),
                                   VecDBL (atof (file.champLigne (5, l)),
                                           atof (file.champLigne (6, l)),
                                           atof (file.champLigne (7, l))));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::initialiseGyro") == 0)
          {
            checkLine (file, l, 4);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->initialiseGyro (basename (directory, file.champLigne (3, l)),
                                     string (file.champLigne (4, l)),
                                     atof   (file.champLigne (5, l)),
                                     atof   (file.champLigne (6, l)));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::modifieReference") == 0)
          {
            checkLine (file, l, 6);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->modifieReference (basename (directory, file.champLigne (3, l)),
                                       string (file.champLigne (4, l)),
                                       RotDBL (atof (file.champLigne (5, l)),
                                               atof (file.champLigne (6, l)),
                                               atof (file.champLigne (7, l)),
                                               atof (file.champLigne (8, l))));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::desinitialise") == 0)
          {
            checkLine (file, l, 0);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->desinitialise ();
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::deuxConsignes") == 0)
          {
            checkLine (file, l, 9);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            RotDBL attitude;
            VecDBL spin;
            thisOne->deuxConsignes (atof (file.champLigne (3, l)),
                                    VecDBL (atof (file.champLigne  (4, l)),
                                            atof (file.champLigne  (5, l)),
                                            atof (file.champLigne  (6, l))),
                                    VecDBL (atof (file.champLigne  (7, l)),
                                            atof (file.champLigne  (8, l)),
                                            atof (file.champLigne  (9, l))),
                                    atof (file.champLigne (10, l)),
                                    atof (file.champLigne (11, l)),
                                    &attitude, &spin);
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::attitude") == 0)
          {
            checkLine (file, l, 10);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            RotDBL attitude;
            VecDBL spin;
            thisOne->attitude (atof (file.champLigne (3, l)),
                               VecDBL (atof (file.champLigne  (4, l)),
                                       atof (file.champLigne  (5, l)),
                                       atof (file.champLigne  (6, l))),
                               VecDBL (atof (file.champLigne  (7, l)),
                                       atof (file.champLigne  (8, l)),
                                       atof (file.champLigne  (9, l))),
                               atof (file.champLigne (10, l)),
                               atof (file.champLigne (11, l)),
                               atof (file.champLigne (12, l)),
                               &attitude, &spin);
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::imposeAttitude") == 0)
          {
            checkLine (file, l, 11);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->imposeAttitude (atof (file.champLigne (3, l)),
                                     VecDBL (atof (file.champLigne  (4, l)),
                                             atof (file.champLigne  (5, l)),
                                             atof (file.champLigne  (6, l))),
                                     VecDBL (atof (file.champLigne  (7, l)),
                                             atof (file.champLigne  (8, l)),
                                             atof (file.champLigne  (9, l))),
                                     RotDBL (atof (file.champLigne (10, l)),
                                             atof (file.champLigne (11, l)),
                                             atof (file.champLigne (12, l)),
                                             atof (file.champLigne (13, l))));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::imposeSpin") == 0)
          {
            checkLine (file, l, 10);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->imposeSpin (atof (file.champLigne (3, l)),
                                 VecDBL (atof (file.champLigne  (4, l)),
                                         atof (file.champLigne  (5, l)),
                                         atof (file.champLigne  (6, l))),
                                 VecDBL (atof (file.champLigne  (7, l)),
                                         atof (file.champLigne  (8, l)),
                                         atof (file.champLigne  (9, l))),
                                 VecDBL (atof (file.champLigne (10, l)),
                                         atof (file.champLigne (11, l)),
                                         atof (file.champLigne (12, l))));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::repereBase") == 0)
          {
            checkLine (file, l, 2);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            RotDBL repereBase;
            thisOne->repereBase (basename (directory, file.champLigne (3, l)),
                                 string (file.champLigne (4, l)),
                                 &repereBase);
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::repere") == 0)
          {
            checkLine (file, l, 2);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            RotDBL repere;
            thisOne->repere (basename (directory, file.champLigne (3, l)),
                             string (file.champLigne (4, l)),
                             &repere);
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::mesure") == 0)
          {
            checkLine (file, l, 2);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            double mesure;
            thisOne->mesure (basename (directory, file.champLigne (3, l)),
                             string (file.champLigne (4, l)),
                             &mesure);
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::controlable") == 0)
          {
            checkLine (file, l, 2);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            int controlable;
            thisOne->controlable (basename (directory, file.champLigne (3, l)),
                                  string (file.champLigne (4, l)),
                                  &controlable);
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::criteresControlabilite") == 0)
          {
            checkLine (file, l, 2);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            Senseur::codeAstre inhibant, eclipsant;
            double ecartFrontiere;
            bool   amplitudeSignificative;
            thisOne->criteresControlabilite (basename (directory, file.champLigne (3, l)),
                                             string (file.champLigne (4, l)),
                                             &inhibant, &eclipsant,
                                             &ecartFrontiere,
                                             &amplitudeSignificative);
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::unitesPositionVitesse") == 0)
          {
            checkLine (file, l, 2);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->unitesPositionVitesse (basename (directory, file.champLigne (3, l)),
                                            string (file.champLigne (4, l)));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::respecterConsignes") == 0)
          {
            checkLine (file, l, 2);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->respecterConsignes (basename (directory, file.champLigne (3, l)),
                                         string (file.champLigne (4, l)));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::convertirConsignes") == 0)
          {
            checkLine (file, l, 2);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->convertirConsignes (basename (directory, file.champLigne (3, l)),
                                         string (file.champLigne (4, l)));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::respecterMesures") == 0)
          {
            checkLine (file, l, 2);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->respecterMesures (basename (directory, file.champLigne (3, l)),
                                       string (file.champLigne (4, l)));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::convertirMesures") == 0)
          {
            checkLine (file, l, 2);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->convertirMesures (basename (directory, file.champLigne (3, l)),
                                       string (file.champLigne (4, l)));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::wMax") == 0)
          {
            checkLine (file, l, 1);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->wMax (atof (file.champLigne (3, l)));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::convergence") == 0)
          {
            checkLine (file, l, 1);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->convergence (atof (file.champLigne (3, l)));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::dichotomie") == 0)
          {
            checkLine (file, l, 1);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->dichotomie (atoi (file.champLigne (3, l)));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::autoriseExtrapolation") == 0)
          {
            checkLine (file, l, 0);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->autoriseExtrapolation ();
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::interditExtrapolation") == 0)
          {
            checkLine (file, l, 0);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->interditExtrapolation ();
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::initialiseDerive") == 0)
          {
            checkLine (file, l, 2);
            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            thisOne->initialiseDerive (basename (directory, file.champLigne (3, l)),
                                       string (file.champLigne (3, l)),
                                       atof   (file.champLigne (4, l)));
            continue;
          }

          if (strcmp (file.champLigne (1, l), "Marmottes::enregistreCorps") == 0)
          {
            checkLine (file, l, 9);

            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);

            BodyEphemC::TypeFuncTsid *ptrSiderealTime  = NULL;
            BodyEphemC::TypeFuncPos  *ptrSunPosition   = NULL;
            BodyEphemC::TypeFuncPos  *ptrMoonPosition  = NULL;
            BodyEphemC::TypeFuncPos  *ptrEarthPosition = NULL;

            if ((strcmp (file.champLigne (8, l), "0x0") != 0)
                && (strcmp (file.champLigne (8, l), "0") != 0))
              ptrSiderealTime = *userSiderealTime;
            if ((strcmp (file.champLigne (9, l), "0x0") != 0)
                && (strcmp (file.champLigne (9, l), "0") != 0))
              ptrSunPosition = *userSunPosition;
            if ((strcmp (file.champLigne (10, l), "0x0") != 0)
                && (strcmp (file.champLigne (10, l), "0") != 0))
              ptrMoonPosition = *userMoonPosition;
            if ((strcmp (file.champLigne (11, l), "0x0") != 0)
                && (strcmp (file.champLigne (11, l), "0") != 0))
              ptrEarthPosition = *userEarthPosition;

            thisOne->enregistreCorps (atof   (file.champLigne (3, l)),
                                      atof   (file.champLigne (4, l)),
                                      atof   (file.champLigne (5, l)),
                                      atof   (file.champLigne (6, l)),
                                      atof   (file.champLigne (7, l)),
                                      *ptrSiderealTime,
                                      *ptrSunPosition,
                                      *ptrMoonPosition,
                                      *ptrEarthPosition);
            continue;
          }

          if ((strcmp (file.champLigne (1, l), "BodyEphemC::siderealTime") == 0) ||
              (strcmp (file.champLigne (1, l), "BodyEphemF::siderealTime") == 0))
          {
            checkLine (file, l, 2);
            continue;
          }
          
          if ((strcmp (file.champLigne (1, l), "BodyEphemC::sunPosition") == 0) ||
              (strcmp (file.champLigne (1, l), "BodyEphemF::sunPosition") == 0))
          {
            checkLine (file, l, 1);
            continue;
          }
          
          if ((strcmp (file.champLigne (1, l), "BodyEphemC::moonPosition") == 0) ||
              (strcmp (file.champLigne (1, l), "BodyEphemF::moonPosition") == 0))
          {
            checkLine (file, l, 1);
            continue;
          }
          
          if ((strcmp (file.champLigne (1, l), "BodyEphemC::earthPosition") == 0) ||
              (strcmp (file.champLigne (1, l), "BodyEphemF::earthPosition") == 0))
          {
            checkLine (file, l, 1);
            continue;
          }


          if (strcmp (file.champLigne (1, l), "Marmottes::lireParametres") == 0)
          {
            checkLine (file, l, 14);

            Marmottes *thisOne = getSimulator (file.champLigne (2, l), simulator,
                                               true);
            double date_lue = atof   (file.champLigne (3, l));
            VecDBL pos_lue(atof (file.champLigne (4, l)), 
                           atof (file.champLigne (5, l)), 
                           atof (file.champLigne (6, l)));
            VecDBL vit_lue(atof (file.champLigne (7, l)), 
                           atof (file.champLigne (8, l)), 
                           atof (file.champLigne (9, l)));
            RotDBL att_lue(atof (file.champLigne (10,l)), 
                           atof (file.champLigne (11,l)), 
                           atof (file.champLigne (12,l)), 
                           atof (file.champLigne (13,l)));
            VecDBL spin_lu(atof (file.champLigne (14,l)), 
                           atof (file.champLigne (15,l)), 
                           atof (file.champLigne (16,l)));

            thisOne->lireParametres (&date_lue, &pos_lue, &vit_lue, &att_lue, &spin_lu);
            continue;
          }

          throw ClubErreurs (ClubErreurs::message_simple, file.ligne (l));
        }

        catch (MarmottesErreurs e)
        {
          cout << "exception MarmottesErreurs caught:" << endl;
          cout << "  " << e.why () << endl;
          e.correction ();
        }
        catch (CantorErreurs e)
        {
          cout << "exception CantorErreurs caught:" << endl;
          cout << "  " << e.why () << endl;
          e.correction ();
        }
        catch (ClubErreurs e)
        {
          cout << "exception ClubErreurs caught:" << endl;
          cout << "  " << e.why () << endl;
          e.correction ();
        }

      }
    }
  }
  catch (MarmottesErreurs e)
  { return 1; }
  catch (CantorErreurs e)
  { return 1; }
  catch (ClubErreurs e)
  { return 1; }
  catch (...)
  { return 1; }

  return 0;

}
