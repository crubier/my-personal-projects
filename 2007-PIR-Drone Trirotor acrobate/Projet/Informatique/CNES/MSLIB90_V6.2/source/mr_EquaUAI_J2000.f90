subroutine mr_EquaUAI_J2000 ( planete, modeleUAI, jul1950, pos_EquaUAI, pos_J2000, code_retour, &
          asc_droite, declinaison, vit_EquaUAI, vit_J2000, jacob )

! (C) Copyright CNES - MSLIB - 2003

!************************************************************************
!
! But:  Passage du repere equatorial planetaire UAI d'un astre au repere EME2000
! ===
!
! Note d'utilisation:  
! ==================
!
! Historique:
! ==========
!   + Version 5.0 (SP 496 ed01 rev00): creation
!
!************************************************************************


! Modules
! =======
use int_mslib_mu_3rot_quat
use int_mslib_mu_quat_mat
use int_mslib_mu_quat_rep
use int_mslib_mri_def_rep_UAI

use code_transfo_mslib
use code_modeles_mslib
use math_mslib
use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mr_EquaUAI_J2000.h'

! Autres declarations
! ===================

integer                      :: def_3rot               ! definition de la rotation
real(pm_reel)                :: alpha0                 ! ascension droite
real(pm_reel)                :: delta0                 ! declinaison
real(pm_reel)                :: W                      ! meridien origine (seulement pour l'appel)
real(pm_reel)                :: dW                     ! derivee (seulement pour l'appel)
real(pm_reel)                :: angle1, angle2, angle3 ! angles de la rotation
type(tm_quat)                :: quat                   ! quaternion de la rotation
real(pm_reel),dimension(3,3) :: mat                    ! matrice de la rotation
type(tm_code_retour)         :: code_retour_local
integer                      :: retour_local

intrinsic present

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mr_EquaUAI_J2000.f90: derniere modification V5.0 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mr_EquaUAI_J2000.f90,v 1.4 2003/12/15 17:35:23 mslibdev Exp $ '

!************************************************************************

! initialisations
! ===============

! initialisation de la valeur du code retour

code_retour%valeur = pm_OK

! Verifications
! ===============

! modeles
if ((modeleUAI < pm_UAI_modeles_min).OR.(modeleUAI > pm_UAI_modeles_max)) then
   code_retour%valeur = pm_err_ind_model
   go to 6000
end if

if ((modeleUAI /= pm_UAI_autre_modele).AND.(present(asc_droite).OR.present(declinaison))) then
   code_retour%valeur = pm_warn_para_option
end if

! Calculs
! =======

! determination des angles du pole de rotation de l'astre
if ( modeleUAI == pm_UAI_autre_modele) then   ! modele fourni par l'utilisateur

   if (present(asc_droite).AND.present(declinaison)) then
      alpha0 = asc_droite
      delta0  = declinaison
   else
      code_retour%valeur = pm_err_para_option
      go to 6000
   end if

else    ! modele predefini

   call  mri_def_rep_UAI ( planete, modeleUAI, jul1950, alpha0, delta0, W, dW, retour_local )
   if (retour_local /= pm_OK) then
      code_retour%valeur = retour_local
      if (retour_local < pm_OK)  go to 6000
   end if

end if

! determination des angles de rotation   
def_3rot = pm_1x_2z_3y
angle1 = delta0 - pm_pi_sur2
angle2 = - alpha0 - pm_pi_sur2
angle3 = 0._pm_reel

! calcul du quaternion de la rotation
call mu_3rot_quat(def_3rot, angle1, angle2, angle3, quat, code_retour_local) 
if (code_retour_local%valeur /= pm_OK)  then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK)  go to 6000
end if

! calcul du vecteur position
call mu_quat_rep (pos_EquaUAI,quat, pos_J2000, code_retour_local)
if (code_retour_local%valeur /= pm_OK)  then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK)  go to 6000
end if

! calcul du vecteur vitesse si demande
if ((present(vit_J2000)) .and. (.not. present(vit_EquaUAI))) then
   code_retour%valeur = pm_err_para_option
   go to 6000
end if

if ((present(vit_EquaUAI)) .and. (.not. present(vit_J2000))) then
   code_retour%valeur = pm_warn_para_option
end if

if  (present(vit_EquaUAI).and.present(vit_J2000)) then
   call mu_quat_rep (vit_EquaUAI,quat,vit_J2000, code_retour_local)
   if (code_retour_local%valeur /= pm_OK)  then
      code_retour%valeur = code_retour_local%valeur
      if (code_retour_local%valeur < pm_OK)  go to 6000
   end if
end if

! calcul du jacobien si demande
if (present(jacob)) then
   
   call mu_quat_mat (quat, mat, code_retour_local)
   if (code_retour_local%valeur /= pm_OK)  then
      code_retour%valeur = code_retour_local%valeur
      if (code_retour_local%valeur < pm_OK)  go to 6000
   end if

   jacob(1:3,1:3) = mat(:,:)
   jacob(1:3,4:6) = 0._pm_reel
   jacob(4:6,4:6) = mat(:,:)
   jacob(4:6,1:3) = 0._pm_reel

end if

6000 continue

code_retour%routine = pm_num_mr_EquaUAI_J2000
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mr_EquaUAI_J2000
