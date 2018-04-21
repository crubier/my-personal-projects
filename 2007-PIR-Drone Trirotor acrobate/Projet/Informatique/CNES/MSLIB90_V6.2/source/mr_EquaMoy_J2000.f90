subroutine mr_EquaMoy_J2000 ( model, jul1950, delta_tai, pos_EquaMoy, pos_J2000, code_retour, &
     inertiel, vit_EquaMoy, vit_J2000, jacob )

! (C) Copyright CNES - MSLIB - 1999-2005

!************************************************************************
!
! But: Passage du repere equatorial moyen a la date t au repere equatorial moyen J2000
! ===
!
! Notes d'utlisation:  [DR1] "Les systemes de reference utilises en astronomie"
! ===================        de M. Chapront-Touze, G. Francou et B. Morando
!                            Bureau Des Longitudes (BDL) novembre 1994
!                            ISSN 1243-4272
!                            ISBN 2-910015-05-X
!                            nomenclature MSLIB M-NT-0-160-CN
!                      Nota: Les epoques J1900 et J2000 sont explicitees en
!                            page 23 table 1.1
!
!                      Les vitesses declarees en sorties optionnelles ne peuvent etre calculees que si les vitesses declarees
!                      en entree optionnelles sont specifiees.
!
! Historique:
! ==========
!   + Version 2.0 (SP 380 ed01 rev00): creation a partir de la routine MRChgRepCMJ2000 de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.0 (FA globale 479 ed01 rev00) : Modif du test en sortie sur les vitesses optionnelles
!   + Version 4.0 (DE globale 480 ed01 rev00) : remplacement des tests de report de code retour en select
!   + Version 4.1 (DE globale 484 ed01 rev00): calcul de la jacobienne 
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!   + Version 6.1 (DE 1): ajout de l'option inertiel (calcul sans vitesse d'entrainement
!   + Version 6.2 (DE globale 1): remplacement des calculs matriciels par des calculs bases sur des quaternions
!
!************************************************************************


! Modules
! =======
use int_mslib_mu_3rot_quat
use int_mslib_mu_quat_rep
use int_mslib_mu_quat_conjug
use int_mslib_mu_prod_vect
use int_mslib_mu_quat_mat

use parametres_internes_mslib
use code_modeles_mslib
use code_transfo_mslib
use math_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mr_EquaMoy_J2000.h'

! Autres declarations
! ===================
integer       :: def_3rot               ! definition de la rotation
real(pm_reel) :: angle1, angle2, angle3 ! angles de la rotation

type(tm_quat) :: quat, quat_conjug ! quaternion de la rotation et de l'inverse

real(pm_reel), dimension (3,3) :: mat, mat_vect_rot ! matrices de changement de repere et rotation

real(pm_reel), dimension(3) :: vect_omega   ! vecteur rotation (cas non inertiel)

real(pm_reel), dimension(3) :: vit_J2000_iner, vit_entrainement ! vecteur vitesse dans le repere equatorial vrai 

type(tm_jour_sec) :: jourTAI ! date en TAI
type(tm_jour_sec) :: jourTE  ! date en TE

real(pm_reel) :: tu, tu2, tu3 ! ecart entre le 01/01/2000 a 12h30 et la date courante (et ecart au carre, au cube)

real(pm_reel) :: dzeta, z, teta ! parametres de la precession
real(pm_reel) :: cos_z, sin_z, cos_t, sin_t ! fonctions trigo des parametres de la precession

logical :: flag_iner ! variable de test de la presence ou non de flag inertiel

type(tm_code_retour) :: code_retour_local ! code retour local


intrinsic matmul, present, cos, sin

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB mr_EquaMoy_J2000.f90: derniere modification V6.2 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mr_EquaMoy_J2000.f90,v 1.18 2005/02/28 15:18:46 mslibatv Exp $ '

!************************************************************************

! initialisations
! ===============
code_retour%valeur = pm_OK

! Verifications
! =============

! test sur la coherence des entrees/sorties optionnelles si precisees

if ((present(vit_J2000)) .and. (.not. present(vit_EquaMoy))) then
   code_retour%valeur = pm_err_para_option
   go to 6000
end if

if ((present(vit_EquaMoy)) .and. (.not. present(vit_J2000))) then
   code_retour%valeur = pm_warn_para_option
end if

! test sur le modele choisi

if (model /= pm_lieske_wahr) then
   code_retour%valeur = pm_err_ind_model
   go to 6000
end if

! Calculs
! =======

! ** Cas du modele de precession de Lieske **

! ---- Voir le paragraphe 7.4 de [DR1] pour la theorie ----

! passage de la date t en date TE (inutile de normaliser la date ainsi obtenue)

! -> passage de T a TAI
jourTAI%jour = jul1950%jour
jourTAI%sec  = jul1950%sec + delta_tai

! -> puis passage de TAI a TE
jourTE%jour = jourTAI%jour
jourTE%sec  = jourTAI%sec + pm_i_delta_TAI_TE


! nombre de milliers d'annees juliennes entre la date t et le 01-01-2000 a 12h
! (echelle TE)

tu  = ((real(jourTE%jour, pm_reel)) - pm_i_date_t2000 + jourTE%sec * pm_i_unsur86400) * pm_i_unsurKanJul
tu2 =  tu*tu
tu3 = tu2*tu


! calcul des parametres de la precession (dzeta, z, teta)

dzeta = (pm_i_Lieske_PBD1*tu + pm_i_Lieske_PBD2*tu2 + pm_i_Lieske_PBD3*tu3) * pm_i_sec2rad
z     = (pm_i_Lieske_PBZ1*tu + pm_i_Lieske_PBZ2*tu2 + pm_i_Lieske_PBZ3*tu3) * pm_i_sec2rad
teta  = (pm_i_Lieske_PBT1*tu + pm_i_Lieske_PBT2*tu2 + pm_i_Lieske_PBT3*tu3) * pm_i_sec2rad


! ---- Voir le paragraphe 12.4 de [DR1] pour la theorie ----

! calcul du quaternion de changement de repere J2000 -> EquaMoy

! determination des parametres de la rotation

def_3rot = pm_1z_2x_3z

angle1 = pm_pi_sur2 - dzeta
angle2 = teta
angle3 = - pm_pi_sur2 - z

! calcul du quaternion associe a la rotation (pour changement de repere J2000 -> EquaMoy)

call mu_3rot_quat(def_3rot, angle1, angle2, angle3, quat, code_retour_local) 
if (code_retour_local%valeur /= pm_OK) then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK) go to 6000
end if

! calcul du quaternion de changement de repere EquaMoy -> J2000 par passage au conjugue

call mu_quat_conjug(quat, quat_conjug, code_retour_local)
if (code_retour_local%valeur /= pm_OK) then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK) go to 6000
end if

! calcul du vecteur position

call mu_quat_rep (pos_EquaMoy, quat_conjug, pos_J2000, code_retour_local)
if (code_retour_local%valeur /= pm_OK) then
   code_retour%valeur = code_retour_local%valeur
   if (code_retour_local%valeur < pm_OK) go to 6000
end if

! calcul du vecteur vitesse si demande

if  ((present(vit_EquaMoy)) .and. (present(vit_J2000))) then

   call mu_quat_rep (vit_EquaMoy, quat_conjug, vit_J2000_iner, code_retour_local)
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

      vit_J2000(:) = vit_J2000_iner(:)

   else !  vecteur vitesse cas non inertiel (avec vitesse d'entrainement)

      ! construction de la matrice de precession

      ! fonctions trigonometriques des parametres de la precession :
      cos_z = cos(z)
      sin_z = sin(z)
      cos_t = cos(teta)
      sin_t = sin(teta)

      ! calcul du vecteur rotation 
      ! (inverse du vecteur de rotation EquaMoy -> J2000)

      vect_omega(1) = - ( pm_i_dzetad*cos_z*sin_t - pm_i_thetad*sin_z)
      vect_omega(2) = - ( pm_i_dzetad*sin_z*sin_t + pm_i_thetad*cos_z)
      vect_omega(3) = - (- pm_i_dzetad*cos_t      - pm_i_zd)

      ! calcul de la vitesse d'entrainement

      call mu_prod_vect(vect_omega, pos_J2000, vit_entrainement, code_retour_local)
      if (code_retour_local%valeur /= pm_OK) then
         code_retour%valeur = code_retour_local%valeur
         if (code_retour_local%valeur < pm_OK) go to 6000
      end if

      ! vecteur vitesse avec vitesse d'entrainement

      vit_J2000(:) = vit_J2000_iner(:) - vit_entrainement(:)

   end if
end if



! calcul du jacobien si demande

if (present(jacob)) then

   ! matrice de rotation associee au quaternion de changement de repere

   call mu_quat_mat (quat_conjug, mat, code_retour_local)
   if (code_retour_local%valeur /= pm_OK) then
      code_retour%valeur = code_retour_local%valeur
      if (code_retour_local%valeur < pm_OK) go to 6000
   end if

   jacob(1:3,1:3) = mat(:,:)
   jacob(1:3,4:6) = 0._pm_reel

   if  ((present(vit_EquaMoy)) .and. (present(vit_J2000))) then ! partie liee aux vitesses

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

code_retour%routine = pm_num_mr_EquaMoy_J2000
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mr_EquaMoy_J2000
