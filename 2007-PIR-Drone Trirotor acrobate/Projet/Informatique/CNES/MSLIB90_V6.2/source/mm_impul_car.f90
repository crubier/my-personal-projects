subroutine mm_impul_car (pos_car, vit_car_avant, rep, impul, vit_car_apres, code_retour)

! (C) Copyright CNES - MSLIB - 1999-2003

!************************************************************************
!
! But: Pour un satellite, calcul du bulletin d'orbite en coordonnee CARtesiennes suite a la realisation d'une manoeuvre orbitale modelisee par une mono-IMPULsion quelconque 
! ===
!
! Historique:
! ==========
!   + Version 2.0 (SP 337 ed01 rev00): creation a partir de la routine MMIMPS de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======
use int_mslib_mo_qsw_geo
use int_mslib_mo_tnw_geo


use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib
use indic_reperes_mslib

! Declarations
! ============
implicit none

include 'arg_mm_impul_car.h'

! Autres declarations
! ===================
real(pm_reel), dimension(3) :: rveco
type(tm_code_retour)        :: code_retour_local


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mm_impul_car.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mm_impul_car.f90,v 1.7 2003/10/14 12:47:08 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! calcul des composantes de l'impulsion dans le repere choisi
! ...........................................................

select case (rep)

case (pm_rep_geo)
   rveco(:) = impul(:)
   
case (pm_rep_qsw)                   ! vecteur impulsion donne dans le repere qsw
   call mo_qsw_geo ( pos_car, vit_car_avant, impul, rveco, code_retour_local )
   if (code_retour_local%valeur < 0) then
      code_retour%valeur = code_retour_local%valeur
      go to 6000
   else
      code_retour%valeur = code_retour_local%valeur
   end if

case (pm_rep_tnw)                   ! vecteur impulsion donne dans le repere tnw
   call mo_tnw_geo( pos_car, vit_car_avant, impul, rveco, code_retour_local )
   if (code_retour_local%valeur < 0) then
      code_retour%valeur = code_retour_local%valeur
      go to 6000
   else
      code_retour%valeur = code_retour_local%valeur
   end if

case default                        ! repere non prevu 
   code_retour%valeur = pm_err_ind_rep
   go to 6000

end select

! calcul des positions vitesses apres impulsion
! .............................................

vit_car_apres(:) = vit_car_avant(:) + rveco(:)


6000 continue

code_retour%routine = pm_num_mm_impul_car
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mm_impul_car
