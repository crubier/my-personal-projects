subroutine mr_PlaVrai_PlaIner (planete, modeleUAI, long, pos_PlaVrai, pos_PlaIner, code_retour, &
          vit_rot, jul1950, vit_PlaVrai, vit_PlaIner, jacob)

! (C) Copyright CNES - MSLIB - 2003

!************************************************************************
!
! But:  Passage du repere planetocentrique vrai au repere planetocentrique
! ===   inertiel "H0-n" pour n=0
!
! Note d'utilisation:  
! ==================
!
! Historique:
! ==========
!   + Version 5.0 (SP 611 ed01 rev00): creation
!
!************************************************************************


! Modules
! =======
use int_mslib_mt_ref_iner
use int_mslib_mri_def_rep_UAI

use code_modeles_mslib
use code_planetes_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib

! Declarations
! ============
implicit none

include 'arg_mr_PlaVrai_PlaIner.h'

! Autres declarations
! ===================

real(pm_reel)                :: dW                     ! derivee de la longitude du meridien origine 
real(pm_reel)                :: angle                  ! angle de la rotation
real(pm_reel)                :: alpha0, delta0, W      ! pour l'appel a mri_def_rep_UAI
real(pm_reel)                :: sec                    ! pour l'appel a mt_ref_iner
type(tm_jour_sec)            :: date                   ! date en entree pour utilisation des modeles
type(tm_code_retour)         :: code_retour_local
integer                      :: retour_local

intrinsic present, matmul


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mr_PlaVrai_PlaIner.f90: derniere modification V5.0 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mr_PlaVrai_PlaIner.f90,v 1.6 2003/12/15 17:35:48 mslibdev Exp $ '

!************************************************************************

! initialisations
! ===============

! initialisation de la valeur du code retour

code_retour%valeur = pm_OK

! Verifications
! ===============

! modeles
if ((modeleUAI < pm_UAI_autre_modele).OR.(modeleUAI > pm_UAI2000)) then
   code_retour%valeur = pm_err_ind_model
   go to 6000
end if

! date si planete = Neptune
if ((planete == pm_pla_neptune).AND.(modeleUAI /= pm_UAI_autre_modele).AND..NOT.(present(jul1950))) then
   code_retour%valeur = pm_err_para_option
   go to 6000
end if

! Calculs
! =======

! determination de la vitesse de rotation de l'astre
if ( modeleUAI == pm_UAI_autre_modele) then   ! modele fourni par l'utilisateur

   if (present(vit_rot))  then
      dW = vit_rot
   else
      code_retour%valeur = pm_err_para_option
      go to 6000
   end if

else    ! modele predefini. On recupere la vitesse de rotation

   if ((planete == pm_pla_neptune).AND.(modeleUAI /= pm_UAI_autre_modele)) then
   ! seul cas ou la date intervient dans le calcul de la derivee du temps sideral
      date%jour = jul1950%jour
      date%sec = jul1950%sec
   else ! la date n'a aucune importance dans les autres cas
      date%jour = 0_pm_entier
      date%sec = 0._pm_reel
   end if
      
   call  mri_def_rep_UAI ( planete, modeleUAI, date, alpha0, delta0, W, dW, retour_local )
   if (retour_local /= pm_OK) then
      code_retour%valeur = retour_local
      if (retour_local < pm_OK)  go to 6000
   end if

end if

! appel a mt_ref_iner
sec = 0._pm_reel   ! on n'introduit pas de decalage de la longitude de depart
if (present(vit_PlaVrai).AND.present(vit_PlaIner)) then ! avec les vitesses
   if (present(jacob)) then
      call mt_ref_iner (dW, long, sec, pos_PlaVrai, pos_PlaIner, code_retour_local, &
           vit_ref = vit_PlaVrai, vit_iner = vit_PlaIner, jacob = jacob)
   else
      call mt_ref_iner (dW, long, sec, pos_PlaVrai, pos_PlaIner, code_retour_local,  &
           vit_ref = vit_PlaVrai, vit_iner = vit_PlaIner)
   end if
else if (.NOT.present(vit_PlaVrai).AND.present(vit_PlaIner)) then
   code_retour%valeur = pm_err_para_option
   go to 6000
else   ! sans les vitesses
   if (present(vit_PlaVrai).AND..NOT.present(vit_PlaIner))  code_retour%valeur = pm_warn_para_option
   if (present(jacob)) then
      call mt_ref_iner (dW, long, sec, pos_PlaVrai, pos_PlaIner, code_retour_local, jacob = jacob)
   else
      call mt_ref_iner (dW, long, sec, pos_PlaVrai, pos_PlaIner, code_retour_local)
   end if
end if


if (code_retour_local%valeur /= pm_OK) then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK)  go to 6000
end if


6000 continue

code_retour%routine = pm_num_mr_PlaVrai_PlaIner
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mr_PlaVrai_PlaIner
