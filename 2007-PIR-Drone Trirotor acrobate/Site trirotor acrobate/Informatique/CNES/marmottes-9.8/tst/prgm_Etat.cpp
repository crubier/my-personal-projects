#include <cstdio>

#include "club/OptionsAppli.h"
#include "club/ClubErreurs.h"

#include "cantor/Util.h"
#include "cantor/DeclDBL.h"

#include "marmottes/Etat.h"
#include "marmottes/MarmottesErreurs.h"

double LitDate (const char *chaine);

static int analyseArguments (int argc, char** argv,
                             int* ptrSortI, int* ptrSortJ, int *ptrSortK,
                             int* ptrSortQ, int* ptrSortS,
                             VecDBL* ptrPosition, VecDBL* ptrVitesse,
                             RotDBL* ptrAttitude, VecDBL* ptrSpin,
                             double* ptrDate,
                             double* ptrDuree, double* ptrPas,
                             MarmottesErreurs* ptrErreur)
{ const int maxChaine = 100;

  OptionsAppli analyseur (argv [0]);

  // indicateurs de sortie de l'attitude
  analyseur.ajouterOption (OptionSansValeur ("si", 0, 1));
  analyseur.ajouterOption (OptionSansValeur ("sj", 0, 1));
  analyseur.ajouterOption (OptionSansValeur ("sk", 0, 1));
  analyseur.ajouterOption (OptionSansValeur ("sq", 0, 1));
  analyseur.ajouterOption (OptionSansValeur ("ss", 0, 1));

  // position initiale: zero ou une occurrence,
  // valeur par defaut: (42165, 0, 0)
  double axe [3];
  axe [0] = 42165.0;
  axe [1] = 0.0;
  axe [2] = 0.0;
  analyseur.ajouterOption (OptionTableauReels ("position", 0, 1,
                                               avecValeurDefaut,
                                               3, axe, -1.0e5, 1.0e5));

  // vitesse initiale: zéro ou une occurrence,
  // valeur par défaut: (0, 3075, 0)
  axe [0] = 0.0;
  axe [1] = 3075.0;
  axe [2] = 0.0;
  analyseur.ajouterOption (OptionTableauReels ("vitesse", 0, 1,
                                               avecValeurDefaut,
                                               3, axe, -1.0e5, 1.0e5));

  // directions initiales des vecteurs de base
  // options i, j, k: zero ou une occurrence,
  // valeurs par defaut: alignes avec le repere inertiel
  axe [0] = 1.0;
  axe [1] = 0.0;
  axe [2] = 0.0;
  analyseur.ajouterOption (OptionTableauReels ("i", 0, 1,
                                               avecValeurDefaut,
                                               3, axe, -1.0, 1.0));
  axe [0] = 0.0;
  axe [1] = 1.0;
  axe [2] = 0.0;
  analyseur.ajouterOption (OptionTableauReels ("j", 0, 1,
                                               avecValeurDefaut,
                                               3, axe, -1.0, 1.0));
  axe [0] = 0.0;
  axe [1] = 0.0;
  axe [2] = 1.0;
  analyseur.ajouterOption (OptionTableauReels ("k", 0, 1,
                                               avecValeurDefaut,
                                               3, axe, -1.0, 1.0));

  // autre parametrage de l'attitude: par un quaternion
  double q [4];
  q [0] = 1.0;
  q [1] = 0.0;
  q [2] = 0.0;
  q [3] = 0.0;
  analyseur.ajouterOption (OptionTableauReels ("q", 0, 1,
                                               sansValeurDefaut,
                                               4, q, -1.0, 1.0));

  // option spin: zero ou une occurrence, valeur par defaut: (0.0, 0.0, 0.0)
  axe [0] = 0.0;
  axe [1] = 0.0;
  axe [2] = 0.0;
  analyseur.ajouterOption (OptionTableauReels ("spin", 0, 1,
                                               avecValeurDefaut,
                                               3, axe, -100.0, 100.0));

  // option -dc: zero ou une occurrence, valeur par defaut: "22/10/93-00:00:00"
  analyseur.ajouterOption (OptionChaine ("dc", 0, 1,
                                         avecValeurDefaut, "22/10/93-00:00:00",
                                         maxChaine));

  // option -dj: zero ou une occurrence, sans valeur par defaut
  analyseur.ajouterOption (OptionReel   ("dj", 0, 1,
                                         sansValeurDefaut, 0.0,
                                         0.0, 99999.9999));

  // option dt: zero ou une occurrence, valeur par defaut: 1 heure
  analyseur.ajouterOption (OptionReel  ("dt", 0, 1,
                                        avecValeurDefaut, 1.0, 0.0, 1000.0));

  // option pas: zero ou une occurrence, valeur par defaut: 10 minutes
  analyseur.ajouterOption (OptionReel  ("pas", 0, 1,
                                        avecValeurDefaut, 10.0, 0.0, 1000.0));

  // analyse de la ligne
  analyseur.initialiser (argc, argv);
  analyseur.garantirComplet ();

  // recuperation des donnees
  *ptrSortI = (analyseur.occurrencesPassees ("si") > 0);
  *ptrSortJ = (analyseur.occurrencesPassees ("sj") > 0);
  *ptrSortK = (analyseur.occurrencesPassees ("sk") > 0);
  *ptrSortQ = (analyseur.occurrencesPassees ("sq") > 0);
  *ptrSortS = (analyseur.occurrencesPassees ("ss") > 0);

  analyseur.lireValeur ("position", 3, axe);
  *ptrPosition = VecDBL (axe [0], axe [1], axe [2]);

  analyseur.lireValeur ("vitesse", 3, axe);
  *ptrVitesse = VecDBL (axe [0], axe [1], axe [2]);

  if (analyseur.occurrencesPassees ("q") > 0)
  { // on ne prend le quaternion que s'il est explicitement passe
    analyseur.lireValeur ("q", 4, q);
    *ptrAttitude = RotDBL (q [0], q [1], q [2], q [3]);
  }
  else
  { double matrice [3][3];
    analyseur.lireValeur ("i", 3, matrice [0]);
    analyseur.lireValeur ("j", 3, matrice [1]);
    analyseur.lireValeur ("k", 3, matrice [2]);
    *ptrAttitude = RotDBL (matrice);
  }

  analyseur.lireValeur ("spin", 3, axe);
  *ptrSpin = VecDBL (axe [0], axe [1], axe [2]);

  if (analyseur.occurrencesPassees ("dj") > 0)
  { // on ne prend la date julienne que si elle est explicitement passee
    analyseur.lireValeur ("dj", ptrDate);
  }
  else
  { // date calendaire (c'est peut-etre la valeur par defaut)
    char chaine [maxChaine];
    analyseur.lireValeur ("dc", chaine);
    *ptrDate = LitDate (chaine);
  }

  analyseur.lireValeur ("dt",  ptrDuree);
  *ptrDuree /= 24.0;
  analyseur.lireValeur ("pas", ptrPas);
  *ptrPas   /= 1440.0;

  return 1;

}

int main (int argc, char** argv)
{ ClubAllocHandler h; // utilise uniquement pour ses constructeur/destructeur
  MarmottesErreurs erreur;

  // analyse des arguments de la ligne de commande
  int    sortI, sortJ, sortK, sortQ, sortS;
  double date0, duree, pas;
  VecDBL position0;
  VecDBL vitesse0;
  RotDBL attitude0;
  VecDBL spin0;
  if (! analyseArguments (argc, argv,
                          &sortI, &sortJ, &sortK, &sortQ, &sortS,
                          &position0, &vitesse0, &attitude0, &spin0,
                          &date0, &duree, &pas, &erreur))
    return 1;
  double dateFin = date0 + duree;

  // fabrication de l'etat
  Etat etat (date0, position0, vitesse0, attitude0, spin0, 1.0, 1.0);
  VecDBL iSat (1.0, 0.0, 0.0);
  VecDBL jSat (0.0, 1.0, 0.0);
  VecDBL kSat (0.0, 0.0, 1.0);

  // extrapolation
  for (double date = date0 + pas; date <= dateFin; date += pas)
  { RotDBL nouvelleAttitude = etat.attitudeExtrapolee (date);
    (void) fprintf (stdout, "%12.6f", date);

    if (sortI)
    { VecDBL i = (-nouvelleAttitude) (iSat);
      (void) fprintf (stdout, "  %8.4f %8.4f %8.4f",
                      i.x (), i.y (), i.z ());
    }
    if (sortJ)
    { VecDBL j = (-nouvelleAttitude) (jSat);
      (void) fprintf (stdout, "  %8.4f %8.4f %8.4f",
                      j.x (), j.y (), j.z ());
    }
    if (sortK)
    { VecDBL k = (-nouvelleAttitude) (kSat);
      (void) fprintf (stdout, "  %8.4f %8.4f %8.4f",
                      k.x (), k.y (), k.z ());
    }

    if (sortQ)
    { (void) fprintf (stdout, "  %8.4f %8.4f %8.4f %8.4f",
                      nouvelleAttitude.q0 (), nouvelleAttitude.q1 (),
                      nouvelleAttitude.q2 (), nouvelleAttitude.q3 ());
    }

    if (sortS)
    { VecDBL spin = etat.spinExtrapole (date, nouvelleAttitude);
      (void) fprintf (stdout, "  %8.4f %8.4f %8.4f",
                      spin.x (), spin.y (), spin.z ());
    }

    (void) fprintf (stdout, "\n");

  }

  // fin normale du programme
  return 0;

}
