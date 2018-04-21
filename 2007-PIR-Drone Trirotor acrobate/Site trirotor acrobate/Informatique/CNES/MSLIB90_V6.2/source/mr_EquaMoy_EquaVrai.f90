subroutine mr_EquaMoy_EquaVrai ( model, jul1950, delta_tai, pos_EquaMoy, pos_EquaVrai, code_retour,  &
     inertiel, vit_EquaMoy, vit_EquaVrai, jacob )

! (C) Copyright CNES - MSLIB - 2003-2005

!************************************************************************
!
! But:  Passage du repere equatorial moyen a la date t au repere equatorial vrai a la meme date t
! ===
!
! Note d'utilisation:  [DR1] "Les systemes de reference utilises en astronomie"
! ==================         de M. Chapront-Touze, G. Francou et B. Morando
!                            Bureau Des Longitudes (BDL) novembre 1994
!                            ISSN 1243-4272
!                            ISBN 2-910015-05-X
!                            nomenclature MSLIB M-NT-0-160-CN
!                      Nota: Les epoques J1900 et J2000 sont explicitees en
!                            page 23 table 1.1
!
! Historique:
! ==========
!   + Version 4.0 (SP 472 ed01 rev00): creation a partir de la routine mri_EquaMoy_EquaVrai 
!                                      (corrigee de m-de-1000-480-CIS et m-fa-1000-479-CIS)
!   + Version 4.1 (DE globale 484 ed01 rev00): calcul de la jacobienne 
!   + Version 6.1 (DE 1): ajout de l'option inertiel (calcul sans vitesse d'entrainement)
!   + Version 6.2 (DE globale 1): remplacement des calculs matriciels par des calculs bases sur des quaternions
!
!************************************************************************


! Modules
! =======
use int_mslib_mr_nuta
use int_mslib_mr_obli_moy
use int_mslib_mu_3rot_quat
use int_mslib_mu_quat_rep
use int_mslib_mu_prod_vect
use int_mslib_mu_quat_mat

use code_modeles_mslib
use code_transfo_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib 
use longueur_chaine_mslib

! Declarations
! ============
implicit none

include 'arg_mr_EquaMoy_EquaVrai.h'

! Autres declarations
! ===================
integer       :: def_3rot               ! definition de la rotation
real(pm_reel) :: angle1, angle2, angle3 ! angles de la rotation

type(tm_nuta) :: nuta                     ! nutation en longitude, nutation en obliquite
type(tm_nuta) :: deriv1_nuta, deriv2_nuta ! derivees premieres et secondes de la nutation en longitude et en obliquite
real(pm_reel) :: obli_moy                 ! obliquite moyenne
real(pm_reel) :: deriv1_obli, deriv2_obli ! derivees premieres et secondes de l'obliquite moyenne

type(tm_quat) :: quat ! quaternion de la rotation
real(pm_reel), dimension(3,3) :: mat, mat_vect_rot ! matrices de changement de repere et rotation
real(pm_reel), dimension(3)   :: vect_omega ! vecteur rotation (cas non inertiel)
real(pm_reel), dimension(3)   :: vit_EquaVrai_iner, vit_entrainement ! vecteur vitesse dans le repere equatorial vrai 
!(sans prise en compte de la vitesse d'entrainement) 
! et vecteur vitesse d'entrainement

logical :: flag_iner ! variable de test de la presence ou non de flag inertiel

integer :: modele_precession, modele_nutation  ! indicateurs des modeles de precession et de nutation

type(tm_code_retour) :: code_retour_local ! code retour local

intrinsic matmul, present, cos, sin

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB mr_EquaMoy_EquaVrai.f90: derniere modification V6.2 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mr_EquaMoy_EquaVrai.f90,v 1.15 2005/02/28 07:50:10 mslibdev Exp $ '

!************************************************************************

! initialisations
! ===============
code_retour%valeur = pm_OK

! Verifications
! =============

! test sur la coherence des entrees/sorties optionnelles si precisees

if ((present(vit_EquaVrai)) .and. (.not. present(vit_EquaMoy))) then
   code_retour%valeur = pm_err_para_option
   go to 6000
end if

if ((present(vit_EquaMoy)) .and. (.not. present(vit_EquaVrai))) then
   code_retour%valeur = pm_warn_para_option
end if

! test sur le modele choisi

if (model /= pm_lieske_wahr) then
   code_retour%valeur = pm_err_ind_model
   go to 6000
end if

! Dans le cas ou l'on a bien model = pm_lieske_wahr (test effectue ci-dessus)
modele_precession = pm_lieske
modele_nutation   = pm_wahr

! Calculs
! =======

! nutations en longitude (nuta%long) et en obliquite (nuta%obli) de la date

call mr_nuta (modele_nutation, jul1950, nuta, code_retour_local, delta_tai=delta_tai, &
     deriv1_nuta=deriv1_nuta, deriv2_nuta=deriv2_nuta)
if (code_retour_local%valeur /= pm_OK) then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK) go to 6000
end if


! obliquite moyenne de la date

call mr_obli_moy (modele_precession, jul1950, obli_moy, code_retour_local, &
     delta_tai=delta_tai, deriv1_obli=deriv1_obli, deriv2_obli=deriv2_obli)
if (code_retour_local%valeur /= pm_OK) then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK) go to 6000
end if

! ---- Voir le paragraphe 12.7 de [DR1] pour la theorie ----

! determination des parametres de la rotation

def_3rot = pm_1x_2z_3x

angle1 = obli_moy
angle2 = - nuta%long
angle3 = - obli_moy - nuta%obli


! calcul du quaternion associe a la rotation

call mu_3rot_quat(def_3rot, angle1, angle2, angle3, quat, code_retour_local) 
if (code_retour_local%valeur /= pm_OK) then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK) go to 6000
end if


! calcul du vecteur position

call mu_quat_rep (pos_EquaMoy, quat, pos_EquaVrai, code_retour_local)
if (code_retour_local%valeur /= pm_OK) then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK) go to 6000
end if


! calcul du vecteur vitesse si demande

if  ((present(vit_EquaMoy)) .and. (present(vit_EquaVrai))) then

   ! matrice de rotation associee au quaternion de changement de repere
   call mu_quat_rep (vit_EquaMoy, quat, vit_EquaVrai_iner, code_retour_local)
   if (code_retour_local%valeur /= pm_OK) then
      code_retour%valeur = code_retour_local%valeur
      if (code_retour_local%valeur < pm_OK) go to 6000
   end if

   ! test de la presence ou non du flag inertiel
   if (.not.present(inertiel)) then
      flag_iner = .false.
   else
      flag_iner = inertiel
   end if

   if (flag_iner) then !  vecteur vitesse cas inertiel

      vit_EquaVrai(:) = vit_EquaVrai_iner(:)

   else ! vecteur vitesse cas non inertiel (avec vitesse d'entrainement)

      ! calcul du vecteur rotation

      vect_omega(1) = deriv1_obli*cos(nuta%long) - deriv1_obli - deriv1_nuta%obli
      vect_omega(2) = deriv1_obli*sin(nuta%long)*cos(nuta%obli+obli_moy) + deriv1_nuta%long*sin(nuta%obli+obli_moy)
      vect_omega(3) = deriv1_obli*sin(nuta%long)*sin(nuta%obli+obli_moy) - deriv1_nuta%long*cos(nuta%obli+obli_moy)

      ! calcul de la vitesse d'entrainement

      call mu_prod_vect(vect_omega, pos_EquaVrai, vit_entrainement, code_retour_local)
      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur
         if (code_retour_local%valeur < pm_OK) go to 6000
      end if

      ! vecteur vitesse avec vitesse d'entrainement

      vit_EquaVrai(:) = vit_EquaVrai_iner(:) - vit_entrainement(:)

   end if
end if


! calcul du jacobien si demande

if (present(jacob)) then

   ! matrice de rotation associee au quaternion de changement de repere

   call mu_quat_mat (quat, mat, code_retour_local)
   if (code_retour_local%valeur /= pm_OK) then
      code_retour%valeur = code_retour_local%valeur
      if (code_retour_local%valeur < pm_OK) go to 6000
   end if

   jacob(1:3,1:3) = mat(:,:)
   jacob(1:3,4:6) = 0._pm_reel

   if ((present(vit_EquaMoy)) .and. (present(vit_EquaVrai))) then ! partie liee aux vitesses

      jacob(4:6,4:6) = mat(:,:)

      if (flag_iner) then ! cas inertiel

         jacob(4:6,1:3) = 0._pm_reel

      else ! cas non inertiel

         ! matrice associee au vecteur rotation

         mat_vect_rot(1,1) = 0._pm_reel
         mat_vect_rot(1,2) = vect_omega(3)
         mat_vect_rot(1,3) = - vect_omega(2)
         mat_vect_rot(2,1) = - vect_omega(3)
         mat_vect_rot(2,2) = 0._pm_reel
         mat_vect_rot(2,3) = vect_omega(1)
         mat_vect_rot(3,1) = vect_omega(2)
         mat_vect_rot(3,2) = - vect_omega(1)
         mat_vect_rot(3,3) = 0._pm_reel

         ! elements de la jacobienne lies a la non inertialite

         jacob(4:6,1:3) = matmul(mat_vect_rot, mat)

      end if

   else ! mise a zero de la partie inutile
      jacob(4:6,1:3) = 0._pm_reel
      jacob(4:6,4:6) = 0._pm_reel
   end if

end if

6000 continue

code_retour%routine = pm_num_mr_EquaMoy_EquaVrai
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mr_EquaMoy_EquaVrai
