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
//>       MarmottesErreurs.h
//
//$Resume
//       fichier d'en-tête de la classe MarmottesErreurs
//
//$Description
//       Module de déclaration de la classe
//
//$Contenu
//>       class MarmottesErreurs     
//>       void InitDomaineMarmottes()
//
//$Historique
//       $Log: MarmottesErreurs.h,v $
//       Revision 2.36  2003/10/08 09:40:09  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 2.35  2003/02/27 16:16:28  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 2.34  2002/12/11 17:06:15  marmottes
//       DM-ID 12 Ajout d'un destructeur pour prévenir celui construit par le compilateur.
//
//       Revision 2.33  2002/12/02 17:02:47  marmottes
//       DM-ID 12 Réorganisation des fichiers H de déclaration des classes selon le principe public/protected/private.
//
//       Revision 2.32  2002/02/27 14:09:09  marmottes
//       suppression de la description de la révision insérée manuellement
//       et mise à jour du copyright CNES
//
//       Revision 2.31  2002/02/22 09:47:24  marmottes
//       Ajout de l'erreur pas_senseur_cinematique (DM 0002)
//
//       Revision 2.30  2002/02/04 15:33:34  marmottes
//       ajout des erreurs champ_inhibition_cible_soleil et champ_inhibition_cible_lune
//
//       Revision 2.29  2002/01/17 14:30:19  marmottes
//       ajout de l'erreur consignes_gyro_elevees
//
//       Revision 2.28  2001/07/17 15:28:46  luc
//       ajout de l'erreur pas_de_point_sol
//
//       Revision 2.27  2001/06/06 07:50:00  luc
//       élimination des erreurs echec_heuristique, ouverture_fichier,
//       trace_inactif et frontiere_ouverte
//
//       Revision 2.26  2000/11/16 18:18:22  luc
//       ajout des erreurs points_echantillon, echantillon_vide et echantillon_rejete
//
//       Revision 2.25  2000/11/13 09:03:41  luc
//       remplacement de l'erreur point_triple par echec_heuristique,
//       ajout de l'erreur frontiere_ouverte
//
//       Revision 2.24  2000/09/13 09:45:55  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 2.23  2000/09/05 13:23:31  luc
//       ajout des erreurs ouverture_fichier, allocation_memoire,
//       trace_inactif, objet_inconnu
//
//       Revision 2.22  2000/06/07 14:02:43  luc
//       ajout de l'erreur senseur_mesure_pure
//
//       Revision 2.21  2000/03/30 17:01:22  luc
//       ajout du copyright CNES
//
//       Revision 2.20  1999/11/02 07:19:21  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 2.19  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines méthodes (correction des oublis
//       après le passage aux exceptions)
//
//       Revision 2.18  1999/04/23 11:40:26  luc
//       ajout de erreur_non_reconnue
//
//       Revision 2.17  1998/10/05 15:13:24  luc
//       élimination d'un const inutile dans une signature
//
//       Revision 2.16  1998/09/17 14:27:02  luc
//       démarrage des erreurs à 1 pour éviter d'avoir une erreur à code nul
//
//       Revision 2.15  1998/09/14 11:53:09  luc
//       ajout de l'erreur consigne_degeneree
//
//       Revision 2.14  1998/07/31 08:46:02  luc
//       ajout d'un en-tête d'interface pour la fonction InitDomaineMarmottes
//
//       Revision 2.13  1998/07/22 06:33:33  luc
//       ajout d'une erreur pour les consignes incompatibles
//
//       Revision 2.12  1998/07/15 12:16:38  luc
//       remplacement de l'erreur cardan_inconnu par genre_cardan_inconnu
//       ajout des erreurs : reference_cardan_inconnue, cible_utilisateur,
//       modifie_cible, senseur_sans_cible, pas_gyro_integrateur,
//       reference_utilisateur, modifie_reference, senseur_sans_reference
//       et cas_impossible
//
//       Revision 2.11  1998/06/25 06:02:29  luc
//       modification du format des en-têtes
//       élimination de la variable statique RCS
//
//       Revision 2.10  1998/05/14 12:03:52  luc
//       suppression d'erreurs inutilisées (depuis longtemps)
//
//       Revision 2.9  1998/04/26 20:13:20  luc
//       déplacement de Champ et Secteurs vers la bibliothèque marmottes
//
//       Revision 2.8  1998/04/26 18:21:18  luc
//       ajout des messages liés à la gestion d'unités de position et vitesse
//
//       Revision 2.7  1998/02/04 08:24:56  luc
//       mise en place d'un en-tête de classe au format AMIGAU
//
//       Revision 2.6  1997/11/27 07:06:53  luc
//       ajout d'un message pour les masques d'antennes des stations sol
//
//       Revision 2.5  1997/09/21 11:10:25  luc
//       ajout d'une erreur pour les variations d'angles de Cardan
//
//       Revision 2.4  1997/08/20 09:34:30  luc
//       ajout d'un en-tête de fichier
//       ajout d'une erreur lors de la réinitialisation des senseurs
//       ajout d'une erreur lors du filtrage des solutions parasites
//
//       Revision 2.3  1997/04/27 19:32:51  luc
//       inversion des codes de retour
//       changement des règles de nommage
//       passage de SCCS à RCS
//       
//       Revision 2.2  1996/09/11 17:37:07  luc
//       ajout des erreurs "id_marmottes_non_initialise" et "types_incompatibles"
//       élimination de l'erreur "solutions_multiples" (inutilisée depuis longtemps)
//       
//       Revision 2.1  1996/07/31 16:47:48  luc
//       abandon des tools.h++ (Rogue Wave)
//       destruction et création de plusieurs erreurs pour le passage en version 2
//       
//       Revision 1.3  1996/03/21 17:30:41  luc
//       ajout du senseur STD15
//       
//       Revision 1.2  1995/01/26 15:23:07  mercator
//       ajout d'une verification sur l'ecart de date avec l'etat precedent
//       
//       Revision 1.1  1995/01/25 14:46:37  mercator
//       Initial revision
//
//$Version
//       $Id: MarmottesErreurs.h,v 2.36 2003/10/08 09:40:09 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_MarmottesErreurs_h
#define __marmottes_MarmottesErreurs_h

#include "club/BaseErreurs.h"


///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class MarmottesErreurs
//
//$Resume
//       gestion des erreurs de la bibliothèque MARMOTTES
//
//$Description
//       cette classe gère toutes les erreurs de la bibliothèque MARMOTTES,
//       elle dérive de BaseErreurs
//
//$Usage
//>     construction : 
//          à partir du code d'erreur et des arguments associés, par copie
//>     utilisation  : 
//>       MarmottesErreurs& operator = () 
//          affectation 
//>       static int erreur            () 
//          crée une erreur à partir de son code (ou d'un format) et
//          de ses arguments et la retourne à l'appelant, éventuellement
//>       virtual const char* domaine  () 
//          retourne le domaine
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class MarmottesErreurs : public BaseErreurs
{

  public :

  // liste des codes d'erreurs
  enum { id_marmottes_non_initialise = 1,
         bloc_non_terminal,
         rotation_bloc,
         nombre_champs_bloc,
         bloc_introuvable,
         vecteur_nul,
         quaternion_nul,
         liste_non_initialisee,
         gyros_coaxiaux,
         consignes_gyro_elevees,
         consigne_degeneree,
         consignes_incompatibles,
         type_inconnu,
         cible_inconnue,
         champ_inhibition_cible_soleil,
         champ_inhibition_cible_lune,
         champ_inhibition_cible_central,
         omega_neg,
         seuil_neg,
         tranches_neg,
         pas_de_solution,
         controlabilite,
         calage_interdit,
         types_incompatibles,
         consigne_interdite,
         genre_cardan_inconnu,
         reference_cardan_inconnue,
         rotation_cardan,
         points_masque,
         unite_position,
         unite_vitesse,
         normes_litigieuses,
         cible_utilisateur,
         modifie_cible,
         senseur_sans_cible,
         pas_gyro_integrateur,
         reference_utilisateur,
         modifie_reference,
         senseur_sans_reference,
         erreur_non_reconnue,
         senseur_mesure_pure,
         allocation_memoire,
         points_echantillon,
         echantillon_vide,
         echantillon_rejete,
         objet_inconnu,
         pas_senseur_cinematique,
         cas_impossible
       };

  // constructeurs
  MarmottesErreurs       () : BaseErreurs () {}
  MarmottesErreurs       (int code ...);
  MarmottesErreurs       (const char* format ...);
  MarmottesErreurs       (const MarmottesErreurs& e) : BaseErreurs (e) {}

  // affectation
  MarmottesErreurs& operator =   (const MarmottesErreurs& e);

  // destructeur
  ~MarmottesErreurs () {}

  // fonctions d'accès aux éléments canoniques
  virtual const char* domaine    () const { return "marmottes"; }

  // déclenchement général d'une erreur
  static int erreur (MarmottesErreurs* ptr, int code ...);
  static int erreur (MarmottesErreurs* ptr, const char* format ...);

  protected :

  virtual const string& formate (int code, va_list ap) const;

};


///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       MarmottesErreurs.h
//
//$Resume
//        fonction d'initialisation du domaine de traduction marmottes
//
//$Description
//        fonction d'initialisation du domaine de traduction marmottes
//
//$Usage
//>     utilisation : 
//>       void InitDomaineMarmottes () 
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//      
//$<>
///////////////////////////////////////////////////////////////////////////////

void InitDomaineMarmottes ();

#endif
