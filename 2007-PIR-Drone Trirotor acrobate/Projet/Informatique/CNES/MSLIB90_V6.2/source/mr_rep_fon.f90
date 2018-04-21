subroutine mr_rep_fon (trsf, model, jul1950_t1, jul1950_t2, mat_pass, code_retour, delta_tai)

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But: Calcul de la matrice de passage entre deux REPeres FONdamentaux.
! ===
!
! Note d'utilisation:  Le numero de la transformation (trsf) est de la forme ij avec i dans {1,2,3,4} et j dans {1,2,3,4}
! ==================
!
! Historique:
! ==========
!   + Version 1.0 (SP 263 ed01 rev00): creation a partir des routines MRCCMO, MRCCMV, MRCCVM, MRCCVV, MRCQMO, MRCQMV, 
!                                      MRCQVM, MRCQVV, MRQCMO, MRQCMV, MRQCVM, MRQCVV, MRQQMO, MRQQMV, MRQQVM, MRQQVV
!                                      de la MSLIB f77
!   + Version 2.0 (DE 362 ed01 rev00): suppression des commentaires sur la limitation sur les dates et des codes retours - ajout du parametre delta_tai en entree optionnelle - revision de l'utilisation des clefs
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!
!************************************************************************


! Modules
! =======
use code_transfo_mslib   ! contient toutes les valeurs possibles pour "trsf"
use code_modeles_mslib

use int_mslib_mri_equa_moy_t1_t2
use int_mslib_mri_equa_M_equa_V
use int_mslib_mri_equa_M_eclip_M
use int_mslib_mri_equa_M_eclip_V

use int_mslib_mri_equa_V_equa_M
use int_mslib_mri_equa_vrai_t1_t2
use int_mslib_mri_equa_V_eclip_M
use int_mslib_mri_equa_V_eclip_V

use int_mslib_mri_eclip_M_equa_M
use int_mslib_mri_eclip_M_equa_V
use int_mslib_mri_eclip_moy_t1_t2
use int_mslib_mri_eclip_M_eclip_V

use int_mslib_mri_eclip_V_equa_M
use int_mslib_mri_eclip_V_equa_V
use int_mslib_mri_eclip_V_eclip_M
use int_mslib_mri_eclip_vrai_t1_t2

use int_mslib_md_joursec_norme

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mr_rep_fon.h'

! Autres declarations
! -------------------
type(tm_jour_sec)         :: joursec1_tai, joursec2_tai      ! variables intermediaires
type(tm_jour_sec)         :: joursec1_norme, joursec2_norme  ! variables intermediaires pour l appel a md_joursec_norme
integer                   :: modele_precession          ! indicateur de modele de precession associe a "model" en entree
type(tm_code_retour)      :: code_retour_local
integer                   :: retour


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mr_rep_fon.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mr_rep_fon.f90,v 1.7 2003/10/14 12:49:14 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

if (model /= pm_lieske_wahr) then                      ! seul le modele Lieske+Wahr est disponible
      code_retour%valeur = pm_err_ind_model

else                                                   ! le parametrage est correct

   modele_precession = pm_lieske

   joursec1_tai%jour = jul1950_t1%jour
   joursec2_tai%jour = jul1950_t2%jour

   if (.not. present(delta_tai)) then

      joursec1_tai%sec  = jul1950_t1%sec               ! delta_tai est fixe a 0._pm_reel par defaut
      joursec2_tai%sec  = jul1950_t2%sec               !

   else

      joursec1_tai%sec  = jul1950_t1%sec + delta_tai   ! si delta_tai est precise par l'appelant
      joursec2_tai%sec  = jul1950_t2%sec + delta_tai   ! si delta_tai est precise par l'appelant

   end if

   call md_joursec_norme ( joursec1_tai, joursec1_norme, code_retour_local) ! code retour non teste car toujours = a 0
   call md_joursec_norme ( joursec2_tai, joursec2_norme, code_retour_local) ! code retour non teste car toujours = a 0

   select case(trsf)

   case (pm_equa_moy_equa_moy)  ! passage du repere equatorial moyen a t1 au repere equatorial moyen a t2 
      call mri_equa_moy_t1_t2(modele_precession, joursec1_norme, joursec2_norme, mat_pass, retour)

   case (pm_equa_moy_equa_vrai)  ! passage du repere equatorial moyen a t1 au repere equatorial vrai a t2 
      call mri_equa_M_equa_V(model, joursec1_norme, joursec2_norme, mat_pass, retour)

   case (pm_equa_moy_ecli_moy)  ! passage du repere equatorial moyen a t1 au repere ecliptique moyen a t2 
      call mri_equa_M_eclip_M(modele_precession, joursec1_norme, joursec2_norme, mat_pass, retour)

   case (pm_equa_moy_ecli_vrai)  ! passage du repere equatorial moyen a t1 au repere ecliptique vrai a t2 
      call mri_equa_M_eclip_V(model, joursec1_norme, joursec2_norme, mat_pass, retour)



   case (pm_equa_vrai_equa_moy)  ! passage du repere equatorial vrai a t1 au repere equatorial moyen a t2 
      call mri_equa_V_equa_M(model, joursec1_norme, joursec2_norme, mat_pass, retour)

   case (pm_equa_vrai_equa_vrai)  ! passage du repere equatorial vrai a t1 au repere equatorial vrai a t2 
      call mri_equa_vrai_t1_t2(model, joursec1_norme, joursec2_norme, mat_pass, retour)

   case (pm_equa_vrai_ecli_moy)  ! passage du repere equatorial vrai a t1 au repere ecliptique moyen a t2 
      call mri_equa_V_eclip_M(model, joursec1_norme, joursec2_norme, mat_pass, retour)

   case (pm_equa_vrai_ecli_vrai)  ! passage du repere equatorial vrai a t1 au repere ecliptique vrai a t2 
      call mri_equa_V_eclip_V(model, joursec1_norme, joursec2_norme, mat_pass, retour)



   case (pm_ecli_moy_equa_moy)  ! passage du repere ecliptique moyen a t1 au repere equatorial moyen a t2 
      call mri_eclip_M_equa_M(modele_precession, joursec1_norme, joursec2_norme, mat_pass, retour)

   case (pm_ecli_moy_equa_vrai)  ! passage du repere ecliptique moyen a t1 au repere equatorial vrai a t2 
      call mri_eclip_M_equa_V(model, joursec1_norme, joursec2_norme, mat_pass, retour)

   case (pm_ecli_moy_ecli_moy)  ! passage du repere ecliptique moyen a t1 au repere ecliptique moyen a t2 
      call mri_eclip_moy_t1_t2(modele_precession, joursec1_norme, joursec2_norme, mat_pass, retour)

   case (pm_ecli_moy_ecli_vrai)  ! passage du repere ecliptique moyen a t1 au repere ecliptique vrai a t2 
      call mri_eclip_M_eclip_V(model, joursec1_norme, joursec2_norme, mat_pass, retour)



   case (pm_ecli_vrai_equa_moy)  ! passage du repere ecliptique vrai a t1 au repere equatorial moyen a t2 
      call mri_eclip_V_equa_M(model, joursec1_norme, joursec2_norme, mat_pass, retour)

   case (pm_ecli_vrai_equa_vrai)  ! passage du repere ecliptique vrai a t1 au repere equatorial vrai a t2 
      call mri_eclip_V_equa_V(model, joursec1_norme, joursec2_norme, mat_pass, retour)

   case (pm_ecli_vrai_ecli_moy)  ! passage du repere ecliptique vrai a t1 au repere ecliptique moyen a t2 
      call mri_eclip_V_eclip_M(model, joursec1_norme, joursec2_norme, mat_pass, retour)

   case (pm_ecli_vrai_ecli_vrai)  ! passage du repere ecliptique vrai a t1 au repere ecliptique vrai a t2 
      call mri_eclip_vrai_t1_t2(model, joursec1_norme, joursec2_norme, mat_pass, retour)

   case default 
      retour = pm_err_ind_trsf

   end select

   code_retour%valeur = retour

end if


6000 continue

code_retour%routine = pm_num_mr_rep_fon
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mr_rep_fon
