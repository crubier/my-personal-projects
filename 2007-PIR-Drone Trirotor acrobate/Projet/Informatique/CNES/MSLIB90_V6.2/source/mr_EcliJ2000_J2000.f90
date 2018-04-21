subroutine mr_EcliJ2000_J2000 ( pos_EcliJ2000, pos_J2000, code_retour,  &
                                  obliquite, vit_EcliJ2000, vit_J2000, jacob )

! (C) Copyright CNES - MSLIB - 2003

!************************************************************************
!
! But:  Passage du repere ecliptique J2000 au repere EME2000 
! ===
!
! Note d'utilisation:  
! ==================
!
! Historique:
! ==========
!   + Version 5.0 (SP 494 ed01 rev00): creation
!
!************************************************************************


! Modules
! =======
use int_mslib_mu_quat_mat
use int_mslib_mu_quat_rep
use int_mslib_mui_axe_norme_quat

use phys_mslib
use parametres_internes_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib


! Declarations
! ============
implicit none

include 'arg_mr_EcliJ2000_J2000.h'

! Autres declarations
! ===================

real(pm_reel) :: angle                 ! angle de la rotation
type(tm_quat) :: quat                  ! quaternion de la rotation
real(pm_reel), dimension(3,3) :: mat   ! matrice de passage 
type(tm_code_retour)  :: code_retour_local

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mr_EcliJ2000_J2000.f90: derniere modification V5.0 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mr_EcliJ2000_J2000.f90,v 1.8 2003/12/15 17:35:18 mslibdev Exp $ '

!************************************************************************

! initialisations
! ===============

! initialisation de la valeur du code retour

code_retour%valeur = pm_OK

! rotation autour de l'axe X
! -------------------
! Calcul des positions
! -------------------

if (present(obliquite)) then
   angle = - obliquite
else
   angle = - pm_obliquite2000
end if

quat = mui_axe_norme_quat(pm_i_axe_x, angle)
call mu_quat_rep(pos_EcliJ2000,quat,pos_J2000,code_retour_local)
if (code_retour_local%valeur /= pm_OK)  then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK)  go to 6000
end if

! -------------------
! calcul optionnels
! -------------------

if ((present(vit_J2000)) .and. (.not. present(vit_EcliJ2000))) then
   code_retour%valeur = pm_err_para_option
   go to 6000
end if

if ((present(vit_EcliJ2000)) .and. (.not. present(vit_J2000))) then
   code_retour%valeur = pm_warn_para_option
end if


if  (present(vit_EcliJ2000).and.present(vit_J2000)) then      ! calcul des composantes vitesses
   call mu_quat_rep(vit_EcliJ2000,quat,vit_J2000,code_retour_local)
   if (code_retour_local%valeur /= pm_OK)  then
      code_retour%valeur = code_retour_local%valeur
      if (code_retour_local%valeur < pm_OK)  go to 6000
   end if
end if

if (present(jacob)) then  
! calcul du jacobien : calcul des derivees partielles des vecteurs position et vitesse 
! On calcule en fait la matrice de passage

   call mu_quat_mat(quat,mat,code_retour_local)
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

code_retour%routine = pm_num_mr_EcliJ2000_J2000
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mr_EcliJ2000_J2000
