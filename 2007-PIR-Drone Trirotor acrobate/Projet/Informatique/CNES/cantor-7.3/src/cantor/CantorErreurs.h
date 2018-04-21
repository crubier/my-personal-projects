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
//       Cantor
//
//$Nom
//>       CantorErreurs.h
//
//$Resume
//       fichier d'en-tête de la classe CantorErreurs
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class CantorErreurs
//
//$Historique
//       $Log: CantorErreurs.h,v $
//       Revision 2.20  2002/12/02 13:51:36  cantor
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 2.19  2002/09/03 15:10:45  cantor
//       ajout de l'erreur 'alignement_axe_extremite' (FA15)
//
//       Revision 2.18  2002/09/02 09:21:52  cantor
//       ajout de l'erreur desequilibre_connexions
//
//       Revision 2.17  2002/02/04 09:15:18  cantor
//       ajout du message singularite_angle emis lors du calcul des angles de rotation de Cardan ou d'Euler
//
//       Revision 2.17  2002/01/18 15:25:22  cantor
//       ajout de l'erreur singularite_angle
//
//       Revision 2.16  2001/06/05 15:25:22  cantor
//       ajout des erreurs ordre_inconnu, matrice_singuliere,
//       echec_heuristique, frontiere_ouverte et erreur_interne
//
//       Revision 2.15  2000/10/25 12:30:56  cantor
//       modification du chemin vers le fichier CantorConfig.h dans l'include
//
//       Revision 2.14  2000/10/24 16:21:38  cantor
//       utilisation du namespace std et ajout de l'include CantorConfig.h
//
//       Revision 2.13  2000/09/11 13:38:07  cantor
//       modification de la signature de la fonction virtuelle formate : elle
//       retourne un string STL au lieu d'une ChaineSimple.
//
//       Revision 2.12  2000/08/09 14:36:43  cantor
//       Réunion de la branche 5.2.2 dans le tronc principal.
//
//       Revision 2.11.4.1  2000/03/30 15:36:08  cantor
//       ajout du copyright CNES
//
//       Revision 2.11  1998/09/17 14:21:23  cantor
//       démarrage des erreurs à 1 pour éviter d'avoir une erreur à code nul
//
//       Revision 2.10  1998/07/24 14:09:47  luc
//       ajout de l'erreur repere_indirect
//
//       Revision 2.9  1998/06/24 10:05:16  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 2.8  1998/05/12 10:11:40  luc
//       correction d'un const inutile dans une signature
//
//       Revision 2.7  1998/04/19 18:21:39  luc
//       élimination du code d'erreur inversion
//
//       Revision 2.6  1998/01/22 10:38:40  luc
//       amélioration de l'en-tête de classe
//
//       Revision 2.5  1997/07/06 10:15:19  luc
//       ajout d'un en-tête de fichier
//       ajout d'une erreur pour les points triples des frontières de champ
//
//       Revision 2.4  1997/04/03 19:34:42  luc
//       modification de commentaires
//       ajout d'un destructeur virtuel
//       
//       Revision 2.3  1997/03/26 06:53:48  luc
//       changement du type de retour de la méthode formate
//       (const char *  -->  const ChaineSimple&)
//       changement des conventions de nommage
//       
//       Revision 2.2  1997/03/24 09:22:08  luc
//       passage de SCCS à RCS
//       
//       Revision 2.1  1996/07/16 09:42:39  luc
//       élimination de la dépendance aux tools.h++ (Rogue Wave)
//       ajout des erreurs liés à l'approximation fonctionnelle
//       
//       Revision 1.3  1994/11/26 15:22:57  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.2  1994/11/09 16:04:13  mercator
//       remplacement de la fonction "lance" par "erreur"
//       
//       Revision 1.1  1994/07/27 14:57:07  luc
//       Initial revision
//
//$Version
//       $Id: CantorErreurs.h,v 2.20 2002/12/02 13:51:36 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Erreurs_h
#define __cantor_Erreurs_h

#include <cantor/CantorConfig.h>

#if CANTOR_HAVE_NAMESPACES
using namespace std;
#endif

#include <string>

#include "club/BaseErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class CantorErreurs
//$Resume
//       gestion des erreurs de la bibliothèque CANTOR
//
//$Description
//       cette classe gère toutes les erreurs de la bibliothèque CANTOR,
//       elle dérive de BaseErreurs
//
//$Usage
//>     construction : 
//          à partir du code d'erreur et des arguments associés, par copie
//>     utilisation  : 
//>       CantorErreurs& operator =   () 
//          affectation
//>       static int erreur           () 
//          crée une erreur dans l'instance fournie en argument si
//          elle existe (pointeur non nul) ou dans un objet local
//>       virtual const char* domaine () 
//          retourne le domaine "cantor"
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class CantorErreurs : public BaseErreurs
{ 
  public :

  // liste des codes d'erreurs
  enum { norme_nulle = 1,
         axe_rotation_nul,
         ordre_inconnu,
         matrice_non_orthogonalisable,
         matrice_singuliere,
         repere_indirect,
         alignement_axe_extremite,
         cones_coaxiaux,
         cones_disjoints,
         creneau_vide,
         indice_hors_bornes,
         polynome_invalide,
         aucune_fonction_base,
         erreur_fonction_base,
         ajuste_dimension_nulle,
         non_ajustable,
         non_ajustee,
         point_triple,
         echec_heuristique,
         frontiere_ouverte,
         desequilibre_connexions,
         erreur_interne,
         singularite_angle
       };

  // constructeurs
  CantorErreurs          () : BaseErreurs () {}
  CantorErreurs          (int code ...);
  CantorErreurs          (const char* format ...);
  CantorErreurs          (const CantorErreurs& e) : BaseErreurs (e) {}

  // destructeur
  virtual ~CantorErreurs () {}

  // affectation
  CantorErreurs& operator =        (const CantorErreurs& e);

  // fonctions d'accès aux éléments canoniques
  virtual const char* domaine    () const { return "cantor"; }

  // déclenchement général d'une erreur
  static int erreur (CantorErreurs* ptr, int code ...);
  static int erreur (CantorErreurs* ptr, const char* format ...);

  protected :

  virtual const string& formate (int code, va_list ap) const;

};


#endif
