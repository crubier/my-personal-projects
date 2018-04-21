////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//        CHOPE
//
//$Application
//        Club
//
//$Nom
//>       prgm_AnalyseurLexical.cc
//
//$Resume
//       fichier d'implantation du test prgm_AnalyseurLexical
//
//$Description
//       teste la classe AnalyseurLexical
//
//$Contenu
//>       static void imprimeElements()
//>       static double date2000()     
//>       int main()                   
//
//$Historique
//       $Log: prgm_AnalyseurLexical.cpp,v $
//       Revision 1.8  2000/10/24 14:23:11  club
//       ajout de l'include ClubConfigNoInstall.h et des tests de configuration.
//
//       Revision 1.7  2000/10/24 08:36:33  club
//       ajout de l'include src/ClubConfig.h et modification des includes du
//       standard C : utilisation des includes du type cNAME au lieu de NAME.h
//       pour permettre la compilation avec le Sun Workshop 5.0
//
//       Revision 1.6  2000/09/07 08:35:52  club
//       utilisation de string de la STL au lieu de ChaineSimple.
//       mise à jour du cartouche.
//
//       Revision 1.5  1999/08/26 09:04:02  club
//       Conformément à la norme ANSI C++, la fonction main a
//       désormais un type de retour
//
//$Version
//       $Id: prgm_AnalyseurLexical.cpp,v 1.8 2000/10/24 14:23:11 club Exp $
//$Auteur
//        P-A.Cros      CSSI
//        M. Julien    CSSI
//        O. Queyrut   CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#if STDC_HEADERS
#include <cstdio>
#endif

#include "club/AnalyseurLexical.h"

static void   imprimeElements (AnalyseurLexical al)
{ // imprime les éléments canoniques de l'analyseur
  al.redemarre ();

  (void) fprintf (stdout, "analyse de la chaîne \"%s\" :\n",
                  al.chaine ().c_str ());
  while (al.suivant () != AnalyseurLexical::codeFin)
  { switch (al.type ())
    { case AnalyseurLexical::codeSeparateur :
        (void) fprintf (stdout, "\"%s\" : séparateur '%c'\n",
                        al.lexeme ().c_str (), al.separateur ());
        break;

      case AnalyseurLexical::codeOperateur :
        (void) fprintf (stdout, "\"%s\" : opérateur '%c'\n",
                        al.lexeme ().c_str (), al.operateur ());
        break;

      case AnalyseurLexical::codeParenthese :
        (void) fprintf (stdout, "\"%s\" : parenthèse '%c'\n",
                        al.lexeme ().c_str (), al.parenthese ());
        break;

      case AnalyseurLexical::codeEntier :
        (void) fprintf (stdout, "\"%s\" : entier %d\n",
                        al.lexeme ().c_str (), al.entier ());
        break;

      case AnalyseurLexical::codeReel :
        (void) fprintf (stdout, "\"%s\" : reel %f\n",
                        al.lexeme ().c_str (), al.reel ());
        break;

      case AnalyseurLexical::codeNom :
        (void) fprintf (stdout, "\"%s\" : nom %s\n",
                        al.lexeme ().c_str (), al.nom ().c_str ());
        break;

      case AnalyseurLexical::codeInconnu :
        (void) fprintf (stdout, "\"%s\" : inconnu\n",
                        al.lexeme ().c_str ());
        break;


      default :
        (void) fprintf (stdout, "erreur de retour de type de lexème !!!\n%s\n",
                        al.chaine ().c_str ());
        break;
    }
  }

}

static double date2000 (int j, int m, int a,
                        int h, int mn, int sec, int ms)
{ // construction à partir des éléments calendaires
  int nonBis = (a & 3) || ((a % 100 == 0) && ((a / 100) & 3));
  int      s = (a - 1201) / 100;

  // formule valable à partir du 15/10/1582 (calendrier grégorien)
  return double (((1461 * (a - 1581)) >> 2)
                 + (s >> 2)
                 - s
                 + ((m * 489) >> 4)
                 - ((m > 2) ? (nonBis ? 32 : 31) : 30)
                 + j
                 - 153034) * 86400.0
    + double ((((h - 12) * 60 + mn) * 60 + sec) * 1000 + ms) / 1000.0;

}

int main (int argc, char **argv)
{ for (int i = 1; i < argc; i++)
  { AnalyseurLexical al (argv [i]);
    double t;

    // on commence par tenter un format calendaire
    al.initSeparateurs (":/-.");
    al.interditReels   ();
    int n [7];
    for (int j = 0; j < 7; j++)
      n [j] = 0;
    int nbEntiers = 0;
    int ok = 1;

    (void) al.suivant ();
    while (ok && (al.type () == AnalyseurLexical::codeEntier))
    { // boucle sur les entiers du format
      n [nbEntiers++] = al.entier ();
      ok = (nbEntiers <= 7);

      if (al.suivant () != AnalyseurLexical::codeSeparateur)
      { // les séparateurs sont optionnels entre année et heure ou à la fin
        ok = ok
          && (((nbEntiers == 3) && (al.type () == AnalyseurLexical::codeEntier))
              || (al.type () == AnalyseurLexical::codeFin));
      }
      else
        (void) al.suivant ();

    }
    ok = ok
      && ((nbEntiers == 3) || (nbEntiers == 6) || (nbEntiers == 7))
      && (al.type () == AnalyseurLexical::codeFin);

    if (ok)
    { // correction de l'année si elle n'est que sur deux chiffres
      if (n [2] < 50)
        n [2] += 2000;   // années 2000 à 2049, notées 00 à 49
      else if (n [2] < 100)
        n [2] += 1900;   // années 1950 à 1999, notées 50 à 99

      t = date2000 (n [0], n [1], n [2], n [3], n [4], n [5], n [6]);
      (void) fprintf (stdout, "%s => %15.3f (%15.8f)\n",
                      argv [i], t, (t / 86400.0) + 18262.5);

    }
    else
    { // le format calendaire ne convenait pas, on essaie un simple réel
      al.initSeparateurs ("");
      al.autoriseReels   ();
      if ((al.suivant () == AnalyseurLexical::codeReel)
          &&
          (al.suivant () == AnalyseurLexical::codeFin))
      { t = al.reel ();
        (void) fprintf (stdout, "%s => %15.3f (%15.8f)\n",
                        argv [i], t, (t / 86400.0) + 18262.5);
      }
      else
        imprimeElements (al);
    }

  }

  return 0;

}
