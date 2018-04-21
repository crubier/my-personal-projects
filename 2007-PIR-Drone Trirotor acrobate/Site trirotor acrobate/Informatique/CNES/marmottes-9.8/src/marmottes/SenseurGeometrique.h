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
//>       SenseurGeometrique.h
//
//$Resume
//       fichier d'en-tête de la classe SenseurGeometrique
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class SenseurGeometrique
//>       enum typeGeom           
//
//$Historique
//       $Log: SenseurGeometrique.h,v $
//       Revision 2.23  2003/10/08 09:40:09  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 2.22  2002/12/11 17:18:58  marmottes
//       DM-ID 12 Ajout d'un constructeur par défaut (protégé) pour prévenir celui construit par le compilateur.
//
//       Revision 2.21  2002/12/02 17:07:22  marmottes
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 2.20  2001/06/06 07:46:12  luc
//       prise en compte du déplacement de la classe Secteurs vers Cantor
//
//       Revision 2.19  2000/09/13 10:39:46  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 2.18  2000/03/30 17:01:24  luc
//       ajout du copyright CNES
//
//       Revision 2.17  1999/11/02 07:19:23  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 2.16  1999/08/06 13:32:19  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 2.15  1999/07/29 12:19:05  filaire
//       ajout de la méthode creneauConsigne
//
//       Revision 2.14  1999/04/27 08:25:21  luc
//       ajout de la méthode nouvelleReferenceSecteurs
//
//       Revision 2.13  1998/09/14 11:54:06  luc
//       ajout de la méthode verifieConsigne
//
//       Revision 2.12  1998/06/25 06:15:24  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 2.11  1998/04/26 20:13:47  luc
//       déplacement de Champ et Secteurs vers la bibliothèque marmottes
//
//       Revision 2.10  1998/04/26 18:25:37  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.9  1998/02/04 08:50:24  luc
//       mise en place d'un en-tête de classe au format AMIGAU
//
//       Revision 2.8  1997/08/20 09:52:10  luc
//       ajout d'un en-tête de fichier
//       réorganisation du code à raison d'une seule classe par fichier
//       remplacement du cône de consigne par un secteur de consigne
//
//       Revision 2.7  1997/04/27 19:33:50  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 2.6  1997/04/15 16:08:28  luc
//       remontée possible des champs d'inhibition des senseurs terre
//       
//       Revision 2.5  1997/02/13 09:57:58  luc
//       ajout du moment comme cible observable
//       
//       Revision 2.4  1997/02/12 10:58:20  luc
//       ajout de la cible pseudo-soleil pour les senseurs optiques
//       
//       Revision 2.3  1997/02/10 11:21:10  luc
//       ajout de la vitesse en tant que cible observable par un senseur
//       
//       Revision 2.2  1996/09/11 17:45:56  luc
//       ajout du nom du senseur dans l'instance
//       
//       Revision 2.1  1996/07/31 17:24:26  luc
//       ajout d'une possibilité de modifier le repère senseur à l'exécution
//       report au niveau du senseur terre de base de la séparation des inhibitions soleil/lune
//       élimination du senseur std15
//       
//       Revision 1.6  1996/05/15 14:41:18  luc
//       ajout du type de senseur "elevation"
//       
//       Revision 1.5  1996/03/21 17:30:39  luc
//       ajout du senseur STD15
//       
//       Revision 1.4  1995/09/12 06:25:13  mercator
//       ajout des pseudo-senseurs d'ascension droite et de declinaison
//       
//       Revision 1.3  1995/01/30 09:43:32  mercator
//       ajout de l'initialisation de pointeurs d'erreur en sortie
//       ajout d'initialisations des cibles de senseurs geometriques
//       
//       Revision 1.2  1995/01/27 16:59:53  mercator
//       propagation du spin dans tous les calculs depuis la modelisation
//       jusqu'a la sauvegarde de la solution finale dans l'etat
//       
//       Revision 1.1  1995/01/25 09:29:02  mercator
//       Initial revision
//
//$Version
//       $Id: SenseurGeometrique.h,v 2.23 2003/10/08 09:40:09 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurGeometrique_h
#define __marmottes_SenseurGeometrique_h

#include "cantor/Secteurs.h"
#include "marmottes/Senseur.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurGeometrique
//$Resume
//       classe abstraite de modélisation d'un senseur géométrique
//
//$Description
//       modélisation d'un senseur géométrique
//
//$Usage
//>     construction : 
//          à partir du nom, du repère satellite, de l'axe de calage
//          et de la précision, par copie
//          La classe étant abstraite, les constructeurs sont appelés
//          par les constructeurs des classes dérivées.
//>     utilisation  : 
//>       enum typeGeom  : 
//>       SenseurGeometrique& operator =   () 
//          affectation
//>       virtual void nouveauRepere       () 
//          tourne le senseur pour l'aligner sur le repère donné
//>       virtual typeGeom typeGeometrique () 
//          retourne le type de senseur géométrique (fonction virtuelle
//          pure dans cette classe)
//>       virtual ValeurDerivee1 foncEcart () 
//          calcule la fonction d'écart du senseur par rapport à sa
//          consigne à la date donnée et dans l'attitude donnée en
//          tenant compte de l'état précédent.
//>       void nouvelleReferenceSecteurs   () 
//          change la référence des secteurs de consigne
//>       const Creneau& creneauConsigne   () 
//          retourne le créneau de consigne
//>       const Secteurs& secteursConsigne () 
//          retourne les secteurs de consigne
//>       const VecDBL& cible              () 
//          retourne la cible inertielle 
//>       virtual int methode              () 
//          retourne un identificateur qui permet de regrouper les
//          senseurs de même principe général (géométrique ou
//          cinématique).
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurGeometrique : public Senseur
{

public :

  enum typeGeom { optique, pseudoSenseur };

  // constructeurs
  SenseurGeometrique (const string& nom, const RotDBL& repere,
                      const VecDBL& axeCalage, double precision)
    : Senseur (nom, repere, axeCalage, precision)
  {}
  SenseurGeometrique (const SenseurGeometrique& s)
    : Senseur (s), secteursConsigne_ (s.secteursConsigne_),
      axeVD1_ (s.axeVD1_), cible_ (s.cible_), cibleVD1_ (s.cibleVD1_)
  {}

  SenseurGeometrique& operator = (const SenseurGeometrique& s);

  // destructeur
  virtual ~SenseurGeometrique () {}

  // réorientation du senseur
  virtual void  nouveauRepere (const RotDBL& nouveau);

  void          nouvelleReferenceSecteurs (const VecDBL& reference)
    { secteursConsigne_.modifieReference (reference); }

  const Creneau& creneauConsigne () const { return  secteursConsigne_.creneau(); }

  // fonctions d'accès aux éléments internes
  const Secteurs&  secteursConsigne () const { return secteursConsigne_; }
  const VecDBL&    cible            () const { return cible_;            }
  virtual typeGeom typeGeometrique  () const = 0;

  // fonctions de résolution de l'attitude
  virtual int      methode          () const { return intersectionCones; }
  virtual ValeurDerivee1 foncEcart  (const Etat& etatPrecedent,
                                     const Etat& etatResolution,
                                     const RotVD1& attitude,
                                     const VecVD1& spin
                                    );

protected :

  // constructeur par defaut : ne doit JAMAIS être utilisé
  SenseurGeometrique () {}

  Secteurs   secteursConsigne_;
  VecVD1     axeVD1_;
  VecDBL     cible_;
  VecVD1     cibleVD1_;
  
  void       verifieConsigne () const
    throw (MarmottesErreurs);

};

#endif
