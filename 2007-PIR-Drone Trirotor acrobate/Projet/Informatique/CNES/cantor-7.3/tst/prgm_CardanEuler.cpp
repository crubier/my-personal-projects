////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//        Chope
//$Application
//        Cantor
//$Nom
//
//$Resume
//       programme de test des angles de Cardan et d'Euler
//
//$Description
//       programme de test des angles de Cardan et d'Euler
//
//$Contenu
//
//$Historique
//       $Log: prgm_CardanEuler.cpp,v $
//       Revision 1.2  2002/02/04 13:24:03  cantor
//       mise a jour du test en adequation avec la protection singularite_angle
//
//       Revision 1.1  2001/06/06 07:16:35  cantor
//       version initiale
//
//$Version
//       $Id: prgm_CardanEuler.cpp,v 1.2 2002/02/04 13:24:03 cantor Exp $
//$Auteur
//        Luc Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <CantorConfigNoInstall.h>

#if STDC_HEADERS
#include <cstdio>
#endif

#include "club/OptionsAppli.h"
#include "cantor/DeclDBL.h"
#include "cantor/Util.h"

void analyseArguments (int argc, char **argv,
                       RotDBL::AxesRotation *ptrOrdre,
                       double angles [3],
                       int *ptrN,
                       VecDBL *ptrV)
  throw (ClubErreurs)
{

  OptionsAppli analyseur (argv [0]);

  // ordre des rotations élémentaires pour les angles de Cardan
  analyseur.ajouterOption (OptionSansValeur ("xyz", 0, 1));
  analyseur.ajouterOption (OptionSansValeur ("xzy", 0, 1));
  analyseur.ajouterOption (OptionSansValeur ("yxz", 0, 1));
  analyseur.ajouterOption (OptionSansValeur ("yzx", 0, 1));
  analyseur.ajouterOption (OptionSansValeur ("zxy", 0, 1));
  analyseur.ajouterOption (OptionSansValeur ("zyx", 0, 1));

  // ordre des rotations élémentaires pour les angles d'Euler
  analyseur.ajouterOption (OptionSansValeur ("xyx", 0, 1));
  analyseur.ajouterOption (OptionSansValeur ("xzx", 0, 1));
  analyseur.ajouterOption (OptionSansValeur ("yxy", 0, 1));
  analyseur.ajouterOption (OptionSansValeur ("yzy", 0, 1));
  analyseur.ajouterOption (OptionSansValeur ("zxz", 0, 1));
  analyseur.ajouterOption (OptionSansValeur ("zyz", 0, 1));

  // angles des rotations élémentaires
  // option angles : une occurrence, pas de valeur par defaut
  analyseur.ajouterOption (OptionTableauReels ("angles", 1, 1, sansValeurDefaut,
                                               3, (double *) 0,
                                               -180.0, 180.0));

  // nombre d'étapes pour chaque rotation élémentaire
  // option n: une occurrence, valeur par defaut : 10
  analyseur.ajouterOption (OptionEntier ("n", 0, 1, avecValeurDefaut,
                                         10, 1, 10000));

  // vecteur à tester
  // option v : une occurrence, pas de valeur par defaut
  analyseur.ajouterOption (OptionTableauReels ("v", 1, 1, sansValeurDefaut,
                                               3, (double *) 0,
                                               -1.0, 1.0));

  // analyse de la ligne
  analyseur.initialiser (argc, argv);
  analyseur.garantirComplet ();

  if (analyseur.occurrencesPassees ("xyz") > 0)
    *ptrOrdre = RotDBL::XYZ;
  else if (analyseur.occurrencesPassees ("xzy") > 0)
    *ptrOrdre = RotDBL::XZY;
  else if (analyseur.occurrencesPassees ("yxz") > 0)
    *ptrOrdre = RotDBL::YXZ;
  else if (analyseur.occurrencesPassees ("yzx") > 0)
    *ptrOrdre = RotDBL::YZX;
  else if (analyseur.occurrencesPassees ("zxy") > 0)
    *ptrOrdre = RotDBL::ZXY;
  else if (analyseur.occurrencesPassees ("zyx") > 0)
    *ptrOrdre = RotDBL::ZYX;
  else if (analyseur.occurrencesPassees ("xyx") > 0)
    *ptrOrdre = RotDBL::XYX;
  else if (analyseur.occurrencesPassees ("xzx") > 0)
    *ptrOrdre = RotDBL::XZX;
  else if (analyseur.occurrencesPassees ("yxy") > 0)
    *ptrOrdre = RotDBL::YXY;
  else if (analyseur.occurrencesPassees ("yzy") > 0)
    *ptrOrdre = RotDBL::YZY;
  else if (analyseur.occurrencesPassees ("zxz") > 0)
    *ptrOrdre = RotDBL::ZXZ;
  else if (analyseur.occurrencesPassees ("zyz") > 0)
    *ptrOrdre = RotDBL::ZYZ;
  else
  {
    char tampon [10000];
    (void) sprintf (tampon,
                    "ordre des rotations élémentaire non spécifié\n%s",
                    analyseur.usage ());
    throw ClubErreurs (ClubErreurs::message_simple, tampon);
  }

  analyseur.lireValeur ("n", ptrN);
  analyseur.lireValeur ("angles", 3, angles);

  double v [3];
  analyseur.lireValeur ("v", 3, v);
  *ptrV = VecDBL (v [0], v [1], v [2]);

}

void traiteRotation (RotDBL::AxesRotation ordre,
                     double alpha1, double alpha2, double alpha3,
                     const VecDBL& v)
{

  try
  {

    RotDBL r (ordre, alpha1, alpha2, alpha3);
    double beta1, beta2, beta3;
    
    r.initAngles (ordre, &beta1, &beta2, &beta3);
    
    double erreur1 = recaleAngle (beta1, alpha1) - alpha1;
    double erreur2 = recaleAngle (beta2, alpha2) - alpha2;
    double erreur3 = recaleAngle (beta3, alpha3) - alpha3;
    if (erreur1 < -1.5 || erreur1 > 1.5
        || erreur2 < -1.5 || erreur2 > 1.5
        || erreur3 < -1.5 || erreur3 > 1.5)
      {
        if (ordre == RotDBL::XYZ
            || ordre == RotDBL::XZY
            || ordre == RotDBL::YXZ
            || ordre == RotDBL::YZX
            || ordre == RotDBL::ZXY
            || ordre == RotDBL::ZYX)
          { // cas des angles de Cardan
            alpha1 = recaleAngle (alpha1 + M_PI, 0.0);
            alpha2 = recaleAngle (M_PI - alpha2, 0.0);
            alpha3 = recaleAngle (alpha3 + M_PI, 0.0);
          }
        else
          { // cas des angles d'Euler
            alpha1 = recaleAngle (alpha1 + M_PI, 0.0);
            alpha2 = recaleAngle (-alpha2, 0.0);
            alpha3 = recaleAngle (alpha3 + M_PI, 0.0);
          }
      }
    erreur1 = degres (recaleAngle (beta1, alpha1) - alpha1);
    erreur2 = degres (recaleAngle (beta2, alpha2) - alpha2);
    erreur3 = degres (recaleAngle (beta3, alpha3) - alpha3);
    
    VecDBL image = r (v);
    
    printf ("%11.8f %11.8f %11.8f %12.5e %12.5e %12.5e\n",
            image.x (), image.y (), image.z (),
            erreur1, erreur2, erreur3);
  }

  catch (CantorErreurs& ce)
  {
    ce.affiche();
    ce.correction();
  }

}

int main (int argc, char** argv)
{ ClubAllocHandler h; // utilise uniquement pour ses constructeur/destructeur

  try
  {

    // analyse des arguments de la ligne de commande
    RotDBL::AxesRotation ordre;
    int n;
    double angles [3];
    VecDBL v;
    analyseArguments (argc, argv, &ordre, angles, &n, &v);

    // construction progressive des rotations
    for (int i = 0; i <= n; ++i)
      traiteRotation (ordre,
                      i * radians (angles [0]) / n,
                      0.0,
                      0.0,
                      v);
    for (int i = 0; i <= n; ++i)
      traiteRotation (ordre,
                      radians (angles [0]),
                      i * radians (angles [1]) / n,
                      0.0,
                      v);
    for (int i = 0; i <= n; ++i)
      traiteRotation (ordre,
                      radians (angles [0]),
                      radians (angles [1]),
                      i * radians (angles [2]) / n,
                      v);

  }

  catch (ClubErreurs& e)
  {
    return 1;
  }

  catch (CantorErreurs& e)
  {
    return 1;
  }

  return 0;

}
