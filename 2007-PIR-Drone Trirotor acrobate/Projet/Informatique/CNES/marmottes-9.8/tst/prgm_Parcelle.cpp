#include "club/OptionsAppli.h"
#include "club/ClubErreurs.h"

#include "cantor/Util.h"
#include "cantor/Secteurs.h"
#include "cantor/Field.h"

#include "marmottes/Parcelle.h"
#include "marmottes/ParcelleElementaire.h"
#include "marmottes/ReunionEtParcelles.h"
#include "marmottes/ReunionOuParcelles.h"

static void analyseArguments (int argc, char** argv, int* ptrParcours,
                              double* ptrMarge, double* ptrTolerance,
                              Cone* ptrHorizon, double* ptrLargeurBolometre,
                              double* ptrDemiScan, double* ptrPositionZero)
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

  // horizon à tester
  // option axe: zéro ou une occurrence, valeur par défaut: (0.0, 90.0 degrés)
  double axeZ [2];
  axeZ [0] = 0.0;
  axeZ [1] = 90.0;
  analyseur.ajouterOption (OptionTableauReels ("axe", 0, 1,
                                               avecValeurDefaut,
                                               2, axeZ, -360.0, 360.0));

  // option angle: zéro ou une occurrence, valeur par défaut: 8.6
  analyseur.ajouterOption (OptionReel ("angle", 0, 1,
                                       avecValeurDefaut, 8.6, 0.0, 180.0));

  // modélisation de l'IRES
  // option b: taille bolomètre: zéro ou une occurrence, valeur par défaut: 1.3
  analyseur.ajouterOption (OptionReel ("b", 0, 1,
                                       avecValeurDefaut, 1.3, 0.0, 10.0));

  // option z: position zéro: zéro ou une occurrence, valeur par défaut: 6.2
  analyseur.ajouterOption (OptionReel ("z", 0, 1,
                                       avecValeurDefaut, 6.2, 0.0, 10.0));

  // option s: demi-scan: zéro ou une occurrence, valeur par défaut: 5.3
  analyseur.ajouterOption (OptionReel ("s", 0, 1,
                                       avecValeurDefaut, 5.3, 0.0, 10.0));

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
  analyseur.lireValeur ("axe", 2, tab);
  double angle;
  analyseur.lireValeur ("angle", &angle);
  *ptrHorizon = Cone (VecDBL (radians (tab [0]), radians (tab [1])),
                      radians (angle));
  analyseur.lireValeur ("b", ptrLargeurBolometre);
  *ptrLargeurBolometre = radians (*ptrLargeurBolometre);
  analyseur.lireValeur ("z", ptrPositionZero);
  *ptrPositionZero     = radians (*ptrPositionZero);
  analyseur.lireValeur ("s", ptrDemiScan);
  *ptrDemiScan         = radians (*ptrDemiScan);

}

static void initChampsDeVue (double largeurBolometre, double demiScan,
                             double positionZero,
                             Parcelle** adrPtrChampRoulis,
                             Parcelle** adrPtrChampTangage)
  throw (CantorErreurs, MarmottesErreurs)
{ // modélisation du champ de vue d'un IRES
  // quatre scans aux alentours de +Z

  // bolomètre fictif centré sur l'axe +Z
  double p                  = cos (0.5 * largeurBolometre) / sqrt (2.0);
  double q                  = sin (0.5 * largeurBolometre);
  Cone c (VecDBL (-p, -p, q), 0.5 * M_PI);
  Field  boloFictif   (c);
  boloFictif *= Field (Cone (VecDBL (-p,  p, q), 0.5 * M_PI));
  boloFictif *= Field (Cone (VecDBL ( p,  p, q), 0.5 * M_PI));
  boloFictif *= Field (Cone (VecDBL ( p, -p, q), 0.5 * M_PI));

  // scan 4 (situé dans la zone X > 0, Y > 0)
  Field scan4  (boloFictif);
  scan4.rotate (RotDBL (VecDBL (1.0, 0.0, 0.0), -positionZero));
  scan4.rotate (RotDBL (VecDBL (0.0, 1.0, 0.0),  positionZero));
  scan4.rotate (RotDBL (VecDBL (0.0, 1.0, 0.0), -demiScan));
  scan4.spread (VecDBL (0.0, 1.0, 0.0),  2.0 * demiScan);

  // scan 3 (situé dans la zone X > 0, Y < 0)
  Field scan3  (boloFictif);
  scan3.rotate (RotDBL (VecDBL (1.0, 0.0, 0.0),  positionZero));
  scan3.rotate (RotDBL (VecDBL (0.0, 1.0, 0.0),  positionZero));
  scan3.rotate (RotDBL (VecDBL (0.0, 1.0, 0.0), -demiScan));
  scan3.spread (VecDBL (0.0, 1.0, 0.0),  2.0 * demiScan);

  // scan 2 (situé dans la zone X < 0, Y > 0)
  Field scan2  (boloFictif);
  scan2.rotate (RotDBL (VecDBL (1.0, 0.0, 0.0), -positionZero));
  scan2.rotate (RotDBL (VecDBL (0.0, 1.0, 0.0), -positionZero));
  scan2.rotate (RotDBL (VecDBL (0.0, 1.0, 0.0), -demiScan));
  scan2.spread (VecDBL (0.0, 1.0, 0.0),  2.0 * demiScan);

  // scan 1 (situé dans la zone X < 0, Y < 0)
  Field scan1  (boloFictif);
  scan1.rotate (RotDBL (VecDBL (1.0, 0.0, 0.0),  positionZero));
  scan1.rotate (RotDBL (VecDBL (0.0, 1.0, 0.0), -positionZero));
  scan1.rotate (RotDBL (VecDBL (0.0, 1.0, 0.0), -demiScan));
  scan1.spread (VecDBL (0.0, 1.0, 0.0),  2.0 * demiScan);

  // logique de visibilité des champs de vue
  Parcelle* pcl1           = new ParcelleElementaire (scan1);
  Parcelle* pcl2           = new ParcelleElementaire (scan2);
  Parcelle* pcl3           = new ParcelleElementaire (scan3);
  Parcelle* pcl4           = new ParcelleElementaire (scan4);

  Parcelle* parcellePlusX  = new ReunionEtParcelles (pcl3, pcl4);
  Parcelle* parcelleMoinsX = new ReunionEtParcelles (pcl1, pcl2);
  *adrPtrChampRoulis       = new ReunionOuParcelles (parcellePlusX,
                                                     parcelleMoinsX);

  Parcelle* parcellePlusY  = new ReunionEtParcelles (pcl2->copie (),
                                                     pcl4->copie ());
  Parcelle* parcelleMoinsY = new ReunionEtParcelles (pcl1->copie (),
                                                     pcl3->copie ());
  *adrPtrChampTangage      = new ReunionOuParcelles (parcellePlusY,
                                                     parcelleMoinsY);

}

struct SConeDouble
{ Cone   _c;
  double _tolerance;
  SConeDouble (const Cone& c, double t) : _c (c), _tolerance (t) {}
};

static void TraceIntersection (const Field& msq, void* d)
{ // limitation de l'horizon par le champ courant
  Secteurs troncons = msq.selectInside (((SConeDouble *) d)->_c);

  // tracé de la partie restante
  for (int i = 0; i < troncons.nombre (); i++)
  { // constitution du ième arc d'horizon visible
    VecDBL axe;
    VecDBL planDebut;
    VecDBL planFin;
    double balayage;
    troncons.diedre (i, &axe, &planDebut, &planFin, &balayage);
    Arc arc (axe, troncons.angle (), planDebut, balayage);

    // itération sur les points de l'arc
    ArcIterateur iter (arc, ((SConeDouble *) d)->_tolerance);
    while (iter.suivant ())
    { VecDBL point = iter.point ();
      cout << point.x () << ' ' << point.y () << ' ' << point.z () << endl;
    }
    cout << "&\n";

  }

}

int main (int argc, char** argv)
{ ClubAllocHandler h; // utilisé uniquement pour ses constructeur/destructeur

  // analyse des arguments de la ligne de commande
  int    parcours;
  double marge;
  double tolerance;
  Cone   horizon;
  double largeurBolometre;
  double demiScan;
  double positionZero;
  analyseArguments (argc, argv, &parcours, &marge, &tolerance, &horizon,
                    &largeurBolometre, &demiScan, &positionZero);

  try
  {
    // fabrication des champs de vue
    Parcelle* champRoulis;
    Parcelle* champTangage;
    initChampsDeVue (largeurBolometre, demiScan, positionZero,
                     &champRoulis, &champTangage);

    // prise en compte de la marge
    champRoulis->appliqueMarge  (marge);
    champTangage->appliqueMarge (marge);

    // test de la visibilité de l'horizon
    if (champRoulis->visible (horizon))
      cerr << "Le senseur de roulis voit l'horizon\n";
    else
      cerr << "Le senseur de roulis ne voit pas l'horizon\n";
    if (champTangage->visible (horizon))
      cerr << "Le senseur de tangage voit l'horizon\n";
    else
      cerr << "Le senseur de tangage ne voit pas l'horizon\n";
    cerr << endl;

    if (parcours)
    { // parcours des bords de champs
      bool dernier;
      VecDBL point;

      champRoulis->initParcours (tolerance);
      while (champRoulis->pointSuivant (&point, &dernier))
      {
        cout << point.x () << ' ' << point.y () << ' ' << point.z () << endl;
        if (dernier)
          cout << "&\n";
      }
      champRoulis->arreteParcours ();

      // on ne dessine pas le champ tangage qui donnerait les mêmes points
      // (la seule différence tient à la logique des visibilités d'horizon)

      // parcours des secteurs visibles de l'horizon
      SConeDouble donnee (horizon, tolerance);
      champRoulis->applique (TraceIntersection, (void *) &donnee);

    }

    delete champRoulis;
    delete champTangage;

  }
  catch (MarmottesErreurs e)
  {
    return 1;
  }
  catch (CantorErreurs e)
  {
    return 1;
  }

  // fin normale du programme
  return 0;

}
