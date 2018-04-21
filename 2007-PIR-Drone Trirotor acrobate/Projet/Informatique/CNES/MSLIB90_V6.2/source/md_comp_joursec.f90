subroutine md_comp_joursec (joursec1, joursec2, eps, ordre, code_retour)
! (C) Copyright CNES - MSLIB - 1999
!************************************************************************
!
! But:  comparaison de deux quantites exprimees en jours et secondes.
! ===   
!
! Historique:
! ==========
!   + Version 2.0 (SP 333 ed01 rev00): creation a partir de la routine MUCOMPJJS de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!
!************************************************************************


! Modules
! =======

use int_mslib_mdi_som_diff_joursec
use int_mslib_md_joursec_jourfrac

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib
use indic_comp_joursec_mslib

! Declarations
! ============
implicit none

include 'arg_md_comp_joursec.h'

!declaration des variables locales
!---------------------------------
type(tm_jour_sec)    :: joursec3                       ! quantite (jours, sec) tampon
integer              :: code_inter                     ! code retour des routines intermediaires
type(tm_code_retour) :: code_retour_local              ! code retour des routines intermediaires

real(pm_reel)        :: jourfrac3, presque_zero        ! variables intermediaires pour les tests

intrinsic tiny

!declaration des initialisations
!-------------------------------
character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB md_comp_joursec.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: md_comp_joursec.f90,v 1.7 2003/10/14 12:45:29 mslibdev Exp $ '

!************************************************************************
! initialisation de la valeur du code retour 
! ..........................................
code_retour%valeur = pm_OK

! initialisation constantes de test
! .................................
presque_zero = tiny(1._pm_reel)             ! recherche du plus petit reel positif non nul

! test pour savoir si eps > 0
! ...........................
if (eps < 0._pm_reel) then
   code_retour%valeur = pm_err_eps_negatif
   go to 6000
end if

if (eps <= presque_zero) then
   code_retour%valeur = pm_err_eps_nul
   go to 6000
end if

! calcul de la soustraction des 2 quantitees
! ..........................................
call mdi_som_diff_joursec (joursec1, joursec2, code_inter, joursec_diff=joursec3)
if (code_inter < 0) then
   code_retour%valeur = code_inter
   go to 6000
else
   code_retour%valeur = code_inter
end if

call md_joursec_jourfrac(joursec3, jourfrac3, code_retour_local)
if (code_retour_local%valeur < 0) then
   code_retour%valeur = code_retour_local%valeur
   go to 6000
end if

! test pour savoir si la premiere quantitee est plus grande que la deuxieme
! .........................................................................
if ((jourfrac3*86400._pm_reel) > eps) then
   ordre = pm_joursec1_sup_joursec2
   go to 6000
end if

! test pour savoir si la premiere quantitee est egale a la deuxieme
! .................................................................
if (abs(jourfrac3*86400._pm_reel) <= eps) then
   ordre = pm_joursec1_egal_joursec2
   go to 6000
end if

! test pour savoir si la premiere quantitee est plus petite que la deuxieme
! .........................................................................
if ((jourfrac3*86400._pm_reel) < (- eps)) then
   ordre = pm_joursec1_inf_joursec2
   go to 6000
end if


6000 continue

code_retour%routine = pm_num_md_comp_joursec
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine md_comp_joursec
