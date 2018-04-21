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
//>       SenseurDiedre.h
//
//$Resume
//       fichier d'en-tête de la classe SenseurDiedre
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class SenseurDiedre
//
//$Historique
//       $Log: SenseurDiedre.h,v $
//       Revision 1.20  2003/10/08 09:40:09  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 1.19  2003/02/27 16:15:47  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.18  2002/12/11 17:15:33  marmottes
//       DM-ID 12 Ajout d'un constructeur par défaut (protégé) pour prévenir celui construit par le compilateur.
//
//       Revision 1.17  2002/12/02 17:05:19  marmottes
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.16  2002/01/17 09:39:05  marmottes
//       correction de spécifications throw (FA 0003)
//
//       Revision 1.15  2001/07/17 15:31:13  luc
//       ajout du vecteur observé pour la cible vitesse-sol-apparente
//
//       Revision 1.14  2001/03/26 11:12:36  luc
//        mise à jour résultant de la modélisation des inhibitions dans la
//       classe SenseurOptique
//
//       Revision 1.13  2000/09/13 10:20:59  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.12  2000/03/30 17:01:24  luc
//       ajout du copyright CNES
//
//       Revision 1.11  1999/11/02 07:19:22  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.10  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines méthodes (correction des oublis
//       après le passage aux exceptions)
//
//       Revision 1.9  1999/08/06 13:32:19  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.8  1999/04/20 16:04:38  luc
//       mise au propre du filtrage des secteurs de consigne
//       par les champs de vue
//
//       Revision 1.7  1998/06/25 06:15:00  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.6  1998/04/26 18:25:33  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.5  1998/02/04 17:50:10  luc
//       ajout d'une spécialisation de foncEcart de sorte que
//       la valeur produite soit bien un écart entre mesure et consigne
//       (dans le cas contraire, des problèmes se posent pour des
//       pseudo-senseurs utilisant une cible très proche de l'axe sensible)
//
//       Revision 1.4  1998/02/04 08:46:45  luc
//       mise en place d'un en-tête de classe au format AMIGAU
//
//       Revision 1.3  1997/11/27 07:08:09  luc
//       remplacement de la notion d'astre par la notion de cible
//       ajout du paramétrage des cibles de type stations sol
//
//       Revision 1.2  1997/09/23 09:26:34  luc
//       ajout d'une gestion des unités de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/08/20 09:51:29  luc
//       Initial revision
//
//$Version
//       $Id: SenseurDiedre.h,v 1.20 2003/10/08 09:40:09 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurDiedre_h
#define __marmottes_SenseurDiedre_h

#include "marmottes/SenseurOptique.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurDiedre
//
//$Resume
//       modélisation d'un senseur optique mesurant des angles dièdres.
//
//$Description
//       modélisation d'un senseur optique mesurant des  dièdres,
//       c'est à dire des angles entre plans.
//
//$Usage
//>     construction : 
//          à partir du nom, du repère satellite, de l'axe de calage
//          et de la précision, par copie
//          La classe étant abstraite, les constructeurs sont appelés
//          par les constructeurs des classes dérivées.
//>     utilisation  : 
//>       SenseurDiedre& operator =        () 
//          affectation
//>       virtual void respecterMesures    () 
//          force le senseur à respecter les unités de mesures dans
//          ses sorties
//>       virtual void convertirMesures    () 
//          force le senseur à convertir les unités de mesures dans
//          ses sortie
//>       virtual void nouveauRepere       () 
//          tourne le senseur pour l'aligner sur le repère donné
//>       virtual int modeliseConsigne     () 
//          permet de stocker un modèle de la consigne que doit
//          respecter un senseur contrôlant l'attitude du satellite
//          dans l'état courant ATTENTION: dans cet état, l'attitude
//          ne doit pas être utilisée, elle ne sera initialisée
//          correctement qu'à la fin de la résolution ayant utilisé ce
//          modèle!
//>       virtual double mesure            () 
//          retourne la mesure que donnerait le senseur dans l'état donné
//>       virtual ValeurDerivee1 foncEcart () 
//          calcule la fonction d'écart du senseur par rapport à sa
//          consigne à la date donnée et dans l'attitude donnée en
//          tenant compte de l'état précédent.
//>       virtual Senseur* copie           () 
//          retourne une copie du senseur allouée en mémoire
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurDiedre : public SenseurOptique
{

public :

  // constructeurs
  SenseurDiedre (const string& nom, const RotDBL& repere,
                 const VecDBL& axeCalage, double precision,
                 codeCible code, const StationCible *ptrStation,
                 const VecDBL& observe,
                 Parcelle* ptrChampDeVue,
                 Parcelle *ptrChampInhibitionSoleil,
                 Parcelle *ptrChampInhibitionLune,
                 Parcelle *ptrChampInhibitionCentral,
                 double margeEclipseSoleil, double margeEclipseLune,
                 double seuilPhaseLune,
                 const VecDBL& referenceZero, const VecDBL& axeSensible);
  SenseurDiedre (const SenseurDiedre& s)
    : SenseurOptique (s),
      dansPlan0_ (s.dansPlan0_), normalPlan0_ (s.normalPlan0_)
  {}

  SenseurDiedre& operator = (const SenseurDiedre& s);

  // destructeur
  virtual ~SenseurDiedre () {}

  virtual void respecterMesures ();
  virtual void convertirMesures ();

  virtual Senseur* copie () const { return new SenseurDiedre (*this); }

  // réorientation du senseur
  virtual void  nouveauRepere (const RotDBL& nouveau);

  // fonctions de résolution de l'attitude
  virtual void   modeliseConsigne (const Etat& etat, double valeur)
    throw (CantorErreurs, MarmottesErreurs);
  virtual double mesure           (const Etat& etat)
    throw (MarmottesErreurs);
  virtual ValeurDerivee1 foncEcart (const Etat& etatPrecedent,
                                    const Etat& etatResolution,
                                    const RotVD1& attitude,
                                    const VecVD1& spin
                                   );

protected :

  // constructeur par defaut : ne doit JAMAIS être utilisé
  SenseurDiedre () {}

private :

  VecDBL dansPlan0_;
  VecDBL normalPlan0_;

};

#endif
