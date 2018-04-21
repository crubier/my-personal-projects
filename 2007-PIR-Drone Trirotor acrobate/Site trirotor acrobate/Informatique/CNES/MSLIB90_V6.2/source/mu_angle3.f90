subroutine mu_angle3 (vect_a, vect_b, angle, code_retour)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Calcul de l'angle non oriente de deux vecteurs a et b de R3. 
! ===
!
! Note d'utilisation: L'angle calcule est exprime en radians et appartient a l'intervalle [0,pi]
! ==================
!
! Historique:
! ==========
!   + Version 1.0 (SP 203 ed01 rev00): creation a partir de la routine MUAVES de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======
use math_mslib
use int_mslib_mu_angle2
use int_mslib_mu_prod_vect
use int_mslib_mu_norme

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mu_angle3.h'

! Autres declarations
! -------------------
real(pm_reel) :: rscal,rvect      !produit scalaire des deux vecteurs en entree et norme de leur produit vectoriel
real(pm_reel), dimension(3) :: rc !produit vectoriel des deux vecteurs en entree
real(pm_reel) :: res

intrinsic  dot_product


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mu_angle3.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mu_angle3.f90,v 1.7 2003/10/14 12:53:43 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! calcul du produit scalaire et du produit vectoriel
! ==================================================
rscal = dot_product (vect_a, vect_b)                     ! produit scalaire

call mu_prod_vect(vect_a, vect_b, rc, code_retour)       ! produit vectoriel 
                                                         ! pas de code retour a tester car toujours nul dans mu_prod_vect
                    
call mu_norme(rc,rvect,code_retour)  ! norme du produit vectoriel (pas de code retour en erreur)

! calcul de l'angle non oriente entre 0 et pi (sin(angle) >= 0)
! =============================================================

call mu_angle2 (rscal,rvect,res,code_retour)
if (code_retour%valeur == pm_err_vect_nul) then
   angle = 0._pm_reel
else
   angle = res
end if

6000 continue

code_retour%routine = pm_num_mu_angle3
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mu_angle3
