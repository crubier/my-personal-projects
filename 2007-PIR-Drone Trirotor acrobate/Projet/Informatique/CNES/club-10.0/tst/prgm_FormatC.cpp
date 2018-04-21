////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//        DEF
//
//$Projet
//        CHOPE
//
//$Application
//        Club
//
//$Nom
//>       prgm_FormatC.cc
//
//$Resume
//       fichier d'implantation du test prgm_FormatC
//
//$Description
//       teste la classe FormatC
//
//$Contenu
//>       void imprimeCaracteristiques()
//>       void compare()                
//>       void appliqueFormat()         
//>       int main()                    
//
//$Historique
//       $Log: prgm_FormatC.cpp,v $
//       Revision 1.5  2000/10/24 14:23:11  club
//       ajout de l'include ClubConfigNoInstall.h  et des tests de configuration.
//
//       Revision 1.4  2000/10/24 08:36:33  club
//       ajout de l'include src/ClubConfig.h et modification des includes du
//       standard C : utilisation des includes du type cNAME au lieu de NAME.h
//       pour permettre la compilation avec le Sun Workshop 5.0
//
//       Revision 1.3  2000/09/13 15:34:38  club
//       modification de la fonction appliqueFormat pour qu'elle teste la méthode
//       applique de FormatC.
//
//       Revision 1.2  2000/09/07 08:35:52  club
//       utilisation de string de la STL au lieu de ChaineSimple.
//       mise à jour du cartouche.
//
//       Revision 1.1  2000/08/25 07:47:10  club
//       Ajout d'un test sur la classe FormatC.
//
//$Version
//       $Id: prgm_FormatC.cpp,v 1.5 2000/10/24 14:23:11 club Exp $
//$Auteur
//        O. Queyrut  CSSI
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#if STDC_HEADERS
#include <cstdio>
#endif

#include "club/FormatC.h"

void imprimeCaracteristiques (const FormatC& f)
{ (void) fprintf (stdout, "format : \"%s\"\n", f.chaine ().c_str ());
  (void) fprintf (stdout, "  %d arguments : ", f.nbArgs ());
  for (int i = 0; i < f.nbArgs (); i++)
    switch (f.typeArg (i))
    { case FormatC::ENTIER :
        (void) fprintf (stdout, " d");
        break;

      case FormatC::REEL :
        (void) fprintf (stdout, " f");
        break;

      case FormatC::CHAINE :
        (void) fprintf (stdout, " s");
        break;

      case FormatC::CARACTERE :
        (void) fprintf (stdout, " c");
        break;

      default :
        (void) fprintf (stdout, " ???");
        break;

    }

  (void) fprintf (stdout, "\n");

}

void compare (const FormatC& f1, const FormatC& f2)
{ if (f1.compatible (f2))
    (void) fprintf (stdout, "\"%s\" compatible avec \"%s\"\n\n",
                    f1.chaine ().c_str (), f2.chaine ().c_str ());
  else
    (void) fprintf (stdout, "\"%s\" incompatible avec \"%s\"\n\n",
                    f1.chaine ().c_str (), f2.chaine ().c_str ());
}

void appliqueFormat (const FormatC* ptrF, ...)
{
  va_list ap;
  va_start(ap, ptrF);

  string chaineResultat;
  ap = ptrF->applique (ap, &chaineResultat);
  chaineResultat += "\n";
  (void) fprintf (stdout, chaineResultat.c_str ());

  va_end(ap);
}


int main (int argc, char **argv)
{ int i1 = 4, i2 = 11, i3 = 2010, i4 = 5, i5 = 19, i6 = 58, i7 = 80, i8 = 88;
  double r1 = 1.1e-11, r2 = 22222.2222, r3 = -0.033;
  const char *c1 = "aaaa";
  const char *c2 = "bbb";
  long  l1 = 4l;
  long  l2 = 3l;

  FormatC fa1 ("erreur %-2d fonction %4s");
  imprimeCaracteristiques (fa1);
  appliqueFormat (&fa1, i1, c1, 0l, l1);
  FormatC fb1 ("%-2d error in function %4s");
  imprimeCaracteristiques (fb1);
  appliqueFormat (&fb1, i1, c1, 0l, l1);
  compare (fa1, fb1);

  FormatC fa2 ("pas d'integration trop faible: %9.2e");
  imprimeCaracteristiques (fa2);
  appliqueFormat (&fa2, r1, 0l);
  FormatC fb2 ("too small integration step: %9.2e");
  imprimeCaracteristiques (fb2);
  appliqueFormat (&fb2, r1, 0l);
  compare (fa2, fb2);

  FormatC fa3 ("convergence du Cowell impossible en %2d iterations");
  imprimeCaracteristiques (fa3);
  appliqueFormat (&fa3, i2, 0l);
  FormatC fb3 ("Cowell unable to converge in %2d iterations");
  imprimeCaracteristiques (fb3);
  appliqueFormat (&fb3, i2, 0l);
  compare (fa3, fb3);

  FormatC fa4 ("\n\n  final date : %12.5f     %2.2i/%2.2i/%4.4i/%2.2i/%2.2i/%2.2i/%3.3i\n"
               "  step for the numerical integration: %5.1f h\n"
               "  cpssm : %7.4fm**2/kg\n"
               "  number of impulsions : %+3i");
  imprimeCaracteristiques (fa4);
  appliqueFormat (&fa4, r2, i1, i2, i3, i4, i5, i6, i7, r1, r3, i8, 0l);
  FormatC fb4 ("\n\n  date finale: %12.5f     %2.2i/%2.2i/%4.4i/%2.2i/%2.2i/%2.2i/%3.3i\n"
               "  pas pour l''integration numerique : %5.1f h\n"
               "  cpssm : %7.4fm**2/kg\n"
               "  nombre d'impulsions : %+3i");
  imprimeCaracteristiques (fb4);
  appliqueFormat (&fb4, r2, i1, i2, i3, i4, i5, i6, i7, r1, r3, i8, 0l);
  compare (fa4, fb4);

  FormatC fa5 ("mode : %20s - code : %4i");
  imprimeCaracteristiques (fa5);
  appliqueFormat (&fa5, c1, i1, 0l, l1);
  FormatC fb5 ("mode : %20s - A098L telemetry value : %4i");
  imprimeCaracteristiques (fb5);
  appliqueFormat (&fb5, c1, i1, 0l, l1);
  compare (fa5, fb5);

  FormatC fa6 (" Donnees:\n --------\nMode traite : % 11s");
  imprimeCaracteristiques (fa6);
  appliqueFormat (&fa6, c2, 0l, l2);
  FormatC fb6 (" Data:\n -----\n    Computed mode           : %11s");
  imprimeCaracteristiques (fb6);
  appliqueFormat (&fb6, c2, 0l, l2);
  compare (fa6, fb6);

  FormatC fa8 ("| Tuyere |   %1i   |   %1i   |   %1i   |   %1i   |   %1i   |   %1i   |   %1i   |");
  imprimeCaracteristiques (fa8);
  appliqueFormat (&fa8, i1, i2, i3, i4, i5, i6, i7, 0l);
  FormatC fb8 ("| Thruster |   %1i   |   %1i   |   %1i   |   %1i   |   %1i   |   %1i   |   %1i   |");
  imprimeCaracteristiques (fb8);
  appliqueFormat (&fb8, i1, i2, i3, i4, i5, i6, i7, 0l);
  compare (fa8, fb8);

  compare (fa3, fa8);
  compare (fa1, fb3);
  compare (fa5, fb6);


  return 0;
}
