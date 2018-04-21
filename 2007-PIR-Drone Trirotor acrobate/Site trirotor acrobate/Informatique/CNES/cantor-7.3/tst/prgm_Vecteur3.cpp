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
//       $Log: prgm_Vecteur3.cpp,v $
//       Revision 1.7  2000/10/24 16:26:42  cantor
//       utilisation des tests de configuration à l'aide des variables définies
//       dans CantorConfigNoInstall.h pour les includes du standard C ou C++.
//
//$Version
//       $Id: prgm_Vecteur3.cpp,v 1.7 2000/10/24 16:26:42 cantor Exp $
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <CantorConfigNoInstall.h>

#ifdef HAVE_IOSTREAM
#include <iostream>
#endif

#include "club/ClubErreurs.h"
#include "cantor/Util.h"
#include "cantor/DeclDBL.h"

int main ()

{ ClubAllocHandler h; // utilise uniquement pour ses constructeur/destructeur

#ifdef HAVE_EXCEPTIONS
  try
  {
#endif

    VecDBL u (1, 0, 0);
    VecDBL v (0, degres (90.0));
    VecDBL w = u ^ (-v * 3.0);
    double            t = u | VecDBL (0.5, 0.5, 0);

    cout << "w = " << w << '\n';
    cout << " alpha = " << degres (w.alpha ());
    cout << " delta = " << degres (w.delta ());
    cout << '\n';

    cout << "t = " << t << '\n';

    w = u * 2.0 + v * 3.0;
    cout << w << '\n';

    u = VecDBL (1, 1, 1);
    w = u.orthogonal ();
    cout << u << " | " << w << " = " << (u | w) << '\n';

#ifdef HAVE_EXCEPTIONS
  }

  catch (ClubErreurs& e)
  { e.affiche (cerr);
    return 1;
  }
#endif

  return 0;

}
