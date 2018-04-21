subroutine mr_TerVrai_EquaVrai (model, jul1950, delta_tu1, delta_tai, pos_TerVrai, pos_EquaVrai, code_retour, &
     inertiel, vit_TerVrai, vit_EquaVrai, jacob)

! (C) Copyright CNES - MSLIB - 2002-2005

!************************************************************************
!
! But: Passage du repere terrestre vrai a la date t au repere equatorial vrai a la meme date t  
! ===
!
! Note d'utilisation:  [DR1] "Les systemes de reference utilises en astronomie"
! ===================        de M. Chapront-Touze, G. Francou et B. Morando
!                            Bureau Des Longitudes (BDL) novembre 1994
!                            ISSN 1243-4272
!                            ISBN 2-910015-05-X
!                            nomenclature MSLIB M-NT-0-160-CN
!                      Nota: Les epoques B1900, J1900 et J2000 sont explicitees en
!                            page 23 table 1.1
!
!                      Les vitesses declarees en sorties optionnelles ne peuvent etre calculees que si les vitesses declarees
!                      en entree optionnelles sont specifiees.
!
! Historique:
! ==========
!   + Version 4.0 (SP 458 ed01 rev00): creation a partir de mr_veis_EquaVrai
!   + Version 4.1 (DE globale 484 ed01 rev00): calcul de la jacobienne 
!   + Version 6.0 (DE 565 ed01 rev00): ajout de l'option inertiel (calcul sans vitesse d'entrainement) 
!   + Version 6.2 (DE globale 1): remplacement des calculs matriciels par des calculs bases sur des quaternions
!
!************************************************************************


! Modules
! =======
use int_mslib_mr_tsid_vrai
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

include 'arg_mr_TerVrai_EquaVrai.h'

! Autres declarations
! ===================
integer       :: def_3rot               ! definition de la rotation
real(pm_reel) :: angle1, angle2, angle3 ! angles de la rotation

type(tm_quat) :: quat ! quaternion de la rotation
real(pm_reel), dimension(3,3) :: mat, mat_vect_rot ! matrices de changement de repere et rotation
real(pm_reel), dimension(3)   :: vect_omega ! vecteur rotation (cas non inertiel)
real(pm_reel), dimension(3)   :: vit_EquaVrai_iner, vit_entrainement ! vecteur vitesse dans le repere equatorial vrai 
!(sans prise en compte de la vitesse d'entrainement) 
! et vecteur vitesse d'entrainement

real(pm_reel) :: tsvrai, tsvraid         ! temps sideral vrai,  derivee du temps sideral vrai

logical :: flag_iner ! variable de test de la presence ou non de flag inertiel

type(tm_code_retour) :: code_retour_local ! code retour local

intrinsic matmul, present

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB mr_TerVrai_EquaVrai.f90: derniere modification V6.2 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id = &
     ' $Id: mr_TerVrai_EquaVrai.f90,v 1.17 2005/02/28 07:50:43 mslibdev Exp $ '

!************************************************************************

! initialisations
! ===============
code_retour%valeur = pm_OK

! Verifications
! ===============

! test sur la coherence des entrees/sorties optionnelles si precisees

if ((present(vit_EquaVrai)) .and. (.not. present(vit_TerVrai))) then
   code_retour%valeur = pm_err_para_option
   go to 6000
end if

if ((present(vit_TerVrai)) .and. (.not. present(vit_EquaVrai))) then
   code_retour%valeur = pm_warn_para_option
end if

! test sur le modele choisi

if (model /= pm_lieske_wahr) then
   code_retour%valeur = pm_err_ind_model
   go to 6000
end if


! Calculs
! =======

! ---- Voir le paragraphe 4.4 de [DR1] pour la theorie ----

! calcul du temps sideral vrai de la date t et de sa derivee

call mr_tsid_vrai ( model, jul1950, delta_tu1, delta_tai, tsvrai, code_retour_local, &
     deriv_tsid_vrai = tsvraid )
if (code_retour_local%valeur /= pm_OK) then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK) go to 6000
end if

! determination des parametres de la rotation

def_3rot = pm_1y_2x_3z

angle1 = 0._pm_reel
angle2 = 0._pm_reel
angle3 =  - tsvrai

! calcul du quaternion associe a la rotation

call mu_3rot_quat(def_3rot, angle1, angle2, angle3, quat, code_retour_local) 
if (code_retour_local%valeur /= pm_OK) then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK) go to 6000
end if

! calcul du vecteur position

call mu_quat_rep (pos_TerVrai, quat, pos_EquaVrai, code_retour_local)
if (code_retour_local%valeur /= pm_OK) then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK) go to 6000
end if

! calcul du vecteur vitesse si demande

if  ((present(vit_TerVrai)) .and. (present(vit_EquaVrai))) then

   call mu_quat_rep (vit_TerVrai, quat, vit_EquaVrai_iner, code_retour_local)
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

   if (flag_iner) then ! vecteur vitesse cas inertiel

      vit_EquaVrai(:) = vit_EquaVrai_iner(:)

   else ! vecteur vitesse cas non inertiel (avec vitesse d'entrainement)

      ! calcul du vecteur rotation

      vect_omega(1) = 0._pm_reel
      vect_omega(2) = 0._pm_reel
      vect_omega(3) = - tsvraid

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

   if  ((present(vit_TerVrai)) .and. (present(vit_EquaVrai))) then ! partie liee aux vitesses

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

code_retour%routine = pm_num_mr_TerVrai_EquaVrai
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mr_TerVrai_EquaVrai
