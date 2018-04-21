///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//       Marmottes
//
//$Application
//       Marmottes
//
//$Nom
//>       SenseurVecteur.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurVecteur
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class SenseurVecteur
//>         SenseurVecteur()  
//>         operator =()      
//>         respecterMesures()
//>         convertirMesures()
//>         nouveauRepere()   
//>         modeliseConsigne()
//>         mesure()          
//
//$Historique
//       $Log: SenseurVecteur.cpp,v $
//       Revision 1.16  2003/02/27 16:47:12  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.15  2003/02/04 16:42:01  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.14  2002/09/09 14:22:26  marmottes
//       déplacement de la vérification de consigne avant le filtrage des
//       secteurs (problème trouvé lors de la correction de la FA 0015)
//
//       Revision 1.13  2002/01/17 09:27:32  marmottes
//       correction de spécifications throw
//
//       Revision 1.12  2001/07/17 15:12:04  luc
//       ajout du vecteur observé pour la cible vitesse-sol-apparente
//       lancement d'une exception par le constructeur
//
//       Revision 1.11  2001/03/26 11:18:20  luc
//       mise à jour résultant de la modélisation des inhibitions
//       dans la classe SenseurOptique
//
//       Revision 1.10  2000/09/13 10:53:04  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.9  2000/03/30 17:01:21  luc
//       ajout du copyright CNES
//
//       Revision 1.8  1999/08/20 07:37:29  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des méthodes "throw"
//
//       Revision 1.7  1999/08/06 13:32:16  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.6  1998/09/14 11:51:28  luc
//       vérification de la consigne générée
//
//       Revision 1.5  1998/06/24 20:06:22  luc
//       élimination des variables statiques RCS
//       modification du format des en-têtes
//
//       Revision 1.4  1998/04/26 19:56:27  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.3  1997/11/27 07:00:14  luc
//       remplacement de la notion d'astre par la notion de cible
//       ajout du paramétrage des cibles de type stations sol
//
//       Revision 1.2  1997/09/23 09:31:46  luc
//       ajout d'une gestion des unités de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/08/20 09:26:50  luc
//       Initial revision
//
//
//$Version
//       $Id: SenseurVecteur.cpp,v 1.16 2003/02/27 16:47:12 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurVecteur.h"

SenseurVecteur::SenseurVecteur (const string& nom, const RotDBL& repere,
                                const VecDBL& axeCalage, double precision,
                                codeCible code, const StationCible *ptrStation,
                                const VecDBL& observe,
                                Parcelle* ptrChampDeVue,
                                Parcelle *ptrChampInhibitionSoleil,
                                Parcelle *ptrChampInhibitionLune,
                                Parcelle *ptrChampInhibitionCentral,
                                double margeEclipseSoleil,
                                double margeEclipseLune,
                                double seuilPhaseLune,
                                const VecDBL& reference)
  throw (CantorErreurs)
 : SenseurOptique (nom, repere, axeCalage, radians (precision),
                   code, ptrStation, observe, ptrChampDeVue,
                   ptrChampInhibitionSoleil, ptrChampInhibitionLune,
                   ptrChampInhibitionCentral,
                   margeEclipseSoleil, margeEclipseLune, seuilPhaseLune),
   reference_ (reference)
{
  reference_ = (-repere) (reference_);
  reference_.normalise ();
}

SenseurVecteur& SenseurVecteur::operator = (const SenseurVecteur& s)
{ if (&s != this)    // protection contre x = x
  { SenseurOptique::operator = (s);
    reference_ = s.reference_;
  }

  return *this;

}

void SenseurVecteur::respecterMesures ()
{ // mémorisation du besoin de fournir des mesures en radians

  if (conversionMesures ())
    reinitialisePrecision (radians (precision ())); // jusque là on était en degrés

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::respecterMesures ();

}

void SenseurVecteur::convertirMesures ()
{ // mémorisation du besoin de fournir des mesures en degrés

  if (! conversionMesures ())
    reinitialisePrecision (degres (precision ())); // jusque là on était en radians

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::convertirMesures ();

}

void SenseurVecteur::nouveauRepere (const RotDBL& nouveau)
{ // réorientation du senseur
  RotDBL decalage ((-nouveau) (repere ()));
  reference_ = decalage (reference_);

  // appel de la fonction de la classe de base
  SenseurOptique::nouveauRepere (nouveau);

}

void SenseurVecteur::modeliseConsigne (const Etat& etat, double valeur)
  throw (CantorErreurs, MarmottesErreurs)
{ 
  if (conversionConsignes ())
    valeur = radians (valeur);  // la consigne était en degrés

  // la valeur mémorisée doit l'être dans l'unité de mesure
  if (conversionMesures ())
    Senseur::modeliseConsigne (etat, degres (valeur));
  else
    Senseur::modeliseConsigne (etat, valeur);

  // initialisation de la direction de la cible du senseur
  initialiseCible (etat);

  secteursConsigne_ = Secteurs (Cone (reference_, valeur));
  verifieConsigne ();
  filtreSecteurs ();

  // on fait la conversion en ValeurDerivee1 une fois pour toutes
  axeVD1_ = VecDBLVD1 (secteursConsigne_.cone ().axe ());

}

double SenseurVecteur::mesure (const Etat& etat)
  throw (MarmottesErreurs)
{ 
  // initialisation de la direction de la cible du senseur
  initialiseCible (etat);

  double m = angle (etat.attitude () (cible_), reference_);
  if (conversionMesures ())
    m = degres (m);      // la mesure doit être en degrés

  return m;

}
