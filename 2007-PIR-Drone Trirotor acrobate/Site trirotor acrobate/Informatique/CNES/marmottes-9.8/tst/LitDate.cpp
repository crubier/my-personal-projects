#include "club/AnalyseurLexical.h"

static double date1950 (int j, int m, int a,
                        int h, int mn, int sec, int ms)
{ // construction à partir des éléments calendaires
  int nonBis = (a & 3) || ((a % 100 == 0) && ((a / 100) & 3));
  int      s = (a - 1201) / 100;

  // formule valable à partir du 15/10/1582 (calendrier grégorien)
  return double ((1461 * (a - 1581)) >> 2) + (s >> 2) - s
                 + ((m * 489) >> 4) - ((m > 2) ? (nonBis ? 32 : 31) : 30)
                 + j - 134772
       + double (((h * 60 + mn) * 60 + sec) * 1000 + ms) / 86400000.0;

}

double LitDate (const char *chaine)
{ // lecture d'une date dans une chaîne avec un format variable
  AnalyseurLexical al (chaine);

  // on commence par tenter un format calendaire
  al.initSeparateurs (":/-");
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
  { // un format calendaire a été reconnu

    if (n [0] > 999)
    { // la date est au format ISO 8601 (année en premier)
      // on la ramène dans l'ordre français
      int tmp = n [0];
      n [0]   = n [2];
      n [2]   = tmp;
    }

    // correction de l'année si elle n'est que sur deux chiffres
    if (n [2] < 50)
      n [2] += 2000;   // années 2000 à 2049, notées 00 à 49
    else if (n [2] < 100)
      n [2] += 1900;   // années 1950 à 1999, notées 50 à 99

    return date1950 (n [0], n [1], n [2], n [3], n [4], n [5], n [6]);

  }
  else
  { // le format calendaire ne convenait pas, on essaie un simple réel
    al.initSeparateurs ("");
    if ((al.suivant () == AnalyseurLexical::codeReel)
        &&
        (al.suivant () == AnalyseurLexical::codeFin))
      return al.reel ();
    else
      return 0.0;
  }

}
