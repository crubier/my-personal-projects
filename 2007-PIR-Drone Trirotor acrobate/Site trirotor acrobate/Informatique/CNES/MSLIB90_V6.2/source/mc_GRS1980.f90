subroutine mc_GRS1980 ( code_retour, r_equa, inv_apla, apla)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Acces aux constantes relatives au systeme geodesique de reference 1980 (= GRS80)
! ===

! Historique:
! ==========
!   + Version 1.0 (SP 214 ed01 rev00): creation a partir de la routine MCRPOT de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======
use GRS1980_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mc_GRS1980.h'

! Autres declarations
! -------------------


intrinsic present

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mc_GRS1980.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mc_GRS1980.f90,v 1.7 2003/10/14 12:45:40 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! Affectation des valeurs des constantes demandees

if (present(r_equa))   r_equa   = pm_r_equa_GRS1980
if (present(inv_apla)) inv_apla = pm_inv_apla_GRS1980
if (present(apla))     apla     = pm_apla_GRS1980


6000 continue

code_retour%routine = pm_num_mc_GRS1980
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mc_GRS1980
