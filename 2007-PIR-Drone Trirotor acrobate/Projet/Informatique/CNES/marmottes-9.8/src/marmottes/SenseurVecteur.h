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
//>       SenseurVecteur.h
//
//$Resume
//       fichier d'en-tête de la classe SenseurVecteur
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class SenseurVecteur
//
//$Historique
//       $Log: SenseurVecteur.h,v $
//       Revision 1.18  2003/02/27 16:12:23  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.17  2002/12/11 17:18:58  marmottes
//       DM-ID 12 Ajout d'un constructeur par défaut (protégé) pour prévenir celui construit par le compilateur.
//
//       Revision 1.16  2002/12/02 17:07:38  marmottes
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.15  2002/01/17 09:39:05  marmottes
//       correction de spécifications throw (FA 0003)
//
//       Revision 1.14  2001/07/17 15:20:12  luc
//       élimination de la méthode nomType inutilisée
//
//       Revision 1.13  2001/07/17 15:11:20  luc
//       ajout du vecteur observé pour la cible vitesse-sol-apparente
//       lancement d'une exception par le constructeur
//
//       Revision 1.12  2001/03/26 11:13:43  luc
//        mise à jour résultant de la modélisation des inhibitions dans la
//       classe SenseurOptique
//
//       Revision 1.11  2000/09/13 10:52:50  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.10  2000/03/30 17:01:24  luc
//       ajout du copyright CNES
//
//       Revision 1.9  1999/11/02 07:19:23  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.8  1999/08/25 09:41:05  filaire
//       Changement des signatures de certaines méthodes (correction des oublis
//       après le passage aux exceptions)
//
//       Revision 1.7  1999/08/06 13:32:20  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.6  1998/06/25 06:15:48  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.5  1998/04/26 19:35:18  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.5  1998/04/26 18:25:41  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.4  1998/02/04 08:51:58  luc
//       mise en place d'un en-tête de classe au format AMIGAU
//
//       Revision 1.3  1997/11/27 07:08:40  luc
//       remplacement de la notion d'astre par la notion de cible
//       ajout du paramétrage des cibles de type stations sol
//
//       Revision 1.2  1997/09/23 09:26:55  luc
//       ajout d'une gestion des unités de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/08/20 09:55:24  luc
//       Initial revision
//
//$Version
//       $Id: SenseurVecteur.h,v 1.18 2003/02/27 16:12:23 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurVecteur_h
#define __marmottes_SenseurVecteur_h

#include "marmottes/SenseurOptique.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurVecteur
//
//$Resume
//       modélisation d'un senseur mesurant des angles entre vecteurs.
//
//$Description
//       modélisation d'un senseur géométrique mesurant des
//       angles entre vecteurs.
//
//$Usage
//>     construction : 
//          à partir du nom, du repère satellite, de l'axe de calage
//          et de la précision, par copie
//          La classe étant abstraite, les constructeurs sont appelés
//          par les constructeurs des classes dérivées.
//>     utilisation  : 
//>       SenseurVecteur& operator =    () 
//          affectation
//>       virtual void respecterMesures () 
//          force le senseur à respecter les unités de mesures dans
//          ses sorties
//>       virtual void convertirMesures () 
//          force le senseur à convertir les unités de mesures dans
//          ses sortie
//>       virtual void nouveauRepere    () 
//          tourne le senseur pour l'aligner sur le repère donné
//>       virtual int modeliseConsigne  () 
//          permet de stocker un modèle de la consigne que doit
//          respecter un senseur contrôlant l'attitude du satellite
//          dans l'état courant ATTENTION: dans cet état, l'attitude
//          ne doit pas être utilisée, elle ne sera initialisée
//          correctement qu'à la fin de la résolution ayant utilisé ce
//          modèle!
//>       virtual double mesure         () 
//          retourne la mesure que donnerait le senseur dans l'état donné
//>       virtual Senseur* copie        () 
//          retourne une copie du senseur allouée en mémoire
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurVecteur : public SenseurOptique
{

public :

  // constructeurs
  SenseurVecteur (const string& nom, const RotDBL& repere,
                  const VecDBL& axeCalage, double precision,
                  codeCible code, const StationCible *ptrStation,
                  const VecDBL& observe,
                  Parcelle *ptrChampDeVue,
                  Parcelle *ptrChampInhibitionSoleil,
                  Parcelle *ptrChampInhibitionLune,
                  Parcelle *ptrChampInhibitionCentral,
                  double margeEclipseSoleil,
                  double margeEclipseLune,
                  double seuilPhaseLune,
                  const VecDBL& reference)
    throw (CantorErreurs);

  SenseurVecteur (const SenseurVecteur& s)
    : SenseurOptique (s), reference_ (s.reference_)
  { axeVD1_ = VecDBLVD1 (reference_); }

  SenseurVecteur& operator = (const SenseurVecteur& s);

  // destructeur
  virtual ~SenseurVecteur () {}

  virtual void respecterMesures ();
  virtual void convertirMesures ();

  virtual Senseur* copie () const { return new SenseurVecteur (*this); }

  // réorientation du senseur
  virtual void  nouveauRepere (const RotDBL& nouveau);

  // fonctions de résolution de l'attitude
  virtual void    modeliseConsigne (const Etat& etat, double valeur)
    throw (CantorErreurs, MarmottesErreurs);
  virtual double  mesure           (const Etat& etat)
    throw (MarmottesErreurs);

protected :

  // constructeur par defaut : ne doit JAMAIS être utilisé
  SenseurVecteur () {}

private :

  VecDBL reference_;

};

#endif
