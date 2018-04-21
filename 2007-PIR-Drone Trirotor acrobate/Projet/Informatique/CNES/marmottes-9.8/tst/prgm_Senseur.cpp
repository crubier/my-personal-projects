#include <cstdio>
#include <sys/time.h>

#include "club/OptionsAppli.h"
#include "cantor/Util.h"
#include "cantor/DeclDBL.h"

#include "marmottes/Etat.h"
#include "marmottes/Marmottes.h"
#include "marmottes/MarmottesErreurs.h"

#include "marmottes/Senseur.h"
#include "marmottes/SenseurAlpha.h"
#include "marmottes/SenseurCardan.h"
#include "marmottes/SenseurCartesien.h"
#include "marmottes/SenseurCinematique.h"
#include "marmottes/SenseurDelta.h"
#include "marmottes/SenseurDiedre.h"
#include "marmottes/SenseurElevation.h"
#include "marmottes/SenseurFonction.h"
#include "marmottes/SenseurFonctionEchant1D.h"
#include "marmottes/SenseurFonctionGauss.h"
#include "marmottes/SenseurFonctionSinCard2.h"
#include "marmottes/SenseurFonctionSinCardXY.h"
#include "marmottes/SenseurGeometrique.h"
#include "marmottes/SenseurGyroInteg.h"
#include "marmottes/SenseurLimbe.h"
#include "marmottes/SenseurOptique.h"
#include "marmottes/SenseurVecteur.h"

double LitDate (const char *chaine);

static int analyseArguments (int argc, char** argv,
                             double       *ptrDate, double orbite [6],
                             double       *ptrPas,
                             double        attitude [4], double spin [3],
                             double       *ptrMu,
                             int          *ptrIteration,
                             string       *ptrFichier,
                             string        senseurs [3],
                             double        mesures [3],
                             string       *ptrSenseur,
                             double       *ptrArgScal1,
                             double       *ptrArgScal2,
                             double        argVec [3],
                             double        argRot [4])
{ // analyse des arguments de la ligne de commande

  try {
  OptionsAppli analyseur (argv [0]);

  // itérations
  // options i: zéro ou une occurrence
  analyseur.ajouterOption (OptionEntier ("i", 0, 1,
                                         avecValeurDefaut, 3,  1, 100000));

  // nom du fichier des senseurs
  // option f: zéro ou une occurrence, valeur par défaut: "senseurs.fr"
  analyseur.ajouterOption (OptionChaine ("f", 0, 1,
                                         avecValeurDefaut, "senseurs.fr",
                                         256));
  // senseurs de contrôle
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

  // option s: une occurrence, pas de valeur par défaut
  analyseur.ajouterOption (OptionChaine ("s", 1, 1,
                                         sansValeurDefaut, "", 25));

  // analyse de la ligne
  analyseur.initialiser (argc, argv);
  analyseur.garantirComplet ();

  // récupération des données
  analyseur.lireValeur ("i", ptrIteration);
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

  analyseur.lireValeur ("s",  ptrSenseur);

  analyseur.lireValeur ("mu", ptrMu);

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

  return 0;  

  }
  catch (ClubErreurs ce) {
    return 1;
  }

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
            -sinPOM * cosGOM - cosPOM * cosI * sinGOM,
             sinI * sinGOM);

  VecDBL Q ( cosPOM * sinGOM + sinPOM * cosI * cosGOM,
            -sinPOM * sinGOM + cosPOM * cosI * cosGOM,
            -sinI * cosGOM);

  position [0] = xp * P.x () + xq * Q.x ();
  position [1] = xp * P.y () + xq * Q.y ();
  position [2] = xp * P.z () + xq * Q.z ();

  vitesse  [0] = vp * P.x () + vq * Q.x ();
  vitesse  [1] = vp * P.y () + vq * Q.y ();
  vitesse  [2] = vp * P.z () + vq * Q.z ();

}

void testSenseur (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                  int iter, int iterMax)
  throw (MarmottesErreurs)
{
  int    control = 0;
  double mes     = 9999.999;

  // il est certain de toujours passer dans cette fonction :
  // ici sont donc placés les appels aux méthodes de plus
  // haut niveau

  cout << s->nom() << endl;
  mes     = s->mesure(etatCourant);
  control = s->controlable(etatCourant);
  if (control)
    (void) fprintf (stdout, "  contrôlable,      %12.8f\n",
                     mes);
  else
    (void) fprintf (stdout, "  non contrôlable,  %12.8f\n",
                    mes);

  // cas particulier s'il s'agit d'un senseur utilisé en
  // contrôle
  if (! utiliseEnMesure)
    {
      double val = s->valeurConsigne();
      (void) fprintf (stdout, "  consigne,         %12.8f\n",
                      val);
    };

  // critére de contrôlabilité
  Senseur::codeAstre codeInhib, codeEclipse;
  double ecartFrontiere;
  bool amplitudeSignificative;
  s->criteresControlabilite(etatCourant,
                            &codeInhib,
                            &codeEclipse,
                            &ecartFrontiere,
                            &amplitudeSignificative);
  switch (codeInhib)
    {
      case Senseur::nonSignificatif :
        cout << "  inhibition      : non significative" << endl;
        break;
      case Senseur::soleil :
        cout << "  inhibition      : soleil" << endl;
        break;
      case Senseur::lune :
        cout << "  inhibition      : lune" << endl;
        break;
      case Senseur::corpsCentral :
        cout << "  inhibition      : corps central" << endl;
        break;
      case Senseur::aucunAstre :
        cout << "  inhibition      : aucun astre" << endl;
        break;
      default :
        throw MarmottesErreurs (MarmottesErreurs::cas_impossible,
                                __LINE__, __FILE__);
        break;
    }

  switch (codeEclipse)
    {
      case Senseur::nonSignificatif :
        cout << "  eclipse         : non significative" << endl;
        break;
      case Senseur::soleil :
        cout << "  eclipse         : soleil" << endl;
        break;
      case Senseur::lune :
        cout << "  eclipse         : lune" << endl;
        break;
      case Senseur::corpsCentral :
        cout << "  eclipse         : corps central" << endl;
        break;
      case Senseur::aucunAstre :
        cout << "  eclipse         : aucun astre" << endl;
        break;
      default :
        throw MarmottesErreurs (MarmottesErreurs::cas_impossible,
                                __LINE__, __FILE__);
        break;
    }

  cout << "  ecart frontiere : " << ecartFrontiere << " ";

  if (amplitudeSignificative)
    cout << "(amplitude significative)" << endl;
  else
    cout << "(amplitude non significative)" << endl;
}

void testSenseurAlpha (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                       int iter, int iterMax)
{
  SenseurAlpha * specializedS;
  specializedS = dynamic_cast <SenseurAlpha *> (s);
  // Si le cast retourne le pointeur NULL alors le senseur passé
  // en paramétre n'était pas du bon type.

  if ( specializedS == 0 )
    return;
}

void testSenseurCardan (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                        int iter, int iterMax)
{
  SenseurCardan * specializedS;
  specializedS = dynamic_cast <SenseurCardan *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurCartesien (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                           int iter, int iterMax)
{
  SenseurCartesien * specializedS;
  specializedS = dynamic_cast <SenseurCartesien *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurCinematique (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                             int iter, int iterMax)
{
  SenseurCinematique * specializedS;
  specializedS = dynamic_cast <SenseurCinematique *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurDelta (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                       int iter, int iterMax)
{
  SenseurDelta * specializedS;
  specializedS = dynamic_cast <SenseurDelta *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurDiedre (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                        int iter, int iterMax)
{
  SenseurDiedre * specializedS;
  specializedS = dynamic_cast <SenseurDiedre *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurElevation (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                           int iter, int iterMax)
{
  SenseurElevation * specializedS;
  specializedS = dynamic_cast <SenseurElevation *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurFonction (Senseur*s, const Etat & etatCourant, bool utiliseEnMesure,
                          int iter, int iterMax)
{
  SenseurFonction * specializedS;
  specializedS = dynamic_cast <SenseurFonction *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurFonctionEchant1D (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                                  int iter, int iterMax)
{
  SenseurFonctionEchant1D * specializedS;
  specializedS = dynamic_cast <SenseurFonctionEchant1D *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurFonctionGauss (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                               int iter, int iterMax)
{
  SenseurFonctionGauss * specializedS;
  specializedS = dynamic_cast <SenseurFonctionGauss *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurFonctionSinCard2 (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                                  int iter, int iterMax)
{
  SenseurFonctionSinCard2 * specializedS;
  specializedS = dynamic_cast <SenseurFonctionSinCard2 *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurFonctionSinCardXY (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                                   int iter, int iterMax)
{
  SenseurFonctionSinCardXY * specializedS;
  specializedS = dynamic_cast <SenseurFonctionSinCardXY *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurGeometrique (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                             int iter, int iterMax)
{
  SenseurGeometrique * specializedS;
  specializedS = dynamic_cast <SenseurGeometrique *> (s);
  if ( specializedS == 0 )
    return;
  if (! utiliseEnMesure)
    {
      const VecDBL & cib=specializedS->cible();
      const Secteurs & sec=specializedS->secteursConsigne();
      VecDBL cibSat = etatCourant.attitude() (cib);
      
      cout << "  cible [x/y/z] (repere inertiel)  : " ;
      cout << cib.x() << " " << cib.y() << " " << cib.z() << endl;
      cout << "  cible [x/y/z] (repere satellite) : " ;
      cout << cibSat.x() << " " << cibSat.y() << " " << cibSat.z() << endl;
      cout << "  secteur" << endl;
      cout << "    axe [x/y/z]                      " ;
      cout << sec.cone().axe().x() << " " << sec.cone().axe().y() << " " << sec.cone().axe().z() << endl;
      cout << "    angle                            " ;
      cout << degres(sec.cone().angle()) << endl;
      cout << "    reference [x/y/z]                " ;
      cout << sec.reference().x() << " " << sec.reference().y() << " " << sec.reference().z() << endl;
      cout << "    creneau(x)                       " ;
      for (int i=0; i<sec.creneau().nombre();++i)
        {
          cout << "[" << degres(sec.creneau()[i].inf()) << " ; " << degres(sec.creneau()[i].sup()) << "]" << "  ";
        }
      cout << endl;

      // test si la cible est l'origine pour prévenir des problèmes eventuels
      // dans le calcul de l'écart cible/secteur consigne (distance sur la
      // sphère entre la frontiére et le point considéré) 
      if (cib.norme() < 1.e-6)
        return;

      Arc unArc(sec.cone());
      cout << "  ecart cible - secteur consigne :   " << unArc.distance(cibSat) << endl;
    }
}

void testSenseurGyroInteg (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                           int iter, int iterMax)
{
  SenseurGyroInteg * specializedS;
  specializedS = dynamic_cast <SenseurGyroInteg *> (s);
  if ( specializedS == 0 )
    return;
  if ( iter >= (iterMax / 2) )
    specializedS->initialiseGyro(etatCourant.date(), 0.);
}

void testSenseurLimbe (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                       int iter, int iterMax)
{
  SenseurLimbe * specializedS;
  specializedS = dynamic_cast <SenseurLimbe *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurOptique (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                         int iter, int iterMax)
{
  SenseurOptique * specializedS;
  specializedS = dynamic_cast <SenseurOptique *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurVecteur (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                         int iter, int iterMax)
{
  SenseurVecteur * specializedS;
  specializedS = dynamic_cast <SenseurVecteur *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurEchant1D (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                          int iter, int iterMax)
{
  SenseurVecteur * specializedS;
  specializedS = dynamic_cast <SenseurVecteur *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurGauss (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                       int iter, int iterMax)
{
  SenseurVecteur * specializedS;
  specializedS = dynamic_cast <SenseurVecteur *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurSinCard2 (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                          int iter, int iterMax)
{
  SenseurVecteur * specializedS;
  specializedS = dynamic_cast <SenseurVecteur *> (s);
  if ( specializedS == 0 )
    return;
}

void testSenseurSinCardXY (Senseur *s, const Etat & etatCourant, bool utiliseEnMesure,
                           int iter, int iterMax)
{
  SenseurVecteur * specializedS;
  specializedS = dynamic_cast <SenseurVecteur *> (s);
  if ( specializedS == 0 )
    return;
}

int main (int argc, char** argv)
{ // programme de test des fonctions spécialisées de senseurs
  // (pour tester de la façon la plus complète, les interfaces C++ sont utilisées)
  ClubAllocHandler h; // utilisé uniquement pour ses constructeur/destructeur
  int i, j;

  // analyse des arguments de la ligne de commande
  double       orbite   [6], position [3], vitesse [3];
  double       attitude [4], spin     [3], mesures [3];
  double       date, pas, mu;
  int          iteration;
  string       fichier;
  string       senseurs [4], senseurTest;
  double       argScal1, argScal2, argVec [3], argRot [4];
  bool         utiliseEnMesure = false;

  if (analyseArguments (argc, argv, &date, orbite, &pas, attitude, spin,
                        &mu, &iteration,
                        &fichier, senseurs, mesures,
                        &senseurs[3],
                        &argScal1, &argScal2, argVec, argRot))
    return 1;

  try {

    // transformation de l'orbite en paramétres position-vitesse
    cartesiens (orbite, mu, position, vitesse);

    // création du simulateur
    Marmottes simulateur (date,
                          VecDBL (position [0], position [1], position [2]),
                           VecDBL (vitesse [0], vitesse [1], vitesse [2]),
                           RotDBL (attitude [0], attitude [1],
                                   attitude [2], attitude [3]),
                           VecDBL (spin [0], spin [1], spin [2]),                          
                           fichier.c_str(),
                           senseurs[0].c_str(),
                           senseurs[1].c_str(),
                           senseurs[2].c_str());
    
    RotDBL atti;
    VecDBL spi;

    for (i = 0; i < iteration ; i++)
      {
        extrapole  (&date, orbite, mu, pas);
        cartesiens (orbite, mu, position, vitesse);

        // calcul de l'attitude
        simulateur.attitude(date,
                            VecDBL (position [0], position [1], position [2]),
                            VecDBL (vitesse [0], vitesse [1], vitesse  [2]),
                            mesures [0], mesures [1], mesures [2],
                            &atti, &spi);

        const Etat & etatCourant = simulateur.etat();         
        // boucle sur chaque senseur sans distinction (à charge pour les
        // méthodes appelées de faire les opérations adéquates selon le
        // type de senseur)
        for (j=0; j<= 3; j++)
          {
            utiliseEnMesure = false;
            
            if (j == 3 )
              utiliseEnMesure = true;
            
            Senseur *senseurTest = simulateur.accesSenseur (fichier.c_str(),
                                                            senseurs[j].c_str());
            if (senseurTest == 0)
              return 1;
            
            (void) testSenseur            (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurGeometrique (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurAlpha       (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurCardan      (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurDelta       (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurOptique     (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurVecteur     (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurElevation   (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurCartesien   (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurDiedre      (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurLimbe       (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurFonction    (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurEchant1D    (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurGauss       (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurSinCard2    (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurSinCardXY   (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurCinematique (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
            (void) testSenseurGyroInteg   (senseurTest, etatCourant, utiliseEnMesure,
                                           i, iteration);
          }
        
      }

  }
  catch (ClubErreurs ce)
    {
      return ce.code();
    }
  catch (CantorErreurs cce)
    {
      return cce.code();
    }
  catch (MarmottesErreurs me)
    {
      return me.code();
    }
  catch (...)
    {
      return 1;
    }
    
  // fin normale du programme
  return 0;

}
