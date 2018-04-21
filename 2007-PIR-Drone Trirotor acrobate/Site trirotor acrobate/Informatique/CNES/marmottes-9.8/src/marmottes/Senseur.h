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
//>       Senseur.h
//$Resume
//       fichier d'en-tête de la classe Senseur
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class Senseur    
//>       enum typeMethode 
//>       enum codeAstre 
//$Historique
//       $Log: Senseur.h,v $
//       Revision 3.20  2003/10/08 09:40:09  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 3.19  2002/12/11 17:11:00  marmottes
//       DM-ID 12 Ajout d'un constructeur par défaut (protégé) pour prévenir celui construit par le compilateur.
//
//       Revision 3.18  2002/02/27 14:09:09  marmottes
//       suppression de la description de la révision insérée manuellement
//       et mise à jour du copyright CNES
//
//       Revision 3.17  2002/02/22 09:48:55  marmottes
//       Déclaration de la méthode Senseur::initialiseDerive (DM 0002)
//
//       Revision 3.16  2002/01/17 09:38:03  marmottes
//       correction de spécifications throw (FA 0003)
//
//       Revision 3.15  2001/04/05 09:58:04  luc
//       élimination de l'initialisation à 1 inutile
//
//       Revision 3.14  2001/04/04 12:09:19  luc
//       ajout de la méthode criteresControlabilite
//
//       Revision 3.13  2000/10/02 12:32:12  luc
//       remplacement d'attributs entiers en booléens
//
//       Revision 3.12  2000/09/13 09:48:26  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 3.11  2000/03/30 17:01:23  luc
//       ajout du copyright CNES
//
//       Revision 3.10  1999/11/02 07:19:22  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 3.9  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines méthodes (correction des oublis
//       après le passage aux exceptions)
//
//       Revision 3.8  1999/08/06 13:32:18  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 3.7  1998/07/15 12:22:59  luc
//       ajout des méthodes virtuelles :
//       modifieCible, initialiseGyro, modifieReference, prendEtatEnCompte
//
//       Revision 3.6  1998/06/25 06:12:16  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 3.5  1998/04/26 18:25:25  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.4  1997/09/23 09:25:32  luc
//       ajout d'une gestion des unités de consigne et de mesure
//       interne au senseur
//
//       Revision 3.3  1997/08/20 09:50:06  luc
//       ajout d'un en-tête de fichier
//       ajout d'un attribut valeurConsigne_
//       utilisation de ChaineSimple
//       déplacement de constructeurs dans le .h (simplifiés grâce à ChaineSimple)
//       implantation d'une version générique de la méthode modeliseConsigne
//
//       Revision 3.2  1997/04/27 19:33:40  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//
//       Revision 3.1  1997/01/28 12:46:31  luc
//       ajout d'un #include "marmottes/marmottes_erreurs.h"
//       (car "marmottes/etat.h" ne le fait plus)
//
//       Revision 2.2  1996/09/11 17:44:19  luc
//       ajout du nom du senseur dans l'instance
//
//       Revision 2.1  1996/07/31 17:21:48  luc
//       ajout d'une possibilité de modifier le repère senseur à l'exécution
//
//       Revision 1.3  1995/01/30 09:43:27  mercator
//       ajout de l'initialisation de pointeurs d'erreur en sortie
//       ajout d'initialisations des cibles de senseurs geometriques
//
//       Revision 1.2  1995/01/27 16:59:47  mercator
//       propagation du spin dans tous les calculs depuis la modelisation
//       jusqu'a la sauvegarde de la solution finale dans l'etat
//
//       Revision 1.1  1994/12/23 11:00:13  luc
//       Initial revision
//
//$Version
//       $Id: Senseur.h,v 3.20 2003/10/08 09:40:09 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_Senseur_h
#define __marmottes_Senseur_h

#include <string>

#include "cantor/DeclDBLVD1.h"

#include "marmottes/Etat.h"
#include "marmottes/MarmottesErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Senseur
//$Resume
//       classe abstraite masquant le type sous-jacent de senseur utilisé.
//
//$Description
//       Cette classe abstraite est l'interface d'accès à tous les
//       types de senseurs, elle permet de rendre les routines de
//       calculs appelantes indépendantes des détails de modélisation
//       des senseurs.
//
//$Usage
//>     construction : 
//          à partir du nom, du repère satellite, de l'axe de calage
//          et de la précision, par copie
//          La classe étant abstraite, les constructeurs sont appelés
//          par les constructeurs des classes dérivées.
//>     utilisation  : 
//>       enum typeMethode  : 
//          méthode de modélisation analytique
//>       Senseur& operator =              () 
//          affectation
//>       virtual Senseur *copie           () 
//          retourne une copie du senseur allouée en mémoire
//>       virtual void respecterMesures    () 
//          force le senseur à respecter les unités de mesures dans
//          ses sorties
//>       virtual void convertirMesures    () 
//          force le senseur à convertir les unités de mesures dans
//          ses sortie
//>       virtual void nouveauRepere       () 
//          tourne le senseur pour l'aligner sur le repère donné
//>       int calage                       () 
//          tourne le senseur à partir du repère de base autour de
//          l'axe de calage.
//>       virtual double mesure            () 
//          retourne la mesure que donnerait le senseur dans l'état donné
//>       virtual int controlable          () 
//          indique si le senseur serait capable de contrôler
//          l'attitude de l'état donné
//>       virtual int criteresControlabilite () 
//          calcule les critères de contrôlabilité de l'attitude
//          dans l'état donné
//>       virtual int methode              () 
//          retourne un identificateur qui permet de regrouper les
//          senseurs de même principe général (géométrique ou
//          cinématique).
//>       virtual int modeliseConsigne     () 
//          permet de stocker un modèle de la consigne que doit
//          respecter un senseur contrôlant l'attitude du satellite
//          dans l'état courant ATTENTION: dans cet état, l'attitude
//          ne doit pas être utilisée, elle ne sera initialisée
//          correctement qu'à la fin de la résolution ayant utilisé ce
//          modèle!
//>       virtual ValeurDerivee1 foncEcart () 
//          calcule la fonction d'écart du senseur par rapport à sa
//          consigne à la date donnée et dans l'attitude donnée en
//          tenant compte de l'état précédent.
//>       const string& nom                () 
//          retourne le nom du senseur
//>       const RotDBL& repereBase         () 
//          retourne la rotation qui projette un vecteur exprimé en
//          repère satellite dans le repère senseur de base.
//>       const RotDBL& repere             () 
//          retourne la rotation qui projette un vecteur exprimé en
//          repère satellite dans le repère senseur courant.
//>       const VecDBL& axeCalage          () 
//          retourne l'axe de calage prédéfini pour le senseur
//>       double precision                 () 
//          retourne la précision du senseur (toujours dans la même
//          unité que mesure ()).
//>       bool conversionConsignes         () 
//          indique si le senseur doit convertir les consignes en
//          entrée dans son unité interne
//>       bool conversionMesures           () 
//          indique si le senseur doit convertir les mesures en sortie
//          dans les unités externes
//>       double valeurConsigne            () 
//          retourne la valeur de consigne courante (toujours dans la
//          même unité que mesure ()).
//>       void respecterConsignes          () 
//          force le senseur à respecter les unités de consignes
//          fournies en entrée
//>       void convertirConsignes          () 
//          force le senseur à convertir les unités de mesures dans
//          ses sorties
//>       VecDBL satSens                   () 
//          projette un vecteur donné en repère satellite dans le
//          repère senseur.
//>       VecDBL sensSat                   () 
//          projette un vecteur donné en repère senseur dans le repère
//          satellite.
//>       virtual int modifieCible         () 
//          mémorise une cible utilisateur pour un senseur optique
//>       virtual int initialiseGyro       () 
//          initialise l'angle d'un gyro intégrateur
//>       virtual int modifieReference     () 
//          initialise l'attitude de référence d'un senseur de Cardan
//>       virtual void prendEtatEnCompte   () 
//>       void reinitialisePrecision       () protegee - 
//>       virtual void initialiseDerive    ()
//          initialisation de la dérive d'un senseur
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


class Senseur
{
public :

  enum typeMethode { intersectionCones, integrationSpin, aucuneMethode };

  enum codeAstre { nonSignificatif, soleil, lune, corpsCentral, aucunAstre };

  // constructeurs
  Senseur (const string &nom, const RotDBL& repere,
           const VecDBL& axeCalage, double precision)
  : nom_ (nom), repereBase_ (repere), repere_ (repere),
    axeCalage_ (axeCalage), precision_ (precision),
    convertirConsignes_ (false), convertirMesures_ (false),
    valeurConsigne_ (0)
  {}

  Senseur (const Senseur& s)
  : nom_ (s.nom_), repereBase_ (s.repereBase_), repere_ (s.repere_),
    axeCalage_ (s.axeCalage_), precision_ (s.precision_),
    convertirConsignes_ (s.convertirConsignes_),
    convertirMesures_ (s.convertirMesures_),
    valeurConsigne_ (s.valeurConsigne_)
  {}

  Senseur& operator = (const Senseur& s);

  // destructeur
  virtual ~Senseur () {}

  virtual Senseur *copie () const = 0;

  // accès aux éléments internes
  const string&       nom            () const { return nom_;            }
  const RotDBL&       repereBase     () const { return repereBase_;     }
  const RotDBL&       repere         () const { return repere_;         }
  const VecDBL&       axeCalage      () const { return axeCalage_;      }
  double              precision      () const { return precision_;      }
  bool           conversionConsignes () const { return convertirConsignes_; }
  bool           conversionMesures   () const { return convertirMesures_;   }
  double              valeurConsigne () const { return valeurConsigne_; }

  // conversions d'unités en entrée et en sortie
  void respecterConsignes () { convertirConsignes_ = false; }
  void convertirConsignes () { convertirConsignes_ = true;  }
  virtual void respecterMesures () = 0;
  virtual void convertirMesures () = 0;

  // réorientation du senseur
  virtual void  nouveauRepere   (const RotDBL& nouveau);
          void  calage          (double c)
            throw (MarmottesErreurs);

  // changements de repères
  VecDBL satSens (const VecDBL& sat)  const { return repere_ (sat);     }
  VecDBL sensSat (const VecDBL& sens) const { return (-repere_) (sens); }

  // mesure fournie par le senseur
  virtual double mesure                 (const Etat& etat)
    throw (MarmottesErreurs) = 0;

  // contrôlabilité d'une attitude
  virtual int    controlable            (const Etat& etat)
    throw (MarmottesErreurs, CantorErreurs) = 0;

  virtual void   criteresControlabilite (const Etat& etat,
                                         codeAstre *ptrInhibant,
                                         codeAstre *ptrEclipsant,
                                         double    *ptrEcartFrontiere,
                                         bool      *ptrAmplitudeSignificative)
    throw (MarmottesErreurs, CantorErreurs);

  // modélisations des consignes d'attitude
  virtual int            methode          () const = 0;
  virtual void           modeliseConsigne (const Etat& etat,
                                           double valeur)  
    throw (CantorErreurs, MarmottesErreurs) = 0;

  // fonction de résolution de l'attitude
  virtual ValeurDerivee1 foncEcart        (const Etat& etatPrecedent,
                                           const Etat& etatResolution,
                                           const RotVD1& attitude,
                                           const VecVD1& spin
                                          ) = 0;

  // fonction de modification de la cible
  virtual void modifieCible (const VecDBL& cible)
    throw  (MarmottesErreurs)
  { throw  MarmottesErreurs (MarmottesErreurs::senseur_sans_cible,
                             nom ().c_str ());
  }

  // initialisation d'un gyro intégrateur
  virtual void initialiseGyro (double date, double angle)
    throw (MarmottesErreurs)
  { throw  MarmottesErreurs (MarmottesErreurs::pas_gyro_integrateur,
                             nom ().c_str ());
  }

  // mise en place du repère de référence pour un senseur de Cardan
  virtual void modifieReference (const RotDBL& reference)
    throw (MarmottesErreurs)
  { throw  MarmottesErreurs (MarmottesErreurs::senseur_sans_reference,
                             nom ().c_str ());
  }

  // prise en compte des états après résolution d'attitude (ce n'est
  // utile que pour les senseurs cinématiques, et plus précisément que
  // pour ceux qui intègrent les évolutions et doivent être tenus au
  // courant de l'état réel du satellite à chaque pas)
  virtual void prendEtatEnCompte (const Etat& etat)
  {}

  // initialisation de la dérive d'un senseur cinématique
  virtual void initialiseDerive (double derive)
    throw (MarmottesErreurs)
  { throw  MarmottesErreurs (MarmottesErreurs::pas_senseur_cinematique,
                             nom ().c_str ());
  }

protected :

  // méthode utilisée pour changer les unités de la précision
  void reinitialisePrecision (double precision) { precision_ = precision; }

  // constructeur par defaut : ne JAMAIS utiliser
  Senseur () {}

private :

  string nom_;
  RotDBL repereBase_;
  RotDBL repere_;
  VecDBL axeCalage_;  // <-- ATTENTION : coordonnées dans le REPÈRE DE BASE
  double precision_;
  bool   convertirConsignes_;
  bool   convertirMesures_;

  double valeurConsigne_;

};

#endif
