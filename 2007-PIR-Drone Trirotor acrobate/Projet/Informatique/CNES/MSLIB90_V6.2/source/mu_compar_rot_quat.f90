subroutine mu_compar_rot_quat (quat1, quat2, angle, code_retour)

! (C) Copyright CNES - MSLIB - 2004

!************************************************************************
!
! But:  COMPARaison des ROTations associees a 2 QUATernions
! ===
!
! Note d'utilisation:  
! ==================
!
! Historique:
! ==========
!   + Version 6.0 (SP 627 ed01 rev00): creation 
!
!************************************************************************


! Modules
! =======
use int_mslib_mu_prod_quat
use int_mslib_mu_quat_norme
use int_mslib_mu_quat_axe_angle

use math_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mu_compar_rot_quat.h'

! Autres declarations
! ===================

type(tm_quat)    ::  quat_inv, quat3         ! quaternion inverse de quat2 et produit de quat1 par cet inverse
type(tm_quat)    ::  quat1_norme, quat2_norme! quaternions normes de quat1 et quat2
real(pm_reel), dimension(3) :: axe            
real(pm_reel)               :: angle_temp    ! angle d'ecart entre les rotations
real(pm_reel)               :: norme         ! norme des quaternions
real(pm_reel)               :: presque_zero  ! plus petit reel machine
type(tm_code_retour)        :: code_retour_local

intrinsic tiny

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mu_compar_rot_quat.f90: derniere modification V6.0 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mu_compar_rot_quat.f90,v 1.9 2005/01/17 14:37:15 mslibdev Exp $ '

!************************************************************************

! initialisations
! ===============

! initialisation de la valeur du code retour
code_retour%valeur = pm_OK

! plus petit reel machine
presque_zero = tiny(1._pm_reel)

! calculs
! =======

! normalisation des quaternions
call mu_quat_norme ( quat1, quat1_norme, norme, code_retour_local )
if (code_retour_local%valeur /= pm_OK)  then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK)  go to 6000
end if

call mu_quat_norme ( quat2, quat2_norme, norme, code_retour_local )
if (code_retour_local%valeur /= pm_OK)  then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK)  go to 6000
end if

! A ce stade des calculs: quat1_norme et quat2_norme sont des quaternions non nuls

! Calcul de l'inverse de quat2
quat_inv%q0=-quat2_norme%q0
quat_inv%q123(:)=quat2_norme%q123(:)

! produit de quat1_norme * inverse(quat2) 
call mu_prod_quat ( quat1_norme, quat_inv, quat3, code_retour_local)
if (code_retour_local%valeur /= pm_OK)  then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK)  go to 6000
end if

! angle associe au produit
call mu_quat_axe_angle ( quat3, axe, angle_temp, code_retour_local )
if (code_retour_local%valeur /= pm_OK)  then

    if (code_retour_local%valeur == pm_err_axe_rot_indef) then 
    ! Cas special: cela signifie qu'on compare des quaternions identiques ou 
    !              opposes, ce n'est donc pas une erreur, au contraire
       code_retour_local%valeur = pm_OK                        
    endif 

   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK)  go to 6000
end if


! angle est dans [0, 2pi] a ce stade des calculs

if ((angle_temp - pm_pi) >= presque_zero)  then ! angle obtus entre pi et 2pi: l'ecart de rotation n'ayant pas de sens 
   angle = pm_deux_pi - angle_temp   !(direct ou retrograde) on recadre entre 0 et pi
else
   angle = angle_temp  
end if

6000 continue

code_retour%routine = pm_num_mu_compar_rot_quat
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mu_compar_rot_quat
