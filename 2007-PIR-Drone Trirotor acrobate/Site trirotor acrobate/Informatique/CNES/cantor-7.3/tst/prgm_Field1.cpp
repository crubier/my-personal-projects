#include "club/OptionsAppli.h"
#include "club/ClubErreurs.h"

#include "cantor/Util.h"
#include "cantor/DeclDBL.h"
#include "cantor/Cone.h"
#include "cantor/Field.h"

static void analyseArguments (int argc, char** argv, int* ptrParcours,
                              double* ptrMarge, double* ptrTolerance,
                              VecDBL* ptrCible)
{ OptionsAppli analyseur (argv [0]);

  // indicateur de parcours
  // option p: zéro ou une occurrence, pas de valeur
  analyseur.ajouterOption (OptionSansValeur ("p", 0, 1));

  // marge autour du champ
  // option m: zéro ou une occurrence, valeur par défaut: 0.0
  analyseur.ajouterOption (OptionReel ("m", 0, 1,
                                       avecValeurDefaut, 0.0, -180.0, 180.0));

  // tolérance sur le parcours
  // option t: zéro ou une occurrence, valeur par défaut: 1.0e-4
  analyseur.ajouterOption (OptionReel ("t", 0, 1,
                                       avecValeurDefaut, 1.0e-4, 0.0, 10.0));

  // cible à tester
  // option c: zéro ou une occurrence, valeur par défaut: (0.0, 90.0 degrés)
  double axeZ [2];
  axeZ [0] = 0.0;
  axeZ [1] = 90.0;
  analyseur.ajouterOption (OptionTableauReels ("c", 0, 1,
                                               avecValeurDefaut,
                                               2, axeZ, -360.0, 360.0));

  // analyse de la ligne
  analyseur.initialiser (argc, argv);
  analyseur.garantirComplet ();

  // récupération des données
  *ptrParcours = (analyseur.occurrencesPassees ("p") > 0);
  analyseur.lireValeur ("m", ptrMarge);
  *ptrMarge = radians (*ptrMarge);
  analyseur.lireValeur ("t", ptrTolerance);
  *ptrTolerance = radians (*ptrTolerance);
  double tab [2];
  analyseur.lireValeur ("c", 2, tab);
  *ptrCible = VecDBL (radians (tab [0]), radians (tab [1]));

}

static void initChamps (Field **adrPtrCSud, Field **adrPtrCNord)
{ // modélisation d'un champ de vue de senseur terre
  // deux scans aux alentours de +Z, décalés de 6.166 degrés du plan (X,Z)

  VecDBL v1 (radians (180.0), radians (25.0));
  Cone planLimitationScan1 (v1, radians (90.0));
  VecDBL v2 (radians (0.0),   radians (25.0));
  Cone planLimitationScan2 (v2, radians (90.0));
  Field diedreOuvertureScan    (planLimitationScan1);
  diedreOuvertureScan *= Field (planLimitationScan2);

  *adrPtrCSud    = new Field (Cone (VecDBL (0.0, -1.0, 0.0),
                                    radians (96.491)));
  **adrPtrCSud  *= Field (Cone (VecDBL (0.0,  1.0, 0.0), radians (84.159)));
  **adrPtrCSud  *= diedreOuvertureScan;

  *adrPtrCNord   = new Field (Cone (VecDBL (0.0, -1.0, 0.0),
                                    radians (84.159)));
  **adrPtrCNord *= Field (Cone (VecDBL (0.0,  1.0, 0.0), radians (96.491)));
  **adrPtrCNord *= diedreOuvertureScan;

}

int main (int argc, char** argv)
{ ClubAllocHandler h; // utilisé uniquement pour ses constructeur/destructeur

  try 
  {
    // analyse des arguments de la ligne de commande
    int    parcours;
    double marge;
    double tolerance;
    VecDBL cible;
    analyseArguments (argc, argv, &parcours, &marge, &tolerance, &cible);

    // fabrication des champs
    Field* scanSud;
    Field* scanNord;
    initChamps (&scanSud, &scanNord);

    // prise en compte de la marge
    scanSud->applyMargin  (marge);
    scanNord->applyMargin (marge);

    // test de la visibilité de la cible
    if (scanSud->isInside (cible))
      cerr << "Le scan sud voit la cible\n";
    else
      cerr << "Le scan sud ne voit pas la cible\n";
    if (scanNord->isInside (cible))
      cerr << "Le scan nord voit la cible\n";
    else
      cerr << "Le scan nord ne voit pas la cible\n";
    cerr << endl;

    if (parcours)
    { // parcours des champs
      VecDBL point;
      bool   dernier;

      scanSud->initWalk (tolerance);
      while (scanSud->nextPoint (&point, &dernier))
      {
        cout << point.x () << ' ' << point.y () << ' ' << point.z () << endl;
        if (dernier)
          cout << "&\n";
      }
      scanSud->stopWalk ();

      scanNord->initWalk (tolerance);
      while (scanNord->nextPoint (&point, &dernier))
      {
        cout << point.x () << ' ' << point.y () << ' ' << point.z () << endl;
        if (dernier)
          cout << "&\n";
      }
      scanNord->stopWalk ();

    }

    delete scanSud;
    delete scanNord;

  }
  catch (CantorErreurs e)
  { return 1; }

  // fin normale du programme
  return 0;

}
