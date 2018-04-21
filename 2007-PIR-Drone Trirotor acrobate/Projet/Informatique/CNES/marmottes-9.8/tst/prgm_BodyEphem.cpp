////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//
//$Application
//
//$Nom
//
//$Resume
//       fichier d'implantation de la classe XXXX
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//
//$Historique
//       $Log: prgm_BodyEphem.cpp,v $
//       Revision 1.5  2003/03/27 14:36:56  marmottes
//       Annulation des modifications effectuées suite à la correction de la FA 23,
//       cette FA n'ayant pas été complètement corrigée.
//
//       Revision 1.4  2003/03/26 18:18:26  marmottes
//       FA-ID 0023 Problème de prise en compte du 0 comme fonctions fortran dans enregistreCorps
//
//       Revision 1.3  2003/02/27 17:01:07  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.2  2002/09/05 12:56:25  marmottes
//       correction de valeurs physiques
//
//       Revision 1.1  2002/08/29 12:16:12  marmottes
//       Fichier de test de la DM7 (paramétrage des modèles d'environnement spatial)
//
//$Version
//       $Id: prgm_BodyEphem.cpp,v 1.5 2003/03/27 14:36:56 marmottes Exp $
//$Auteur
//      
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <sys/time.h>

#include <string>

#include "club/OptionsAppli.h"
#include "cantor/Util.h"
#include "cantor/DeclDBL.h"

#include "marmottes/InterfaceC.h"
#include "marmottes/InterfaceF.h"
#include "marmottes/MarmottesErreurs.h"

double LitDate (const char *chaine);

// rayon equatorial terrestre
double r_terre = 6378.39;
// aplatissement de la Terre
double aplatissement = 1.0 / 298.256;
// vitesse de rotation de la Terre sur elle-meme
// valeur bidon pour utiliser la valeur par defaut
double vit_bidon      = -1.0;
double r_lune_bidon   = -1.0;
double r_soleil_bidon = -1.0;

static void analyseArguments (int argc, char** argv,
                              double* ptrDate, double orbite [6],
                              double* ptrPas,
                              double attitude [4], double spin [3],
                              int* ptrIteration1,
                              int* ptrIteration2,
                              int* ptrIteration3,
                              int* ptrIteration4,
                              int* ptrTranches,
                              int* ptrReperes, int *ptrSpin,
                              double *ptrMu,
                              string *ptrLog,
                              string *ptrFichier,
                              string senseurs [3],
                              double mesures [3],
                              double *ptrCalage)
{
  // analyse des arguments de la ligne de commande
  OptionsAppli analyseur (argv [0]);
  
  // itérations
  // option i1: zéro ou une occurrence, valeur par défaut: 10
  // nombre d'itérations réalisées avant enregistrement des
  // fonctions (surcouche C)
  analyseur.ajouterOption (OptionEntier ("i1", 0, 1,
                                         avecValeurDefaut, 10, 1, 100000));
  // option i2: zéro ou une occurrence, valeur par défaut: 10
  // nombre d'itérations réalisées avant r.a.z. des fonctions
  // (surcouche C)
  analyseur.ajouterOption (OptionEntier ("i2", 0, 1,
                                         avecValeurDefaut, 10, 1, 100000));
  // option i3: zéro ou une occurrence, valeur par défaut: 10
  // nombre d'itérations réalisées avant enregistrement des
  // fonctions (surcouche Fortran)
  analyseur.ajouterOption (OptionEntier ("i3", 0, 1,
                                         avecValeurDefaut, 10, 1, 100000));
  // option i4: zéro ou une occurrence, valeur par défaut: 10
  // nombre d'itérations réalisées avant r.a.z. des fonctions
  // (surcouche Fortran)
  analyseur.ajouterOption (OptionEntier ("i4", 0, 1,
                                         avecValeurDefaut, 10, 1, 100000));

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
  analyseur.lireValeur ("i1",  ptrIteration1);
  analyseur.lireValeur ("i2",  ptrIteration2);
  analyseur.lireValeur ("i3",  ptrIteration3);
  analyseur.lireValeur ("i4",  ptrIteration4);
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

static double tsidrLocal (double t, double offset)
{

  // sidereal time upgraded wrt the CNES julian date t (seconds are expressed in fraction of day)
  const double a1  = 0.1746647708617871e1;
  const double a3  = 0.7292115146705e-04;
  const double eps = 1.7202179573714597e-02;

  double r = t - floor (t);
  r = a1 + eps * t + a3 * offset + (M_PI + M_PI) * r;

  return recaleAngle (r, M_PI);

}

static void sunLocal (double t, double BodySun[3])
{

  // computation of the Sun  position wrt the central body (units: km)
  // =================================================================
  // In this case : central body = Earth
  double date   = t - 10000.0;
  double f   = radians (225.768 + 13.2293505 * date);
  double d   = radians (11.786 + 12.190749 * date);
  double xlp = radians (134.003 + 0.9856 * date);
  double g   = radians (282.551 + 0.000047 * date);
  double e   = radians (23.44223 - 3.5626e-07 * date);
  double ce  = cos (e);
  double se  = sin (e);
  double rot = 0.6119022e-06 * t;
  double cr  = cos (rot);
  double sr  = sin (rot);


  // Newcomb's theory

  double cl   = 99972.0 * cos (xlp + g) + 1671.0 * cos (xlp + xlp + g) - 1678.0 * cos (g);
  cl   = cl + 32.0 * cos (3.0 * xlp + g) + cos (4.0 * xlp + g) + 2.0 * cos (xlp + d + g);
  cl   = cl - 4.0 * cos (g - xlp) - 2.0 * cos (xlp - d + g) + 4.0 * cos (f - d);
  cl   = cl - 4.0 * cos (xlp + xlp - f + d + g + g);
  cl   = cl * 1.e-05;

  double sl   = 99972.0 * sin (xlp + g) + 1671.0 * sin (xlp + xlp + g) - 1678.0 * sin (g);
  sl   = sl + 32.0 * sin (3.0 * xlp + g) + sin (4.0 * xlp + g) + 2.0 * sin (xlp + d + g);
  sl   = sl - 4.0 * sin (g - xlp) - 2.0 * sin (xlp - d + g) + 4.0 * sin (f - d);
  sl   = sl - 4.0 * sin (xlp + xlp - f + d + g + g);
  sl   = sl * 1.e-05;

  double q    = sqrt (cl * cl + sl * sl);
  double sx   = cl / q;
  double sy   = sl * ce / q;

  double  EarthSun[3];
  EarthSun[0] = sx * cr + sy * sr;
  EarthSun[1] = sy * cr - sx * sr;
  EarthSun[2] = sl * se / q;

  double dasr = 1672.2 * cos (xlp) + 28.0 * cos (xlp + xlp) - 0.35 * cos (d);

  // units: km
  BodySun[0] = EarthSun[0] * 149597870.0 / (1.0 + 1.e-05 * dasr);
  BodySun[1] = EarthSun[1] * 149597870.0 / (1.0 + 1.e-05 * dasr);
  BodySun[2] = EarthSun[2] * 149597870.0 / (1.0 + 1.e-05 * dasr);

}

static void moonLocal (double t, double BodyMoon[3])
{

  // computation of the Moon position wrt the central body (units: km)
  // =================================================================
  // In this case : central body = Earth

  double date   = t - 10000.0;
  double f   = radians (225.768 + 13.2293505 * date);
  double xl  = radians (185.454 + 13.064992 * date);
  double d   = radians (11.786 + 12.190749 * date);
  double xlp = radians (134.003 + 0.9856 * date);
  double e   = radians (23.44223 - 3.5626e-07 * date);
  double ce  = cos (e);
  double se  = sin (e);
  double rot = 0.6119022e-06 * t;
  double cr  = cos (rot);
  double sr  = sin (rot);

  // Brown's theory
  double dl = 10976.0 * sin (xl) - 2224.0 * sin (xl - d - d) + 1149.0 * sin (d + d);
  dl   = dl + 373.0 * sin (xl + xl) - 324.0 * sin (xlp) - 200.0 * sin (f + f);
  dl   = dl - 103.0 * sin (xl + xl - d - d) - 100.0 * sin (xl + xlp - d - d);
  dl   = dl + 93.0 * sin (xl + d + d);
  dl   = dl - 80.0 * sin (xlp - d - d) + 72.0 * sin (xl - xlp) - 61.0 * sin (d);
  dl   = dl - 53.0 * sin (xl + xlp);
  dl   = dl + 14.0 * sin (xl - xlp - d - d) + 19.0 * sin (xl - f - f);
  dl   = dl - 19.0 * sin (xl - 4.0 * d);
  dl   = dl + 17.0 * sin (3.0 * xl) - 27.0 * sin (f + f - d - d);
  dl   = dl - 12.0 * sin (xlp + d + d);
  dl   = dl - 22.0 * sin (xl + f + f) - 15.0 * sin (xl + xl - 4.0 * d);
  dl   = dl + 7.0 * sin (xl + xl + d + d) + 9.0 * sin (xl - d);
  dl   = dl - 6.0 * sin (3.0 * xl - d - d);
  dl   = dl + 7.0 * sin (4.0 * d) + 9.0 * sin (xlp + d) + 7.0 * sin (xl - xlp + d + d);
  dl   = dl + 5.0 * sin (xl + xl - xlp);
  dl   = dl * 1.e-05;

  double b = 8950.0 * sin (f) + 490.0 * sin (xl + f) + 485.0 * sin (xl - f);
  b    = b - 302.0 * sin (f - d - d);
  b    = b - 97.0 * sin (xl - f - d - d) - 81.0 * sin (xl + f - d - d);
  b    = b + 57.0 * sin (f + d + d);
  b    = b - 14.0 * sin (xlp + f - d - d) + 16.0 * sin (xl - f + d + d);
  b    = b + 15.0 * sin (xl + xl - f) + 30.0 * sin (xl + xl + f);
  b    = b - 6.0 * sin (xlp - f + d + d) - 7.0 * sin (xl + xl + f - d - d);
  b    = b + 7.0 * sin (xl + f + d + d);
  b    = b * 1.e-05;

  double u  = radians (68.341 + 13.176397 * date) + dl;
  double cu = cos (u);
  double su = sin (u);
  double cb = cos (b);
  double sb = sin (b);
  double rx = cu * cb;
  double ry = su * cb * ce - sb * se;

  double EarthMoon[3];
  EarthMoon[0] =  rx * cr + ry * sr;
  EarthMoon[1] =  ry * cr - rx * sr;
  EarthMoon[2] =  sb * ce + su * cb * se;

  double dasr = 5450.0 * cos (xl) + 1002.0 * cos (xl - d - d) + 825.0 * cos (d + d);
  dasr = dasr + 297.0 * cos (xl + xl) + 90.0 * cos (xl + d + d);
  dasr = dasr + 56.0 * cos (xlp - d - d);
  dasr = dasr + 42.0 * cos (xl + xlp - d - d) + 34.0 * cos (xl - xlp);
  dasr = dasr - 12.0 * cos (xlp) - 29.0 * cos (d) - 21.0 * cos (xl - f - f);
  dasr = dasr + 18.0 * cos (xl - 4.0 * d) - 28.0 * cos (xl + xlp);
  dasr = dasr + 11.0 * cos (xl + xl - 4.0 * d) + 18.0 * cos (3.0 * xl);
  dasr = dasr - 9.0 * cos (xlp + d + d) - 7.0 * cos (xl - xlp - d - d);
  dasr = dasr + 7.0 * cos (xl - xlp + d+d);
  dasr = dasr - 9.0 * cos (xl + xl - d - d) + 8.0 * cos (xl + xl + d + d);
  dasr = dasr + 8.0 * cos (4.0 * d);

  // units: km
  BodyMoon[0] = EarthMoon[0] * 384389.3 / (1.0 + 1.0e-5 * dasr);
  BodyMoon[1] = EarthMoon[1] * 384389.3 / (1.0 + 1.0e-5 * dasr);
  BodyMoon[2] = EarthMoon[2] * 384389.3 / (1.0 + 1.0e-5 * dasr);

}

static void earthLocal (double t, double BodyEarth[3])
{

  // computation of the Earth position wrt the central body (units: km)
  // =================================================================
  // In this case : central body = Earth

  BodyEarth[0] = 0. ;
  BodyEarth[1] = 0. ; 
  BodyEarth[2] = 0. ;

}

static double tsidrLocalC (double t, double offset)
{

  (void) fprintf(stdout, "user's function tsidrLocal C : function called\n");
  return tsidrLocal(t, offset);

}

static void sunLocalC (double t, double BodySun[3])
{

  (void) fprintf(stdout, "user's function sunLocal C : function called\n");
  sunLocal(t, BodySun);

}

static void moonLocalC (double t, double BodyMoon[3])
{

  (void) fprintf(stdout, "user's function moonLocal C : function called\n");
  moonLocal(t, BodyMoon);

}

static void earthLocalC (double t, double BodyEarth[3])
{

  (void) fprintf(stdout, "user's function earthLocal C : function called\n");
  earthLocal(t, BodyEarth);

}

static double tsidrLocalF (double * t, double * offset)
{

  (void) fprintf(stdout, "user's function tsidrLocal Fortran : function called\n");
  return tsidrLocal(* t, * offset);

}

static void sunLocalF (double * t, double BodySun[3])
{

  (void) fprintf(stdout, "user's function sunLocal Fortran : function called\n");
  sunLocal(* t, BodySun);

}

static void moonLocalF (double * t, double BodyMoon[3])
{

  (void) fprintf(stdout, "user's function moonLocal Fortran : function called\n");
  moonLocal(* t, BodyMoon);

}

static void earthLocalF (double *t, double BodyEarth[3])
{

  (void) fprintf(stdout, "user's function earthLocal Fortran : function called\n");
  earthLocal( * t, BodyEarth);

}

int main (int argc, char** argv)
{

  // programme de test de haut niveau des fonctionnalitées d'enregistrement
  // de fonctions utilisateurs lors de l'appel de la classe BodyEphem

  try {
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
    int              iteration1;
    int              iteration2;
    int              iteration3;
    int              iteration4;
    int              tranches;
    int              reperes;
    int              avecSpin;
    string           log;
    string           fichier;
    string           senseurs [3];
    double           mesures  [3];
    double           calage;

    analyseArguments (argc, argv, &date, orbite, &pas, attitude, spin,
                      &iteration1, &iteration2, &iteration3, &iteration4,
                      &tranches, &reperes, &avecSpin, &mu,
                      &log, &fichier, senseurs, mesures, &calage);

    if (log.size () > 0)
      if (MarmottesActiveTrace (log.c_str (), messageErreur, lgMessage) != 0)
      {
        (void) fprintf (stderr, "%s\n", messageErreur);
        return 1;
      }

    // création du simulateur
    cartesiens (orbite, mu, position, vitesse);
    IdentMarmottes id = MarmottesCreer (date, position, vitesse, attitude, spin,
                                        fichier.c_str (), senseurs [0].c_str (),
                                        senseurs [1].c_str (), senseurs [2].c_str (),
                                        messageErreur, lgMessage);
    if (id <= 0)
    {
      (void) fprintf (stderr, "%s\n", messageErreur);
      return 1;
    }

    // utilisation des fonctions par defaut
    fprintf(stdout,"Begin %d iteration(s) with default functions\n",iteration1);
    // appel de l'interface C
    if (MarmottesEnregistreCorps (id, r_terre, aplatissement, vit_bidon,
                                  r_lune_bidon, r_soleil_bidon,
                                  NULL, NULL, NULL, NULL,
                                  messageErreur, lgMessage))
    {
      (void) fprintf (stderr, "%s\n", messageErreur);
    }
    for (int i = 0; i < iteration1; i++)
    {
      extrapole  (&date, orbite, mu, pas);
      cartesiens (orbite, mu, position, vitesse);

      if (MarmottesAttitude (id, date, position, vitesse, mesures [0],
                             mesures [1], mesures [2],
                             attitude, spin,
                             messageErreur, lgMessage))
      {
        (void) fprintf (stderr, "%s\n", messageErreur);
      }
      for (int j = 0; j < 3; j++)
      {
        double m;
        if (MarmottesMesure (id, senseurs [j].c_str (), &m,
                             messageErreur, lgMessage))
        {
          (void) fprintf (stderr, "%s\n", messageErreur);
          MarmottesDetruire (id);
          return 1;
        }

        (void) fprintf (stdout,
                        "mesure réalisée par le senseur \"%s\" : %8.4f\n",
                        senseurs [j].c_str (), degres (m));
        
      }

    }

    // utilisation des fonctions utilisateurs
    fprintf(stdout,"Begin %d iteration(s) with user's functions\n",iteration2);
    // appel de l'interface C
    if (MarmottesEnregistreCorps (id, r_terre, aplatissement, vit_bidon,
                                  r_lune_bidon, r_soleil_bidon,
                                  tsidrLocalC, sunLocalC, moonLocalC, earthLocalC,
                                  messageErreur, lgMessage))
    {
      (void) fprintf (stderr, "%s\n", messageErreur);       
    }
    for (int i = 0; i < iteration2; i++)
    {
      extrapole  (&date, orbite, mu, pas);
      cartesiens (orbite, mu, position, vitesse);

      if (MarmottesAttitude (id, date, position, vitesse, mesures [0],
                             mesures [1], mesures [2],
                             attitude, spin,
                             messageErreur, lgMessage))
      {
        (void) fprintf (stderr, "%s\n", messageErreur);
      }
      for (int j = 0; j < 3; j++)
      {
        double m;
        if (MarmottesMesure (id, senseurs [j].c_str (), &m,
                           messageErreur, lgMessage))
        {
          (void) fprintf (stderr, "%s\n", messageErreur);
          MarmottesDetruire (id);
          return 1;
        }

        (void) fprintf (stdout,
                        "mesure réalisée par le senseur \"%s\" : %8.4f\n",
                        senseurs [j].c_str (), degres (m));
        
      }
    }

    // utilisation des fonctions par defaut
    fprintf(stdout,"Begin %d iteration(s) with default functions\n",iteration3);
    // appel de l'interface Fortran
    if (marmottesenregistrecorps_ (id, r_terre, aplatissement, vit_bidon,
                                   r_lune_bidon, r_soleil_bidon,
                                   NULL, NULL, NULL, NULL,
                                   messageErreur, lgMessage))
    {
      (void) fprintf (stderr, "%s\n", messageErreur);
    }
    for (int i = 0; i < iteration3; i++)
    {
      extrapole  (&date, orbite, mu, pas);
      cartesiens (orbite, mu, position, vitesse);

      if (MarmottesAttitude (id, date, position, vitesse, mesures [0],
                             mesures [1], mesures [2],
                             attitude, spin,
                             messageErreur, lgMessage))
      {
        (void) fprintf (stderr, "%s\n", messageErreur);
      }
      for (int j = 0; j < 3; j++)
      {
        double m;
        if (MarmottesMesure (id, senseurs [j].c_str (), &m,
                           messageErreur, lgMessage))
        {
          (void) fprintf (stderr, "%s\n", messageErreur);
          MarmottesDetruire (id);
          return 1;
        }

        (void) fprintf (stdout,
                        "mesure réalisée par le senseur \"%s\" : %8.4f\n",
                        senseurs [j].c_str (), degres (m));
        
      }
    }

     // utilisation des fonctions utilsateurs
    fprintf(stdout,"Begin %d iteration(s) with user's functions\n",iteration4);
    // appel de l'interface Fortran
    if (marmottesenregistrecorps_ (id, r_terre, aplatissement, vit_bidon,
                                   r_lune_bidon, r_soleil_bidon,
                                   tsidrLocalF, sunLocalF, moonLocalF, earthLocalF,
                                   messageErreur, lgMessage))
    {
      (void) fprintf (stderr, "%s\n", messageErreur);
    }
    for (int i = 0; i < iteration4; i++)
    {
      extrapole  (&date, orbite, mu, pas);
      cartesiens (orbite, mu, position, vitesse);

      if (MarmottesAttitude (id, date, position, vitesse, mesures [0],
                             mesures [1], mesures [2],
                             attitude, spin,
                             messageErreur, lgMessage))
      {
        (void) fprintf (stderr, "%s\n", messageErreur);
      }
      for (int j = 0; j < 3; j++)
      {
        double m;
        if (MarmottesMesure (id, senseurs [j].c_str (), &m,
                           messageErreur, lgMessage))
        {
          (void) fprintf (stderr, "%s\n", messageErreur);
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
