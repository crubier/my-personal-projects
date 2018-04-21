subroutine mu_quat_3rot (def_3rot, quat, angle1, angle2, angle3, code_retour)

! (C) Copyright CNES - MSLIB - 2003

!************************************************************************
!
! But:  Calcul des trois angles de Cardan ou d'Euler associe a une rotation 
! ===   definie par un quaternion 
!
! Note d'utilisation:   voir la documentation utilisateur et la note algorithmique
! ==================
!
! Historique:
! ==========
!   + Version 5.0 (SP 606 ed01 rev00): creation par transfert de la routine de meme nom de la MSPRO
!   
!
!************************************************************************


! Modules
! =======
use math_mslib
use parametre_mslib

use int_mslib_mu_quat_norme
use int_mslib_mu_quat_rep
use int_mslib_mu_angle2

use parametres_internes_mslib
use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mu_quat_3rot.h'

! Autres declarations
! ===================

type (tm_quat)        :: quat_norme      ! quaternion norme
type (tm_quat)        :: quatinv         ! quaternion precedent inverse
real(pm_reel)         :: norme           ! norme
real(pm_reel), dimension(3) ::V, V1, V2  ! vecteurs transformes par rotation

! Parametres
!============

real(pm_reel),parameter :: eps_angle = 1.e-9_pm_reel ! environ 1 milliseconde d'arc
real(pm_reel),parameter :: un_moins_epsilon = 1._pm_reel-eps_angle   ! valeur de comparaison pour un vecteur


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mu_quat_3rot.f90: derniere modification V5.0 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mu_quat_3rot.f90,v 1.7 2003/12/15 17:36:03 mslibdev Exp $ '

!************************************************************************

! initialisations
! ===============

! initialisation de la valeur du code retour

code_retour%valeur = pm_OK

!normalisation du quaternion
!==========================
call mu_quat_norme ( quat, quat_norme, norme, code_retour )
if (code_retour%valeur < pm_ok) go to 6000

!calcul du quaternion inverse q-1
!================================
quatinv%q0   = -quat_norme%q0
quatinv%q123(:) = quat_norme%q123(:)


! ALGO
! ======

! A ce stade des calculs: quat_norme et quatinv sont des quaternions non nuls
! (pas de test necessaire sur le code retour de mu_quat_rep)

select case (def_3rot)

   ! Angle d'Euler
   !==============

case(pm_1x_2y_3x)

   call mu_quat_rep ( pm_i_axe_x, quat_norme, V1, code_retour )
   call mu_quat_rep ( pm_i_axe_x, quatinv, V2, code_retour )
   
   if (abs(V1(1)) < un_moins_epsilon)then
      call mu_angle2 ( V1(3) , V1(2) , angle3 , code_retour )
      call mu_angle2 ( -V2(3) , V2(2) , angle1 , code_retour )
      angle2 = acos(V1(1))

   else ! cosinus(angle2)= +/- 1
      call mu_quat_rep ( pm_i_axe_y, quatinv, V, code_retour )     
      if (V1(1)>0._pm_reel) then
         angle2 = 0._pm_reel
      else
         angle2 = pm_pi
      end if
      angle3 = 0._pm_reel
      call mu_angle2 ( V(2) , V(3) , angle1 , code_retour ) 
      code_retour%valeur = pm_warn_angle1_ou_3_indef
   end if




case(pm_1x_2z_3x)

   call mu_quat_rep ( pm_i_axe_x, quat_norme, V1, code_retour )
   call mu_quat_rep ( pm_i_axe_x, quatinv, V2, code_retour )

   if (abs(V1(1)) < un_moins_epsilon)then
      call mu_angle2 ( -V1(2) , V1(3) , angle3 , code_retour )
      call mu_angle2 ( V2(2) , V2(3) , angle1 , code_retour )
      angle2 = acos(V1(1))

   else ! cosinus(angle2)= +/- 1
      call mu_quat_rep ( pm_i_axe_z, quatinv, V, code_retour )

      if (V1(1)>0._pm_reel) then
         angle2 = 0._pm_reel      
      else
         angle2 = pm_pi
      end if
      angle3 = 0._pm_reel
      call mu_angle2 ( V(3) , -V(2) , angle1 , code_retour )
      code_retour%valeur = pm_warn_angle1_ou_3_indef
   end if




case(pm_1y_2x_3y)

   call mu_quat_rep ( pm_i_axe_y, quat_norme, V1, code_retour )
   call mu_quat_rep ( pm_i_axe_y, quatinv, V2, code_retour )

   if (abs(V1(2)) < un_moins_epsilon) then
      call mu_angle2 ( -V1(3) , V1(1) , angle3 , code_retour )
      call mu_angle2 ( V2(3) , V2(1) , angle1 , code_retour )
      angle2 = acos(V1(2))

   else ! cosinus(angle2)= +/- 1
      call mu_quat_rep ( pm_i_axe_x, quatinv, V, code_retour )

      if (V1(2)>0._pm_reel) then
         angle2 = 0._pm_reel     
      else
         angle2  = pm_pi
      end if
      angle3 = 0._pm_reel
      call mu_angle2 ( V(1) , -V(3) , angle1 , code_retour )
      code_retour%valeur = pm_warn_angle1_ou_3_indef
   end if





case(pm_1y_2z_3y)

   call mu_quat_rep ( pm_i_axe_y, quat_norme, V1, code_retour )
   call mu_quat_rep ( pm_i_axe_y, quatinv, V2, code_retour )

   if (abs(V1(2)) < un_moins_epsilon) then
      call mu_angle2 ( V1(1) , V1(3) , angle3 , code_retour )
      call mu_angle2 (  -V2(1) ,  V2(3) , angle1 , code_retour )
      angle2 = acos(V1(2))

   else ! cosinus(angle2)= +/-1
      call mu_quat_rep ( pm_i_axe_z, quatinv, V, code_retour )

      if (V1(2)>0._pm_reel) then
         angle2 = 0._pm_reel     
      else
         angle2 = pm_pi
      end if
      angle3 = 0._pm_reel
      call mu_angle2 ( V(3) , V(1) , angle1 , code_retour )
      code_retour%valeur = pm_warn_angle1_ou_3_indef
   end if




case(pm_1z_2x_3z)

   call mu_quat_rep ( pm_i_axe_z, quat_norme, V1, code_retour )
   call mu_quat_rep ( pm_i_axe_z, quatinv, V2, code_retour )

   if ( abs(V1(3)) < un_moins_epsilon) then
      call mu_angle2 ( V1(2) , V1(1) , angle3 , code_retour )
      call mu_angle2 ( -V2(2) , V2(1) , angle1 , code_retour )
      angle2 = acos(V1(3))

   else ! cosinus(angle2)= +/- 1
      call mu_quat_rep ( pm_i_axe_x, quatinv, V, code_retour )

      if (V1(3)>0._pm_reel) then
         angle2 = 0._pm_reel     
      else
         angle2 = pm_pi
      end if
      angle3 = 0._pm_reel
      call mu_angle2 ( V(1) , V(2) , angle1 , code_retour )
      code_retour%valeur = pm_warn_angle1_ou_3_indef
   end if


case(pm_1z_2y_3z)

   call mu_quat_rep ( pm_i_axe_z, quat_norme, V1, code_retour )
   call mu_quat_rep ( pm_i_axe_z, quatinv, V2, code_retour )

   if (abs(V1(3)) < un_moins_epsilon) then
      call mu_angle2 ( -V1(1) , V1(2) , angle3 , code_retour )
      call mu_angle2 ( V2(1) , V2(2) , angle1 , code_retour )
      angle2 = acos(V1(3))

   else ! cosinus(angle2)= +/- 1
      call mu_quat_rep ( pm_i_axe_y, quatinv, V, code_retour )


      if (V1(3)>0._pm_reel) then
         angle2 = 0._pm_reel

      else
         angle2 = pm_pi
      end if
      angle3 = 0._pm_reel
      call mu_angle2 ( V(2), -V(1) , angle1 , code_retour )
      code_retour%valeur = pm_warn_angle1_ou_3_indef
   end if


   ! Angle de Cardan
   !==================

case(pm_1x_2y_3z)

   call mu_quat_rep ( pm_i_axe_x, quat_norme, V1, code_retour )
   call mu_quat_rep ( pm_i_axe_z, quatinv, V2, code_retour )

   if (abs(V1(3)) < un_moins_epsilon) then
      call mu_angle2 ( V1(1) ,-V1(2) , angle3 , code_retour )
      call mu_angle2 ( V2(3) , -V2(2) , angle1 , code_retour )
      angle2 = asin(V1(3))

   else ! sinus(angle2)= +/- 1
      call mu_quat_rep ( pm_i_axe_y, quat_norme, V, code_retour ) 
      angle1 = 0._pm_reel
      call mu_angle2 ( v(2) , V(1) , angle3 , code_retour )
      angle2 = sign( pm_pi_sur2 ,V1(3))   
      code_retour%valeur = pm_warn_angle1_ou_3_indef
   end if



case(pm_1x_2z_3y)

   call mu_quat_rep ( pm_i_axe_x, quat_norme, V1, code_retour )
   call mu_quat_rep ( pm_i_axe_y, quatinv, V2, code_retour )

   if (abs(V1(2)) < un_moins_epsilon) then
      call mu_angle2 (  V1(1), V1(3) , angle3 , code_retour )
      call mu_angle2 ( V2(2) , V2(3) , angle1 , code_retour )
      angle2 = asin( -V1(2))

   else ! sinus(angle2)= +/- 1
      call mu_quat_rep ( pm_i_axe_z, quat_norme, V, code_retour ) 
      angle1 = 0._pm_reel
      call mu_angle2 ( v(3) ,- V(1) , angle3 , code_retour )
      angle2 = sign( pm_pi_sur2 ,-V1(2))  
      code_retour%valeur = pm_warn_angle1_ou_3_indef
   end if


case(pm_1y_2x_3z)

   call mu_quat_rep ( pm_i_axe_y, quat_norme, V1, code_retour )
   call mu_quat_rep ( pm_i_axe_z, quatinv, V2, code_retour )

   if (abs(V1(3)) < un_moins_epsilon) then
      call mu_angle2 ( V1(2) , V1(1) , angle3 , code_retour )
      call mu_angle2 ( V2(3),  V2(1) , angle1 , code_retour )
      angle2 = asin(-V1(3))

   else ! sinus(angle2)= +/- 1
      call mu_quat_rep ( pm_i_axe_x, quat_norme, V, code_retour )
      angle1 = 0._pm_reel
      call mu_angle2 ( v(1) , -V(2) , angle3 , code_retour )
      angle2 = sign( pm_pi_sur2 ,-V1(3))
      code_retour%valeur = pm_warn_angle1_ou_3_indef
   end if

case(pm_1y_2z_3x)

   call mu_quat_rep ( pm_i_axe_y, quat_norme, V1, code_retour )
   call mu_quat_rep ( pm_i_axe_x, quatinv, V2, code_retour )

   if (abs(V1(1)) < un_moins_epsilon) then
      call mu_angle2 ( V1(2), -V1(3)  , angle3 , code_retour )
      call mu_angle2 ( V2(1), -V2(3)  , angle1 , code_retour )
      angle2 = asin(V1(1))

   else ! sinus(angle2)= +/- 1
      call mu_quat_rep ( pm_i_axe_z, quat_norme, V, code_retour )
      angle1 = 0._pm_reel
      call mu_angle2 ( V(3) , V(2) , angle3 , code_retour )
      angle2 = sign( pm_pi_sur2 ,V1(1))
      code_retour%valeur = pm_warn_angle1_ou_3_indef 
   end if


case(pm_1z_2x_3y)


   call mu_quat_rep ( pm_i_axe_z, quat_norme, V1, code_retour )
   call mu_quat_rep ( pm_i_axe_y, quatinv, V2, code_retour )

   if (abs(V1(2)) < un_moins_epsilon) then
      call mu_angle2 ( V1(3)  ,- V1(1)  , angle3 , code_retour )
      call mu_angle2 ( V2(2), -V2(1) , angle1 , code_retour )
      angle2 = asin(V1(2))

   else ! sinus(angle2)= +/- 1
      call mu_quat_rep ( pm_i_axe_x, quat_norme, V, code_retour )
      angle1 = 0._pm_reel
      call mu_angle2 ( v(1), V(3) , angle3 , code_retour )
      angle2 = sign( pm_pi_sur2 ,V1(2))
      code_retour%valeur = pm_warn_angle1_ou_3_indef
   end if

case(pm_1z_2y_3x)

   call mu_quat_rep ( pm_i_axe_z, quat_norme, V1, code_retour )

   call mu_quat_rep ( pm_i_axe_x, quatinv, V2, code_retour )

   if (abs(V1(1)) < un_moins_epsilon) then
      call mu_angle2 ( V1(3), V1(2) , angle3 , code_retour )
      call mu_angle2 ( V2(1) , V2(2) , angle1 , code_retour )
      angle2 = asin(-V1(1))

   else ! sinus(angle2)= +/- 1
      call mu_quat_rep ( pm_i_axe_y, quat_norme, V, code_retour )
      angle1 = 0._pm_reel
      call mu_angle2 ( V(2) , -V(3) , angle3 , code_retour )
      angle2 = sign( pm_pi_sur2 ,-V1(1))
      code_retour%valeur = pm_warn_angle1_ou_3_indef
   end if


case default
   code_retour%valeur=pm_err_clef_rot
   go to 6000
end select



6000 continue

code_retour%routine = pm_num_mu_quat_3rot
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mu_quat_3rot
