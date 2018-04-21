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
//>       prgm_FormatFortran.cc
//$Resume
//       fichier d'implantation du test prgm_FormatFortran
//
//$Description
//       teste la classe FormatFortran
//
//$Contenu
//>       void imprimeCaracteristiques()
//>       void compare()                
//>       void appliqueFormat()         
//>       int main()                    
//
//$Historique
//       $Log: prgm_FormatFortran.cpp,v $
//       Revision 1.8  2000/10/24 14:23:11  club
//       ajout de l'include ClubConfigNoInstall.h  et des tests de configuration.
//
//       Revision 1.7  2000/10/24 08:36:33  club
//       ajout de l'include src/ClubConfig.h et modification des includes du
//       standard C : utilisation des includes du type cNAME au lieu de NAME.h
//       pour permettre la compilation avec le Sun Workshop 5.0
//
//       Revision 1.6  2000/09/07 08:35:52  club
//       utilisation de string de la STL au lieu de ChaineSimple.
//       mise à jour du cartouche.
//
//       Revision 1.5  1999/08/26 09:04:02  club
//       Conformément à la norme ANSI C++, la fonction main a
//       désormais un type de retour
//
//$Version
//       $Id: prgm_FormatFortran.cpp,v 1.8 2000/10/24 14:23:11 club Exp $
//$Auteur
//        P-A.Cros    CSSI
//        M. Julien   CSSI 
//        O. Queyrut  CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#if STDC_HEADERS
#include <cstdio>
#endif

#include "club/FormatFortran.h"

void imprimeCaracteristiques (const FormatFortran& f)
{ (void) fprintf (stdout, "format : \"%s\"\n", f.chaine ().c_str ());
  (void) fprintf (stdout, "  %d arguments : ", f.nbArgs ());
  for (int i = 0; i < f.nbArgs (); i++)
    switch (f.typeArg (i))
    { case FormatFortran::ENTIER :
        (void) fprintf (stdout, " i");
        break;

      case FormatFortran::REEL :
        (void) fprintf (stdout, " f");
        break;

      case FormatFortran::CHAINE_ARG :
        (void) fprintf (stdout, " c");
        break;

      case FormatFortran::BOOLEEN :
        (void) fprintf (stdout, " b");
        break;

      default :
        (void) fprintf (stdout, " ???");
        break;

    }

  (void) fprintf (stdout, "\n");

}

void compare (const FormatFortran& f1, const FormatFortran& f2)
{ if (f1.compatible (f2))
    (void) fprintf (stdout, "%s compatible avec %s\n\n",
                    f1.chaine ().c_str (), f2.chaine ().c_str ());
  else
    (void) fprintf (stdout, "%s incompatible avec %s\n\n",
                    f1.chaine ().c_str (), f2.chaine ().c_str ());
}

void appliqueFormat (const FormatFortran *ptrF ...)
{ string       c;
  int          nbLong = 1;
  long int     longFormat;
  va_list      ap;

  va_start(ap, ptrF);
  ptrF->applique (ap, nbLong, &longFormat, &c);
  va_end(ap);

  (void) fprintf (stdout, "%s\n", c.c_str ());

}

int main (int argc, char **argv)
{ int i1 = 4, i2 = 11, i3 = 2010, i4 = 5, i5 = 19, i6 = 58, i7 = 80, i8 = 88;
  double r1 = 1.1e-11, r2 = 22222.2222, r3 = -0.033;
  const char *c1 = "aaaa";
  const char *c2 = "bbb";
  long  l1 = 4l;
  long  l2 = 3l;

  FormatFortran fa1 ("('erreur ', i2, ' fonction ', a6, ' (MSLIB)')");
  imprimeCaracteristiques (fa1);
  appliqueFormat (&fa1, &i1, c1, 0l, l1);
  FormatFortran fb1 ("(i2, ' error in function ', a6, ' (MSLIB)')");
  imprimeCaracteristiques (fb1);
  appliqueFormat (&fb1, &i1, c1, 0l, l1);
  compare (fa1, fb1);

  FormatFortran fa2 ("('pas d''integration trop faible: ', e9.2)");
  imprimeCaracteristiques (fa2);
  appliqueFormat (&fa2, &r1, 0l);
  FormatFortran fb2 ("('too small integration step: ', e9.2)");
  imprimeCaracteristiques (fb2);
  appliqueFormat (&fb2, &r1, 0l);
  compare (fa2, fb2);

  FormatFortran fa3 ("('convergence du Cowell impossible en ', i2, ' iterations')");
  imprimeCaracteristiques (fa3);
  appliqueFormat (&fa3, &i2, 0l);
  FormatFortran fb3 ("('Cowell unable to converge in ', i2, ' iterations')");
  imprimeCaracteristiques (fb3);
  appliqueFormat (&fb3, &i2, 0l);
  compare (fa3, fb3);

  FormatFortran fa4 ("(//,2x,'final date :',f12.5,5x,i2.2,'/',i2.2,'/',i4.4,'/',i2.2,'/',i2.2,'/',i2.2,'/',i3.3,/,2x,'step for the numerical integration: ',f5.1,' h',/,2x,'cpssm : ',f7.4,'m**2/kg',/,2x,'number of impulsions : ',i3)");
  imprimeCaracteristiques (fa4);
  appliqueFormat (&fa4, &r2, &i1, &i2, &i3, &i4, &i5, &i6, &i7, &r1, &r3, &i8, 0l);
  FormatFortran fb4 ("(//,2x,'date finale:',f12.5,5x,i2.2,'/',i2.2,'/',i4.4,'/',i2.2,'/',i2.2,'/',i2.2,'/',i3.3,/,2x,'pas pour l''integration numerique : ',f5.1,' h',/,2x,'cpssm : ',f7.4,'m**2/kg',/,2x,'nombre d''impulsions : ',i3)");
  imprimeCaracteristiques (fb4);
  appliqueFormat (&fb4, &r2, &i1, &i2, &i3, &i4, &i5, &i6, &i7, &r1, &r3, &i8, 0l);
  compare (fa4, fb4);

  FormatFortran fa5 ("('mode :',A20,' - code :',I4)");
  imprimeCaracteristiques (fa5);
  appliqueFormat (&fa5, c1, &i1, 0l, l1);
  FormatFortran fb5 ("(' mode :',A20,' - A098L telemetry value :',I4)");
  imprimeCaracteristiques (fb5);
  appliqueFormat (&fb5, c1, &i1, 0l, l1);
  compare (fa5, fb5);

  FormatFortran fa6 ("(' Donnees:',/,' --------',/,'Mode traite :',a11)");
  imprimeCaracteristiques (fa6);
  appliqueFormat (&fa6, c2, 0l, l2);
  FormatFortran fb6 ("(' Data:',/,' -----',/,'    Computed mode           :',a11)");
  imprimeCaracteristiques (fb6);
  appliqueFormat (&fb6, c2, 0l, l2);
  compare (fa6, fb6);

  FormatFortran fa7 ("(126('-'))");
  imprimeCaracteristiques (fa7);
  appliqueFormat (&fa7, 0l);
  FormatFortran fb7 ("(1x,126('-'))");
  imprimeCaracteristiques (fb7);
  appliqueFormat (&fb7, 0l);
  compare (fa7, fb7);

  FormatFortran fa8 ("('| Tuyere     ',7('|',7x,i1,7x),'|',/,126('-'))");
  imprimeCaracteristiques (fa8);
  appliqueFormat (&fa8, &i1, &i2, &i3, &i4, &i5, &i6, &i7, 0l);
  FormatFortran fb8 ("(' | Thruster   ',7('|',7x,i1,7x),'|',/,1x,126('-'))");
  imprimeCaracteristiques (fb8);
  appliqueFormat (&fb8, &i1, &i2, &i3, &i4, &i5, &i6, &i7, 0l);
  compare (fa8, fb8);

  compare (fa3, fa8);
  compare (fa1, fb3);
  compare (fa5, fb6);

  return 0;
}
