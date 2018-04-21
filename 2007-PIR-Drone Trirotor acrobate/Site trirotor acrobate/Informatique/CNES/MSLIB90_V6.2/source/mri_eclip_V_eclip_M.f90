subroutine mri_eclip_V_eclip_M (model, jul1950_t1, jul1950_t2, mat_pass, retour)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Calcul de la matrice de passage du repere ECLIPtique VRAI a T1 au repere ECLIPtique MOYen a T2.
! ===
!
! Note d'utilisation: - Routine interne
! ==================  
!
! Historique:
! ==========
!   + Version 1.0 (SP 278 ed01 rev00): creation a partir de la routine MRCCVM de la MSLIB f77
!   + Version 2.0 (DE 362 ed01 rev00): suppression des commentaires sur la limitation sur les dates et des codes retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======
use int_mslib_mri_eclip_M_eclip_V
use code_modeles_mslib ! contient toutes les valeurs possibles pour "model"

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mri_eclip_V_eclip_M.h'

! Autres declarations
! -------------------

real(pm_reel), dimension(3,3)  :: mat_pass1                        ! matrice intermediaire

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mri_eclip_V_eclip_M.f90: derniere modification V4.1 >'

intrinsic transpose
! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mri_eclip_V_eclip_M.f90,v 1.8 2003/10/14 12:50:11 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
retour = pm_OK


if (model == pm_lieske_wahr) then 

   ! calcul de la matrice de passage du repere ecliptique vrai a t1 au repere ecliptique moyen a t2
   ! avec le modele de precession de Lieske et le modele de nutation de Wahr (epoque de base : J2000)



   ! ===============================================================
   ! calcul de la matrice de passage du repere ecliptique moyen a t2
   ! au repere  ecliptique vrai a t1
   ! ===============================================================

   call mri_eclip_M_eclip_V (model, jul1950_t2, jul1950_t1, mat_pass1, retour)
   ! pas de test de retour car il ne peut etre que nul (controles deja effectues)


   ! =======================
   ! transposition de matrice
   ! =======================

   mat_pass(:,:) = transpose (mat_pass1)

else   ! modele inconnu

   retour = pm_err_ind_model

end if

6000 continue

end subroutine mri_eclip_V_eclip_M
