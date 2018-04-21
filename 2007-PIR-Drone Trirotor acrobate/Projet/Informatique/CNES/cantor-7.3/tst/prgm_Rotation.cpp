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
//       fichier d'implantation de la classe XXXX
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//
//$Historique
//       $Log: prgm_Rotation.cpp,v $
//       Revision 1.13  2000/10/26 16:56:36  cantor
//       suppression de l'include CantorConfig.h
//
//       Revision 1.12  2000/10/24 16:26:42  cantor
//       utilisation des tests de configuration à l'aide des variables définies
//       dans CantorConfigNoInstall.h pour les includes du standard C ou C++.
//
//       Revision 1.11  2000/10/18 16:04:42  cantor
//       modification des include.
//
//$Version
//       $Id: prgm_Rotation.cpp,v 1.13 2000/10/26 16:56:36 cantor Exp $
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <CantorConfigNoInstall.h>

#if STDC_HEADERS
#include <cstdio>
#endif

#ifdef HAVE_IOSTREAM
#include <iostream>
#endif

#ifdef HAVE_IOMANIP
#include <iomanip>
#endif

#include "club/OptionsAppli.h"
#include "club/ClubErreurs.h"
#include "cantor/Util.h"
#include "cantor/DeclDBL.h"

static void AfficheRotation (const RotDBL& r)
{ cout << "rotation d'axe " << r.axe ()
       << " et d'angle "    << degres (r.angle ())
       << endl;

  cout << "coefficients du quaternion associe:\n"
       <<  "q0 = " << r.q0 ()
       << " q1 = " << r.q1 ()
       << " q2 = " << r.q2 ()
       << " q3 = " << r.q3 ()
       << endl;

  double m [3][3];
  r.initMatrice (m);
  cout << "matrice associee:\n" << setprecision (6)
       << "[ " << m [0][0] << ' ' << m [0][1] << ' ' << m [0][2] << "]\n"
       << "[ " << m [1][0] << ' ' << m [1][1] << ' ' << m [1][2] << "]\n"
       << "[ " << m [2][0] << ' ' << m [2][1] << ' ' << m [2][2] << "]\n";

  cout << "r (i)  : " << r (VecDBL (1.0, 0.0, 0.0)) << endl;
  cout << "r (j)  : " << r (VecDBL (0.0, 1.0, 0.0)) << endl;
  cout << "r (k)  : " << r (VecDBL (0.0, 0.0, 1.0)) << endl;
  cout << "r (axe): " << r (r.axe ()) << endl;

  cout << "axe   de la rotation inverse: " << (-r).axe   () << endl;
  cout << "angle de la rotation inverse: " << degres ((-r).angle ()) << endl;

}

int main (int argc, char** argv)
{ ClubAllocHandler h; // utilise uniquement pour ses constructeur/destructeur

#ifdef HAVE_EXCEPTIONS
  try
  {
#endif

    VecDBL u1, u2;
    VecDBL v1, v2;

    OptionsAppli analyseur (argv [0]);

    // premier vecteur d'origine
    // option u1: une occurrence, pas de valeur par defaut
    analyseur.ajouterOption (OptionTableauReels ("u1", 0, 1, sansValeurDefaut,
                                                 3));

    // second vecteur d'origine
    // option u2: une occurrence, pas de valeur par defaut
    analyseur.ajouterOption (OptionTableauReels ("u2", 0, 1, sansValeurDefaut,
                                                 3));

    // premier vecteur destination
    // option v1: une occurrence, pas de valeur par defaut
    analyseur.ajouterOption (OptionTableauReels ("v1", 0, 1, sansValeurDefaut,
                                                 3));

    // second vecteur destination
    // option v2: une occurrence, pas de valeur par defaut
    analyseur.ajouterOption (OptionTableauReels ("v2", 0, 1, sansValeurDefaut,
                                                 3));

    // axe
    // option axe: une occurrence, pas de valeur par defaut
    analyseur.ajouterOption (OptionTableauReels ("axe", 0, 1, sansValeurDefaut,
                                                 3));

    // angle
    // option angle: une occurrence, pas de valeur par defaut
    analyseur.ajouterOption (OptionReel ("angle", 0, 1, sansValeurDefaut,
                                         0.0, -360.0, 360.0));

    // quaternion
    // option q: une occurrence, pas de valeur par defaut
    analyseur.ajouterOption (OptionTableauReels ("q", 0, 1, sansValeurDefaut,
                                                 4));

    // vecteur auquel appliquer la rotation
    // option u: une occurrence, pas de valeur par defaut
    analyseur.ajouterOption (OptionTableauReels ("u", 0, 1, sansValeurDefaut,
                                                 3));

    // analyse de la ligne
    analyseur.initialiser (argc, argv);
    analyseur.garantirComplet ();

    // recuperation des donnees
    if (analyseur.occurrencesPassees ("axe") > 0)
    { // l'utilisateur a passe un axe et un angle

      if ((analyseur.occurrencesPassees ("u1") > 0)
          ||
          (analyseur.occurrencesPassees ("q")  > 0))
      { char tampon [1000];
        (void) sprintf (tampon, "options -axe, -u1, et -q incompatibles");
        ClubErreurs::erreur (0, ClubErreurs::message_simple, tampon);
      }

      double tableau [3];
      analyseur.lireValeur ("axe", 3, tableau);
      VecDBL axe (tableau [0], tableau [1], tableau [2]);

      if (analyseur.occurrencesPassees ("angle") <= 0)
      { char tampon [1000];
        (void) sprintf (tampon, "option -axe sans option -angle");
        ClubErreurs::erreur (0, ClubErreurs::message_simple, tampon);
      }

      double angle;
      analyseur.lireValeur ("angle", &angle);
      angle = radians (angle);

      RotDBL  r (axe, angle);
      AfficheRotation (r);

      VecDBL normal = axe.orthogonal ();
      cout << "normal        : " <<    normal  << endl;
      cout << "r (normal)    : " << r (normal) << endl;
      cout << "angle (" << normal
           << ", " << r (normal)
           << ") = " << degres (normal.angleAvecVecteur (r (normal)))
           << " degres\n";

      if (analyseur.occurrencesPassees ("u") > 0)
      { analyseur.lireValeur ("u", 3, tableau);
        VecDBL u (tableau [0], tableau [1], tableau [2]);
        cout << "u     : " << u     << endl;
        cout << "r (u) : " << r (u) << endl;
      }

    }
    else if (analyseur.occurrencesPassees ("u1") > 0)
    { // l'utilisateur a passe un couple de vecteurs

      if (analyseur.occurrencesPassees ("q")  > 0)
      { char tampon [1000];
        (void) sprintf (tampon, "options -axe, -u1, et -q incompatibles");
        ClubErreurs::erreur (0, ClubErreurs::message_simple, tampon);
      }

      double tableau [3];
      analyseur.lireValeur ("u1", 3, tableau);
      u1 = VecDBL (tableau [0], tableau [1], tableau [2]);

      if (analyseur.occurrencesPassees ("v1") <= 0)
      { char tampon [1000];
        (void) sprintf (tampon, "option -u1 sans option -v1");
        ClubErreurs::erreur (0, ClubErreurs::message_simple, tampon);
      }
      analyseur.lireValeur ("v1", 3, tableau);
      v1 = VecDBL (tableau [0], tableau [1], tableau [2]);

      if (analyseur.occurrencesPassees ("u2") <= 0)
      { // l'utilisateur n'a donne qu'un couple de vecteurs
        RotDBL  r (u1, v1);
        AfficheRotation (r);
        cout << " r (u1): " << r (u1)    << '\n';
        cout << "-r (v1): " << (-r) (v1) << '\n';

        if (analyseur.occurrencesPassees ("u") > 0)
        { analyseur.lireValeur ("u", 3, tableau);
          VecDBL u (tableau [0], tableau [1], tableau [2]);
          cout << "u     : " << u     << endl;
          cout << "r (u) : " << r (u) << endl;
        }

      }
      else
      { // l'utilisateur a donne deux couples de vecteurs

        analyseur.lireValeur ("u2", 3, tableau);
        u2 = VecDBL (tableau [0], tableau [1], tableau [2]);

        if (analyseur.occurrencesPassees ("v2") <= 0)
        { char tampon [1000];
          (void) sprintf (tampon, "option -u2 sans option -v2");
          ClubErreurs::erreur (0, ClubErreurs::message_simple, tampon);
        }

        analyseur.lireValeur ("v2", 3, tableau);
        v2 = VecDBL (tableau [0], tableau [1], tableau [2]);

        RotDBL  r (u1, u2, v1, v2);
        AfficheRotation (r);
        cout << " r (u1): " << r (u1)    << '\n';
        cout << " r (u2): " << r (u2)    << '\n';
        cout << "-r (v1): " << (-r) (v1) << '\n';
        cout << "-r (v2): " << (-r) (v2) << '\n';

        if (analyseur.occurrencesPassees ("u") > 0)
        { analyseur.lireValeur ("u", 3, tableau);
          VecDBL u (tableau [0], tableau [1], tableau [2]);
          cout << "u     : " << u     << endl;
          cout << "r (u) : " << r (u) << endl;
        }

      }
    }
    else if (analyseur.occurrencesPassees ("q") > 0)
    { // l'utilisateur a passe les composantes du quaternion

      double tableau [4];
      analyseur.lireValeur ("q", 4, tableau);
      RotDBL r (tableau [0], tableau [1], tableau [2], tableau [3]);

      AfficheRotation (r);

      if (analyseur.occurrencesPassees ("u") > 0)
      { double tabVec [3];
        analyseur.lireValeur ("u", 3, tabVec);
        VecDBL u (tabVec [0], tabVec [1], tabVec [2]);
        cout << "u     : " << u     << endl;
        cout << "r (u) : " << r (u) << endl;
      }

    }
    else
    { char tampon [1000];
      (void) sprintf (tampon,
                      "une des options -axe, -u1, ou -q doit etre passee\n");
      (void) strcat (tampon, analyseur.usage ());
      ClubErreurs::erreur (0, ClubErreurs::message_simple, tampon);
    }


#ifdef HAVE_EXCEPTIONS
  }

  catch (ClubErreurs& e)
  { e.affiche (cerr);
    return 1;
  }
#endif

  return 0;

}
