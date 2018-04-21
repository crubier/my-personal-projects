#include <iostream>

#include "club/OptionsAppli.h"
#include "club/ClubErreurs.h"

#include "cantor/Util.h"
#include "cantor/DeclDBL.h"
#include "cantor/Arc.h"
#include "cantor/Field.h"

static void parseCmdLine (int argc, char** argv,
                          VecDBL *ptrAxis,
                          double *ptrAngle,
                          VecDBL *ptrBegin,
                          double *ptrSpread,
                          VecDBL *ptrMAxis,
                          double* ptrMSpread)
  throw (ClubErreurs)
{ OptionsAppli analyzer (argv [0]);

  analyzer.ajouterOption (OptionTableauReels ("axis", 1, 1,
                                              sansValeurDefaut,
                                              2, (double *)0,
                                              -360.0, 360.0));

  analyzer.ajouterOption (OptionReel ("angle", 1, 1,
                                       sansValeurDefaut, 0.0, 0.0, 360.0));

  analyzer.ajouterOption (OptionTableauReels ("begin", 0, 1,
                                              sansValeurDefaut,
                                              2, (double *)0,
                                              -360.0, 360.0));

  analyzer.ajouterOption (OptionReel ("spread", 1, 1,
                                      sansValeurDefaut, 0.0, 0.0, 360.0));

  analyzer.ajouterOption (OptionTableauReels ("mAxis", 1, 1,
                                              sansValeurDefaut,
                                              2, (double *)0,
                                              -360.0, 360.0));

  analyzer.ajouterOption (OptionReel ("mSpread", 1, 1,
                                      sansValeurDefaut, 0.0, -360.0, 360.0));

  analyzer.initialiser (argc, argv);
  analyzer.garantirComplet ();

  // récupération des données
  double sphericalCoordinates [2];
  sphericalCoordinates [0] = 0.0;
  sphericalCoordinates [1] = 0.0;

  analyzer.lireValeur ("axis", 2, sphericalCoordinates);
  *ptrAxis = VecDBL (radians (sphericalCoordinates [0]),
                     radians (sphericalCoordinates [1]));

  analyzer.lireValeur ("angle", ptrAngle);
  *ptrAngle = radians (*ptrAngle);

  if (analyzer.occurrencesPassees ("begin") > 0)
  {
    analyzer.lireValeur ("begin", 2, sphericalCoordinates);
    *ptrBegin = VecDBL (radians (sphericalCoordinates [0]),
                        radians (sphericalCoordinates [1]));
  }
  else
  {
    *ptrBegin = VecDBL (0.0, 0.0, 0.0);
  }

  analyzer.lireValeur ("spread", ptrSpread);
  *ptrSpread = radians (*ptrSpread);

  analyzer.lireValeur ("mAxis", 2, sphericalCoordinates);
  *ptrMAxis = VecDBL (radians (sphericalCoordinates [0]),
                      radians (sphericalCoordinates [1]));

  analyzer.lireValeur ("mSpread", ptrMSpread);
  *ptrMSpread = radians (*ptrMSpread);

}

int main (int argc, char** argv)
{ ClubAllocHandler h; // utilisé uniquement pour ses constructeur/destructeur

  try 
  {
    VecDBL axis, begin, mAxis;
    double angle, spread, mSpread;
    parseCmdLine (argc, argv,
                  &axis, &angle, &begin, &spread, &mAxis, &mSpread);

    Field field;
    if (begin.norme () > 0.1)
    {
      // build the arc to spread
      Arc arc (axis, angle, begin, spread);

      // spread it to build a field
      field = Field (arc, mAxis, mSpread);
    }
    else
    {
      // build a field representing a complete cone
      Cone c (axis, angle);
      field = Field (c);

      // spread it to build a field
      field.spread (mAxis, mSpread);

     }

    if (field.isEmpty ())
      cout << "the field is empty" << endl;
    else if (field.isFull ())
      cout << "the field covers the full sphere" << endl;
    else
    {
      // draw the field
      VecDBL point;
      bool   last;
      field.initWalk (1.0e-4);
      while (field.nextPoint (&point, &last))
      {
        cout << point.x () << ' ' << point.y () << ' ' << point.z () << endl;
        if (last)
          cout << "&\n";
      }
      field.stopWalk ();
    }

  }
  catch (ClubErreurs e)
  { return e.code (); }
  catch (CantorErreurs e)
  { return e.code (); }

  return 0;

}
