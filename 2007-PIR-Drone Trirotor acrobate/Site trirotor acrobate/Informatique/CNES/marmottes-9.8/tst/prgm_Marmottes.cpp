#include <cstdio>
#include <sys/time.h>

#include <string>

#include "club/OptionsAppli.h"
#include "cantor/Util.h"
#include "cantor/DeclDBL.h"

#include "marmottes/InterfaceC.h"
#include "marmottes/MarmottesErreurs.h"

double LitDate (const char *chaine);

static void analyseArguments (int argc, char** argv,
                              double* ptrDate, double orbite [6],
                              double* ptrPas,
                              double attitude [4], double spin [3],
                              int* ptrIterations, int* ptrTranches,
                              int* ptrReperes, int *ptrSpin,
                              double *ptrMu,
                              string *ptrLog,
                              string *ptrFichier,
                              string senseurs [3],
                              double mesures [3],
                              double *ptrCalage)
{ // analyse des arguments de la ligne de commande
  OptionsAppli analyseur (argv [0]);

  // itérations
  // option i: zéro ou une occurrence, valeur par défaut: 1000
  analyseur.ajouterOption (OptionEntier ("i", 0, 1,
                                         avecValeurDefaut, 1000, 1, 100000));

  // tranches de dichotomie
  // option n: zéro ou une occurrence, valeur par défaut: 50
  analyseur.ajouterOption (OptionEntier ("n", 0, 1,
                                         avecValeurDefaut, 50, 2, 100000));

  // test des repères
  // option n: zéro ou une occurrence
  analyseur.ajouterOption (OptionSansValeur ("r", 0, 1));

  // affichage du spin
  // option spin: zéro ou une occurrence
  analyseur.ajouterOption (OptionSansValeur ("spin", 0, 1));

  // nom du fichier des senseurs
  // option f: zéro ou une occurrence, valeur par défaut: "senseurs.fr"
  analyseur.ajouterOption (OptionChaine ("f", 0, 1,
                                         avecValeurDefaut, "senseurs.fr",
                                         256));

  // senseurs
  // option s1: une occurrence, pas de valeur par défaut
  analyseur.ajouterOption (OptionChaine ("s1", 1, 1,
                                         sansValeurDefaut, "", 25));

  // option s2: une occurrence, pas de valeur par défaut
  analyseur.ajouterOption (OptionChaine ("s2", 1, 1,
                                         sansValeurDefaut, "", 25));

  // option s3: une occurrence, pas de valeur par défaut
  analyseur.ajouterOption (OptionChaine ("s3", 1, 1,
                                         sansValeurDefaut, "", 25));

  // option m1: zéro ou une occurrence, valeur par défaut: 0.0
  analyseur.ajouterOption (OptionReel   ("m1", 0, 1,
                                         avecValeurDefaut, 0.0, -1.0e6, 1.0e6)
                          );

  // option m2: zéro ou une occurrence, valeur par défaut: 0.0
  analyseur.ajouterOption (OptionReel   ("m2", 0, 1,
                                         avecValeurDefaut, 0.0, -1.0e6, 1.0e6)
                          );

  // option m3: zéro ou une occurrence, valeur par défaut: 0.0
  analyseur.ajouterOption (OptionReel   ("m3", 0, 1,
                                         avecValeurDefaut, 0.0, -1.0e6, 1.0e6)
                          );

  // option -dc: zéro ou une occurrence, valeur par défaut: "22/10/93-00:00:00"
  analyseur.ajouterOption (OptionChaine ("dc", 0, 1,
                                         avecValeurDefaut, "22/10/93-00:00:00",
                                         25));

  // option -dj: zéro ou une occurrence, sans valeur par défaut
  analyseur.ajouterOption (OptionReel   ("dj", 0, 1,
                                         sansValeurDefaut, 0.0,
                                         0.0, 99999.9999));

  // option -o: zéro ou une occurrence,
  // valeur par défaut: 42164.0, 0.0, 0.0, 0.0, 0.0, 0.0
  double defautOrbite [6];
  defautOrbite [0] = 42164.0;
  defautOrbite [1] = 0.0;
  defautOrbite [2] = 0.0;
  defautOrbite [3] = 0.0;
  defautOrbite [4] = 0.0;
  defautOrbite [5] = 0.0;
  analyseur.ajouterOption (OptionTableauReels ("o", 0, 1,
                                               avecValeurDefaut,
                                               6, defautOrbite));

  // option -mu: zéro ou une occurrence, valeur par défaut : 398600.436
  analyseur.ajouterOption (OptionReel   ("mu", 0, 1,
                                         avecValeurDefaut, 398600.436,
                                         1000.0, 1.0e6));

  // option -p: zéro ou une occurrence, sans valeur par défaut
  analyseur.ajouterOption (OptionReel   ("p", 0, 1,
                                         sansValeurDefaut, 0.0,
                                         0.0, 99999.9999));

  // option -a: zéro ou une occurrence, valeur par défaut: 0.5, -0.5, -0.5, 0.5
  // (Xsat: {0, 1, 0}, Ysat: {0, 0, -1}, Zsat: {-1, 0, 0})
  double defautAttitude [4];
  defautAttitude [0] =  0.5;
  defautAttitude [1] = -0.5;
  defautAttitude [2] = -0.5;
  defautAttitude [3] =  0.5;
  analyseur.ajouterOption (OptionTableauReels ("a", 0, 1,
                                               avecValeurDefaut,
                                               4, defautAttitude, -1.0, 1.0));

  // option -sp: zéro ou une occurrence, valeur par défaut: 0.0, 0.0, 0.0
  double defautSpin [3];
  defautSpin [0] = 0.0;
  defautSpin [1] = 0.0;
  defautSpin [2] = 0.0;
  analyseur.ajouterOption (OptionTableauReels ("sp", 0, 1,
                                               avecValeurDefaut,
                                               3, defautSpin, -10.0, 10.0));

  // option -c: zéro ou une occurrence, valeur par défaut: 5.0
  analyseur.ajouterOption (OptionReel   ("c", 0, 1,
                                         avecValeurDefaut, 5.0,
                                         -1000.0, 1000.0));

  // nom du fichier de log
  // option l: zéro ou une occurrence, valeur par défaut: ""
  analyseur.ajouterOption (OptionChaine ("l", 0, 1,
                                         avecValeurDefaut, "",
                                         256));

  // analyse de la ligne
  analyseur.initialiser (argc, argv);
  analyseur.garantirComplet ();

  // récupération des données
  analyseur.lireValeur ("i",  ptrIterations);
  analyseur.lireValeur ("n",  ptrTranches);
  *ptrReperes = (analyseur.occurrencesPassees ("r") > 0);
  *ptrSpin    = (analyseur.occurrencesPassees ("spin") > 0);
  analyseur.lireValeur ("f",  ptrFichier);
  analyseur.lireValeur ("s1", &(senseurs [0]));
  analyseur.lireValeur ("s2", &(senseurs [1]));
  analyseur.lireValeur ("s3", &(senseurs [2]));
  analyseur.lireValeur ("m1", &(mesures  [0]));
  mesures [0] = radians (mesures [0]);
  analyseur.lireValeur ("m2", &(mesures  [1]));
  mesures [1] = radians (mesures [1]);
  analyseur.lireValeur ("m3", &(mesures  [2]));
  mesures [2] = radians (mesures [2]);
  analyseur.lireValeur ("mu", ptrMu);
  analyseur.lireValeur ("l",  ptrLog);

  if (analyseur.occurrencesPassees ("dj") > 0)
  { // on ne prend la date julienne que si elle est explicitement passée
    analyseur.lireValeur ("dj", ptrDate);
  }
  else
  { // date calendaire (c'est peut-être la valeur par défaut)
    string chaine;
    analyseur.lireValeur ("dc", &chaine);
    *ptrDate = LitDate (chaine.c_str ());
  }

  analyseur.lireValeur ("o", 6, orbite);
  for (int i = 2; i < 6; i++)
    orbite [i] = radians (orbite [i]);
  if (analyseur.occurrencesPassees ("p") > 0)
    analyseur.lireValeur ("p", ptrPas);
  else
    *ptrPas = (M_PI + M_PI) * orbite [0] * sqrt (orbite [0] / *ptrMu) / 100.0;

  analyseur.lireValeur ("a",  4, attitude);
  analyseur.lireValeur ("sp", 3, spin);

  analyseur.lireValeur ("c", ptrCalage);
  *ptrCalage = radians (*ptrCalage);

}

static void extrapole (double* ptrDate, double orbite [6],
                       double mu, double pas)
{ // extrapolation keplérienne de l'orbite

  // moyen mouvement
  double n = sqrt (mu / orbite [0]) / orbite [0];

  // kepler
  orbite [5] += n * pas;
  *ptrDate   += pas / 86400.0;

}

static double anoExc (double M, double e)
{ // résolution de l'équation de Kepler
  double Eold = M;

  while (1)
  { double E = M + e * sin (Eold);
    if (fabs (E - Eold) < 1.0e-6)
      return E;
    Eold = E;
  }

}

static void cartesiens (const double orbite [6], double mu,
                        double position [3], double vitesse [3])
{ // conversion des paramètres orbitaux keplériens en coordonnées cartésiennes
  double E  = anoExc (orbite [5], orbite [1]);
  double n  = sqrt (mu / orbite [0]) / orbite [0];

  double xp =  orbite [0] * (cos (E) - orbite [1]);
  double xq =  orbite [0] * sqrt (1.0 - orbite [1] * orbite [1]) * sin (E);
  double vp = -orbite [0] * sin (E) * n / (1 - orbite [1] * cos (E));
  double vq =  orbite [0] * cos (E) * n / (1 - orbite [1] * cos (E))
                                    * sqrt (1.0 - orbite [1] * orbite [1]);

  double cosI   = cos (orbite [2]);
  double sinI   = sin (orbite [2]);
  double cosPOM = cos (orbite [3]);
  double sinPOM = sin (orbite [3]);
  double cosGOM = cos (orbite [4]);
  double sinGOM = sin (orbite [4]);

  VecDBL P ( cosPOM * cosGOM - sinPOM * cosI * sinGOM,
             cosPOM * sinGOM + sinPOM * cosI * cosGOM,
             sinPOM * sinI);

  VecDBL Q (-sinPOM * cosGOM - cosPOM * cosI * sinGOM,
            -sinPOM * sinGOM + cosPOM * cosI * cosGOM,
             cosPOM * sinI);

  position [0] = xp * P.x () + xq * Q.x ();
  position [1] = xp * P.y () + xq * Q.y ();
  position [2] = xp * P.z () + xq * Q.z ();

  vitesse  [0] = vp * P.x () + vq * Q.x ();
  vitesse  [1] = vp * P.y () + vq * Q.y ();
  vitesse  [2] = vp * P.z () + vq * Q.z ();

}

int main (int argc, char** argv)
{ // programme de test de haut niveau de la bibliothèque Marmottes
  // (pour tester de la façon la plus complète, on utilise les interfaces C)

  try {
  ClubAllocHandler h; // utilisé uniquement pour ses constructeur/destructeur
  const int lgMessage = 1000;
  char messageErreur [lgMessage];

  // analyse des arguments de la ligne de commande
  double           date;
  double           orbite   [6];
  double           position [3];
  double           vitesse  [3];
  double           pas;
  double           attitude [4];
  double           spin     [3];
  double           mu;
  int              iterations;
  int              tranches;
  int              reperes;
  int              avecSpin;
  string           log;
  string           fichier;
  string           senseurs [3];
  double           mesures  [3];
  double           calage;
  analyseArguments (argc, argv, &date, orbite, &pas, attitude, spin,
                    &iterations, &tranches, &reperes, &avecSpin, &mu, &log,
                    &fichier, senseurs, mesures, &calage);

  if (log.size () > 0)
    if (MarmottesActiveTrace (log.c_str (), messageErreur, lgMessage) != 0)
    { (void) fprintf (stderr, "%s\n", messageErreur);
      return 1;
    }

  // création du simulteur
  cartesiens (orbite, mu, position, vitesse);
  IdentMarmottes id = MarmottesCreer (date, position, vitesse, attitude, spin,
                                      fichier.c_str (), senseurs [0].c_str (),
                                      senseurs [1].c_str (), senseurs [2].c_str (),
                                      messageErreur, lgMessage);
  if (id <= 0)
  { (void) fprintf (stderr, "%s\n", messageErreur);
    return 1;
  }

  if (MarmottesDichotomie (id, tranches, messageErreur, lgMessage))
  { (void) fprintf (stderr, "%s\n", messageErreur);
    MarmottesDetruire (id);
    return 1;
  }

  if (reperes)
  { // test des opérations sur les repères
    for (int k = 0; k < 3; k++)
    { // test des fonctions sur les repères
      (void) fprintf (stdout, "senseur : %s\n", senseurs [k].c_str ());

      double rBase [4];
      if (MarmottesRepereBase (id, senseurs [k].c_str (), rBase,
                               messageErreur, lgMessage))
      { (void) fprintf (stderr, "%s\n", messageErreur);
        return 1;
      }
      (void) fprintf (stdout,
                      "repère de base : %8.4f, %8.4f, %8.4f, %8.4f\n",
                      rBase [0], rBase [1], rBase [2], rBase [3]);

      double r [4];
      r [0] = 1.0;
      r [1] = 0.0;
      r [2] = 0.0;
      r [3] = 0.0;
      if (MarmottesNouveauRepere (id, senseurs [k].c_str (), r,
                                  messageErreur, lgMessage))
      { (void) fprintf (stderr, "%s\n", messageErreur);
        return 1;
      }

      double p [4];
      if (MarmottesRepere (id, senseurs [k].c_str (), p,
                           messageErreur, lgMessage))
      { (void) fprintf (stderr, "%s\n", messageErreur);
        return 1;
      }
      (void) fprintf (stdout,
                      "repère modifié : %8.4f, %8.4f, %8.4f, %8.4f\n",
                      p [0], p [1], p [2], p [3]);

      if (! MarmottesCalage (id, senseurs [k].c_str (), calage,
                             messageErreur, lgMessage))
      { if (MarmottesRepere (id, senseurs [k].c_str (), p,
                             messageErreur, lgMessage))
        { (void) fprintf (stderr, "%s\n", messageErreur);
          return 1;
        }
        (void) fprintf (stdout,
                        "repère recalé  : %8.4f, %8.4f, %8.4f, %8.4f\n",
                        p [0], p [1], p [2], p [3]);
      }
      else
        (void) fprintf (stdout, "repère non recalable\n");

      MarmottesNouveauRepere (id, senseurs [k].c_str (), rBase,
                              messageErreur, lgMessage);

    }
  }

  for (int i = 0; i < iterations; i++)
  { extrapole  (&date, orbite, mu, pas);
    cartesiens (orbite, mu, position, vitesse);

    struct timeval t1;
    struct timeval t2;
    (void) gettimeofday (&t1, 0);

    if (MarmottesAttitude (id, date, position, vitesse, mesures [0],
                           mesures [1], mesures [2],
                           attitude, spin,
                           messageErreur, lgMessage))
      (void) fprintf (stderr, "%s\n", messageErreur);

    (void) gettimeofday (&t2, 0);
    long dt = (t2.tv_sec  - t1.tv_sec)  * 1000000l
            + (t2.tv_usec - t1.tv_usec);
    (void) fprintf (stdout,
                    "temps de calcul de \"MarmottesAttitude\" : %8.4f ms\n",
                    double (dt) * 1.0e-3);

    (void) fprintf (stdout,
                    "attitude : %8.4f %8.4f %8.4f %8.4f\n",
                    attitude [0], attitude [1], attitude [2], attitude [3]);

    if (avecSpin)
      (void) fprintf (stdout,
                      "spin     : %8.4f %8.4f %8.4f \n",
                      spin [0], spin [1], spin [2]);

    for (int j = 0; j < 3; j++)
    { double m;
      if (MarmottesMesure (id, senseurs [j].c_str (), &m,
                           messageErreur, lgMessage))
      { (void) fprintf (stderr, "%s\n", messageErreur);
        MarmottesDetruire (id);
        return 1;
      }

      (void) fprintf (stdout,
                      "mesure réalisée par le senseur \"%s\" : %8.4f\n",
                      senseurs [j].c_str (), degres (m));

    }

  }

  // fin normale du programme
  return 0;
  }

  catch (ClubErreurs e)
  { return 1; }
  catch (CantorErreurs e)
  { return 1; }
  catch (MarmottesErreurs e)
  { return 1; }

}
