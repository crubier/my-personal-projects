
module code_transfo_mslib

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Definition des parametres: de passage d'un repere a un autre, de rotations, ... 
! ===
!
! Note d'utilisation:  toute routine ou module utilisant parametre_mslib connait implicitement ce module.
! ==================
!
! Historique:
! ==========
!   + Version  1.0 (SP 283 ed01 rev00):creation
!   + Version 5.0 (DE 609 ed01 rev00): ajout des codes de rotation elementaires
!************************************************************************

use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

implicit none

! Valeurs associees aux indicateurs de changement de repere:
! =========================================================

! Convention adoptee : equatorial moyen -> 1
!                      equatorial vrai  -> 2
!                      ecliptique moyen -> 3
!                      ecliptique vrai  -> 4

integer, parameter :: pm_equa_moy_equa_moy = 11  
integer, parameter :: pm_equa_moy_equa_vrai = 12  
integer, parameter :: pm_equa_moy_ecli_moy = 13  
integer, parameter :: pm_equa_moy_ecli_vrai = 14  

integer, parameter :: pm_equa_vrai_equa_moy = 21  
integer, parameter :: pm_equa_vrai_equa_vrai = 22  
integer, parameter :: pm_equa_vrai_ecli_moy = 23 
integer, parameter :: pm_equa_vrai_ecli_vrai = 24  

integer, parameter :: pm_ecli_moy_equa_moy = 31  
integer, parameter :: pm_ecli_moy_equa_vrai = 32  
integer, parameter :: pm_ecli_moy_ecli_moy = 33 
integer, parameter :: pm_ecli_moy_ecli_vrai = 34  

integer, parameter :: pm_ecli_vrai_equa_moy = 41  
integer, parameter :: pm_ecli_vrai_equa_vrai = 42  
integer, parameter :: pm_ecli_vrai_ecli_moy = 43  
integer, parameter :: pm_ecli_vrai_ecli_vrai = 44  



! Parametres representant une rotation (a partir des 3 rotations elementaires):
! ============================================================================

! Convention adoptee : rotation autour de X -> 1
!                      rotation autour de Y -> 2
!                      rotation autour de Z -> 3

! angles d'Euler
integer, parameter :: pm_1x_2y_3x = 121
integer, parameter :: pm_1x_2z_3x = 131 
integer, parameter :: pm_1y_2x_3y = 212
integer, parameter :: pm_1y_2z_3y = 232
integer, parameter :: pm_1z_2x_3z = 313
integer, parameter :: pm_1z_2y_3z = 323

! angles de Cardan
integer, parameter :: pm_1x_2y_3z = 123
integer, parameter :: pm_1x_2z_3y = 132
integer, parameter :: pm_1y_2x_3z = 213
integer, parameter :: pm_1y_2z_3x = 231
integer, parameter :: pm_1z_2x_3y = 312
integer, parameter :: pm_1z_2y_3x = 321


!...............................................................................................................

 

 character(len=pm_longueur_info_utilisateur),private :: info_utilisateur = &
                    '@(#) Fichier MSLIB code_transfo_mslib.f90: derniere modification V5.0 >'

!................................................................................................................

  character(len=pm_longueur_rcs_id), private :: rcs_id =' $Id: code_transfo_mslib.f90,v 1.12 2003/12/15 17:34:23 mslibdev Exp $ '

end module code_transfo_mslib

