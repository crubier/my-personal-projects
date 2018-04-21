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
//>       ModeleGeom.h
//
//$Resume
//       fichier d'en-tête de la classe ModeleGeom
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class ModeleGeom
//
//$Historique
//       $Log: ModeleGeom.h,v $
//       Revision 2.11  2000/03/30 17:01:22  luc
//       ajout du copyright CNES
//
//       Revision 2.10  1999/11/02 07:19:21  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 2.9  1999/07/29 12:17:18  filaire
//       Restructuration de la classe en accord avec le nouveau modele
//       mathematique (utilisation des Familles de solutions)
//
//       Revision 2.8  1998/08/13 11:59:12  luc
//       correction de caractères exotiques devant certains accents
//       dans les en-têtes
//
//       Revision 2.7  1998/08/04 06:54:43  luc
//       doublement de la taille des ModeleGeomDomaine, en raison
//       de la séparation des modèles plus et moins en instances
//       indépendantes
//
//       Revision 2.6  1998/06/25 06:03:50  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 2.5  1998/06/08 15:56:24  luc
//       élimination d'attributs inutilisés
//
//       Revision 2.4  1998/04/26 18:25:09  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.3  1998/02/19 16:20:39  luc
//       déplacement d'un constructeur inline dans le .cc
//       pour contourner un problème d'optimiseur avec g++ 2.8.0
//
//       Revision 2.2  1998/02/04 09:18:47  luc
//       ajout d'un destructeur virtuel
//
//       Revision 2.1  1997/09/14 19:55:52  luc
//       remplacement de ModeleGeomMono et de ModeleGeomAlig
//       par la nouvelle classe ModeleGeomV1Fixe
//
//       Revision 1.6  1997/08/27 12:38:07  luc
//       initialisation par défaut du nombre de domaines à 0
//
//       Revision 1.5  1997/08/20 09:36:30  luc
//       ajout d'un en-tête de fichier
//       réorganisation du code à raison d'une seule classe par fichier
//
//       Revision 1.4  1997/04/27 19:33:22  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 1.3  1995/09/12 06:44:50  mercator
//       correction du sens d'application de la rotation entre le repere
//       canonique de resolution et le repere satellite
//       
//       Revision 1.2  1995/01/27 16:59:42  mercator
//       propagation du spin dans tous les calculs depuis la modelisation
//       jusqu'a la sauvegarde de la solution finale dans l'etat
//       
//       Revision 1.1  1994/12/23 11:00:07  luc
//       Initial revision
//
//$Version
//       $Id: ModeleGeom.h,v 2.11 2000/03/30 17:01:22 luc Exp $
//
//$Auteur
//       L. Maisonobe CNES et G. Filaire CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_ModeleGeom_h
#define __marmottes_ModeleGeom_h

#include "cantor/DeclVD1.h"
#include "cantor/Creneau.h"
#include "cantor/Intervalle.h"
#include "marmottes/MarmottesErreurs.h"
#include "marmottes/Etat.h"
#include "marmottes/Modele.h"
#include "marmottes/Famille.h"
#include "marmottes/FamilleGenerale.h"
#include "marmottes/FamilleFixe.h"
#include "marmottes/FamilleAlignementMoins.h"
#include "marmottes/FamilleAlignementPlus.h"
#include "marmottes/FamilleProlongementZero.h"
#include "marmottes/FamilleProlongementPi.h"
#include <vector>

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ModeleGeom
//
//$Resume
//       modèle géométrique d'attitude
//
//$Description
//       Cette classe implante un modèle d'attitude à un degré de
//       liberté, elle représente le point d'entrée général de la
//       résolution géométrique et s'appuie sur les divers modèles
//       spécifiques pour la résolution du cas général et de tous les
//       cas particuliers.
//
//$Usage
//>     construction : 
//          sans argument, par copie
//>     utilisation  : 
//>       ModeleGeom& operator =             () 
//          affectation
//>       virtual void prendConsignesEnCompte() 
//          initialise le modèle à partir des consignes courantes des
//          senseurs concernés
//>       virtual void attitude              () 
//          retourne l'attitude et le spin modélisés pour une famille
//          et une valeur du degré de liberté données
//>       virtual int familles               () 
//          retourne le nombre de familles d'attitude disjointes modélisées
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class ModeleGeom : public Modele
{ 
  public :

  // constructeurs
  ModeleGeom ();
  ModeleGeom (const ModeleGeom& m);

  // opérateur d'affectation
  ModeleGeom& operator = (const ModeleGeom& m);

  // destructeur
  virtual ~ModeleGeom () {}

  // activation du modèle
  virtual void prendConsignesEnCompte () throw (MarmottesErreurs);

  // fonction d'accès au nombre de familles
  virtual int    familles () const { return nombreFamilles_; }

  // fonction de modélisation d'attitude
  virtual void   attitude (const Etat& etatPrecedent, double date,
                           const ValeurDerivee1& t, int famille,
                           RotVD1* ptrAtt, VecVD1* ptrSpin) const;

  private :

  int       nombreFamilles_;   // nombre de familles disjointes d'attitudes
  vector<Famille>  table_;     // table de familles
  RotVD1    canSat_;           // repère canonique de résolution

  // méthode privée
  Creneau intersection (double cosMin, double cosMax, 
                        const Creneau& creneauConsigne) const;

};

#endif
