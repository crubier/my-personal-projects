subroutine mri_eclip_M_equa_V (model, jul1950_t1, jul1950_t2, mat_pass, retour)

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But:  Calcul de la matrice de passage du repere ECLIPtique MOYen a T1 au repere EQUAtorial VRAI a T2.
! ===
!
! Note d'utilisation: - Routine interne
! ==================  
!
! Historique:
! ==========
!   + Version 1.0 (SP 273 ed01 rev00): creation a partir de la routine MRCQMV de la MSLIB f77
!   + Version 2.0 (DE 362 ed01 rev00): suppression des commentaires sur la limitation sur les dates et des codes retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!
!************************************************************************


! Modules
! =======
use int_mslib_mri_eclip_M_equa_M
use int_mslib_mr_nuta
use int_mslib_mr_obli_moy
use int_mslib_mr_mat_nuta
use code_modeles_mslib   ! contient toutes les valeurs possibles pour "model"

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mri_eclip_M_equa_V.h'

! Autres declarations
! -------------------

!     -------------------------------
!     declaration des donnees locales
!     -------------------------------

real(pm_reel)                  :: obli_moy           ! obliquite moyenne
real(pm_reel), dimension(3,3)  :: mat_pass1          ! matrice de passage intermediaire
real(pm_reel), dimension(3,3)  :: mat_nuta           ! matrice de nutation
type(tm_nuta)                  :: nuta               ! nutation en longitude et en obliquite a t2
type(tm_code_retour)           :: code_retour
integer        :: modele_precession, modele_nutation ! indicateurs du modele de precession et du modele de nutation

intrinsic matmul


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mri_eclip_M_equa_V.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mri_eclip_M_equa_V.f90,v 1.8 2003/10/14 12:50:05 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
retour = pm_OK

if (model == pm_lieske_wahr) then  ! calcul de la matrice de passage du repere ecliptique moyen a t1 au repere equatorial vrai a t2
   ! avec le modele de precession de Lieske et le modele de nutation de Wahr (epoque de base : J2000)

   modele_precession = pm_lieske
   modele_nutation   = pm_wahr

   ! ===============================================================
   ! calcul de la matrice de passage du repere ecliptique moyen a t1
   ! au repere  equatorial moyen a t2
   ! ===============================================================

   call mri_eclip_M_equa_M (modele_precession, jul1950_t1, jul1950_t2, mat_pass1, retour)
   ! pas de test de retour car il ne peut etre que nul (controles deja effectues)


   ! ==========================================
   ! nutation en longitude et en obliquite a t2
   ! ==========================================

   call mr_nuta (modele_nutation, jul1950_t2, nuta, code_retour)
   ! pas de test de retour car il ne peut etre que nul (controles deja effectues)

   ! ======================
   ! obliquite moyenne a t2
   ! ======================

   call mr_obli_moy (modele_precession, jul1950_t2, obli_moy, code_retour)
   ! pas de test de retour car il ne peut etre que nul (controles deja effectues)


   ! ===================
   ! matrice de nutation
   ! ===================

   call mr_mat_nuta (nuta, obli_moy, mat_nuta, code_retour)
   ! pas de test de retour car il est toujours nul

   !=================
   ! produit matriciel
   !=================

   mat_pass(:,:) =  matmul(mat_nuta(:,:), mat_pass1(:,:))

else  ! modele inconnu

   retour = pm_err_ind_model

end if

6000 continue

end subroutine mri_eclip_M_equa_V
