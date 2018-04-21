///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//       Marmottes
//
//$Application
//       Marmottes
//
//$Nom
//>       prgm_MethodesMarmottes.cpp
//
//$Resume
//       fichier d'implémentation de tests
//
//$Description
//       Implémentation de tests spécifiques aux
//       méthodes de Marmottes.
//
//$Contenu
//>       
//
//$Historique
//       $Log: prgm_MethodesMarmottes.cpp,v $
//       Revision 1.4  2004/06/21 15:21:40  marmottes
//       correction du format d'écriture des réels (FA-ID 33)
//
//       Revision 1.3  2003/10/22 13:08:41  marmottes
//       DM 0026, 0027
//       FA 0031
//
//       Revision 1.2  2003/03/07 16:00:32  marmottes
//       DM-ID 18 Modification de nommage d'include
//
//       Revision 1.1  2003/02/12 09:28:29  marmottes
//       DM-ID 10 Création du programme
//
//
//$Version
//       $Id: prgm_MethodesMarmottes.cpp,v 1.4 2004/06/21 15:21:40 marmottes Exp $
//
//$Auteur
//       S. Vresk CSSI
//       Copyright (C) 2003 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <sys/time.h>

#include <cstdio>
#include <cstring>

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
{
  // programme de test des fonctions
  // marmottesAutoriseExtrapolation() et
  // marmottescopie()

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
    int              codeRetour;
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
      {
        (void) fprintf (stderr, "%s\n", messageErreur);
        return 1;
      }
    
    // création du simulteur
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

    cout << "Operation de copie" << endl;

    IdentMarmottes idClone = MarmottesCopie ( id, messageErreur, lgMessage);
    if (idClone <= 0)
    {
      (void) fprintf (stderr, "%s\n", messageErreur);
      return 1;
    }

    cout << "L'identificateur Marmottes est       " << id << endl;
    cout << "L'identificateur Marmottes copie est " << idClone << endl;
    cout << endl;
    cout << endl;
    cout << "Travail sur l original en autorisant l extrapolation" << endl;
    cout << endl;
    
    codeRetour = MarmottesAutoriseExtrapolation (id, messageErreur, lgMessage);

    for (int i = 0; i < iterations; i++)
    {
      extrapole  (&date, orbite, mu, pas);
      cartesiens (orbite, mu, position, vitesse);

      if (MarmottesAttitude (id, date, position, vitesse, mesures [0],
                             mesures [1], mesures [2],
                             attitude, spin,
                             messageErreur, lgMessage))
        (void) fprintf (stderr, "%s\n", messageErreur);

      (void) fprintf (stdout,
                      "attitude : %8.4f %8.4f %8.4f %8.4f\n",
                      attitude [0], attitude [1], attitude [2], attitude [3]);
      
      if (avecSpin)
        (void) fprintf (stdout,
                        "spin     : %8.4f %8.4f %8.4f \n",
                        spin [0], spin [1], spin [2]);

      for (int j = 0; j < 3; j++)
      {
        double m;
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

    cout << endl;
    cout << endl;
    cout << "Travail sur la copie en interdisant l extrapolation" << endl;
    cout << endl;
    
    codeRetour = MarmottesInterditExtrapolation (idClone, messageErreur, lgMessage);

    for (int i = 0; i < iterations; i++)
    {
      extrapole  (&date, orbite, mu, pas);
      cartesiens (orbite, mu, position, vitesse);

      if (MarmottesAttitude (idClone, date, position, vitesse, mesures [0],
                             mesures [1], mesures [2],
                             attitude, spin,
                             messageErreur, lgMessage))
        (void) fprintf (stderr, "%s\n", messageErreur);

      (void) fprintf (stdout,
                      "attitude : %8.4f %8.4f %8.4f %8.4f\n",
                      attitude [0], attitude [1], attitude [2], attitude [3]);
      
      if (avecSpin)
        (void) fprintf (stdout,
                        "spin     : %8.4f %8.4f %8.4f \n",
                        spin [0], spin [1], spin [2]);

      for (int j = 0; j < 3; j++)
      {
        double m;
        if (MarmottesMesure (idClone, senseurs [j].c_str (), &m,
                             messageErreur, lgMessage))
        { (void) fprintf (stderr, "%s\n", messageErreur);
        MarmottesDetruire (idClone);
        return 1;
        }

        (void) fprintf (stdout,
                        "mesure réalisée par le senseur \"%s\" : %8.4f\n",
                        senseurs [j].c_str (), degres (m));
        
      }

    }

    for (int i = 0; i < iterations; i++)
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

      double date_lue(0.0);
      double position_lue [3];
      double vitesse_lue  [3];
      double attitude_lue [4];
      double spin_lu      [3];

      // Initialisation des valeurs
      attitude[0] = 0.0;
      for (int i=0; i<3; i++)
      {
        position_lue[i]   = 0.0;
        vitesse_lue[i]    = 0.0;
        attitude_lue[i+1] = 0.0;
        spin_lu[i]        = 0.0;
      }

      if (MarmottesLireParametres(id, &date_lue, position_lue, vitesse_lue, attitude_lue, spin_lu, messageErreur, lgMessage))
        { (void) fprintf (stderr, "%s\n", messageErreur);
        MarmottesDetruire (idClone);
        return 1;
        }

      // Ecriture des resultats obtenus dans le fichier de sortie
      fprintf(stdout,"\nDate lue : %f\n",date_lue);
      fprintf(stdout,"Position lue :\n\t x = %f\n\t y = %f\n\t z = %f\n",
              position_lue[0], position_lue[1],  position_lue[2] );
      fprintf(stdout,"Vitesse lue :\n\t x = %f\n\t y = %f\n\t z = %f\n",
              vitesse_lue[0], vitesse_lue[1],  vitesse_lue[2] );
      fprintf(stdout,"Attitude lue :\n\t q0 = %f\n\t q1 = %f\n\t q2 = %f\n\t q3 = %f\n",
              attitude_lue[0], attitude_lue[1], attitude_lue[2], attitude_lue[3]);
      fprintf(stdout,"Spin lu :\n\t x = %f\n\t y = %f\n\t z = %f\n",
              spin_lu[0], spin_lu[1],  spin_lu[2]);
        
  }

  // fin normale du programme
  return 0;
  }

  catch (...)
  {
    return 1;
  }
}
