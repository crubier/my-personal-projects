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
//>       SenseurFonction.h
//
//$Resume
//       fichier d'en-tête de la classe SenseurFonction
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class SenseurFonction
//
//$Historique
//       $Log: SenseurFonction.h,v $
//       Revision 1.9  2003/10/08 09:40:09  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 1.8  2003/02/27 16:13:59  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.7  2002/12/11 17:17:09  marmottes
//       DM-ID 12 Ajout d'un constructeur par défaut (protégé) pour prévenir celui construit par le compilateur.
//
//       Revision 1.6  2002/12/02 17:05:40  marmottes
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.5  2002/01/17 09:39:05  marmottes
//       correction de spécifications throw (FA 0003)
//
//       Revision 1.4  2001/07/17 15:32:39  luc
//       ajout du vecteur observé pour la cible vitesse-sol-apparente
//       lancement d'une exception par le constructeur
//
//       Revision 1.3  2001/03/26 11:12:57  luc
//        mise à jour résultant de la modélisation des inhibitions dans la
//       classe SenseurOptique
//
//       Revision 1.2  2000/09/13 10:57:39  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.1  2000/06/07 14:05:54  luc
//       version initiale
//
//$Version
//       $Id: SenseurFonction.h,v 1.9 2003/10/08 09:40:09 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurFonction_h
#define __marmottes_SenseurFonction_h

#include "marmottes/SenseurOptique.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurFonction
//
//$Resume
//       modélisation d'un pseudo-senseur plaquant une fonction prédéfinie
//       sur la sphère unité
//
//$Description
//       modélisation d'un senseur plaquant une fonction prédéfinie
//       sur la sphère unité. L'utilisation principale d'un tel senseur
//       est de représenter des gains d'antenne.
//
//$Usage
//>     construction : 
//          à partir du nom, du repère satellite, de l'axe de calage
//          et de la précision, par copie
//>     utilisation  : 
//>       SenseurFonction& operator =        () 
//          affectation
//>       virtual void respecterMesures    () 
//          pour ce pseudo-senseur, cette fonction n'agit pas
//          (les mesures dépendent de la fonction plaquée, non modifiable)
//>       virtual void convertirMesures    () 
//          pour ce pseudo-senseur, cette fonction n'agit pas
//          (les mesures dépendent de la fonction plaquée, non modifiable)
//>       virtual void nouveauRepere       () 
//          tourne le senseur pour l'aligner sur le repère donné
//>       virtual void modeliseConsigne     () 
//          ce pseudo-senseur ne pouvant pas être utilisé en consigne,
//          cette fonction retourne systématiquement une erreur
//>       virtual double mesure            () 
//          retourne la mesure que donnerait le senseur dans l'état donné
//>       virtual ValeurDerivee1 foncEcart () 
//          ce pseudo-senseur ne pouvant pas être utilisé en consigne,
//          cette fonction retourne systématiquement 1.0
//>       virtual Senseur* copie           () 
//          retourne une copie du senseur allouée en mémoire
//>       virtual int methode              () 
//          retourne un indicateur interdisant d'utiliser ce senseur
//          en consigne.
//>       virtual double fonction          () 
//          évalue la fonction sous-jacente plaquée sur la sphère unité
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurFonction : public SenseurOptique
{

  public :

  // constructeurs
  SenseurFonction (const string& nom, const RotDBL& repere,
                   const VecDBL& axeCalage, double precision,
                   codeCible code, const StationCible *ptrStation,
                   const VecDBL& observe,
                   Parcelle* ptrChampDeVue,
                   Parcelle *ptrChampInhibitionSoleil,
                   Parcelle *ptrChampInhibitionLune,
                   Parcelle *ptrChampInhibitionCentral,
                   double margeEclipseSoleil, double margeEclipseLune,
                   double seuilPhaseLune,
                   const VecDBL& axe, const VecDBL& origine)
    throw (CantorErreurs);

  SenseurFonction (const SenseurFonction& s)
    : SenseurOptique (s),
      i_ (s.i_), j_ (s.j_), k_ (s.k_)
  {}

  SenseurFonction& operator = (const SenseurFonction& s);

  // destructeur
  virtual ~SenseurFonction () {}

  virtual void respecterMesures ();
  virtual void convertirMesures ();

  // réorientation du senseur
  virtual void  nouveauRepere (const RotDBL& nouveau);

  // fonctions de résolution de l'attitude
  virtual int    methode          () const { return aucuneMethode; }

  virtual void   modeliseConsigne (const Etat& etat, double valeur)
    throw (CantorErreurs, MarmottesErreurs);
  virtual double mesure           (const Etat& etat)
    throw (MarmottesErreurs);
  virtual ValeurDerivee1 foncEcart (const Etat& etatPrecedent,
                                    const Etat& etatResolution,
                                    const RotVD1& attitude,
                                    const VecVD1& spin
                                   );

  // fonction de mesure plaquée sur la sphère
  virtual double fonction (double azimut, double depointage) const
    throw (MarmottesErreurs) = 0;

  protected :

  // constructeur par defaut : ne doit JAMAIS être utilisé
  SenseurFonction () {}

  private :

  VecDBL i_;
  VecDBL j_;
  VecDBL k_;

};

#endif
