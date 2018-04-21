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
//>       SenseurCardan.h
//
//$Resume
//       fichier d'en-tête de la classe SenseurCardan
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class SenseurCardan
//>       enum typeGenre     
//>       enum typeReference 
//
//$Historique
//       $Log: SenseurCardan.h,v $
//       Revision 1.15  2002/12/11 17:12:23  marmottes
//       DM-ID 12 Ajout d'un constructeur par défaut (protégé) pour prévenir celui construit par le compilateur.
//
//       Revision 1.14  2002/12/02 17:04:19  marmottes
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 1.13  2002/01/17 09:38:03  marmottes
//       correction de spécifications throw (FA 0003)
//
//       Revision 1.12  2001/01/25 16:26:20  luc
//       changement du type de refUtilInitialisee_ en bool
//
//       Revision 1.11  2000/09/13 10:04:33  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.10  2000/03/30 17:01:23  luc
//       ajout du copyright CNES
//
//       Revision 1.9  1999/11/02 07:19:22  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.8  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines méthodes (correction des oublis
//       après le passage aux exceptions)
//
//       Revision 1.7  1999/08/06 13:32:18  filaire
//       Passage à la gestion des erreurs par les exceptions
//
//       Revision 1.6  1998/08/07 09:38:27  luc
//       ajout d'attributs séparés pour le repère défini par l'utilisateur
//
//       Revision 1.5  1998/07/15 12:27:32  luc
//       modélisation de tous les angles
//       (auparavant, le troisième angle n'était pas géré par cette classe)
//       support de plusieurs repères de références
//       (dont un spécifié par l'utilisateur)
//
//       Revision 1.4  1998/06/25 06:14:01  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 1.3  1998/04/26 18:25:28  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.2  1997/09/23 09:25:46  luc
//       ajout d'une gestion des unités de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/09/21 11:14:07  luc
//       Initial revision
//
//$Version
//       $Id: SenseurCardan.h,v 1.15 2002/12/11 17:12:23 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurCardan_h
#define __marmottes_SenseurCardan_h

#include "marmottes/SenseurGeometrique.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurCardan
//
//$Resume
//       modélisation de tous les pseudo-senseurs d'angle de Cardan
//
//$Description
//       Cette classe concrète regroupe tous les modèles de senseurs
//       mesurant des angles de Cardan (ou leurs variations). Seules
//       les deux premiers angles de chaque succession de rotation sont
//       modélisés par cette classe, la troisième rotation est toujours
//       représentable directement par un senseur dièdre classique, la
//       conversion est réalisée dès la lecture du senseur.
//
//$Usage
//>     construction : 
//          à partir du nom, du repère satellite, de l'axe de calage
//          et de la précision, par copie
//          La classe étant abstraite, les constructeurs sont appelés
//          par les constructeurs des classes dérivées.
//>     utilisation  : 
//>       enum typeGenre      : 
//          identification d'une rotation dans un triplet ordonné
//>       enum typeReference  : 
//          identification d'un repère de réference
//>       SenseurCardan& operator =        () 
//          affectation
//>       virtual void respecterMesures    () 
//          force le senseur à respecter les unités de mesures dans
//          ses sorties
//>       virtual void convertirMesures    () 
//          force le senseur à convertir les unités de mesures dans
//          ses sortie
//>       virtual double mesure            () 
//          retourne la mesure que donnerait le senseur dans l'état donné
//>       virtual int modeliseConsigne     () 
//          permet de stocker un modèle de la consigne que doit
//          respecter un senseur contrôlant l'attitude du satellite
//          dans l'état courant ATTENTION: dans cet état, l'attitude
//          ne doit pas être utilisée, elle ne sera initialisée
//          correctement qu'à la fin de la résolution ayant utilisé ce
//          modèle!
//>       virtual int modifieReference     () 
//          initialise l'attitude de référence d'un senseur de Cardan
//>       virtual Senseur* copie           () 
//          retourne une copie du senseur allouée en mémoire
//>       virtual typeGeom typeGeometrique () 
//          retourne le type de senseur géométrique (pseudoSenseur)
//>       virtual int controlable          () 
//          indique si le senseur serait capable de contrôler
//          l'attitude de l'état donné
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


class SenseurCardan : public SenseurGeometrique
{

  // on doit commencer par déclarer les énumérations visibles de l'extérieur
  public :

  enum typeGenre     { GenreInconnu,
                       LRTLacet,   LRTRoulis,  LRTTangage,
                       LTRLacet,   LTRTangage, LTRRoulis,
                       RLTRoulis,  RLTLacet,   RLTTangage,
                       RTLRoulis,  RTLTangage, RTLLacet,
                       TLRTangage, TLRLacet,   TLRRoulis,
                       TRLTangage, TRLRoulis,  TRLLacet
                     };

  enum typeReference { ReferenceInconnue,
                       Geocentrique, OrbitalTNW,    OrbitalQSW,
                       Inertiel,     Topocentrique, Utilisateur
                     };

  // constructeurs
  SenseurCardan (typeGenre genre, typeReference reference,
                 const string& nom,
                 const RotDBL& repere, const VecDBL& axeCalage,
                 double precision)
    : SenseurGeometrique (nom, repere, axeCalage, radians (precision)),
      genre_ (genre), reference_ (reference),
      refUtilInitialisee_ (false), referenceUtilisateur_ (1.0, 0.0, 0.0, 0.0),
      xIn_ (1.0, 0.0, 0.0), yIn_ (0.0, 1.0, 0.0), zIn_ (0.0, 0.0, 1.0)
  {}

  SenseurCardan (const SenseurCardan& s)
    : SenseurGeometrique (s),
      genre_ (s.genre_), reference_ (s.reference_),
      refUtilInitialisee_ (s.refUtilInitialisee_),
      referenceUtilisateur_ (s.referenceUtilisateur_),
      xIn_ (s.xIn_), yIn_ (s.yIn_), zIn_ (s.zIn_)
  {}

  SenseurCardan& operator = (const SenseurCardan& s);

  // destructeur
  virtual ~SenseurCardan () {}

  virtual void respecterMesures ();
  virtual void convertirMesures ();

  virtual Senseur* copie           () const
                                   { return new SenseurCardan (*this); }

  virtual typeGeom typeGeometrique () const { return pseudoSenseur; }

  virtual double   mesure          (const Etat& etat)
    throw (MarmottesErreurs);

  virtual int      controlable     (const Etat& etat)
    throw (CantorErreurs, MarmottesErreurs)
                                   { return 1; }

  virtual void     modeliseConsigne (const Etat& etat, double valeur)
    throw (CantorErreurs, MarmottesErreurs);

  // fonction de mise à jour du repère de référence utilisateur
  virtual void     modifieReference (const RotDBL& reference)
    throw (MarmottesErreurs);

  protected :

  // constructeur par defaut : ne doit JAMAIS être utilisé
  SenseurCardan () {}

  private :

  typeGenre     genre_;
  typeReference reference_;

  bool          refUtilInitialisee_;
  RotDBL        referenceUtilisateur_;

  VecDBL        xIn_;
  VecDBL        yIn_;
  VecDBL        zIn_;

  void metAJourReference (const Etat& etat)
    throw (MarmottesErreurs);

};

#endif
