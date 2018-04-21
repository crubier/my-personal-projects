#include <cstdio>
#include <sys/time.h>

#include "club/OptionsAppli.h"
#include "cantor/Util.h"
#include "cantor/DeclDBL.h"

#include "marmottes/InterfaceC.h"
#include "marmottes/MarmottesErreurs.h"

enum TypeFonction { modifieCible, initialiseGyro,
                    modifieReference, initialiseDerive, inconnue };

double LitDate (const char *chaine);

static int analyseArguments (int argc, char** argv,
                             double       *ptrDate, double orbite [6],
                             double       *ptrPas,
                             double        attitude [4], double spin [3],
                             double       *ptrMu,
                             int          *ptrIterations1,
                             int          *ptrIterations2,
                             string       *ptrFichier,
                             string        senseurs [3],
                             double        mesures [3],
                             TypeFonction *ptrFonction,
                             string       *ptrSenseur,
                             double       *ptrArgScal1,
                             double       *ptrArgScal2,
                             double        argVec [3],
                             double        argRot [4])
{ // analyse des arguments de la ligne de commande

  try {
  OptionsAppli analyseur (argv [0]);

  // itérations
  // options i1 et i2: zéro ou une occurrence
  analyseur.ajouterOption (OptionEntier ("i1", 0, 1,
                                         avecValeurDefaut, 3,  1, 100000));
  analyseur.ajouterOption (OptionEntier ("i2", 0, 1,
                                         avecValeurDefaut, 10, 1, 100000));

  // nom du fichier des senseurs
  // option f: zéro ou une occurrence, valeur par défaut: "senseurs.fr"
  analyseur.ajouterOption (OptionChaine ("f", 0, 1,
                                         avecValeurDefaut, "senseurs.fr",
                                         256));
  // senseurs de contrôle
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

  // paramètres des fonctions senseur
  analyseur.ajouterOption (OptionTableauReels ("modifieCible", 0, 1,
                                               sansValeurDefaut, 3));
  analyseur.ajouterOption (OptionTableauReels ("initialiseGyro", 0, 1,
                                               sansValeurDefaut, 2));
  analyseur.ajouterOption (OptionTableauReels ("modifieReference", 0, 1,
                                               sansValeurDefaut, 4));
  analyseur.ajouterOption (OptionTableauReels ("initialiseDerive", 0, 1,
                                               sansValeurDefaut, 1));

  // option s: une occurrence, pas de valeur par défaut
  analyseur.ajouterOption (OptionChaine ("s", 1, 1,
                                         sansValeurDefaut, "", 25));

  // analyse de la ligne
  analyseur.initialiser (argc, argv);
  analyseur.garantirComplet ();

  // récupération des données
  analyseur.lireValeur ("i1", ptrIterations1);
  analyseur.lireValeur ("i2", ptrIterations2);
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

  analyseur.lireValeur ("s",  ptrSenseur);
  if (analyseur.occurrencesPassees ("modifieCible") > 0)
  { analyseur.lireValeur ("modifieCible", 3, argVec);
    *ptrFonction = modifieCible;
  }
  else if (analyseur.occurrencesPassees ("initialiseGyro") > 0)
  { double tab [2];
    analyseur.lireValeur ("initialiseGyro", 2, tab);
    *ptrArgScal1 = tab [0];
    *ptrArgScal2 = tab [1];
    *ptrFonction = initialiseGyro;
  }
  else if (analyseur.occurrencesPassees ("modifieReference") > 0)
  { analyseur.lireValeur ("modifieReference", 4, argRot);
    *ptrFonction = modifieReference;
  }
  else if (analyseur.occurrencesPassees ("initialiseDerive") > 0)
  { 
    analyseur.lireValeur ("initialiseDerive", 1, ptrArgScal1);
    *ptrFonction = initialiseDerive;
  }
  else
  { (void) fprintf (stderr, "fonction senseur absente\n");
    *ptrFonction = inconnue;
    return 1;
  }

  analyseur.lireValeur ("mu", ptrMu);

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

  return 0;  

  }
  catch (ClubErreurs ce) {
    return 1;
  }

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
            -sinPOM * cosGOM - cosPOM * cosI * sinGOM,
             sinI * sinGOM);

  VecDBL Q ( cosPOM * sinGOM + sinPOM * cosI * cosGOM,
            -sinPOM * sinGOM + cosPOM * cosI * cosGOM,
            -sinI * cosGOM);

  position [0] = xp * P.x () + xq * Q.x ();
  position [1] = xp * P.y () + xq * Q.y ();
  position [2] = xp * P.z () + xq * Q.z ();

  vitesse  [0] = vp * P.x () + vq * Q.x ();
  vitesse  [1] = vp * P.y () + vq * Q.y ();
  vitesse  [2] = vp * P.z () + vq * Q.z ();

}

int main (int argc, char** argv)
{ // programme de test des fonctions spécialisées de senseurs
  // (pour tester de la façon la plus complète, on utilise les interfaces C)
  ClubAllocHandler h; // utilisé uniquement pour ses constructeur/destructeur
  int i;

  const int lgMessage = 1000;
  char messageErreur [lgMessage];

  // analyse des arguments de la ligne de commande
  double       orbite   [6], position [3], vitesse [3];
  double       attitude [4], spin     [3], mesures [3];
  double       date, pas, mu;
  int          iterations1, iterations2;
  TypeFonction fonction;
  string       fichier;
  string       senseurs [5], senseurTest;
  double       argScal1, argScal2, argVec [3], argRot [4];

  if (analyseArguments (argc, argv, &date, orbite, &pas, attitude, spin,
                        &mu, &iterations1, &iterations2,
                        &fichier, senseurs, mesures,
                        &fonction, &senseurTest,
                        &argScal1, &argScal2, argVec, argRot))
    return 1;

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

  if (MarmottesConvertirMesures (id, senseurTest.c_str (),
                                 messageErreur, lgMessage))
  { (void) fprintf (stderr, "%s\n", messageErreur);
    return 1;
  }

  int    controlable = 0;
  double mesure      = 9999.999;

  for (i = 0; i < iterations1; i++)
  { // on commence par quelques pas de stabilisation
    extrapole  (&date, orbite, mu, pas);
    cartesiens (orbite, mu, position, vitesse);

    if (MarmottesAttitude (id, date, position, vitesse,
                           mesures [0], mesures [1], mesures [2],
                           attitude, spin, messageErreur, lgMessage))
    { (void) fprintf (stderr, "%s\n", messageErreur);
      MarmottesDetruire (id);
      return 1;
    }

    if (MarmottesControlable (id, senseurTest.c_str (), &controlable,
                              messageErreur, lgMessage))
      (void) fprintf (stdout, "%14.8f : %s\n", date, messageErreur);
    else
    { if (MarmottesMesure (id, senseurTest.c_str (), &mesure,
                           messageErreur, lgMessage))
        (void) fprintf (stdout, "%14.8f : %s\n", date, messageErreur);
      else
      { if (controlable)
          (void) fprintf (stdout, "%14.8f : %s contrôlable,     %7.3f\n",
                          date, senseurTest.c_str (), mesure);
        else
          (void) fprintf (stdout, "%14.8f : %s non contrôlable, %7.3f\n",
                          date, senseurTest.c_str (), mesure);
      }
    }
  }

  int code = 0;
  switch (fonction)
  { // appel de la fonction senseur à tester
    case modifieCible :
      (void) fprintf (stdout, "\nappel de MarmottesModifieCible\n\n");
      code = MarmottesModifieCible      (id, senseurTest.c_str (), argVec,
                                         messageErreur, lgMessage);
      break;

    case initialiseGyro :
      (void) fprintf (stdout, "\nappel de MarmottesInitialiseGyro\n\n");
      code = MarmottesInitialiseGyro    (id, senseurTest.c_str (),
                                         argScal1, argScal2,
                                         messageErreur, lgMessage);
      break;

    case modifieReference :
      (void) fprintf (stdout, "\nappel de MarmottesModifieReference\n\n");
      code = MarmottesModifieReference  (id, senseurTest.c_str (), argRot,
                                         messageErreur, lgMessage);
      break;

    case initialiseDerive :
      (void) fprintf (stdout, "\nappel de MarmottesInitialiseDerive\n\n");
      code = MarmottesInitialiseDerive  (id, senseurTest.c_str (),
                                         argScal1,
                                         messageErreur, lgMessage);
      break;

    default :
      (void) sprintf (messageErreur, "erreur interne ligne %d fichier %s\n",
                      __LINE__, __FILE__);
      code = 1;
      break;

  }

  if (code)
  { (void) fprintf (stderr, "%s\n", messageErreur);
    MarmottesDetruire (id);
    return 1;
  }

  for (i = 0; i < iterations2; i++)
  { // on termine par des pas de calcul
    extrapole  (&date, orbite, mu, pas);
    cartesiens (orbite, mu, position, vitesse);

    if (MarmottesAttitude (id, date, position, vitesse,
                           mesures [0], mesures [1], mesures [2],
                           attitude, spin, messageErreur, lgMessage))
    { (void) fprintf (stderr, "%s\n", messageErreur);
      MarmottesDetruire (id);
      return 1;
    }

    if (MarmottesControlable (id, senseurTest.c_str (), &controlable,
                              messageErreur, lgMessage))
    { (void) fprintf (stderr, "%s\n", messageErreur);
      MarmottesDetruire (id);
      return 1;
    }

    if (MarmottesMesure (id, senseurTest.c_str (), &mesure,
                         messageErreur, lgMessage))
    { (void) fprintf (stderr, "%s\n", messageErreur);
      MarmottesDetruire (id);
      return 1;
    }

    if (controlable)
      (void) fprintf (stdout, "%14.8f : %s contrôlable,     %7.3f\n",
                      date, senseurTest.c_str (), mesure);
    else
      (void) fprintf (stdout, "%14.8f : %s non contrôlable, %7.3f\n",
                      date, senseurTest.c_str (), mesure);

  }

  MarmottesDetruire (id);

  // fin normale du programme
  return 0;

}
