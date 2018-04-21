#include <iostream>

#include "club/OptionsAppli.h"
#include "club/ClubErreurs.h"

#include "cantor/Util.h"
#include "cantor/DeclDBL.h"
#include "cantor/Arc.h"

static void parseCmdLine (int argc, char** argv,
                          VecDBL *ptrAxis1,
                          double *ptrAngle1,
                          VecDBL *ptrBegin1,
                          double *ptrSpread1,
                          bool   *ptrArc2Passed,
                          VecDBL *ptrAxis2,
                          double *ptrAngle2,
                          VecDBL *ptrBegin2,
                          double *ptrSpread2,
                          bool   *ptrVPassed,
                          VecDBL *ptrV)
  throw (ClubErreurs)
{

  OptionsAppli analyzer (argv [0]);

  // the first arc is mandatory
  analyzer.ajouterOption (OptionTableauReels ("axis1", 1, 1,
                                              sansValeurDefaut,
                                              2, (double *)0,
                                              -360.0, 360.0));

  analyzer.ajouterOption (OptionReel ("angle1", 0, 1,
                                      avecValeurDefaut, 90.0, 0.0, 360.0));

  analyzer.ajouterOption (OptionTableauReels ("begin1", 1, 1,
                                              sansValeurDefaut,
                                              2, (double *)0,
                                              -360.0, 360.0));

  analyzer.ajouterOption (OptionReel ("spread1", 0, 1,
                                      avecValeurDefaut, 360.0, 0.0, 360.0));

  // the second arc is optional
  analyzer.ajouterOption (OptionTableauReels ("axis2", 0, 1,
                                              sansValeurDefaut,
                                              2, (double *)0,
                                              -360.0, 360.0));

  analyzer.ajouterOption (OptionReel ("angle2", 0, 1,
                                       sansValeurDefaut, 0.0, 0.0, 360.0));

  analyzer.ajouterOption (OptionTableauReels ("begin2", 0, 1,
                                              sansValeurDefaut,
                                              2, (double *)0,
                                              -360.0, 360.0));

  analyzer.ajouterOption (OptionReel ("spread2", 0, 1,
                                      avecValeurDefaut, 360.0, 0.0, 360.0));

  // the test vector is optional
  analyzer.ajouterOption (OptionTableauReels ("v", 0, 1,
                                              sansValeurDefaut,
                                              2, (double *)0,
                                              -360.0, 360.0));

  analyzer.initialiser (argc, argv);
  analyzer.garantirComplet ();

  double sphericalCoordinates [2];
  sphericalCoordinates [0] = 0.0;
  sphericalCoordinates [1] = 0.0;

  // get the first arc parameters
  analyzer.lireValeur ("axis1", 2, sphericalCoordinates);
  *ptrAxis1 = VecDBL (radians (sphericalCoordinates [0]),
                      radians (sphericalCoordinates [1]));

  analyzer.lireValeur ("angle1", ptrAngle1);
  *ptrAngle1 = radians (*ptrAngle1);

  analyzer.lireValeur ("begin1", 2, sphericalCoordinates);
  *ptrBegin1 = VecDBL (radians (sphericalCoordinates [0]),
                       radians (sphericalCoordinates [1]));

  analyzer.lireValeur ("spread1", ptrSpread1);
  *ptrSpread1 = radians (*ptrSpread1);

  // get the second arc parameters
  *ptrArc2Passed = (analyzer.occurrencesPassees ("axis2") > 0);

  if (*ptrArc2Passed)
  {
    analyzer.lireValeur ("axis2", 2, sphericalCoordinates);
    *ptrAxis2 = VecDBL (radians (sphericalCoordinates [0]),
                        radians (sphericalCoordinates [1]));

    analyzer.lireValeur ("angle2", ptrAngle2);
    *ptrAngle2 = radians (*ptrAngle2);

    analyzer.lireValeur ("begin2", 2, sphericalCoordinates);
    *ptrBegin2 = VecDBL (radians (sphericalCoordinates [0]),
                         radians (sphericalCoordinates [1]));

    analyzer.lireValeur ("spread2", ptrSpread2);
    *ptrSpread2 = radians (*ptrSpread2);
  }

  // get the test vector parameters
  *ptrVPassed = (analyzer.occurrencesPassees ("v") > 0);

  if (*ptrVPassed)
  {
    analyzer.lireValeur ("v", 2, sphericalCoordinates);
    *ptrV = VecDBL (radians (sphericalCoordinates [0]),
                    radians (sphericalCoordinates [1]));
  }

  if (! (*ptrArc2Passed || *ptrVPassed))
    throw ClubErreurs (ClubErreurs::message_simple,
                       "either -v or -axis2 should be used");

}

int main (int argc, char** argv)
{ ClubAllocHandler h; // used only for its constructor/destructor side effects

  try 
  {
    VecDBL axis1, begin1, axis2, begin2, v;
    double angle1, spread1, angle2, spread2;
    bool arc2Passed, vPassed;
    parseCmdLine (argc, argv,
                  &axis1, &angle1, &begin1, &spread1,
                  &arc2Passed, &axis2, &angle2, &begin2, &spread2,
                  &vPassed, &v);

    // build the first arc
    Arc arc1 (axis1, angle1, begin1, spread1);

    if (arc2Passed)
    {
      Arc arc2 = Arc (axis2, angle2, begin2, spread2);

      // compute the intersection of the arcs
      int nbInt;
      VecDBL v1, v2;
      arc1.intersection (arc2, &nbInt, &v1, &v2);
      if (nbInt == 0)
        cout << "no intersection point" << endl;
      else if (nbInt == 1)
      {
        cout << "one intersection point : ["
             << v1.x () << ' ' << v1.y () << ' ' << v1.z () << ']'
             << endl;
      }
      else
      {
        cout << "two intersection points : ["
             << v1.x () << ' ' << v1.y () << ' ' << v1.z () << "] ["
             << v2.x () << ' ' << v2.y () << ' ' << v2.z () << ']'
             << endl;
      }

      if (vPassed)
      {
        // test the point
        cout << "distance of the test point to arc 1 : "
             << degres (arc1.distance (v)) << endl;
        if (arc1.diedreContient (v))
          cout << "the test point is inside the arc dihedra" << endl;
        else
          cout << "the test point is outside of the arc dihedra" << endl;
        cout << "distance of the test point to arc 2 : "
             << degres (arc2.distance (v)) << endl;
        if (arc2.diedreContient (v))
          cout << "the test point is inside the arc dihedra" << endl;
        else
          cout << "the test point is outside of the arc dihedra" << endl;
      }

    }
    else
    {
      // test the point
      cout << "distance of the test point to arc 1 : "
           << degres (arc1.distance (v)) << endl;
      if (arc1.diedreContient (v))
        cout << "the test point is inside the arc dihedra" << endl;
      else
        cout << "the test point is outside of the arc dihedra" << endl;
    }

  }
  catch (ClubErreurs e)
  { return e.code (); }
  catch (CantorErreurs e)
  { return e.code (); }

  return 0;

}
