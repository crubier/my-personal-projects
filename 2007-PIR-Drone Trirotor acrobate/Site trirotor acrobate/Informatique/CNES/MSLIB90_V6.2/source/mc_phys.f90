subroutine mc_phys ( code_retour, ua, vit_lum, i_critique_non_retro, i_critique_retro )

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Acces aux constantes physiques
! ===

! Historique:
! ==========
!   + Version 1.0 (SP 211 ed.1 rev00): creation a partir de la routine MCONST de la MSLIB f77
!   + Version 2.0 (DE 399 ed.1 rev00): ajout des sorties i_critique_non_retro et i_critique_retro
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======
use phys_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mc_phys.h'

! Autres declarations
! -------------------

intrinsic present


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mc_phys.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mc_phys.f90,v 1.7 2003/10/14 12:45:50 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! Affectation des valeurs des constantes demandees

if (present(ua))                                     ua = pm_ua
if (present(vit_lum))                           vit_lum = pm_vit_lum
if (present(i_critique_non_retro)) i_critique_non_retro = pm_i_critique_non_retro
if (present(i_critique_retro))         i_critique_retro = pm_i_critique_retro

6000 continue

code_retour%routine = pm_num_mc_phys
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mc_phys
