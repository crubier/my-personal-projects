subroutine mdi_som_diff_joursec (joursec1, joursec2, retour, joursec_somme, joursec_diff)
! (C) Copyright CNES - MSLIB - 1999-2003

!************************************************************************
!
! But:  Addition ou soustraction de deux quantites exprimees en jours et secondes.
! ===   
!
!
! Note d'utilisation:  -  Routine interne 
! ==================
!
! Historique:
! ==========
!   + Version 2.0 (SP 334 ed01 rev00): creation a partir de la routine MUADDURJJS de la MSLIB f77
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======
use int_mslib_md_joursec_norme

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mdi_som_diff_joursec.h'

! Autres declarations
! -------------------
type(tm_jour_sec)    :: joursecloc1, joursecloc2  ! quantite jours et secondes pour les calculs intermediaires
type(tm_code_retour) :: code_inter                ! code retour intermediaire

intrinsic present

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mdi_som_diff_joursec.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mdi_som_diff_joursec.f90,v 1.8 2003/10/14 12:46:37 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
retour = pm_OK

! calcul selon que la somme ou/et la difference est/sont demandee(s)
! ..................................................................
if (present(joursec_somme)) then

   joursecloc1%jour = joursec1%jour + joursec2%jour
   joursecloc1%sec  = joursec1%sec  + joursec2%sec

   call md_joursec_norme (joursecloc1, joursec_somme, code_inter)

   retour = code_inter%valeur

   if (code_inter%valeur < pm_OK) then
      go to 6000
   end if

end if

if (present(joursec_diff)) then

   joursecloc2%jour = joursec1%jour - joursec2%jour
   joursecloc2%sec  = joursec1%sec  - joursec2%sec

   call md_joursec_norme (joursecloc2, joursec_diff, code_inter)

   retour = code_inter%valeur

   if (code_inter%valeur < pm_OK) then
      go to 6000
   end if

end if

6000 continue

end subroutine mdi_som_diff_joursec 
