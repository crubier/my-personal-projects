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
//>       SenseurFonction.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurFonction
//
//$Description
//       Module de définition de la classe
//
//$Contenu
//>       class SenseurFonction 
//>         SenseurFonction()   
//>         operator =()      
//>         respecterMesures()
//>         convertirMesures()
//>         nouveauRepere()   
//>         modeliseConsigne()
//>         mesure()          
//>         foncEcart()       
//
//$Historique
//       $Log: SenseurFonction.cpp,v $
//       Revision 1.10  2004/06/23 13:38:04  marmottes
//       transformation des vecteurs du repère senseur au repère satellite (FA-ID 35)
//
//       Revision 1.9  2003/10/08 09:39:41  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 1.8  2003/02/27 16:41:14  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.7  2003/02/04 16:39:54  marmottes
//       DM-ID 17 Mise à jour de l'extension du fichier dans le bandeau
//
//       Revision 1.6  2002/01/17 09:27:32  marmottes
//       correction de spécifications throw
//
//       Revision 1.5  2001/07/17 15:38:37  luc
//       ajout du vecteur observé pour la cible vitesse-sol-apparente
//       lancement d'une exception par le constructeur
//
//       Revision 1.4  2001/03/26 11:17:28  luc
//       mise à jour résultant de la modélisation des inhibitions
//       dans la classe SenseurOptique
//
//       Revision 1.3  2000/09/13 10:58:02  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.2  2000/06/07 16:45:50  filaire
//       correction du nom de l'erreur
//
//       Revision 1.1  2000/06/07 14:05:23  luc
//       version initiale
//
//$Version
//       $Id: SenseurFonction.cpp,v 1.10 2004/06/23 13:38:04 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurFonction.h"

SenseurFonction::SenseurFonction (const string& nom, const RotDBL& repere,
                                  const VecDBL& axeCalage, double precision,
                                  codeCible code,
                                  const StationCible *ptrStation,
                                  const VecDBL& observe,
                                  Parcelle* ptrChampDeVue,
                                  Parcelle *ptrChampInhibitionSoleil,
                                  Parcelle *ptrChampInhibitionLune,
                                  Parcelle *ptrChampInhibitionCentral,
                                  double margeEclipseSoleil,
                                  double margeEclipseLune,
                                  double seuilPhaseLune,
                                  const VecDBL& axe, const VecDBL& origine)
  throw (CantorErreurs)
  : SenseurOptique (nom, repere, axeCalage, precision,
                    code, ptrStation, observe, ptrChampDeVue,
                    ptrChampInhibitionSoleil, ptrChampInhibitionLune,
                    ptrChampInhibitionCentral,
                    margeEclipseSoleil, margeEclipseLune, seuilPhaseLune)
{

  // constitution d'une base orthonormée à partir des axes de référence
  k_ = (-repere) (axe);
  k_.normalise ();

  j_ = k_ ^ (-repere) (origine);
  j_.normalise ();

  i_ = j_ ^ k_;

}

SenseurFonction& SenseurFonction::operator = (const SenseurFonction& s)
{ if (&s != this)    // protection contre x = x
  {
    SenseurOptique::operator = (s);
    i_ = s.i_;
    j_ = s.j_;
    k_ = s.k_;
  }

  return *this;

}

void SenseurFonction::respecterMesures ()
{ // ce type de senseur se contentant de reproduire une fonction
  // définie sur la sphère unité, il n'a aucune idée de la signification
  // des valeurs et ne peut les convertir

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::respecterMesures ();

}

void SenseurFonction::convertirMesures ()
{ // ce type de senseur se contentant de reproduire une fonction
  // définie sur la sphère unité, il n'a aucune idée de la signification
  // des valeurs et ne peut les convertir

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::convertirMesures ();

}

void SenseurFonction::nouveauRepere (const RotDBL& nouveau)
{ // réorientation du senseur
  RotDBL decalage ((-nouveau) (repere ()));
  i_ = decalage (i_);
  j_ = decalage (j_);
  k_ = decalage (k_);

  // appel de la fonction de la classe de base
  SenseurOptique::nouveauRepere (nouveau);

}

void SenseurFonction::modeliseConsigne (const Etat& etat, double valeur)
  throw (CantorErreurs, MarmottesErreurs)
{ // ce senseur ne peut pas être utilisé en consigne,
  // on retourne donc systématiquement une erreur
  throw (MarmottesErreurs (MarmottesErreurs::senseur_mesure_pure,
                           nom ().c_str ()));
}

double SenseurFonction::mesure (const Etat& etat)
  throw (MarmottesErreurs)
{ 
  // initialisation de la direction de la cible du senseur
  initialiseCible (etat);
  VecDBL v = etat.attitude () (cible_);

  // appel de la fonction sous-jacente plaquée sur la sphère
  return fonction (atan2 (v | j_, v | i_), k_.angleAvecVecteur (v));

}

ValeurDerivee1 SenseurFonction::foncEcart (const Etat& etatPrecedent,
                                           const Etat& etatResolution,
                                           const RotVD1& attitude,
                                           const VecVD1& spin)
{ // ce senseur ne peut pas être utilisé en consigne,
  // on retourne donc systématiquement la valeur 1.0
  return ValeurDerivee1 (1.0);
}
